#pragma once
#include "gameNode.h"

//총알 구조체
struct tagBullet
{
	image* bulletImage;
	RECT rc;
	float x, y;
	float fireX, fireY;
	float speed;
	float angle;
	float gravity;
	float radius;
	bool fire;
	int count;
};


//=============================================================
//	## bullet ## (공용총알 - 너희들이 만들면 된다)
//=============================================================
class bullet : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	const char* _imageName;		//총알 이미지 이름(키값)
	float _range;				//총알 사거리
	int _bulletMax;				//총알 최대갯수
	bool _isFrameImg;			//프레임 이미지냐?

public:
	HRESULT init(const char* imageName, int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y, float angle, float speed);
	//총알무브
	void move();

	//총알벡터 가져오기
	vector<tagBullet> getVBullet() { return _vBullet; }

	//총알 삭제
	void removeBullet(int index);

	bullet() {}
	~bullet() {}
};

//=============================================================
//	## missile ## (missile[0] -> 배열처럼 미리 장전해두고 총알발사)
//=============================================================
class missile : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();

	missile() {}
	~missile() {}
};

//=============================================================
//	## bomb ## (폭탄처럼 한발씩 발사하면서 생성하고 자동삭제)
//=============================================================
class bomb : public gameNode
{
private:
	//총알 구조체를 담을 벡터, 반복자
	vector<tagBullet> _vBullet;
	vector<tagBullet>::iterator _viBullet;

private:
	float _range;		//총알 사거리
	int _bulletMax;		//총알 최대갯수

public:
	HRESULT init(int bulletMax, float range);
	void release();
	void update();
	void render();

	//총알발사
	void fire(float x, float y);
	//총알무브
	void move();

	//총알벡터 가져오기
	vector<tagBullet> getVBullet() { return _vBullet; }

	//총알 삭제
	void removeBomb(int index);

	bomb() {}
	~bomb() {}
};

