#pragma once
#include "Plant.h"

class Sunflower : public Plant {
private:
    float sun_production_rate;   // Seconds needed to produce sunshine
    float current_sun_cooldown;  // Accumulated production timer
    int width = 50;              // Fixed display width
    int height = 50;             // Fixed display height

public:
    Sunflower(int x, int y);
    void draw() const override;
    void Update(float dt) override;
    int produce_sunshine() override;
};
