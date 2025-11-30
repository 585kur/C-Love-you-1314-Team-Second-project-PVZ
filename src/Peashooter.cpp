#include "Peashooter.h"
#include "Transform.h"
#include <graphics.h>
#include <iostream>

// 手动去黑底函数
void putimage_alpha1(int x, int y, IMAGE* img)
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

// 构造函数：接收objType、type、health、cost，调用Plant基类构造
Peashooter::Peashooter(const std::string& objType, PlantType type, int health, int cost)
    : Plant(objType, type, health, cost) { // 直接传递参数给Plant基类
    // 位置由LevelScene通过SetPosition设置，此处无需处理
}

// 绘制豌豆射手（保持不变）
void Peashooter::draw() const {
    if (is_dead()) return;

    const Transform* trans = GetTransform();
    if (!trans) return;
    float x = trans->GetPosition().x;
    float y = trans->GetPosition().y;
    int width = 50, height = 50;

    IMAGE img_peashooter;
    loadimage(&img_peashooter, _T("C:\\Users\\Administrator\\Documents\\GitHub\\C-Love-you-1314-Team-Second-project-PVZ\\图片素材\\peashooter(1).png"));

    // 使用自定义函数显示（去黑底）
    if (!is_dead()) {
        putimage_alpha1(trans->GetPosition().x, trans->GetPosition().y, &img_peashooter);
    }
}

// 更新逻辑（保持不变）
void Peashooter::update() {
    if (is_dead()) return;

    if (current_cooldown > 0) {
        current_cooldown--;
    }
    else {
        shoot();
        current_cooldown = fire_cooldown;
    }
}

void Peashooter::shoot() {
    const Transform* trans = GetTransform();
    if (!trans) return;
    std::cout << "Peashooter at (" << trans->GetPosition().x << ","
        << trans->GetPosition().y << ") shoots pea!" << std::endl;
}