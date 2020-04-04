#pragma once
#include "gameNode.h"
#include "mapToolBox.h"
#include "useMap.h"

class mapMakingScene :
	public gameNode
{
	mapToolBox* _mapToolBox;
	useMap* _useMap;

	RECT _title;
	RECT _arrow[4];
	bool _arrowOn[4];
	bool _canMakeMap;
	bool _canMakeBoss;

	int _maxMapIndex;
	int _count;
	int _saveCount;

	//========================test========================

	char test2[100];

	void save();
	void load();
	void clear();

public:

	HRESULT init();
	void release();
	void update();
	void render();

	mapMakingScene(){}
	~mapMakingScene(){}
};

