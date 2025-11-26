#include "Object.h"
#include "Component.h"
#include "Transform.h" // 确保Transform组件可正常创建

// 注：Object类中的模板方法（AddComponent/GetComponent）必须留在头文件中，
// 这里仅实现非模板方法或补充析构逻辑（若需要）

// 若Object的析构需要额外处理（比如日志输出），可在这里重写：
Object::~Object() {
    // 可选：添加日志或调试信息
    // std::cout << "Object [" << type << "] 已销毁" << std::endl;

    // 原有逻辑：删除所有组件
    for (auto& pair : components) {
        delete pair.second;
    }
    components.clear();
}

// 若需要实现Update方法（让Object支持帧更新）：
void Object::Update(float dt) {
    // 遍历所有组件，调用组件的Update
    for (auto& pair : components) {
        pair.second->Update(dt);
    }
}