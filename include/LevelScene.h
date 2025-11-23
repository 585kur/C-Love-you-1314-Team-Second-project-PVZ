#include<iostream>
#include<vector>
#include"Scene.h"
#include"Plant.h"
#include"Zombie.h"

using namespace std;

class LevelScene :public Scene {
public:
	class cell {
		//网格上植物数量
		int PlantNum = 0;
		//可种植判断
		bool AblePlant();
	};
	//存储植物
	cell* plantarray[5][9] = { nullptr };

	//植物容器
	vector<Plant> plantVector;
	plantVector.reserve(45);
	//僵尸容器
	vector<Zombie> zombieVector;
	//场上僵尸数量上限
	zombieVector.reserve(50);
	//子弹容器
	vector<Bullet> bulletVector;
	bulletVector.reserve(200);
//上面三个容器的第二行代码，容器名报错“此声明没有存储类或类型说明符”



	//阳光容器
	int Allsunshine=50;
	//初始化植物存储数组
	
	
protected:
	//阳光计数器
	void SunshineCounter();
	//僵尸计数器
	void ZombieCounter();

	//暂停
	void Pause();
	
		
};













