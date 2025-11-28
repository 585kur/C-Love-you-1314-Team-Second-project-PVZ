#include "Plant.h"
#include <iostream>

// 构造函数无需再初始化Entity，直接初始化Object和自身属性
Plant::Plant(const std::string& objType, PlantType type, int health, int cost)
    : Object(objType), plant_type(type), health(health), max_health(health), cost(cost) {
    AddComponent<BoxCollider>(50.0f, 50.0f); // 补全碰撞体添加
}

void Plant::take_damage(int amount) {
    if (health <= 0) return; // 替代原is_dead()

    health -= amount;
    if (health <= 0) {
        health = 0;
        Destroy(); // 调用Object的Destroy()标记死亡
        std::cout << "A plant has been destroyed!" << '\n';
    }
}

int Plant::produce_sunshine() {
    return 0;
}