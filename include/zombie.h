#pragma once
#include "Object.h"   // 继承Object而非Entity
#include "Collider.h" // 添加碰撞组件
#include <memory>

// 前向声明
class Plant;

class Zombie : public Object {
protected:
    float speed;              // 移动速度（像素/秒）
    int hp;                   // 血量
    int attackDamage;         // 每次攻击伤害
    float attackInterval;     // 攻击间隔（秒）
    float attackTimer = 0;    // 攻击计时器

    bool isAttacking = false; // 是否正在攻击
    Plant* targetPlant = nullptr; // 当前攻击目标

public:
    // 构造函数：通过Object的类型标识+组件管理位置尺寸
    virtual void draw() const = 0;
    Zombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval);

    virtual ~Zombie() = default;

    // 每帧逻辑更新（重写Object的Update）
    void Update(float dt) override;

    // 被子弹击中
    virtual void onHit(int damage);

    // 攻击植物
    virtual void onAttackPlant();

    // 死亡处理
    virtual void die();

    // 到达左边尽头（玩家失败）
    virtual void onReachEnd();

    // 战斗控制
    void startAttack();
    void stopAttack();

    // 目标植物
    void setTargetPlant(Plant* plant);
    Plant* getTargetPlant() const;

    // 快捷设置位置（通过Transform组件）
    void SetPosition(float x, float y) {
        if (auto* trans = GetTransform()) {
            trans->SetPosition(x, y);
        }
    }
};