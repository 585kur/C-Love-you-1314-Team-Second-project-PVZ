#include "Sunflower.h"
#include <graphics.h>
#include <iostream>

Sunflower::Sunflower(int x, int y)
    : Plant(PlantType::SUNFLOWER, x, y, 50, 50, 75, 50), // 向日葵：50阳光
    sun_production_rate(240), // 240帧生产一个阳光
    current_sun_cooldown(0)
{
}

// 绘制向日葵
void Sunflower::draw() const {
    if (is_dead()) return;

    // 绘制花茎 (绿色矩形)
    setfillcolor(GREEN);
    solidrectangle(x + 22, y, x + 28, y + height - 20);

    // 绘制花朵 (黄色圆形)
    setfillcolor(YELLOW);
    solidcircle(x + 25, y + 15, 20);

    // 绘制生命值条
    setfillcolor(RED);
    solidrectangle(x, y - 10, x + width, y - 6);
    float health_ratio = static_cast<float>(get_health()) / get_max_health();
    setfillcolor(GREEN);
    solidrectangle(x, y - 10, x + static_cast<int>(width * health_ratio), y - 6);
}

// 更新向日葵状态
void Sunflower::update() {
    if (is_dead()) return;

    if (current_sun_cooldown < sun_production_rate) {
        current_sun_cooldown++;
    }
}

// 生产阳光
int Sunflower::produce_sunshine() {
    if (current_sun_cooldown >= sun_production_rate) {
        current_sun_cooldown = 0;
        std::cout << "Sunflower at (" << x << "," << y << ") produced a sun!" << '\n';
        return 25; // 生产25阳光
    }
    return 0;
}