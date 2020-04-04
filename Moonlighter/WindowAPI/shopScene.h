#pragma once
#include "gameNode.h"
#include "player.h"
#include "npc.h"

class shopScene : public gameNode
{
	player* _player;
	
	npc* _npc;

	RECT _corridor;
	bool _isShop;
	int _shopPosition;

	RECT _shopDoor;

	RECT _sellRc[4];
	RECT _sellRangeRc;
	RECT _counterRc;

	bool _isGameOn;
	bool _isPlaceJOn;
	bool _isSellJOn;
	bool _shopOpenJOn;

	int _shopOpenIndexX;
	int _shopLoadingIndexX;
	int _count;

	bool _shopOpen;
	bool _npcIs;
	bool _npcGo;
	int _tempCost;
	int _tempNum;

	//===============판매대 관련==============

	bool _sellingStandOn;
	bool _sellingStandDisappear;
	int _standLocation; //스탠드y좌표 움직이는거
	int _standLocationA; //위의꺼 가속도
	int _selectSellItem;

	RECT _sellInventoryRc[20];
	RECT _standItemRc[4];

	char _printCost1[10];
	char _printCost2[10];
	char _printCost3[10];
	char _printCost4[10];

	INVEN _sellItemArray[20];
	INVEN _sellStandArray[4];
	INVEN _sellSelectedItem;
	bool _isSellItemSelected;

	RECT _sellingItemName[4];

	//======================================

public:

	HRESULT init();
	void release();
	void update();
	void render();

	void sellingStand();

	shopScene() {}
	~shopScene() {}
};

