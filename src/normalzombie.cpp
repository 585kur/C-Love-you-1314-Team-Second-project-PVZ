#include "NormalZombie.h"

// 加载图片
extern IMAGE normalZombieImage;  // 外部图像资源

NormalZombie::NormalZombie(int x, int y)
    : Zombie(x, y, 50, 100, 0.1f, 100, 10, 1.0f)  // 设置位置、大小、速度、血量、攻击伤害、攻击间隔
{
    // 加载僵尸图片（你需要确保 normalZombieImage 在某个地方被加载）
    loadimage(&normalZombieImage, "normalZombie.png"); // 假设你的图片在当前目录
}

NormalZombie::~NormalZombie()
{
    // 清理资源（如果有其他需要释放的资源）
}

// 绘制 NormalZombie
void NormalZombie::draw()
{
    // 绘制正常僵尸（根据僵尸的 x, y 坐标）
    putimage(x, y, &normalZombieImage);
}
