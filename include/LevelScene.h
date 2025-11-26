#pragma once
#include "Scene.h"
#include "Object.h"
#include "Sprite.h"
#include <vector>
#include <memory>
#include <graphics.h>
#include <string>

class LevelScene : public Scene {
private:
    struct Cell {
        int plantCount = 0;
        bool CanPlant() const { return plantCount == 0; }
    };

    std::vector<std::unique_ptr<Object>> plants;
    std::vector<std::unique_ptr<Object>> zombies;
    std::vector<std::unique_ptr<Object>> projectiles;
    std::vector<std::unique_ptr<Object>> suns;

    Cell grid[5][9];
    int sunshine = 50;
    float zombieSpawnTimer = 0;

public:
    LevelScene(const std::string& name) : Scene(name) {
        plants.reserve(45);
        zombies.reserve(50);
        projectiles.reserve(200);
        suns.reserve(30);
    }

    // 重写基类虚函数
    void eventTick(float dt) override;
    void drawTick() override;

    void AddSunshine(int amount) { sunshine += amount; }
    void SpawnZombie(int row);
    bool PlantOnGrid(int row, int col, const std::string& plantType);
    void Pause() { /* 实现暂停 */ }
};