#pragma once
#include <unordered_map>
#include <typeindex>
#include<string>
#include "Component.h"
#include "Transform.h"

class Object {
private:
    // 【删除冗余成员】：Transform组件已管理位置/尺寸，无需重复定义x/y/height/width
    std::unordered_map<std::type_index, Component*> components;
    bool alive = true;
    std::string type;

public:
    Object(const std::string& type) : type(type) {
        AddComponent<Transform>(); // 依赖Transform管理位置/尺寸
    }

    ~Object() {
        for (auto& pair : components) {
            delete pair.second;
        }
    }
    virtual void Update(float dt) {};

    template<typename T>
    T* GetComponent() {
        auto it = components.find(typeid(T));
        return it != components.end() ? static_cast<T*>(it->second) : nullptr;
    }

    template<typename T>
    const T* GetComponent() const {
        auto it = components.find(typeid(T));
        return it != components.end() ? static_cast<const T*>(it->second) : nullptr;
    }

    Transform* GetTransform() {
        return GetComponent<Transform>();
    }

    const Transform* GetTransform() const {
        return GetComponent<Transform>();
    }

    template<typename T, typename... Args>
    T* AddComponent(Args&&... args) {
        static_assert(std::is_base_of<Component, T>::value, "T必须继承Component");
        T* comp = new T(std::forward<Args>(args)...);
        components[typeid(T)] = comp;
        comp->SetOwner(this);
        return comp;
    }

    bool IsAlive() const { return alive; }
    void Destroy() { alive = false; }
    const std::string& GetType() const { return type; }
};