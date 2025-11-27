#pragma once
#include "Scene.h"
#include "Object.h"
#include "ObjectManager.h" 
#include "Plant.h"         
#include "Sunflower.h"
#include <graphics.h>
#include <string>

class LevelScene : public Scene {
private:
    struct Cell {
        int plantCount = 0;
        bool CanPlant() const { return plantCount == 0; }
    };

    ObjectManager objMgr;   // 新增：对象管理器（管理所有游戏对象）
    Cell grid[5][9];        // 种植网格
    int sunshine = 50;      // 当前阳光
    float zombieSpawnTimer = 0; // 僵尸生成计时器

    // 新增：提供对象管理器的访问方法
    ObjectManager* GetObjectManager() { return &objMgr; }

public:
    LevelScene(const std::string& name) : Scene(name) {}

    // 重写基类虚函数（必须实现）
    void eventTick(float dt) override;
    void drawTick() override;

    // 自定义方法
    void AddSunshine(int amount) { sunshine += amount; }
    void SpawnZombie(int row);
    bool PlantOnGrid(int row, int col, const std::string& plantType);
    void Pause() { /* 后续可补充暂停逻辑 */ }
};