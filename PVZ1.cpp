// PVZ1.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <Scene.h>
#include <LevelScene.h> 
#include <graphics.h>
#include <ExMessage.h>


int main() {
    // 1. 创建Scene主界面
    Scene scene;
    scene.drawTick;

    // 2. 创建LevelScene实例（游戏关卡场景）
    LevelScene levelScene("Level1"); // 传入场景名称

    // 3. 进入场景（触发场景初始化逻辑）
    levelScene.onEnter();

    // 4. 主循环：处理输入、更新逻辑、绘制画面
    ExMessage msg;
    bool isRunning = true;
    DWORD lastTime = GetTickCount(); // 用于计算deltaTime

    while (isRunning) {
        // 计算两帧之间的时间差dt（秒）
        DWORD currentTime = GetTickCount();
        float dt = (currentTime - lastTime) / 1000.0f;
        lastTime = currentTime;

        // 处理输入事件
        while (peekmessage(&msg)) {
            if (msg.message == WM_QUIT) {
                isRunning = false;
                break;
            }
            levelScene.handleInput(msg); // 调用LevelScene的输入处理
        }

        // 暂停逻辑（调用LevelScene的Pause()）
        if (/* 检测暂停条件，未完成 */) {
            levelScene.Pause();
            continue; // 暂停时跳过后续更新和绘制
        }

        // 更新场景逻辑（僵尸移动、植物攻击、子弹飞行等）
        levelScene.eventTick(dt);

        // 绘制场景（背景、植物、僵尸、子弹、UI等）
        levelScene.drawTick();

        // 控制FPS
        Sleep(16); // 约60FPS
    }

    // 5. 退出场景（清理资源）
    levelScene.onExit();

    // 6. 关闭EasyX图形环境
    closegraph();
    return 0;
}
}
