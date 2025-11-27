#include "Peashooter.h"
#include "Transform.h"
#include <graphics.h>
#include <iostream>

// 构造函数：接收objType、type、health、cost，调用Plant基类构造
Peashooter::Peashooter(const std::string& objType, PlantType type, int health, int cost)
    : Plant(objType, type, health, cost) { // 直接传递参数给Plant基类
    // 位置由LevelScene通过SetPosition设置，此处无需处理
}

// 绘制豌豆射手（保持不变）
void Peashooter::draw() const {
    if (is_dead()) return;

    const Transform* trans = GetTransform();
    if (!trans) return;
    float x = trans->GetPosition().x;
    float y = trans->GetPosition().y;
    int width = 50, height = 50;

void Peashooter::Update(float dt) {
    if (current_cooldown > 0.0f) {
        current_cooldown -= dt;
    if (current_cooldown <= 0.0f) {

    // 绘制炮管
    setfillcolor(RGB(0, 100, 0));
    solidrectangle(static_cast<int>(x + width - 5), static_cast<int>(y + 15),
        static_cast<int>(x + width + 10), static_cast<int>(y + 35));

    // 绘制血条
    setfillcolor(RED);
    solidrectangle(static_cast<int>(x), static_cast<int>(y - 10),
        static_cast<int>(x + width), static_cast<int>(y - 6));
    float health_ratio = static_cast<float>(get_health()) / get_max_health();
    setfillcolor(GREEN);
    solidrectangle(static_cast<int>(x), static_cast<int>(y - 10),
        static_cast<int>(x + width * health_ratio), static_cast<int>(y - 6));
}

// 更新逻辑（保持不变）
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

void Peashooter::shoot() {
    const Transform* trans = GetTransform();
    if (!trans) return;
    std::cout << "Peashooter at (" << trans->GetPosition().x << ","
        << trans->GetPosition().y << ") shoots pea!" << std::endl;
}