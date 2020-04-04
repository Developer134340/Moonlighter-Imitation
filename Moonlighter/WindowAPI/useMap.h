#pragma once
#include "gameNode.h"
#include "useMapRoom.h"

class useMap :
	public gameNode
{
	useMapRoom* _arrayRoom[10];

	int _roomIndex;


public:
	HRESULT init();
	void release();
	void update();
	void render();

	useMapRoom* getUseMapRoom(int i) { return _arrayRoom[i]; }

	int getRoomIndex() { return _roomIndex; }
	void setRoomIndex(int tempIndex) {	_roomIndex = tempIndex; }

	useMap() {}
	~useMap() {}
};

