// Peashooter.h
#pragma once
#include "Plant.h"

class Peashooter : public Plant {
private:
    int damage = 25;             // 豌豆伤害
    int fire_cooldown = 120;     // 发射冷却时间
    int current_cooldown = 0;    // 当前冷却时间

public:
    // 匹配Plant的构造函数参数 + 新增位置参数（用于Transform）
    Peashooter(const std::string& objType, PlantType type, int health, int cost)
        : Plant(objType, type, health, cost) {
    } // 调用父类构造

// 实现Plant的纯虚函数
    void draw() const override;

    // 补充更新逻辑
    void update() override;

    // 发射豌豆
    void shoot();
};