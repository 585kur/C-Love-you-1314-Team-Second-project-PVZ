#pragma once
#include <graphics.h>
#include <string>
#include <memory>  

class World;
class ObjectManager;

class Scene
{
protected:
    std::string sceneName;                  // 
    std::unique_ptr<World> sceneWorld;      // 独立碰撞管理器，
    std::unique_ptr<ObjectManager> objMgr;  // 独立碰撞管理器，

public:
    Scene(const std::string& name);
    virtual ~Scene();

    // 每帧绘图（EasyX）
    virtual void drawTick();

    // 每帧更新逻辑（dt = 两帧时间差，秒）
    virtual void eventTick(float dt);

    // 键盘鼠标输入处理
    virtual void handleInput(const ExMessage& msg);

    virtual void onEnter() {
        // 默认进入逻辑：初始化碰撞世界和对象管理器
        sceneWorld = std::make_unique<World>();
        objMgr = std::make_unique<ObjectManager>();
    }

    virtual void onExit() {
        // 默认退出逻辑：清空对象和碰撞体，释放资源
        sceneWorld.reset();
        objMgr.reset();
    }

    // ========== 访问器（给子类暴露核心管理器） ==========
    World* GetWorld() const { return sceneWorld.get(); }
    ObjectManager* GetObjectManager() const { return objMgr.get(); }
    const std::string& getName() const { return sceneName; }
};
