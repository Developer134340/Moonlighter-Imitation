#pragma once
#include "gameNode.h"
#include "useMap.h"
#include "player.h"
#include "enemyManager.h"

class dungeonScene :
	public gameNode
{
	useMap* _useMap;
	player* _player;
	enemyManager* _enemyManager;

	bool _isNewRoom;
	bool _isBossRoom;
	bool _gameClear;
	int _count;

	RECT _bossWall[4];

	vector<int> _vUnbreakableTile;
	vector<int> _vHoleTile;
	vector<int> _vLavaTile;

	bool _isGameOn;

	RECT _goToVillage;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void useMapLoad();


	dungeonScene() {}
	~dungeonScene() {}
};

