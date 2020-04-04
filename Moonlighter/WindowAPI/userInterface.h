#pragma once
#include "gameNode.h"
#include "inventory.h"

class userInterface :
	public gameNode
{
	inventory* _inventory;
	item* _nowEquip;

	int _nowHp;
	int _maxHp;
	float _whiteGauge;
	float _hpGauge;

	int _equipChange0;
	int _equipChange1;
	bool _changeOn;
	bool _inventoryOn;
	bool _invenAnimationOn;

	int _money;
	char _printMoney[100];
	
public:

	HRESULT init();
	void release();
	void update();
	void render();

	void setHp(int nowHp, int maxHp) { _nowHp = nowHp, _maxHp = maxHp; }
	void setInventoryOn(bool tempBool) { _inventoryOn = tempBool; }
	item* getNowEquip() { return _nowEquip; }
	inventory* getInventory() { return _inventory; }
	bool getInventoryOn() { return _inventoryOn; }
	void setInvenAnimationOn(bool tempBool) { _invenAnimationOn = tempBool; }
	bool getInvenAnimationOn() { return _invenAnimationOn; }

	int getMoney() { return _money; }
	void setMoney(int x) { _money = x; }

	userInterface() {}
	~userInterface() {}
};

