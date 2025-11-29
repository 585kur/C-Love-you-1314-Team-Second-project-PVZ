#pragma once
#include "Zombie.h"
#include <graphics.h>

// 全局图片资源（避免每个僵尸对象重复加载）
extern IMAGE g_normalZombieImage;

class NormalZombie : public Zombie {
public:
    // 构造函数：适配Zombie的Object架构参数
    NormalZombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval);

    // 析构函数（无需额外清理，图片为全局资源）
    ~NormalZombie() override = default;

    // 重写绘制虚函数
    void draw() const override;
};