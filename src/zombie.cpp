#include "Zombie.h"
#include "Plant.h"
#include <iostream>

// 构造函数
Zombie::Zombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval)
    : Object(objType), speed(speed), hp(hp),
    attackDamage(attackDamage), attackInterval(attackInterval)
{
    // 添加矩形碰撞体（60×80）
    AddComponent<BoxCollider>(60.0f, 80.0f);
}

void Zombie::Update(float dt)
{
    if (!IsAlive()) return;

    // ========== 僵尸正在攻击 ==========
    if (isAttacking)
    {
        attackTimer += dt;

        // 如果目标植物不存在或已死亡 → 停止攻击，恢复移动
        if (!targetPlant || targetPlant->is_dead())
        {
            stopAttack();
            targetPlant = nullptr;
            return;
        }

        // 攻击冷却计时
        if (attackTimer >= attackInterval)
        {
            attackTimer = 0;
            onAttackPlant();  // 扣植物 HP

            // 植物可能在攻击后死亡 → 下一帧自动解除攻击
            if (targetPlant && targetPlant->is_dead())
            {
                stopAttack();
                targetPlant = nullptr;
            }
        }

        return; // 攻击模式下不移动
    }

    // ========== 移动 ==========
    if (auto* trans = GetTransform())
    {
        Vector2D pos = trans->GetPosition();
        pos.x -= speed * dt;  // 向左移动
        trans->SetPosition(pos.x, pos.y);

        // 到最左边：游戏失败
        if (pos.x < -60)  // 僵尸宽度 60
        {
            Destroy();
            onReachEnd();
            return;
        }
    }

    // ========== 检测植物碰撞，触发攻击 ==========
    if (auto* collider = GetComponent<BoxCollider>())
    {
        auto collided = collider->GetCollisionsByType("Plant");
        Plant* firstPlant = nullptr;

        // 安全筛选（防止 null 或类型不符）
        for (auto* obj : collided)
        {
            if (auto* p = dynamic_cast<Plant*>(obj))
            {
                firstPlant = p;
                break;
            }
        }

        // 找到植物 → 开始攻击
        if (firstPlant && !isAttacking)
        {
            targetPlant = firstPlant;
            startAttack();  // 设置攻击状态
        }
    }
}

void Zombie::onHit(int damage)
{
    if (!IsAlive()) return;

    hp -= damage;
    if (hp <= 0)
    {
        hp = 0;
        die();  // 死亡处理
    }
}

void Zombie::onAttackPlant()
{
    if (!targetPlant) return;

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
    attackTimer = 0;
}

void Zombie::die()
{
    // 死亡时确保彻底停止攻击
    isAttacking = false;
    targetPlant = nullptr;

    Destroy();  // Object 方法：标记为死亡
    std::cout << "A zombie has been defeated!" << '\n';
}

void Zombie::onReachEnd()
{
    std::cout << "Zombie reached the end! Game Over!" << '\n';
}

void Zombie::setTargetPlant(Plant* plant)
{
    targetPlant = plant;
}

Plant* Zombie::getTargetPlant() const
{
    return targetPlant;
}
