#include "Scene.h"
#include "World.h"
#include "ObjectManager.h"
#include "Object.h" 
#include <graphics.h>


// 构造函数：初始化场景名称
//Scene::Scene() {}
Scene::Scene(const std::string& name) : sceneName(name) {}

// 虚析构函数
Scene::~Scene() {}

//void Scene::eventTick(float dt) {
//    if (objMgr) {
//        objMgr->UpdateAll(dt);
//    }
//
//}
//
//
//void Scene::drawTick() {
//
//    if (sceneWorld) {
//        setcolor(sceneWorld->GetBackgroundColor());
//    }
//    else {
//        setcolor(WHITE); // 默认白色背景
//    }
//    cleardevice();
//
//    // 2. 获取所有对象并绘制它们
//    if (objMgr) {
//        std::vector<Object*> allObjects = objMgr->GetAllObjects();
//        for (Object* obj : allObjects) {
//            if (obj->IsAlive()) {
//                obj->Draw();
//            }
//        }
//    }
//
//}
//
//void Scene::handleInput(const ExMessage& msg) {
//
//    switch (msg.message) {
//
//    case WM_KEYDOWN:
//        if (msg.vkcode == VK_ESCAPE) {
//
//        }
//        break;
//
//    case WM_LBUTTONDOWN:
//
//        if (sceneWorld) {
//            sceneWorld->HandleClick(msg.x, msg.y);
//        }
//        break;
//
//    }
//}

//void Scene::onEnter() {
//
//    sceneWorld = std::make_unique<World>();
//    objMgr = std::make_unique<ObjectManager>();
//
//    // objMgr->CreateObject<Player>("Player", 100, 100);
//    // objMgr->CreateObject<Enemy>("Enemy", 500, 300);
//}

//void Scene::onExit() {
//
//
//    sceneWorld.reset();
//    objMgr.reset();
//
//}