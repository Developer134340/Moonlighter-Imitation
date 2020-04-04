#pragma once
#include "gameNode.h"
#include "enemy.h"
#include "item.h"
#include "boss.h"

class player;

class enemyManager :
	public gameNode
{

	vector<enemy*> _vEnemy;
	vector<enemy*>::iterator _viEnemy;
	vector<item*> _vItem;
	
	player* _player;

	char test[100];

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void addEnemy(POINT tempPos, int frameX)
	{
		enemy* temp;
		temp = new enemy;
		temp->init(tempPos, frameX);
		_vEnemy.push_back(temp);
	}

	void addEnemy();

	vector<enemy*> getEnemyVector() { return _vEnemy; }
	vector<item*> getItemVector() { return _vItem; }
	void setPlayerLink(player* player) { _player = player; }

	void slimeAbsorbedPlayer();
	void playerEnemyAttack();
	void enemyPlayerAttack();
	void playerGetItem();
	void playerBossAttack();

	enemyManager() {}
	~enemyManager() {}
};

