#define _WIN32_WINNT 0x0600
#include "Scene.h"
#include "LevelScene.h"
#include "ObjectManager.h"
#include "Peashooter.h"
#include <graphics.h>
#include <windows.h> 
#include <iostream>

int main() {
    // 1. 初始化图形环境
    initgraph(800, 600);
    setbkcolor(RGB(100, 180, 100)); // 设置背景色
    cleardevice();

    BeginBatchDraw();

    // 2. 定义场景状态（菜单/关卡）
    enum class GameState { MENU, LEVEL, EXIT };
    GameState currentState = GameState::MENU;

    // 3. 场景实例化
    Scene menuScene("MENU");
    LevelScene levelScene("Level1"); // 关卡场景

    // 4. 时间变量
    ULONGLONG lastTime = GetTickCount64();
    ExMessage msg;

    // 主循环
    while (currentState != GameState::EXIT) {
        // 计算帧时间差dt（秒）
        ULONGLONG currentTime = GetTickCount64();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // ========== 处理输入 ==========
        while (peekmessage(&msg)) {
            if (msg.message == WM_QUIT || msg.vkcode == VK_ESCAPE) {
                currentState = GameState::EXIT;
                break;
            }

            switch (currentState) {
            case GameState::MENU:
                // 菜单逻辑：按回车键进入关卡
                if (msg.message == WM_KEYDOWN && msg.vkcode == VK_RETURN) {
                    currentState = GameState::LEVEL;
                    levelScene.onEnter(); // 初始化关卡（创建植物/僵尸）
                    cleardevice(); // 清屏切换场景
                }
                break;

            case GameState::LEVEL:
                levelScene.handleInput(msg); // 关卡输入（如暂停、放置植物）
                break;

            default:
                break;
            }
        }

        // ========== 更新+绘制逻辑 ==========
        switch (currentState) {
        case GameState::MENU:
            // 绘制菜单界面
            menuScene.drawTick();
            settextcolor(WHITE);
            settextstyle(40, 0, _T("黑体"));
            outtextxy(200, 200, _T("植物大战僵尸 - 菜单"));
            settextstyle(20, 0, _T("宋体"));
            outtextxy(250, 300, _T("按回车键开始游戏"));
            outtextxy(250, 350, _T("按ESC退出游戏"));
            break;

        case GameState::LEVEL:
            // 关卡更新+绘制
            levelScene.eventTick(dt); // 更新游戏逻辑（植物攻击/僵尸移动）
            levelScene.drawTick();    // 绘制场景（背景/植物/僵尸）
            break;

        default:
            break;
        }

        FlushBatchDraw();

        // 控制FPS（约60帧）
        Sleep(16);
    }

    // 5. 清理资源
    levelScene.onExit();
    EndBatchDraw();
    closegraph();
    std::cout << "游戏退出" << std::endl;
    return 0;
}