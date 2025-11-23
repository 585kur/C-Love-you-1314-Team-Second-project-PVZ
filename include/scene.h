#pragma once
#include <graphics.h>
#include <string>

// 抽象基类：所有场景都继承它
class Scene
{
protected:
    std::string sceneName;  // 场景名称，可在调试时显示

public:
    Scene(const std::string& name);
    virtual ~Scene();

    // 每帧绘图（EasyX）
    virtual void drawTick();

    // 每帧更新逻辑（dt = 两帧时间差，秒）
    virtual void eventTick(float dt);

    // 键盘鼠标输入处理
    virtual void handleInput(const ExMessage& msg);

    // 场景进入时调用
    virtual void onEnter();

    // 场景退出时调用
    virtual void onExit();

    // 获取场景名称
    const std::string& getName() const;
};
