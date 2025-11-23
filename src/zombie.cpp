#include "Zombie.h"
#include "Plant.h"  // 需要 Plant::onAttacked()

Zombie::Zombie(int x, int y, int width, int height,
               float speed, int hp, int attackDamage, float attackInterval)
    : Entity(x, y, width, height, true),
      speed(speed), hp(hp),
      attackDamage(attackDamage), attackInterval(attackInterval)
{
}

void Zombie::update(float dt)
{
    if (!alive) return;

    // ========= 攻击模式 =========
    if (isAttacking)
    {
        attackTimer += dt;
        if (attackTimer >= attackInterval)
        {
            attackTimer = 0;
            onAttackPlant(); // 直接攻击植物
        }
        return; // 攻击时不移动
    }

    // ========= 移动 =========
    x -= speed * dt;

    // ========= 到最左边：失败判定 =========
    if (x < -50)    //先假设僵尸矩形宽度为50
    {
        alive = false;
        onReachEnd();
    }
}

void Zombie::onHit(int damage)
{
    if (!alive) return;

    hp -= damage;
    if (hp <= 0)
    {
        hp = 0;
        die();
    }
}

void Zombie::onAttackPlant()
{
    if (!targetPlant) return;

    // 如果植物死了，停止攻击
    if (targetPlant->is_dead())
    {
        stopAttack();
        targetPlant = nullptr;
        return;
    }

    // 直接攻击植物（不需要 LevelScene）
    targetPlant->onAttacked(attackDamage);
}

void Zombie::startAttack()
{
    isAttacking = true;
    attackTimer = 0;
}

void Zombie::stopAttack()
{
    isAttacking = false;
}

void Zombie::die()
{
    alive = false;
    // 可扩展死亡动画、音效
}

void Zombie::onReachEnd()
{
    // 可设置一个标志让游戏结束
}

void Zombie::setTargetPlant(Plant* plant)
{
    targetPlant = plant;
}

Plant* Zombie::getTargetPlant() const
{
    return targetPlant;
}
