// LevelScene.h
#ifndef LEVELSCENE_H
#define LEVELSCENE_H
#include "Scene.h"
#include "ObjectManager.h"
#include "Plant.h"
#include "Zombie.h"
#include <vector>
#include <string>

// 地图和卡槽常量（与main.cpp屏幕尺寸匹配）
const int MAP_ROWS = 5;
const int MAP_COLS = 9;
const int GRID_W = 80;   // 格子宽度
const int GRID_H = 100;  // 格子高度
const int CARD_H = 80;   // 卡槽高度
const int CARD_W = 60;   // 单张卡片宽度
const int CARD_GAP = 10; // 卡片间距
const int CARD_Y = 20;  // 卡槽顶部Y
const int CARD_X_START = 30; // 第一张卡片X
const int MAP_X = 50;    // 地图左上角X
const int MAP_Y = CARD_Y + CARD_H + 20;    // 地图左上角Y




// 地图格子状态（是否可种植）
struct Grid {
    bool canPlant = true; // 默认可种植
    Plant* plant = nullptr; // 格子上的植物（ nullptr表示无）
};

// 卡槽植物信息
struct Card {
    std::string name; // 植物名称（如"豌豆射手"）
    std::string type; // 植物类型（如"Peashooter"）
    int cost; // 阳光成本
    float cd; // 冷却时间（秒）
    float currentCd; // 当前冷却剩余时间
};

class LevelScene : public Scene {
private:
    ObjectManager objMgr; // 对象管理器（植物/僵尸）
    int sunshine = 100; // 初始阳光
    float zombieSpawnTimer = 0; // 僵尸生成计时器

    // 新增：地图和卡槽相关
    std::vector<std::vector<Grid>> grid; // 5行9列地图网格
    std::vector<Card> cards; // 卡槽植物列表
    std::string selectedCard; // 当前选中的卡槽植物（空表示未选中）

public:
    LevelScene(std::string name);
    void onEnter() override; // 场景进入时初始化
    void onExit() override;  // 场景退出时清理
    void eventTick(float dt) override; // 逻辑更新
    void drawTick() override; // 绘制
    void handleInput(ExMessage& msg); // 处理输入（新增）

    // 辅助方法
    void SpawnZombie(int row); // 生成僵尸
    bool PlantOnGrid(int row, int col, const std::string& plantType); // 种植植物
    void AddSunshine(int amount) { sunshine += amount; } // 增加阳光
};
#endif