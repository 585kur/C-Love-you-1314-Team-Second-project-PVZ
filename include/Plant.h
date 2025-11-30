#pragma once
#include "Object.h"  
#include "Collider.h" 
#include<graphics.h>

// 植物类型枚举
enum class PlantType {
    PEASHOOTER,
    SUNFLOWER,
    CHERRY_BOMB,
    WALLNUT
};

// 植物基类：继承Object，用组件实现功能
class Plant : public Object {
protected:
    PlantType plant_type;
    int health;
    int max_health;
    int cost;

public:
    virtual void update() = 0;
    Plant(const std::string& objType, PlantType type, int health, int cost);

    // 纯虚绘制函数（子类实现）
    virtual void draw() const = 0;

    // 植物受伤逻辑
    virtual void take_damage(int amount);

    // 生产阳光（子类重写）
    virtual int produce_sunshine();

    // Getter
    PlantType get_plant_type() const { return plant_type; }
    int get_health() const { return health; }
    int get_max_health() const { return max_health; }
    int get_cost() const { return cost; }

    // 位置/尺寸通过Transform组件操作
    void SetPosition(float x, float y) {
        // 调用非const版本的GetTransform，返回Transform*
        Transform* trans = GetTransform();
        if (trans) trans->SetPosition(x, y);
    }

    // 补充受攻击方法
    void onAttacked(int damage) {
        take_damage(damage);
    }

    // 补充死亡判断方法
    bool is_dead() const {
        return health <= 0;
    }

  

};