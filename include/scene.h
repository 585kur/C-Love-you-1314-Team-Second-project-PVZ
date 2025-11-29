#pragma once
#include <string>
#include <memory>
#include <graphics.h>
#include "World.h"
#include "ObjectManager.h"

class Scene {
protected:
    std::string sceneName;
    std::unique_ptr<World> sceneWorld;
    std::unique_ptr<ObjectManager> objMgr;

public:
    Scene(const std::string& name);
    virtual ~Scene();

    // 虚函数（子类重写）
    virtual void eventTick(float dt) {}
    virtual void drawTick() {}
    virtual void handleInput(const ExMessage& msg) {}

    // 生命周期函数
    virtual void onEnter() {
        sceneWorld = std::make_unique<World>();
        objMgr = std::make_unique<ObjectManager>();
    }

    virtual void onExit() {
        sceneWorld.reset();
        objMgr.reset();
    }

    // 访问器
    World* GetWorld() const { return sceneWorld.get(); }
    ObjectManager* GetObjectManager() const { return objMgr.get(); }
    const std::string& getName() const { return sceneName; }
};