#include "Plant.h"
#include <iostream>

Plant::Plant(PlantType type, int x, int y, int width, int height, int health, int cost)
    : Entity(x, y, width, height), 
    plant_type(type),
    health(health),
    max_health(health),
    cost(cost)
{
}

void Plant::take_damage(int amount) {
    if (is_dead()) return;

    health -= amount;
    if (health <= 0) {
        health = 0;
        kill(); 
        std::cout << "A plant has been destroyed!" << '\n';
    }
}


int Plant::produce_sunshine() {
    return 0;
}

PlantType Plant::get_plant_type() const { return plant_type; }
int Plant::get_health() const { return health; }
int Plant::get_max_health() const { return max_health; }
int Plant::get_cost() const { return cost; }