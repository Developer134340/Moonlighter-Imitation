#pragma once
#include "gameNode.h"
#include "userInterface.h"
#include "moveNode.h"

class enemyManager;

class player : public gameNode
{
	enemyManager* _enemyManager;	//동적할당 절대 안된다!!!

	userInterface* _userInterface;
	item* _nowEquip;

	vector<tagAttack> _vAttack;

	int _hp;
	int _maxHp;
	int _atk;
	
	bool _isAttacked;
	int _attackedCount;
	string _playerWhite;

	POINT _pos;
	POINT _positionBefore;
	POINT _imagePosition;
	POINT _imagePositionBefore;
	
	RECT _rc;
	RECT _directionRc[4];
	int _speed;

	float _vectorX;
	float _vectorY;

	bool _directionMove[4];
	image* _pixelMap;

	DIRECTION _direction;
	LOCATION _location;
	COMBO _combo;

	STATE _state;
	int _indexX;
	int _indexY;
	int _count;
	int _saveCount;

	image* _playerImage;

	char test1[100];
	char test2[100];
	char test3[100];
	char test4[100];

	char test5[100];
	char test6[100];

	bool test;

public:

	HRESULT init(POINT pos);
	void release();
	void update();
	void render();

	void setEMLink(enemyManager* em) { _enemyManager = em; }


	void move();
	void imageChange();

	void setPlayerLocation(LOCATION tempLocation) { _location = tempLocation; }

	RECT getPlayerRc() { return _rc; }
	RECT* getPlayerRcAddress() { return &_rc; }
	RECT getPlayerDirectionRc(int x) { return _directionRc[x]; }
	RECT* getPlayerDirectionRcAddress(int x) { return &_directionRc[x]; }
	void setPlayerPosition(POINT pos) { _pos = pos; }
	void setPlayerPositionY(int y) { _pos.y = y; }
	
	void setDirectionMoveUp(bool tempMove) { _directionMove[0] = tempMove; }
	void setDirectionMoveLeft(bool tempMove) { _directionMove[1] = tempMove; }
	void setDirectionMoveDown(bool tempMove) { _directionMove[2] = tempMove; }
	void setDirectionMoveRight(bool tempMove) { _directionMove[3] = tempMove; }

	POINT getPlayerPositionBefore() { return _positionBefore; }
	void setPlayerPositionBefore(POINT positionBefore) { _positionBefore = positionBefore; }
	POINT getImagePosition() { return _imagePosition; }
	void setImagePosition(POINT pos) { _imagePosition = pos; }

	POINT getPlayerPosition() { return _pos; }
	void setPixelMap(image* pixelImg) { _pixelMap = pixelImg; }

	DIRECTION getPlayerDirection() { return _direction; }

	int getPlayerHp() { return _hp; }
	int getPlayerAtk() { return _atk; }
	
	void setPlayerHp(int tempHp) { _hp = tempHp; }
	int damage()
	{
		int dmg;
		dmg = RND->range(_atk, _atk * 3);
		return dmg;
	}

	void camMove(image* bgImg);
	void pixelCollision();
	userInterface* getUserInterface(){ return _userInterface; }

	void setPlayerAttacked(int tempDmg);

	vector<tagAttack> getPlayerAttack() { return _vAttack; }


	player() {}
	~player() {}
};

