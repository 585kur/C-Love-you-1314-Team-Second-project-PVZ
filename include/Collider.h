#pragma once
#include"CoreMinimal.h"

//碰撞更新在游戏对象之前
class Collider : public SceneCompoent { //继承场景组件
public:
	enum ColliderShape { circle, Box };    //bullet：圆形/矩形
	Collider() { mainWorld.GameCollider.insert(this); } // 构造到全局碰撞集合
	virtual~Collider() { mainWorld.GameCollider.enase(this); } // 统一管理所有碰撞体

	const std::vector<Object*>& GetCollisions(std::string type) {
		aims.clear();
		if (!collisions.empty()) {
			for (auto it = collisions.begin(); it != collisions.end(); ++it) {
				if ((*it)->GetType() == type)aims.push_back((*it)->pOwner);
			}
		}
		return aims;
	}


	int GetLayer()const { return layer; }
	void SetLayer(int layer) { this->layer = layer; }

	const std::string& GetType() { return type; }
	void SetType(std::string type) { this->type = type; }

	CollideShape GetShape()const { return shape; }
	

	void Clear() { collisions.clear(); }
	void Insert(Collider* another) {
		if (collisions.find(another) == collisions.end() && CollisionsJudge(another)) {
			collisions.insert(another);
			another->GetCollisions.insert(this);
		}
	}
	

	virtual void DrawDebugLine() = 0; // 纯虚函数：绘制调试碰撞框
protected:
	ColliderShape shape = Circle;
	virtual bool CollisionJudge(Collider* another) = 0; // 纯虚函数：具体碰撞判断逻辑
	
private:
	std::string type = "Default";
	int layer = 0;
	std::unordered_set<Collider*>collisions; // 存储所有碰撞的其他碰撞体
	std::vector<Object*>aims; // 存储按类型筛选后的Object结果
	
};

