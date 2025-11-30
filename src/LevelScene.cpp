#include "LevelScene.h"
#include "Peashooter.h"
#include "Sunflower.h"
#include "NormalZombie.h"
#include "Transform.h"
#include <graphics.h>
#include <windows.h>
#include <cstdlib>

// 手动去黑底函数
void putimage_alpha0(int x, int y, IMAGE* img)
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

LevelScene::LevelScene(std::string name) : Scene(name) {
    // 初始化5行9列地图网格
    grid.resize(MAP_ROWS, std::vector<Grid>(MAP_COLS));
}

// 场景进入时初始化卡槽和地图
void LevelScene::onEnter() {
    // 初始化卡槽植物（豌豆射手、向日葵）
    cards = {
        {"豌豆射手", "Peashooter", 100, 5.0f, 0.0f}, // 名称、类型、成本、冷却时间、当前冷却
        {"向日葵", "Sunflower", 50, 10.0f, 0.0f}
    };
    selectedCard = ""; // 初始未选中任何卡片
}

void LevelScene::onExit() {
    objMgr.CleanupDestroyed(); // 清理所有对象
}

// 逻辑更新（含卡槽冷却）
void LevelScene::eventTick(float dt) {
    objMgr.UpdateAll(dt); // 更新植物和僵尸

    // 僵尸生成（每5秒随机生成1个）
    zombieSpawnTimer += dt;
    if (zombieSpawnTimer >= 5.0f) {
        SpawnZombie(rand() % MAP_ROWS);
        zombieSpawnTimer = 0;
    }

    // 向日葵产阳光
    auto sunflowers = objMgr.GetObjectsByType("SUNFLOWER");
    for (Object* obj : sunflowers) {
        Sunflower* sun = dynamic_cast<Sunflower*>(obj);
        if (sun) AddSunshine(sun->produce_sunshine());
    }

    // 卡槽冷却更新
    for (auto& card : cards) {
        if (card.currentCd > 0) {
            card.currentCd = (card.currentCd - dt) > 0.0f ? (card.currentCd - dt) : 0.0f;
        }
    }
}

// 绘制地图、卡槽、植物、僵尸
void LevelScene::drawTick() {
    // 1. 绘制背景
    setbkcolor(RGB(120, 200, 120));
    cleardevice();

    // 2. 绘制地图网格
    // 绘制格子背景
    setfillcolor(RGB(140, 210, 140));
    for (int r = 0; r < MAP_ROWS; r++) {
        for (int c = 0; c < MAP_COLS; c++) {
            int x = MAP_X + c * GRID_W;
            int y = MAP_Y + r * GRID_H;
            fillrectangle(x, y, x + GRID_W, y + GRID_H);
        }
    }
    // 绘制网格线
    setlinecolor(BLACK);
    for (int c = 0; c <= MAP_COLS; c++) { // 竖线
        int x = MAP_X + c * GRID_W;
        line(x, MAP_Y, x, MAP_Y + MAP_ROWS * GRID_H);
    }
    for (int r = 0; r <= MAP_ROWS; r++) { // 横线
        int y = MAP_Y + r * GRID_H;
        line(MAP_X, y, MAP_X + MAP_COLS * GRID_W, y);
    }

    //地图图片
    IMAGE img_map;
    loadimage(&img_map, _T("C:\\Users\\Administrator\\Documents\\GitHub\\C-Love-you-1314-Team-Second-project-PVZ\\图片素材\\bg5(1).jpg"));
    putimage(0, 0, &img_map);

    // 3. 绘制卡槽
    // 卡槽背景
    IMAGE img_bar;
    loadimage(&img_bar, _T("C:\\Users\\Administrator\\Documents\\GitHub\\C-Love-you-1314-Team-Second-project-PVZ\\图片素材\\bar(1).png"));
    putimage_alpha0(0, 10, &img_bar);
    
    // 绘制每张卡片
    for (int i = 0; i < cards.size(); i++) {
        const auto& card = cards[i];
        int x = CARD_X_START + i * (CARD_W + CARD_GAP);
        int y = CARD_Y + (CARD_H - CARD_W) / 2; // 居中

        // 卡片背景（选中时高亮）
        setfillcolor(selectedCard == card.type ? RGB(150, 255, 150) : RGB(100, 200, 100));
        fillrectangle(x, y, x + CARD_W, y + CARD_W);
        setlinecolor(BLACK);
        rectangle(x, y, x + CARD_W, y + CARD_W);

        // 卡片文字（名称+成本）
        settextcolor(WHITE);
        settextstyle(12, 0, _T("宋体"));
        outtextxy(x + 5, y + 5, card.name.c_str());
        // 阳光成本
        settextcolor(YELLOW);
        char cost[10];
        sprintf_s(cost, "%d", card.cost);
        outtextxy(x + 5, y + CARD_W - 20, cost);

        // 冷却遮罩（如果在冷却中）
        if (card.currentCd > 0) {
            setfillcolor(RGB(100, 100, 100, 128)); // 半透明灰色
            fillrectangle(x, y, x + CARD_W, y + CARD_W);
        }
    }

    // 4. 绘制植物和僵尸（原有逻辑）
    auto plants = objMgr.GetObjectsByType("Plant");
    for (Object* obj : plants) {
        Plant* p = dynamic_cast<Plant*>(obj);
        if (p) p->draw();
    }
    auto zombies = objMgr.GetObjectsByType("Zombie");
    for (Object* obj : zombies) {
        NormalZombie* z = dynamic_cast<NormalZombie*>(obj);
        if (z) z->draw();
    }

    // 5. 绘制阳光数量
    settextcolor(YELLOW);
    settextstyle(20, 0, _T("宋体"));
    char sunText[20];
    sprintf_s(sunText, "阳光：%d", sunshine);
    outtextxy(10, 10, sunText);
}

// 处理输入（点击卡槽选植物、点击地图种植物）
void LevelScene::handleInput(ExMessage& msg) {
    // 鼠标左键点击
    if (msg.message == WM_LBUTTONDOWN) {
        int x = msg.x;
        int y = msg.y;

        // 检查是否点击卡槽（选中植物）
        if (y >= CARD_Y && y <= CARD_Y + CARD_H) {
            for (int i = 0; i < cards.size(); i++) {
                const auto& card = cards[i];
                int cardX = CARD_X_START + i * (CARD_W + CARD_GAP);
                // 判断点击是否在当前卡片范围内
                if (x >= cardX && x <= cardX + CARD_W &&
                    y >= CARD_Y + (CARD_H - CARD_W) / 2 && y <= CARD_Y + (CARD_H - CARD_W) / 2 + CARD_W) {
                    // 冷却结束且阳光足够时才能选中
                    if (card.currentCd <= 0 && sunshine >= card.cost) {
                        selectedCard = card.type; // 选中当前卡片
                    }
                    break;
                }
            }
        }
        // 检查是否点击地图（种植植物）
        else if (x >= MAP_X && x <= MAP_X + MAP_COLS * GRID_W &&
            y >= MAP_Y && y <= MAP_Y + MAP_ROWS * GRID_H &&
            !selectedCard.empty()) {
            // 计算点击的格子行和列
            int col = (x - MAP_X) / GRID_W;
            int row = (y - MAP_Y) / GRID_H;
            // 种植植物（调用原有种植逻辑）
            if (PlantOnGrid(row, col, selectedCard)) {
                // 种植成功后，触发卡槽冷却
                for (auto& card : cards) {
                    if (card.type == selectedCard) {
                        card.currentCd = card.cd; // 重置冷却
                        break;
                    }
                }
                selectedCard = ""; // 取消选中
            }
        }
    }
}

// 生成僵尸（原有逻辑）
void LevelScene::SpawnZombie(int row) {
    auto zombie = objMgr.CreateObject<NormalZombie>(
        "Zombie", "NormalZombie", 1.0f, 100, 10, 2.0f
    );
    if (zombie) {
        zombie->GetTransform()->SetPosition(800.0f, MAP_Y + row * GRID_H + GRID_H / 2);
    }
}

// 种植植物（原有逻辑，适配卡槽选中）
bool LevelScene::PlantOnGrid(int row, int col, const std::string& plantType) {
    if (row < 0 || row >= MAP_ROWS || col < 0 || col >= MAP_COLS) return false;
    Grid& targetGrid = grid[row][col];
    if (!targetGrid.canPlant || targetGrid.plant != nullptr) return false;

    // 根据选中的植物类型创建对应植物
    Plant* plant = nullptr;
    if (plantType == "Peashooter") {
        if (sunshine < 100) return false;
        plant = objMgr.CreateObject<Peashooter>(
            "Plant", "Peashooter", PlantType::PEASHOOTER, 100, 100
        );
    }
    else if (plantType == "Sunflower") {
        if (sunshine < 50) return false;
        plant = objMgr.CreateObject<Sunflower>(
            "Plant", "Sunflower", PlantType::SUNFLOWER, 100, 50
        );
    }
    if (!plant) return false;

    // 设置植物位置和网格状态
    plant->GetTransform()->SetPosition(
        MAP_X + col * GRID_W + GRID_W / 2,
        MAP_Y + row * GRID_H + GRID_H / 2
    );
    targetGrid.plant = plant;
    sunshine -= plant->get_cost();
    return true;
}

