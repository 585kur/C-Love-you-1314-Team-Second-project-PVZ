// Peashooter.cpp
#include "Peashooter.h"
#include <graphics.h>
#include <iostream>

Peashooter::Peashooter(int x, int y)
    : Plant(PlantType::PEASHOOTER, x, y, 50, 50, 100, 100), // 豌豆射手：100阳光
    damage(25),
    fire_cooldown(120), // 120帧发射一次
    current_cooldown(0)
{
}

// 绘制豌豆射手
void Peashooter::draw() const {
    if (is_dead()) return;

    // 绘制豌豆射手主体 (绿色矩形)
    setfillcolor(GREEN);
    solidrectangle(x, y, x + width - 1, y + height - 1);

    // 绘制豌豆射手的“炮管” (深绿色矩形)
    setfillcolor(DARKGREEN);
    solidrectangle(x + width - 5, y + 15, x + width + 10, y + 35);

    // 绘制生命值条
    // 背景 (红色)
    setfillcolor(RED);
    solidrectangle(x, y - 10, x + width, y - 6);
    // 当前生命值 (绿色)
    float health_ratio = static_cast<float>(get_health()) / get_max_health();
    setfillcolor(GREEN);
    solidrectangle(x, y - 10, x + static_cast<int>(width * health_ratio), y - 6);
}

// 更新豌豆射手状态
void Peashooter::update() {
    if (is_dead()) return;

    if (current_cooldown > 0) {
        current_cooldown--;
    }
    else {
        shoot();
        current_cooldown = fire_cooldown;
    }
}

// 发射豌豆
void Peashooter::shoot() {
    std::cout << "Peashooter at (" << x << "," << y << ") shoots a pea! Damage: " << damage << std::endl;
    // 在这里创建一个 Bullet 实体并添加到游戏世界中
}