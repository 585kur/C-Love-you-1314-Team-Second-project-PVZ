#pragma once
#include "Plant.h"

class Sunflower : public Plant {
private:
    int sun_production_rate; // 阳光生产速率 (帧)
    int current_sun_cooldown;// 当前阳光冷却

public:
    Sunflower(int x, int y);

    // 重写绘制方法
    void draw() const override;

    // 重写更新逻辑
    void update();

    // 重写生产阳光方法
    int produce_sunshine() override;
};
