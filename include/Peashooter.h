#pragma once
#include "Plant.h"

class Peashooter : public Plant {
private:
    int fire_cooldown = 120;  // …‰ª˜¿‰»¥£®÷°£©
    int current_cooldown = 0; // µ±«∞¿‰»¥

public:
    
    Peashooter(const std::string& objType, PlantType type, int health, int cost);
    void draw() const override;
    void update() override;


    void shoot();
};