#include "Sprite.h"
#include "Transform.h"
#include "Object.h"

// 构造函数实现
Sprite::Sprite(IMAGE* img) : m_image(img) {}

// 析构函数实现
Sprite::~Sprite() {}

// Draw方法实现
void Sprite::Draw() {
    if (m_image == nullptr || owner == nullptr) return;
    Transform* transform = owner->GetTransform();
    if (!transform) return;
    Vector2D pos = transform->GetPosition();
    putimage(static_cast<int>(pos.x), static_cast<int>(pos.y), m_image);
}

// SetImage方法实现（确保方法名与头文件一致）
void Sprite::SetImage(IMAGE* img) {
    m_image = img;
}