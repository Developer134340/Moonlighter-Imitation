#pragma once
#include "enemy.h"

//PI
#define PI 3.141592f
#define WORMMAX 5

//지렁이 구조체
struct tagWorm
{
	float x, y;
	float angle;
	float speed;
	float radius;
	float addx, addy;
	RECT rc;
	image* image;
	int indexX, indexY;
	int alpha;
};

class boss : public enemy
{
	vector<tagWorm> _worm;
	bool _isDead[WORMMAX];
	

public:

	HRESULT init(POINT tempImagePosition);
	void release();
	void update();
	void render();

	vector<tagWorm> getWormVector() { return _worm; }
	void wormMove();


	boss() {}
	~boss() {}
};

