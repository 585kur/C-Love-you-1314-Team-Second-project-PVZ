#pragma once
#include "Entity.h"

// 植物类型枚举
enum class PlantType {
    PEASHOOTER,
    SUNFLOWER,
    CHERRY_BOMB,
    WALLNUT
};

// 植物基类
class Plant : public Entity {
protected:
    PlantType plant_type;   // 植物类型
    int health;             // 生命值
    int max_health;         // 最大生命值
    int cost;               // 阳光成本

public:
    // 构造函数
    Plant(PlantType type, int x, int y, int width, int height, int health, int cost);

    // 析构函数
    virtual ~Plant() = default;

    // 纯虚函数，绘制植物，必须在子类中实现
    virtual void draw() const override = 0;

    // 植物受到伤害
    virtual void take_damage(int amount);

    // 生产阳光 (对于向日葵等植物)
    virtual int produce_sunshine();

    // --- Getter 和 Setter ---
    PlantType get_plant_type() const;
    int get_health() const;
    int get_max_health() const;
    int get_cost() const;
};