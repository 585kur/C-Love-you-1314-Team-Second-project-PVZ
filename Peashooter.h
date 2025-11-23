#pragma once
#include "Plant.h"

class Peashooter : public Plant {
private:
    int damage;             // 豌豆伤害
    int fire_cooldown;      // 发射冷却时间
    int current_cooldown;   // 当前冷却时间

public:
    Peashooter(int x, int y);

    // 重写绘制方法
    void draw() const override;

    // 重写更新逻辑
    void update();

    // 发射豌豆
    void shoot();
};