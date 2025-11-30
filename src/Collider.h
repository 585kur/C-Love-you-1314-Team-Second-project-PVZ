#pragma once
#include "Component.h" 
#include "Transform.h"
#include <string>
#include <cmath>
#include <vector>
#include "World.h"
#include "Object.h" 
#include<algorithm>
#include<iostream>

class Collider : public Component {
public:
    // 获取游戏对象
    Object* GetOwner() const {
        return owner; // 子类内部直接访问owner
    }

    //对象位置
    Vector2D GetOwnerPosition() const {
        if (!owner) return { 0, 0 };
        Transform* trans = owner->GetTransform();
        return trans ? trans->GetPosition() : Vector2D{ 0, 0 };
    }

    // 形状
    enum class ColliderShape { Circle, Box };
    Collider(ColliderShape shape) : m_shape(shape) {}

    virtual ~Collider() = default;

    // 纯虚碰撞判断函数（核心：判断与另一个碰撞体是否相交）
    virtual bool CollisionJudge(Collider* other) = 0;

    // 获取形状
    ColliderShape GetShape() const { return m_shape; }

    void ClearCollisions() { collidedObjects.clear(); }  //每帧前调用

    void AddCollisionObject(Object* obj) { collidedObjects.push_back(obj); }  //碰撞成功时添加游戏对象到游戏对象列表中
    std::vector<Object*> GetCollisionsByType(const std::string& type) {  //按照游戏对象获取碰撞
        std::vector<Object*> result;
        for (Object* obj : collidedObjects) {
            if (obj && obj->GetType() == type) {
                result.push_back(obj);
            }
        }
        return result;
    }
    const std::vector<Object*>& GetAllCollisions() const { return collidedObjects; }

protected:
    ColliderShape m_shape;
    std::vector<Object*> collidedObjects; // 存储碰撞到的对象
};

// 前向声明BoxCollider（供CircleCollider使用）
class BoxCollider;

// ===================== 圆形碰撞体子类（先定义，确保BoxCollider能访问） =====================
class CircleCollider : public Collider {
private:
    float m_radius; // 圆形半径

public:
    // 构造函数：传入圆形半径
    CircleCollider(float radius)
        : Collider(ColliderShape::Circle), m_radius(radius) {
    }

    // 实现碰撞判断（处理圆形-圆形、圆形-矩形碰撞）
    bool CollisionJudge(Collider* other) override {
        if (!other || !GetOwner() || !other->GetOwner()) return false;

        Vector2D posA = GetOwnerPosition();
        Vector2D posB = other->GetOwnerPosition();

        // 圆形 vs 圆形
        if (other->GetShape() == ColliderShape::Circle) {
            CircleCollider* circleOther = static_cast<CircleCollider*>(other);
            // 距离判断：两圆心距离 <= 半径之和
            float dx = posA.x - posB.x;
            float dy = posA.y - posB.y;
            float distanceSq = dx * dx + dy * dy;
            float radiusSum = m_radius + circleOther->m_radius;
            return distanceSq <= (radiusSum * radiusSum);
        }
        // 圆形 vs 矩形（复用矩形的判断逻辑）
        else if (other->GetShape() == ColliderShape::Box) {
            return other->CollisionJudge(this); // 对称逻辑，让矩形判断自己
        }
        return false;
    }

    // Getter
    float GetRadius() const { return m_radius; }
};

// ===================== 矩形碰撞体子类（后定义，此时CircleCollider已完整） =====================
class BoxCollider : public Collider {
private:
    float m_width;  // 矩形宽度
    float m_height; // 矩形高度

public:
    // 构造函数：传入矩形尺寸
    BoxCollider(float width, float height)
        : Collider(ColliderShape::Box), m_width(width), m_height(height) {
    }

    // 实现碰撞判断（处理矩形-矩形、矩形-圆形碰撞）
    bool CollisionJudge(Collider* other) override {
        if (!other || !GetOwner() || !other->GetOwner()) return false;

        Vector2D posA = GetOwnerPosition();
        Vector2D posB = other->GetOwnerPosition();

        // 矩形 vs 矩形
        if (other->GetShape() == ColliderShape::Box) {
            BoxCollider* boxOther = static_cast<BoxCollider*>(other);
            // AABB碰撞检测：轴对齐包围盒
            return (posA.x < posB.x + boxOther->m_width &&
                posA.x + m_width > posB.x &&
                posA.y < posB.y + boxOther->m_height &&
                posA.y + m_height > posB.y);
        }
        // 矩形 vs 圆形（此时CircleCollider已完整定义，可安全转换/访问成员）
        else if (other->GetShape() == ColliderShape::Circle) {
            CircleCollider* circleOther = static_cast<CircleCollider*>(other);
            // 计算矩形到圆心的最近点
            float closestX = std::clamp(posB.x, posA.x, posA.x + m_width);
            float closestY = std::clamp(posB.y, posA.y, posA.y + m_height);
            // 计算最近点到圆心的距离
            float dx = posB.x - closestX;
            float dy = posB.y - closestY;
            return (dx * dx + dy * dy) <= (circleOther->GetRadius() * circleOther->GetRadius());
        }
        return false;
    }

    // Getter
    float GetWidth() const { return m_width; }
    float GetHeight() const { return m_height; }
};