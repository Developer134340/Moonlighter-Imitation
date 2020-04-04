#pragma once

enum OBJECT
{
	NONE,
	TERRAIN,
	HOLE,
	BREAKBLE,
	UNBREAKBLE,
	LAVA,
	NOT_LAVA,
	ENEMY,
	FALLING,
	DOOR,
	CAMP,
	POND
};

enum DOOR_DIRECTION
{
	DOOR_NONE, DOOR_UP, DOOR_LEFT, DOOR_DOWN, DOOR_RIGHT
};

enum BUTTON
{
	TILE_BUTTON,
	LAVA_BUTTON ,
	OBJECT_BUTTON,
	ENEMY_BUTTON
};


struct tagTile
{
	POINT pos;
	RECT rc;
	int frameX;
	int frameY;
	OBJECT objectType;
	char t[100];
	
};

struct tagDoor
{
	POINT pos;
	RECT rc;
	int frameX;
	int frameY;
	int roomIndex;
	bool isOpen;
	bool placed;
	bool isBossRoom;
	DOOR_DIRECTION doorDirection;
};