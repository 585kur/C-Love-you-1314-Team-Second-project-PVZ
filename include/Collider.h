#pragma once
#include "Component.h"
#include "Object.h"
#include <unordered_set>
#include <vector>
#include <string>
#include "World.h"

extern World mainWorld;

enum class ColliderShape { Circle, Box };

class Collider : public Component {
protected:
    ColliderShape shape;
    int layer = 0; // 碰撞层级，植物-》僵尸，
    std::unordered_set<Collider*> collisions; // 当亲帧率碰撞结果
    std::vector<Object*> filteredAims; // 按类型筛选的结果

    // 碰撞判断：原队员，原对方，放对方，放队员
    virtual bool CollisionJudge(Collider* other) = 0;
public:
    Collider(ColliderShape shape) : shape(shape) {
        mainWorld.AddCollider(this); // 注册到全局碰撞管理器
    }

    virtual ~Collider() {
        mainWorld.RemoveCollider(this); // 注销
    }

    // 碰撞结果处理，双方都能获的碰撞结果
    void ClearCollisions() { collisions.clear(); }
    void AddCollision(Collider* other) {
        if (collisions.find(other) == collisions.end() && CollisionJudge(other)) {
            collisions.insert(other);
            other->collisions.insert(this); // 双向记录
        }
    }

    // 按类型筛选碰撞对象：植物对僵尸
    const std::vector<Object*>& GetCollisionsByType(const std::string& type) {
        filteredAims.clear();
        for (Collider* col : collisions) {
            if (col->GetOwner()->GetType() == type) {
                filteredAims.push_back(col->GetOwner());
            }
        }
        return filteredAims;
    }

    // Getter
    ColliderShape GetShape() const { return shape; }
    int GetLayer() const { return layer; }
    void SetLayer(int layer) { this->layer = layer; }
};

// 圆形碰撞体子类
class CircleCollider : public Collider {
private:
    float radius = 0;
public:
    CircleCollider(float radius) : Collider(ColliderShape::Circle), radius(radius) {}

    void SetRadius(float r) { radius = r; }
    float GetRadius() const { return radius; }

    bool CollisionJudge(Collider* other) override; // 实现见cpp
};

// 矩形碰撞体子类
class BoxCollider : public Collider {
private:
    float width = 0, height = 0;
public:
    BoxCollider(float w, float h) : Collider(ColliderShape::Box), width(w), height(h) {}

    void SetSize(float w, float h) { width = w; height = h; }
    float GetWidth() const { return width; }
    float GetHeight() const { return height; }

    bool CollisionJudge(Collider* other) override; // 实现见cpp
};

