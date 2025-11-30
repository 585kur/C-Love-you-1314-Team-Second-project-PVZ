#include "NormalZombie.h"
#include "Transform.h" // 用于获取位置

// 全局图片初始化（仅加载一次）
IMAGE g_normalZombieImage;

// 手动去黑底函数
void putimage_alpha(int x, int y, IMAGE* img)
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

// 构造函数：调用Zombie的Object架构构造函数
NormalZombie::NormalZombie(const std::string& objType, float speed, int hp, int attackDamage, float attackInterval)
    : Zombie(objType, speed, hp, attackDamage, attackInterval) {
    // 初始化僵尸位置（通过Transform组件）
    GetTransform()->SetPosition(800.0f, 200.0f); // 默认生成在屏幕右侧
}

// 绘制僵尸：通过Transform获取位置
void NormalZombie::draw() const {
    if (!IsAlive()) return; // 死亡不绘制

    // 获取Transform组件的位置
    Transform* trans = const_cast<NormalZombie*>(this)->GetTransform();
    if (!trans) return;

    Vector2D pos = trans->GetPosition();
    loadimage(&g_normalZombieImage, _T("C:\\Users\\Administrator\\Documents\\GitHub\\C-Love-you-1314-Team-Second-project-PVZ\\图片素材\\normalzombie(1).png"));
    // 绘制全局图片资源
    putimage(static_cast<int>(pos.x), static_cast<int>(pos.y), &g_normalZombieImage);
}