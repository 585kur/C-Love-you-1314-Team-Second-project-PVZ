#pragma once 
#include "Component.h"
#include <graphics.h>

class Sprite : public Component {
private:
    IMAGE* m_image = nullptr;
public:
    Sprite(IMAGE* img);
    ~Sprite() override;
    void Draw() override;
    void SetImage(IMAGE* img);
};