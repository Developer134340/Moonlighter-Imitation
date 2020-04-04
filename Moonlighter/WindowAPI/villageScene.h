#pragma once
#include "gameNode.h"
#include "player.h"

class villageScene :
	public gameNode
{
	player* _player;

	RECT _enterShop;
	RECT _enterDungeon;

	int _count;
	int _actCount[2];
	int _indexX[2];
	int _indexY[2];

	int _witchTalkIndex;

	bool _witchStoreOn;
	bool _isGameOn;
	bool _witchTalkOn;

	RECT _witchTalk;

	RECT _witchSellRect[8];
	int _witchSelectItem;
	char _itemName[100];
	char _itemIntro[200];
	char _itemNum[10];

	RECT _printName;
	RECT _printIntro;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	villageScene() {}
	~villageScene() {}
};

