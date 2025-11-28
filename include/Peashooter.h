#pragma once
#include "Plant.h"

class Peashooter : public Plant {
private:
    float fire_cooldown = 2.0f;    // Time between shots (seconds)
    float current_cooldown = 0.0f; // Remaining cooldown time

public:
    Peashooter(const std::string& objType, PlantType type, int health, int cost);
    void draw() const override;
    void Update(float dt) override;

    void shoot();
};
