#pragma once
#include "gameNode.h"

enum ENEMY_STATE
{
	E_IDLE, E_WALK, E_ATTACK, E_ABSORBED, E_DEAD, E_REMOVED
};

enum ENEMY_DIRECTION
{
	E_UP, E_LEFT, E_DOWN, E_RIGHT
};

struct COIN
{
	RECT rc;
	float angle;
	float speed;
	int indexX;
};

class enemy :
	public gameNode
{
protected:

	bool _isAttacked;
	string _name;
	float _x, _y;
	image* _image;
	int _speed;
	int _atk;

	int _maxHp;
	int _nowHp;
	
	float _whiteGauge;
	float _hpGauge;

	int _attackCount;
	RECT _rc;
	RECT _attackRangeRc;
	RECT* _playerRc;
	RECT _directionRc[4];
	bool _directionMove[4];

	ENEMY_STATE _enemyState;
	ENEMY_DIRECTION _enemyDirection;

	POINT _destination;
	float _vectorX;
	float _vectorY;
	float _angle;
	float _razorAngle;
	float _distance;
	
	bool _effectOn;
	POINT _effectPosition;

	POINT _imagePositionBefore;
	POINT _imagePositionNow;

	int _indexX;
	int _indexY;
	int _effectIndex;
	int _count;
	int _saveCount;
	int _attackedCount;
	float _attackAngle[2];
	int _attackRadius;
	int _alpha;
	
	bool _playerMove;
	bool _attackOn;

	COIN _aCoin[50];

	vector<RECT> _vAttackRc;

	int _logIndex;
	int _logPos;
	POINT _logPosBefore;

	//====================================test================

	char hp[100];
	char attacked[100];


public:

	HRESULT init(POINT pos, int frameX);
	void release();
	void update();
	void render();

	void enemyDirectionChange();

	void setImagePositionNow(POINT tempImageposition) { _imagePositionNow = tempImageposition; }
	void setPlayerRc(RECT* playerRc) { _playerRc = playerRc; }
	void setDestination(POINT tempPos) { _destination = tempPos; }
	void setDirectionMoveUp(bool tempBool) { _directionMove[0] = tempBool; }
	void setDirectionMoveLeft(bool tempBool) { _directionMove[1] = tempBool; }
	void setDirectionMoveDown(bool tempBool) { _directionMove[2] = tempBool; }
	void setDirectionMoveRight(bool tempBool) { _directionMove[3] = tempBool; }
	int damage()
	{
		int dmg;
		dmg = RND->range(_atk, _atk * 2);
		return dmg;
	}

	void setEnemyState(ENEMY_STATE tempEnemyState) { _enemyState = tempEnemyState; }
	void setEnemyHp(int tempHp) { _nowHp = tempHp; }

	bool getPlayerMove() { return _playerMove; }
	string getEnemyName() { return _name; }

	RECT* getDirectionRcAddress(int x) { return &_directionRc[x]; }
	RECT* getEnemyRcAddress() { return &_rc; }
	vector<RECT> getEnemyAttackRc() { return _vAttackRc; }
	void setEnemyAttacked(int tempDmg);
	int getEnemySaveCount() { return _saveCount; }
	ENEMY_STATE getEnemyState() { return _enemyState; }
	POINT getEnemyPos() {
	
		return PointMake(_x, _y);
	}

	enemy() {}
	~enemy() {}
};

