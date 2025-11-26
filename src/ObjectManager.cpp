#pragma once 
#include "Object.h"
#include <vector>
#include <string>
#include <unordered_map>
#include <memory>

class ObjectManager {
private:
    // 成员变量声明（根据你的逻辑补充，比如你用到的allObjects、typeGroups）
    std::vector<std::unique_ptr<Object>> allObjects;
    std::unordered_map<std::string, std::vector<Object*>> typeGroups;

public:
    // 仅保留函数声明（删除头文件中这些函数的{...}实现体）
    void CleanupDestroyed();

    void UpdateAll(float dt);

    std::vector<Object*> GetAllObjects();

    std::vector<Object*> GetObjectsByType(const std::string& type);

    void DestroyObject(Object* obj);
};