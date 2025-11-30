#include "Sunflower.h"
#include "Transform.h"
#include <graphics.h>
#include <iostream>

// 手动去黑底函数
void putimage_alpha2(int x, int y, IMAGE* img)
{
    int width = img->getwidth();
    int height = img->getheight();

    // 临时创建图像用于处理
    DWORD* dst = GetImageBuffer();
    DWORD* src = GetImageBuffer(img);

    for (int i = 0; i < height; i++)
    {
        for (int j = 0; j < width; j++)
        {
            int idx = i * width + j;
            int dst_idx = (y + i) * getwidth() + (x + j);

            BYTE r = GetRValue(src[idx]);
            BYTE g = GetGValue(src[idx]);
            BYTE b = GetBValue(b);

            // 如果不是纯黑色，就绘制
            if (!(r == 0 && g == 0 && b == 0))
            {
                dst[dst_idx] = src[idx];
            }
        }
    }
}

Sunflower::Sunflower(const std::string& objType, PlantType type, int health, int cost)
    : Plant(objType, type, health, cost),
    sun_production_rate(240),
    current_sun_cooldown(0)
{
    
}

// 绘制向日葵（仅用Transform位置 + 自身尺寸）
void Sunflower::draw() const {
    if (is_dead()) return;

    // 获取Transform组件的位置（唯一位置来源）
    const Transform* trans = GetTransform();
    if (!trans) return;
    float posX = trans->GetPosition().x;
    float posY = trans->GetPosition().y;
    IMAGE img_sunflower;
    loadimage(&img_sunflower, _T("C:\\Users\\Administrator\\Documents\\GitHub\\C-Love-you-1314-Team-Second-project-PVZ\\图片素材\\sunflower(1).png"));

    // 使用自定义函数显示（去黑底）
    if (!is_dead() ) { 
        putimage_alpha2(trans->GetPosition().x, trans->GetPosition().y, &img_sunflower);
    }
    
}

void Sunflower::update() {
    if (is_dead()) return;
    if (current_sun_cooldown < sun_production_rate) {
        current_sun_cooldown++;
    }
}

int Sunflower::produce_sunshine() {
    if (current_sun_cooldown >= sun_production_rate) {
        current_sun_cooldown = 0;

        const Transform* trans = GetTransform();
        float posX = trans ? trans->GetPosition().x : 0;
        float posY = trans ? trans->GetPosition().y : 0;
        std::cout << "Sunflower at (" << posX << "," << posY << ") produced a sun!" << '\n';

        return 25;
    }
    return 0;
}