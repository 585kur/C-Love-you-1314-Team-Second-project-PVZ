#pragma once
#include "Zombie.h"
#include <graphics.h>

// NormalZombie 类继承自 Zombie
class NormalZombie : public Zombie
{
private:
    IMAGE normalZombieImage;  // 用于绘制正常僵尸的图像

public:
    NormalZombie(int x, int y);
    virtual ~NormalZombie();

    // 重写绘制函数
    void draw() override;
};
