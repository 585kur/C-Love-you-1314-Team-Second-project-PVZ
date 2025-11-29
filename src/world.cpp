#include "World.h"
#include "Collider.h" // 在这里包含Collider的完整定义（可访问其成员）
#include <algorithm>  // 用于std::remove

// 实现AddCollider
void World::AddCollider(Collider* col) {
    colliders.push_back(col);
}

// 实现RemoveCollider
void World::RemoveCollider(Collider* col) {
    colliders.erase(std::remove(colliders.begin(), colliders.end(), col), colliders.end());
}

// 实现UpdateCollisions
void World::UpdateCollisions() {
    // 1. 清空碰撞结果
    for (Collider* col : colliders) {
        col->ClearCollisions(); // 替换原col->collidedObjects.clear();
    }

    // 2. 两两检测碰撞
    for (size_t i = 0; i < colliders.size(); ++i) {
        for (size_t j = i + 1; j < colliders.size(); ++j) {
            Collider* a = colliders[i];
            Collider* b = colliders[j];
            if (a->CollisionJudge(b)) {
                // 替换原直接访问collidedObjects的代码
                a->AddCollisionObject(b->GetOwner());
                b->AddCollisionObject(a->GetOwner());
            }
        }
    }
}