#pragma once
#include "gameNode.h"

class titleScene :
	public gameNode
{
	RECT _camera;
	
	int _count;
	int _frameIndex;
	int _doorLeftIndex;
	int _doorRightIndex;
	int _doorLogX;

	int _alpha;

	bool _jOn;

	RECT _button[4];

	int _titleSelect;


public:

	HRESULT init();
	void release();
	void update();
	void render();

	titleScene() {}
	~titleScene() {}
};

