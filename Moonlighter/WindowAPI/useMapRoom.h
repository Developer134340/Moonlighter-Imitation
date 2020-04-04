#pragma once
#include "gameNode.h"
#include "tileNode.h"

#define MAXTILEX 20
#define MAXTILEY 11

class useMapRoom :
	public gameNode
{
	RECT _wholeRect;

	tagTile _defaultTile[MAXTILEX * MAXTILEY];
	tagTile _lavaTile[MAXTILEX * MAXTILEY];
	tagTile _objectTile[MAXTILEX * MAXTILEY];
	tagTile _enemyTile[MAXTILEX * MAXTILEY];
	tagDoor _doorTile[4];

	RECT _wall[4];

	int _campIndex;
	int _pondIndex;
	int _count;

	bool _isOnGame;

	image* _defaultTileImage;
	image* _laveTileImage;
	image* _unbreakableImage;
	image* _enemyImage;

	image* _campImage;
	image* _healingpoolImage;
	image* _doorImage;
	image* _wallImage;

public:

	HRESULT init();
	void release();
	void update();
	void render();

	tagTile getDefaultTile(int x) { return _defaultTile[x]; }
	void setDefaultTileFrameX(int x, int tempFrameX) { _defaultTile[x].frameX = tempFrameX; }
	void setDefaultTileFrameY(int y, int tempFrameY) { _defaultTile[y].frameY = tempFrameY; }
	void setDefaultTileType(int x, OBJECT _objectType) { _defaultTile[x].objectType = _objectType; }
	RECT* getDefaultTileRectAddress(int x) { return &_defaultTile[x].rc; }

	tagTile getLavaTile(int x) { return _lavaTile[x]; }
	void setLavaTileFrameX(int x, int tempFrameX) { _lavaTile[x].frameX = tempFrameX; }
	void setLavaTileFrameY(int y, int tempFrameY) { _lavaTile[y].frameY = tempFrameY; }
	void setLavaTileType(int x, OBJECT _objectType) { _lavaTile[x].objectType = _objectType; }
	RECT* getLavaTileRectAddress(int x) { return &_lavaTile[x].rc; }

	tagTile getObjectTile(int x) { return _objectTile[x]; }
	void setObjectTileFrameX(int x, int tempFrameX) { _objectTile[x].frameX = tempFrameX; }
	void setObjectTileFrameY(int y, int tempFrameY) { _objectTile[y].frameY = tempFrameY; }
	void setObjectTileType(int x, OBJECT _objectType) { _objectTile[x].objectType = _objectType; }
	RECT* getObjectTileRectAddress(int x) { return &_objectTile[x].rc; }

	tagTile getEnemyTile(int x) { return _enemyTile[x]; }
	void setEnemyTileFrameX(int x, int tempFrameX) { _enemyTile[x].frameX = tempFrameX; }
	void setEnemyTileFrameY(int y, int tempFrameY) { _enemyTile[y].frameY = tempFrameY; }
	void setEnemyTileType(int x, OBJECT _objectType) { _enemyTile[x].objectType = _objectType; }
	RECT* getEnemyTileRectAddress(int x) { return &_enemyTile[x].rc; }

	tagDoor getDoorTile(int x) { return _doorTile[x]; }
	void setDoorTileFrameX(int x, int tempFrameX) { _doorTile[x].frameX = tempFrameX; }
	void setDoorTileFrameY(int y, int tempFrameY) { _doorTile[y].frameY = tempFrameY; }
	void setDoorTileDirection(int x, DOOR_DIRECTION _doorType) { _doorTile[x].doorDirection = _doorType; }
	void setDoorTileIsPlaced(int x, bool isPlaced) { _doorTile[x].placed = isPlaced; }
	void setDoorRoomIndex(int x, int tempRoomIndex) { _doorTile[x].roomIndex = tempRoomIndex; }
	void setDoorIsBossRoom(int x, bool tempBossRoom) { _doorTile[x].isBossRoom = tempBossRoom; }
	void setDoorIsOpen(int x, bool tempIsOpen) { _doorTile[x].isOpen = tempIsOpen; }
	DOOR_DIRECTION getDoorDirection(int x) { return _doorTile[x].doorDirection; }
	RECT* getDoorTileRectAddress(int x) { return &_doorTile[x].rc; }

	RECT* getWallTileRectAddress(int x) { return &_wall[x]; }

	void setCampIndex(int x) { _campIndex = x; }
	void setPondIndex(int x) { _pondIndex = x; }
	void unbreakableRender();
	void setIsOnGame(bool tempBool) { _isOnGame = tempBool; }


	useMapRoom() {}
	~useMapRoom() {}
};

