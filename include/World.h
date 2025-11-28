#pragma once
#include <vector>
#include <algorithm>
class Collider;

class World {
private:
    std::vector<Collider*> colliders;
public:
    // 仅声明函数（不写函数体）
    void AddCollider(Collider* col);
    void RemoveCollider(Collider* col);
    void UpdateCollisions();
};