// LevelScene.cpp
#include "LevelScene.h"
#include "Peashooter.h"
#include "NormalZombie.h"
#include "Sprite.h"
#include <cstdlib>
#include <tchar.h>

void LevelScene::SpawnZombie(int row) {
    // 创建NormalZombie：参数匹配Zombie的构造函数
    // 调用时总共需要6个参数（1个分组名 + 5个构造参数）
    auto zombie = GetObjectManager()->CreateObject<NormalZombie>(
        "Zombie",                  // 1. 分组类型名（给ObjectManager用）
        "NormalZombie",            // 2. 构造参数1：objType（字符串）
        1.0f,                      // 3. 构造参数2：speed（float类型，必须带f）
        100,                       // 4. 构造参数3：hp（int类型）
        10,                        // 5. 构造参数4：attackDamage（int类型）
        2.0f                       // 6. 构造参数5：attackInterval（float类型，必须带f）
    );
    if (zombie) {
        auto trans = zombie->GetTransform();
        trans->SetPosition(static_cast<float>(800), static_cast<float>(100 + row * 100));
    }
}

bool LevelScene::PlantOnGrid(int row, int col, const std::string& plantType) {
    if (row < 0 || row >= 5 || col < 0 || col >= 9 || !grid[row][col].CanPlant()) {
        return false;
    }

    // 创建Peashooter：参数匹配Peashooter的构造函数
    auto plant = GetObjectManager()->CreateObject<Peashooter>(
        "Plant",                  // 1. 分组类型名（给ObjectManager分组用，不是Peashooter的构造参数）
        "Peashooter",             // 2. Peashooter构造的第1个参数：objType
        PlantType::PEASHOOTER,    // 3. Peashooter构造的第2个参数：PlantType
        100,                      // 4. Peashooter构造的第3个参数：health
        100                       // 5. Peashooter构造的第4个参数：cost（之前漏传的就是这个！）
    );

    if (plant) {
        auto trans = plant->GetTransform();
        trans->SetPosition(
            static_cast<float>(50 + col * 80),
            static_cast<float>(50 + row * 100)
        );
        grid[row][col].plantCount++;
        return true;
    }
    return false;
}