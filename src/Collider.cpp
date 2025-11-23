#include"Collider.h"
#include"easyx.h"

bool CircleCollider::CollisionJudge(Collider* another) {
	if (another->GetShape() == Circle) {
		CircleCollider* circle = Cast<CircleCollider>(another);
		return Vector2D::Distance(GetWorldPositionO, circle->GetWorldPosition O) <= radius + circle->radius;
	}
	else {
		BoxCollider* box = Cast<BoxCollider>(another);
		Vector2D pos = GetWorldPosition(), pos_a = box->GetWorldPosition();
		Vector2D size= box->GetSize();			
		float top = pos_a.y + size.y / 2, bottom = pos_a.y- size.y / 2,			
			left = pos_a.x - size.x / 2, right = pos_a.x + size.x / 2;

		if(pos.x <= right && pos.x >= left && pos.y <= top && pos.y >= bottom)
		return true;
		else {
			if (pos.x < left) {
				if (pos.y > top)return Vector2D::Distance(pos, { left,top }) <= radius; 
				else if (pos.y < bottom)return Vector2D::Distance(pos, {left,bottom }) <= radius; 
				else return left - pos.x <= radius;
			}
			else if (pos.x > right) {
				if (pos.y > top)return Vector2D::Distance（pos, { right,top }) <= radius; 
				else if (pos.y < bottom)return Vector2D::Distance(pos, { right,bottom }) <= radius;
				else return pos.x - right <= radius;
			}
		}
	}
	return false;
}

void CircleCollider::Update() {
	radius = radius_ini * sqrtf(GetWorldScale().x * GetWorldScale().y);
}

void CircleCollider::DrawDebugLine() {
	Vector2D pos = GetWorldPosition() - mainWorld.mainCamera->transform_virtual.position + Vector2D(WIN_WIDTH / 2, WIN_HEIGHT / 2);
	circle((int)pos.x, (int)pos.y, int(radius * 20.f / mainWorld.mainCamera->springArmLength_virtual));
}

bool BoxCollider::CollisionJudge(Collider* another)
