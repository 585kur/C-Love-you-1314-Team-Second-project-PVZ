#include "normalzombie.h"
#include "Transform.h" // 用于获取位置

// 全局图片初始化（仅加载一次）
IMAGE g_normalZombieImage;

// 构造函数：调用Zombie的Object架构构造函数
NormalZombie::NormalZombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval)
    : Zombie(objType, speed, hp, attackDamage, attackInterval) {
    // 初始化僵尸位置（通过Transform组件）
    GetTransform()->SetPosition(800.0f, 200.0f); // 默认生成在屏幕右侧
}

// 绘制僵尸：通过Transform获取位置
void NormalZombie::draw() const {
    if (!IsAlive()) return; // 死亡不绘制

    // 获取Transform组件的位置
    Transform* trans = const_cast<NormalZombie*>(this)->GetTransform();
    if (!trans) return;

    Vector2D pos = trans->GetPosition();
    // 绘制全局图片资源
    putimage(static_cast<int>(pos.x), static_cast<int>(pos.y), &g_normalZombieImage);
}