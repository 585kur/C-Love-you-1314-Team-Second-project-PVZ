#pragma once
#include "Plant.h"

class Sunflower : public Plant {
private:
    int sun_production_rate;   // 阳光生产间隔（帧）
    int current_sun_cooldown;  // 当前冷却
    int width = 50;            // 向日葵自身宽度（固定尺寸）
    int height = 50;           // 向日葵自身高度（固定尺寸）

public:
    Sunflower(const std::string& objType, PlantType type, int health, int cost);
    void draw() const override;
    void update() override;
    int produce_sunshine() override;
};