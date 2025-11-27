#include "LevelScene.h"
#include "Peashooter.h"
#include "NormalZombie.h"
#include "Transform.h"
#include <cstdlib>
#include <tchar.h>
#include <iostream>

// 实现eventTick（关卡逻辑更新）
void LevelScene::eventTick(float dt) {
    // 1. 更新所有游戏对象（植物/僵尸的AI、冷却等）
    objMgr.UpdateAll(dt);

    // 2. 僵尸生成逻辑（每5秒随机生成1个）
    zombieSpawnTimer += dt;
    if (zombieSpawnTimer >= 5.0f) {
        SpawnZombie(rand() % 5); // 0-4行随机生成
        zombieSpawnTimer = 0;
    }

    // 3. 收集向日葵生产的阳光
    auto sunflowers = objMgr.GetObjectsByType("SUNFLOWER");
    for (Object* obj : sunflowers) {
        Sunflower* sunflower = dynamic_cast<Sunflower*>(obj);
        if (sunflower) {
            int sun = sunflower->produce_sunshine();
            if (sun > 0) AddSunshine(sun);
        }
    }
}

// 实现drawTick（关卡绘制）
void LevelScene::drawTick() {
    // 1. 清空绘图区域（背景设为草地色）
    setbkcolor(RGB(120, 200, 120));
    cleardevice();

    // 2. 绘制所有植物
    auto plants = objMgr.GetObjectsByType("Plant");
    for (Object* obj : plants) {
        Plant* plant = dynamic_cast<Plant*>(obj);
        if (plant) plant->draw();
    }

    // 3. 绘制所有僵尸
    auto zombies = objMgr.GetObjectsByType("Zombie");
    for (Object* obj : zombies) {
        NormalZombie* zombie = dynamic_cast<NormalZombie*>(obj);
        if (zombie) zombie->draw();
    }

    // 4. 绘制阳光UI
    settextcolor(YELLOW);
    settextstyle(20, 0, _T("宋体"));
    TCHAR sunText[20];
    _stprintf_s(sunText, _T("阳光：%d"), sunshine);
    outtextxy(10, 10, sunText);
}

// 生成僵尸（修正：匹配NormalZombie的构造参数）
void LevelScene::SpawnZombie(int row) {
    // 调用NormalZombie的构造函数（参数：objType、speed、hp、attackDamage、attackInterval）
    auto zombie = GetObjectManager()->CreateObject<NormalZombie>(
        "Zombie",        // 分组名（ObjectManager用）
        "NormalZombie",  // 构造参数1：objType
        1.0f,            // 构造参数2：移动速度
        100,             // 构造参数3：生命值
        10,              // 构造参数4：攻击力
        2.0f             // 构造参数5：攻击间隔
    );

    if (zombie) {
        // 设置僵尸初始位置（屏幕右侧，对应行）
        Transform* trans = zombie->GetTransform();
        trans->SetPosition(800.0f, 100.0f + row * 100.0f);
    }
}

// 种植植物（修正：匹配Peashooter的构造参数）
bool LevelScene::PlantOnGrid(int row, int col, const std::string& plantType) {
    // 校验：行列合法、网格可种植、阳光足够
    if (row < 0 || row >= 5 || col < 0 || col >= 9 || !grid[row][col].CanPlant() || sunshine < 100) {
        return false;
    }

    // 调用Peashooter的构造函数（参数：objType、PlantType、health、cost）
    auto plant = GetObjectManager()->CreateObject<Peashooter>(
        "Plant",          // 分组名（ObjectManager用）
        "Peashooter",     // 构造参数1：objType
        PlantType::PEASHOOTER, // 构造参数2：植物类型
        100,              // 构造参数3：生命值
        100               // 构造参数4：阳光成本
    );

    if (plant) {
        // 设置植物位置（网格对应的坐标）
        Transform* trans = plant->GetTransform();
        trans->SetPosition(50.0f + col * 80.0f, 50.0f + row * 100.0f);

        grid[row][col].plantCount++; // 标记网格已种植
        sunshine -= 100; // 扣除阳光
        return true;
    }
    return false;
}