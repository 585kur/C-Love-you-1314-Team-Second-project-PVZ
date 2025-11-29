#include "ObjectManager.h"
#include "Object.h"

// 获取所有存活对象
std::vector<Object*> ObjectManager::GetAllObjects() {
    std::vector<Object*> result;
    for (auto& obj : allObjects) {
        if (obj->IsAlive()) {
            result.push_back(obj.get());
        }
    }
    return result;
}

// 按类型获取存活对象
std::vector<Object*> ObjectManager::GetObjectsByType(const std::string& type) {
    std::vector<Object*> result;
    auto it = typeGroups.find(type);
    if (it != typeGroups.end()) {
        for (Object* obj : it->second) {
            if (obj && obj->IsAlive()) {
                result.push_back(obj);
            }
        }
    }
    return result;
}

// 标记对象销毁
void ObjectManager::DestroyObject(Object* obj) {
    if (!obj || !obj->IsAlive()) return;
    obj->Destroy();
}

// 清理已销毁对象
void ObjectManager::CleanupDestroyed() {
    for (auto it = allObjects.begin(); it != allObjects.end();) {
        if (!(*it)->IsAlive()) {
            const std::string& type = (*it)->GetType();
            auto& group = typeGroups[type];
            group.erase(std::remove(group.begin(), group.end(), it->get()), group.end());

            if (group.empty()) {
                typeGroups.erase(type);
            }
            it = allObjects.erase(it);
        }
        else {
            ++it;
        }
    }
}

// 更新所有存活对象
void ObjectManager::UpdateAll(float dt) {
    for (auto& obj : allObjects) {
        if (obj->IsAlive()) {
            obj->Update(dt);
        }
    }
    CleanupDestroyed();
}