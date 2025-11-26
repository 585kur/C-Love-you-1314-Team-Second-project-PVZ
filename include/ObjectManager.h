#pragma once
#include <vector>
#include <memory>
#include <string>
#include <unordered_map>
#include "Object.h"

class ObjectManager {
private:
    // 存储所有对象（用unique_ptr管理生命周期）
    std::vector<std::unique_ptr<Object>> allObjects;
    // 按类型分组存储（如"Plant"/"Zombie"/"Bullet"），方便快速查询
    std::unordered_map<std::string, std::vector<Object*>> typeGroups;

public:
    // ========== 对象创建 ==========
    template<typename T, typename... Args>
    T* CreateObject(const std::string& type, Args&&... args) {
        static_assert(std::is_base_of<Object, T>::value, "T必须继承Object类");
        // 创建对象并添加到容器
        auto obj = std::make_unique<T>(std::forward<Args>(args)...);
        T* rawObj = obj.get(); // 获取裸指针供外部使用
        allObjects.push_back(std::move(obj));
        // 按类型分组
        typeGroups[type].push_back(rawObj);
        return rawObj;
    }

    // ========== 对象查询 ==========
    // 获取所有对象
    std::vector<Object*> GetAllObjects() {
        std::vector<Object*> result;
        for (auto& obj : allObjects) {
            result.push_back(obj.get());
        }
        return result;
    }

    // 按类型获取对象
    std::vector<Object*> GetObjectsByType(const std::string& type) {
        if (typeGroups.find(type) != typeGroups.end()) {
            return typeGroups[type];
        }
        return {};
    }

    // ========== 对象销毁 ==========
    void DestroyObject(Object* obj) {
        if (!obj) return;
        // 标记对象为销毁状态
        obj->Destroy();
        // 后续在Update中清理（避免遍历中修改容器）
    }

    // 清理已标记为销毁的对象
    void CleanupDestroyed() {
        for (auto it = allObjects.begin(); it != allObjects.end();) {
            if (!(*it)->IsAlive()) {
                // 从类型分组中移除
                const std::string& type = (*it)->GetType();
                auto& group = typeGroups[type];
                group.erase(std::remove(group.begin(), group.end(), it->get()), group.end());
                // 从总容器中移除
                it = allObjects.erase(it);
            }
            else {
                ++it;
            }
        }
    }

    // ========== 帧更新 ==========
    void UpdateAll(float dt) {
        // 先更新所有存活对象
        for (auto& obj : allObjects) {
            if (obj->IsAlive()) {
                // 假设Object有Update方法（若没有可添加）
                // obj->Update(dt);
            }
        }
        // 清理已销毁的对象
        CleanupDestroyed();
    }
};