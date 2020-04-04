#pragma once
#include "gameNode.h"
#include "tileNode.h"

class mapToolBox :
	public gameNode
{
	RECT _toolBoxRect; //모든 좌표를 이 툴박스 기준으로 잡는다
	RECT _tileRect[8][6];
	RECT _lavaRect[7][5];
	RECT _objectRect[6][3];
	RECT _enemyRect[6][1];
	RECT _newObjectRect[1][3];
	RECT _bossRect;

	bool _bossOn;
	bool _isBossPlaced;

	RECT _minimizeRect;
	RECT _moveRect;

	POINT _movingVector;
	POINT _toolBoxPosBefore;

	POINT _ptPos; 
	
	bool _isSelectTileOn;
	tagTile _selectTile;

	RECT _saveButton;
	RECT _loadButton;
	RECT _clearButton;

	RECT _tileButton;
	RECT _lavaButton;
	RECT _objectButton;
	RECT _enemyButton;

	RECT _openButton;

	char _saveText[10];
	char _loadText[10];
	char _clearText[10];

	bool _isOnMapToolBox;
	bool _minimize;
	int _count;

	BUTTON _buttonOn;

	int toolBoxIndex;

	//=================================이미지 변수 수정================================

	image* _toolBoxImage;
	image* _openImage;
	image* _moveImage;
	image* _minimizeImage;

	image* _tileImage;
	image* _lavaImage;
	image* _objectImage;
	image* _enemyImage;
	image* _saveImage;
	image* _loadImage;
	image* _clearImage;

	image* _defaultTileSelectImage;
	image* _laveTileSelctImage;
	image* _intersectObjectSelectImage;
	image* _unbreakableSelectImage;
	image* _enemySelectImage;



public:

	HRESULT init();
	void release();
	void update();
	void render();

	bool getIsSelectTileOn() { return _isSelectTileOn; }
	void setIsSelectTileOnFalse() { _isSelectTileOn = false; }
	tagTile getSelectTile() { return _selectTile; }
	RECT* getSelectTileRectAddress() { return &_selectTile.rc; }

	RECT getSaveRect() { return _saveButton; }
	RECT getLoadRect() { return _loadButton; }
	RECT getClearRect() { return _clearButton; }

	bool getIsOnMapToolBox() { return _isOnMapToolBox; }
	bool getBossOn() { return _bossOn; }

	void setIsBossPlaced(bool tempBool) { _isBossPlaced = tempBool; }
	bool getIsBossPlaced() { return _isBossPlaced; }

	BUTTON getButtonOn() { return _buttonOn; }

	mapToolBox() {}
	~mapToolBox() {}
};

