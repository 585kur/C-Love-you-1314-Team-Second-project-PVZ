#include "Scene.h"
#include <iostream>

Scene::Scene(const std::string& name)
    : sceneName(name)
{
}

Scene::~Scene()
{
}

// 绘图：默认绘制背景和场景名称
void Scene::drawTick()
{
    // 默认清屏（避免残影）
    cleardevice();

    // 默认绘制背景为浅灰色
    setfillcolor(RGB(240, 240, 240));
    solidrectangle(0, 0, getwidth(), getheight());

    // 显示当前场景名称（调试）
    settextcolor(BLACK);
    settextstyle(20, 0, "Consolas");
    outtextxy(10, 10, sceneName.c_str());
}

// 逻辑更新：默认只是打印 dt
void Scene::eventTick(float dt)
{
    //这里只提供继承给levelScene的接口，需要levelScene继承后去编写具体逻辑
}

// 输入处理：默认处理 ESC 退出输入
void Scene::handleInput(const ExMessage& msg)
{
    if (msg.message == WM_KEYDOWN)
    {
        if (msg.vkcode == VK_ESCAPE)
        {
            std::cout << "ESC pressed in scene: " << sceneName << std::endl;
        }
    }

    if (msg.message == WM_LBUTTONDOWN)
    {
        std::cout << "[Scene] Mouse click at (" 
                  << msg.x << ", " << msg.y << ")\n";
    }
}

// 场景进入时触发
void Scene::onEnter()
{
    std::cout << "Entering scene: " << sceneName << std::endl;
}

// 场景退出时触发
void Scene::onExit()
{
    std::cout << "Exiting scene: " << sceneName << std::endl;
}

// 获取场景名称
const std::string& Scene::getName() const
{
    return sceneName;
}
