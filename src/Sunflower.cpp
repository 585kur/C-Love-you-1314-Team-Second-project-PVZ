#include "Sunflower.h"
#include "Transform.h"
#include <graphics.h>
#include <iostream>

Sunflower::Sunflower(int x, int y)
    : Plant("SUNFLOWER", PlantType::SUNFLOWER, 75, 50),
    sun_production_rate(240),
    current_sun_cooldown(0)
{
    // 通过Transform设置位置（唯一位置来源，无冲突）
    Transform* trans = GetTransform();
    if (trans) {
        trans->SetPosition(static_cast<float>(x), static_cast<float>(y));
    }
}

// 绘制向日葵（仅用Transform位置 + 自身尺寸）
void Sunflower::draw() const {
    if (is_dead()) return;

    // 获取Transform组件的位置（唯一位置来源）
    const Transform* trans = GetTransform();
    if (!trans) return;
    float posX = trans->GetPosition().x;
    float posY = trans->GetPosition().y;

    // 绘制花茎（用自身height）
    setfillcolor(GREEN);
    solidrectangle(
        static_cast<int>(posX + 22), static_cast<int>(posY),
        static_cast<int>(posX + 28), static_cast<int>(posY + height - 20)
    );

    // 绘制花朵（黄色圆形）
    setfillcolor(YELLOW);
    solidcircle(
        static_cast<int>(posX + 25), static_cast<int>(posY + 15),
        20
    );

    // 绘制生命值条（用自身width）
    setfillcolor(RED);
    solidrectangle(
        static_cast<int>(posX), static_cast<int>(posY - 10),
        static_cast<int>(posX + width), static_cast<int>(posY - 6)
    );
    float health_ratio = static_cast<float>(get_health()) / get_max_health();
    setfillcolor(GREEN);
    solidrectangle(
        static_cast<int>(posX), static_cast<int>(posY - 10),
        static_cast<int>(posX + width * health_ratio), static_cast<int>(posY - 6)
    );
}

void Sunflower::update() {
    if (is_dead()) return;
    if (current_sun_cooldown < sun_production_rate) {
        current_sun_cooldown++;
    }
}

int Sunflower::produce_sunshine() {
    if (current_sun_cooldown >= sun_production_rate) {
        current_sun_cooldown = 0;

        const Transform* trans = GetTransform();
        float posX = trans ? trans->GetPosition().x : 0;
        float posY = trans ? trans->GetPosition().y : 0;
        std::cout << "Sunflower at (" << posX << "," << posY << ") produced a sun!" << '\n';

        return 25;
    }
    return 0;
}