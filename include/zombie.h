#pragma once
#include "Entity.h"

// 前向声明（避免循环包含）
class Plant;

class Zombie : public Entity
{
protected:
    float speed;              // 移动速度（像素/秒）
    int hp;                   // 血量
    int attackDamage;         // 每次攻击伤害
    float attackInterval;     // 攻击间隔（秒）
    float attackTimer = 0;    // 攻击计时器

    bool isAttacking = false; // 是否正在攻击
    Plant* targetPlant = nullptr; // 当前攻击目标

public:
    Zombie(int x, int y, int width, int height,
           float speed, int hp, int attackDamage, float attackInterval);

    virtual ~Zombie() {}

    // 每帧逻辑更新
    virtual void update(float dt);

    // 被子弹击中
    virtual void onHit(int damage);

    // 攻击植物（从 update 中触发）
    virtual void onAttackPlant();

    // 死亡处理
    virtual void die();

    // 到达左边尽头（玩家失败）—— 可留空
    virtual void onReachEnd();

    // 战斗控制
    void startAttack();
    void stopAttack();

    // 目标植物
    void setTargetPlant(Plant* plant);
    Plant* getTargetPlant() const;

};
