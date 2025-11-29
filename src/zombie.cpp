#include "Zombie.h"
#include "Plant.h"
#include <iostream>

// 构造函数：初始化Object+自身属性，添加碰撞体
Zombie::Zombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval)
    : Object(objType), speed(speed), hp(hp), attackDamage(attackDamage), attackInterval(attackInterval) {
    // 添加矩形碰撞体（僵尸尺寸60x80）
    AddComponent<BoxCollider>(60.0f, 80.0f);
}

void Zombie::Update(float dt) {
    if (!IsAlive()) return; // 用Object的IsAlive()替代alive成员

    // ========= 攻击模式 =========
    if (isAttacking) {
        attackTimer += dt;
        if (attackTimer >= attackInterval) {
            attackTimer = 0;
            onAttackPlant();
        }
        return; // 攻击时不移动
    }

    // ========= 移动（通过Transform组件）=========
    if (auto* trans = GetTransform()) {
        Vector2D pos = trans->GetPosition();
        pos.x -= speed * dt; // 向左移动
        trans->SetPosition(pos.x, pos.y);

        // ========= 到最左边：失败判定 =========
        if (pos.x < -60) { // 僵尸宽度60，完全出左边界
            Destroy(); // 用Object的Destroy()标记死亡
            onReachEnd();
        }
    }

    // ========= 碰撞检测：寻找前方植物 =========
    if (auto* collider = GetComponent<BoxCollider>()) {
        // 获取碰撞的植物（通过Collider的类型筛选）
        auto collidedPlants = collider->GetCollisionsByType("Plant");
        if (!collidedPlants.empty() && !targetPlant) {
            targetPlant = dynamic_cast<Plant*>(collidedPlants[0]);
            if (targetPlant) startAttack();
        }
    }
}

void Zombie::onHit(int damage) {
    if (!IsAlive()) return;

    hp -= damage;
    if (hp <= 0) {
        hp = 0;
        die();
    }
}

void Zombie::onAttackPlant() {
    if (!targetPlant || targetPlant->is_dead()) {
        stopAttack();
        targetPlant = nullptr;
        return;
    }

    targetPlant->onAttacked(attackDamage); // 调用Plant的受攻击方法
}

void Zombie::startAttack() {
    isAttacking = true;
    attackTimer = 0;
}

void Zombie::stopAttack() {
    isAttacking = false;
}

void Zombie::die() {
    Destroy(); // 标记为死亡
    std::cout << "A zombie has been defeated!" << '\n';
}

void Zombie::onReachEnd() {
    std::cout << "Zombie reached the end! Game Over!" << '\n';
}

void Zombie::setTargetPlant(Plant* plant) {
    targetPlant = plant;
}

Plant* Zombie::getTargetPlant() const {
    return targetPlant;
}