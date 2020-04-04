#pragma once
#include "gameNode.h"
class item :
	public gameNode
{
protected:
	const char* _name;
	//image* _image;
	string _type;
	int _cost;
	RECT _rc;

public:

	HRESULT init(const char* key);
	void release();
	void update();
	void render();

	const char* getItemKey() { return _name; }
	//image* getItemImage() { return _image; }
	string getItemType() { return _type; }
	int getItemCost() { return _cost; }

	void setItemPos(POINT _pos) { _rc = RectMake(_pos.x, _pos.y, 52, 52); }
	RECT getItemRc() {	return _rc;	}

	item() {}
	~item() {}
};