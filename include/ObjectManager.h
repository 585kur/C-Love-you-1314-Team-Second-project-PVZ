#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include <algorithm>
#include "Object.h" 

class ObjectManager {
private:
    std::vector<std::unique_ptr<Object>> allObjects;
    std::unordered_map<std::string, std::vector<Object*>> typeGroups;

public:
    // 模板方法：创建对象（移除多余的type参数传递给T的构造）
    template<typename T, typename... Args>
    T* CreateObject(const std::string& type, Args&&... args) {
        static_assert(std::is_base_of<Object, T>::value, "T必须继承Object类");
        // 直接传递T的构造参数（如Peashooter的x/y），不再传type
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawObj = obj.get();
        allObjects.push_back(std::move(obj));
        typeGroups[type].push_back(rawObj); // type仅用于分组
        return rawObj;
    }

    // 非模板方法声明
    std::vector<Object*> GetAllObjects();
    std::vector<Object*> GetObjectsByType(const std::string& type);
    void DestroyObject(Object* obj);
    void CleanupDestroyed();
    void UpdateAll(float dt);
};