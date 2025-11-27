#pragma once
#include "Object.h"
#include "Collider.h"

// Supported plant types
enum class PlantType {
    PEASHOOTER,
    SUNFLOWER,
    CHERRY_BOMB,
    WALLNUT
};

// Base class for all plants
class Plant : public Object {
protected:
    PlantType plant_type;
    int health;
    int max_health;
    int cost;

public:
    Plant(const std::string& objType, PlantType type, int health, int cost);

    void Update(float dt) override = 0;
    virtual void draw() const = 0;
    virtual void take_damage(int amount);
    virtual int produce_sunshine();

    PlantType get_plant_type() const { return plant_type; }
    int get_health() const { return health; }
    int get_max_health() const { return max_health; }
    int get_cost() const { return cost; }

    void SetPosition(float x, float y) {
        if (auto* trans = GetTransform()) {
            trans->SetPosition(x, y);
        }
    }

    void onAttacked(int damage) { take_damage(damage); }
    bool is_dead() const { return health <= 0; }
};
