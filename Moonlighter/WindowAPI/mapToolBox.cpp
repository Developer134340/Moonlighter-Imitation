#include "stdafx.h"
#include "mapToolBox.h"


HRESULT mapToolBox::init()
{
	_toolBoxRect = RectMake(WINSIZEX - 470, WINSIZEY - 450, 420, 420);		//모든 좌표의 기준
	_movingVector = { 0,0 };
	_ptPos = { 0,0 };
	_toolBoxPosBefore = { 0,0 };
	_isSelectTileOn = false;
	_count = 0;
	_isBossPlaced = false;
	_bossOn = false;

	_minimizeRect = RectMake(_toolBoxRect.left + 340, _toolBoxRect.top, 80, 30);
	_moveRect = RectMake(_toolBoxRect.left + 250, _toolBoxRect.top, 80, 30);
	_openButton = RectMake(_toolBoxRect.left + 200, _toolBoxRect.top + 230, 80, 30);

	_saveButton = RectMake(_toolBoxRect.left + 20, _toolBoxRect.top + 380, 100, 30);
	_loadButton = RectMake(_toolBoxRect.left + 160, _toolBoxRect.top + 380, 100, 30);
	_clearButton = RectMake(_toolBoxRect.left + 300, _toolBoxRect.top + 380, 100, 30);

	_tileButton = RectMake(_toolBoxRect.left, _toolBoxRect.top + 40, 80, 30);
	_lavaButton = RectMake(_toolBoxRect.left + 100, _toolBoxRect.top + 40, 80, 30);
	_objectButton = RectMake(_toolBoxRect.left + 200, _toolBoxRect.top + 40, 80, 30);
	_enemyButton = RectMake(_toolBoxRect.left + 300, _toolBoxRect.top + 40, 80, 30);

	_isOnMapToolBox = false;
	_buttonOn = TILE_BUTTON;
	
	for (int i = 0; i < 6; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			_tileRect[j][i] = RectMake(_toolBoxRect.left + 10 + 49*j, _toolBoxRect.top + 80 + 49 * i, 49, 49);
		}
	}

	sprintf(_saveText, "SAVE");
	sprintf(_loadText, "LOAD");
	sprintf(_clearText, "CLEAR");

	_selectTile.frameX = 0;
	_selectTile.frameY = 0;
	_selectTile.objectType = TERRAIN;
	_selectTile.pos = { 0,0 };
	_selectTile.rc = { 0, 0, 0, 0 };
	
	ZeroMemory(_lavaRect, sizeof(RECT) * 35);

	_toolBoxImage = IMAGEMANAGER->findImage("툴박스");
	_toolBoxImage->setFrameX(0);
	_toolBoxImage->setFrameY(0);

	_openImage = IMAGEMANAGER->findImage("OPEN");
	_moveImage = IMAGEMANAGER->findImage("이동");
	_minimizeImage = IMAGEMANAGER->findImage("최소화");

	_tileImage = IMAGEMANAGER->findImage("TILE");
	_lavaImage = IMAGEMANAGER->findImage("LAVA");
	_objectImage = IMAGEMANAGER->findImage("OBJECT");
	_enemyImage = IMAGEMANAGER->findImage("ENEMY");
	_saveImage = IMAGEMANAGER->findImage("SAVE");
	_loadImage = IMAGEMANAGER->findImage("LOAD");
	_clearImage = IMAGEMANAGER->findImage("CLEAR");

	_defaultTileSelectImage = IMAGEMANAGER->findImage("사막바닥타일");
	_laveTileSelctImage = IMAGEMANAGER->findImage("사막용암타일");
	_intersectObjectSelectImage = IMAGEMANAGER->findImage("상호작용오브젝트");
	_unbreakableSelectImage = IMAGEMANAGER->findImage("안부서지는오브젝트");
	_enemySelectImage = IMAGEMANAGER->findImage("에너미타일");

	toolBoxIndex = 0;
	_minimize = false;

	return S_OK;
}

void mapToolBox::release()
{
}

void mapToolBox::update()
{
	_count++;

	if (_minimize == false)
	{
		if (_count % 5 == 0)
		{
			toolBoxIndex++;
			if (toolBoxIndex > 10)
			{
				toolBoxIndex = 10;
			}
		}
	}
	else
	{
		if (_count % 5 == 0)
		{
			toolBoxIndex--;
			if (toolBoxIndex < 0)
			{
				toolBoxIndex = 0;
			}
		}
	}

	_toolBoxImage->setFrameX(toolBoxIndex);

	if (PtInRect(&_moveRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_ptPos = _ptMouse;
		_toolBoxPosBefore = PointMake(_toolBoxRect.left, _toolBoxRect.top);
	}

	if (PtInRect(&_moveRect, _ptMouse) && KEYMANAGER->isStayKeyDown(VK_LBUTTON))
	{
		_movingVector.x = _ptMouse.x - _ptPos.x;
		_movingVector.y = _ptMouse.y - _ptPos.y;

		_toolBoxRect = RectMake(_toolBoxPosBefore.x + _movingVector.x, _toolBoxPosBefore.y + _movingVector.y, 420, 420);
	}
	if (PtInRect(&_openButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		_minimize = false;
	}

	//===========================================최소화 품======

	if (_minimize == false)
	{
		if (PtInRect(&_toolBoxRect, _ptMouse))
		{
			_isOnMapToolBox = true;
		}
		else
		{
			_isOnMapToolBox = false;
		}


		//==================================SELECT TILE 설정====================

		if (_isSelectTileOn)
		{
			if (_buttonOn == OBJECT_BUTTON)
			{
				if (_selectTile.objectType == CAMP)
				{
					_selectTile.pos = PointMake(_ptMouse.x, _ptMouse.y);
					_selectTile.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y+40, 256, 208);
				}
				else if (_selectTile.objectType == POND)
				{
					_selectTile.pos = PointMake(_ptMouse.x, _ptMouse.y);
					_selectTile.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 360, 376);
				}
				else
				{
					_selectTile.pos = PointMake(_ptMouse.x - 24, _ptMouse.y - 50);
					_selectTile.rc = RectMake(_selectTile.pos.x, _selectTile.pos.y + 39, 49, 49);
				}
			}
			else
			{
				_selectTile.pos = PointMake(_ptMouse.x - 24, _ptMouse.y - 24);
				_selectTile.rc = RectMake(_selectTile.pos.x, _selectTile.pos.y, 49, 49);
			}

			if (KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_isSelectTileOn = false;
			}
		}

		//=========================================================================

		_saveButton = RectMake(_toolBoxRect.left + 20, _toolBoxRect.top + 380, 100, 30);
		_loadButton = RectMake(_toolBoxRect.left + 160, _toolBoxRect.top + 380, 100, 30);
		_clearButton = RectMake(_toolBoxRect.left + 300, _toolBoxRect.top + 380, 100, 30);

		_tileButton = RectMake(_toolBoxRect.left + 20, _toolBoxRect.top + 40, 80, 30);
		_lavaButton = RectMake(_toolBoxRect.left + 120, _toolBoxRect.top + 40, 80, 30);
		_objectButton = RectMake(_toolBoxRect.left + 220, _toolBoxRect.top + 40, 80, 30);
		_enemyButton = RectMake(_toolBoxRect.left + 320, _toolBoxRect.top + 40, 80, 30);

		_minimizeRect = RectMake(_toolBoxRect.left + 340, _toolBoxRect.top, 80, 30);
		_moveRect = RectMake(_toolBoxRect.left + 250, _toolBoxRect.top, 80, 30);

		if (PtInRect(&_tileButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buttonOn = TILE_BUTTON;
		}
		if (PtInRect(&_lavaButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buttonOn = LAVA_BUTTON;
		}
		if (PtInRect(&_objectButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buttonOn = OBJECT_BUTTON;
		}
		if (PtInRect(&_enemyButton, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_buttonOn = ENEMY_BUTTON;
		}
		if (PtInRect(&_minimizeRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_minimize = true;
		}

		//==================================== TILE BUTTON ON ==============================
		if (_buttonOn == TILE_BUTTON)
		{

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					_tileRect[j][i] = RectMake(_toolBoxRect.left + 10 + 49 * j, _toolBoxRect.top + 80 + 49 * i, 49, 49);
				}
			}

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					if (PtInRect(&_tileRect[j][i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_isSelectTileOn = true;
						_selectTile.frameX = j;
						_selectTile.frameY = i;

						if (j == 0 && i >= 2 && i <= 5)
						{
							_selectTile.objectType = HOLE;
						}
						else if (j == 1 && i == 0)
						{
							_selectTile.objectType = FALLING;
						}
						else
						{
							_selectTile.objectType = TERRAIN;
						}

					}
				}
			}
		}

		//=================================== TILE BUTTON END ==================================
		//=================================== LAVA BUTTON ON ===================================
		if (_buttonOn == LAVA_BUTTON)
		{

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					_lavaRect[j][i] = RectMake(_toolBoxRect.left + 10 + 49 * j, _toolBoxRect.top + 80 + 49 * i, 49, 49);
				}
			}

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					if (PtInRect(&_lavaRect[j][i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_isSelectTileOn = true;
						_selectTile.frameX = j;
						_selectTile.frameY = i;

						if ((i == 0 && j >= 0 && j <= 4) || (i == 0 && j == 6) ||
							(i == 1 && j >= 2 && j <= 6) || (i == 2 && j == 3) || (j == 2 && j >= 5 && j <= 6) ||
							(i == 3 && j == 3) || (i == 3 && j >= 5 && j <= 6))
						{
							_selectTile.objectType = LAVA;
						}
						else
						{
							_selectTile.objectType = NOT_LAVA;
						}

					}
				}
			}

		}
		//=================================== LAVA BUTTON END ==================================
		//=================================== OBJECT BUTTON ON ===================================
		if (_buttonOn == OBJECT_BUTTON)
		{

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					_objectRect[j][i] = RectMake(_toolBoxRect.left + 10 + 49 * j, _toolBoxRect.top + 80 + 88 * i, 49, 88);
				}
			}

			for (int i = 0; i < 3; i++)
			{
				_newObjectRect[0][i] = RectMake(_toolBoxRect.left + 10 + 49 *6 + 10, _toolBoxRect.top + 80 + 88 * i, 90, 88);
			}

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					if (PtInRect(&_objectRect[j][i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_isSelectTileOn = true;
						_selectTile.frameX = j;
						_selectTile.frameY = i;

						if (i==2)
						{
							_selectTile.objectType = BREAKBLE;
						}
						else
						{
							_selectTile.objectType = UNBREAKBLE;
						}

					}
				}
			}

			for (int i = 0; i < 3; i++)
			{
				if (PtInRect(&_newObjectRect[0][i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
				{
					_isSelectTileOn = true;
					_selectTile.frameX = 0;
					_selectTile.frameY = i;

					if (i == 0)
					{
						_selectTile.objectType = DOOR;
					}
					else if (i == 1)
					{
						_selectTile.objectType = CAMP;
						_selectTile.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 256, 208);
					}
					else if (i == 2)
					{
						_selectTile.objectType = POND;
						_selectTile.rc = RectMakeCenter(_ptMouse.x, _ptMouse.y, 360, 376);
					}

				}
			}

		}
		//=================================== OBJECT BUTTON END ==================================
		//=================================== ENEMY BUTTON ON ===================================
		if (_buttonOn == ENEMY_BUTTON)
		{

			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					_enemyRect[j][i] = RectMake(_toolBoxRect.left + 10 + 57 * j, _toolBoxRect.top + 80 + 87 * i, 57, 87);
				}
			}

			_bossRect = RectMake(_toolBoxRect.left + 10, _toolBoxRect.top + 200, 100, 70);

			if (!_isBossPlaced && PtInRect(&_bossRect, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				_bossOn = true;
				setIsSelectTileOnFalse();
			}

			if (_bossOn && KEYMANAGER->isOnceKeyDown(VK_RBUTTON))
			{
				_bossOn = false;
			}

			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 5; j++)
				{
					if (PtInRect(&_enemyRect[j][i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
					{
						_isSelectTileOn = true;
						_selectTile.frameX = j;
						_selectTile.frameY = i;

						if (j == 4)
						{
							_selectTile.objectType = NONE;
						}
						else
						{
							_selectTile.objectType = ENEMY;
						}
					}
				}
			}

		}
		//=================================== ENEMY BUTTON END ==================================
	}
	else
	{
	_openButton = RectMake(_toolBoxRect.left + 150, _toolBoxRect.top + 170, 80, 30);
	_moveRect = RectMake(_toolBoxRect.left + 150, _toolBoxRect.top + 130, 80, 30);
	}


	
}

void mapToolBox::render()
{
	_toolBoxImage->frameRender(getMemDC(), _toolBoxRect.left - 50, _toolBoxRect.top - 70);

	if (toolBoxIndex == 0) 
	{
		_openImage->render(getMemDC(), _openButton.left, _openButton.top);
		_moveImage->render(getMemDC(), _moveRect.left, _moveRect.top);

	}
	else if(toolBoxIndex == 10)
	{
		_minimizeImage->render(getMemDC(), _minimizeRect.left, _minimizeRect.top);
		_moveImage->render(getMemDC(), _moveRect.left, _moveRect.top);

		if (KEYMANAGER->isToggleKey('P'))
		{
			FrameRect(getMemDC(), _toolBoxRect, RGB(0, 0, 0));
		}

		//===========================================버튼에 따른 타일 출력========================

		if (_buttonOn == TILE_BUTTON)
		{
			IMAGEMANAGER->findImage("사막바닥타일")->render(getMemDC(), _tileRect[0][0].left, _tileRect[0][0].top);

			for (int i = 0; i < 6; i++)
			{
				for (int j = 0; j < 8; j++)
				{
					FrameRect(getMemDC(), _tileRect[j][i], RGB(0, 0, 0));
				}
			}
		}
		if (_buttonOn == LAVA_BUTTON)
		{
			IMAGEMANAGER->findImage("사막용암타일")->render(getMemDC(), _lavaRect[0][0].left, _lavaRect[0][0].top);

			for (int i = 0; i < 5; i++)
			{
				for (int j = 0; j < 7; j++)
				{
					FrameRect(getMemDC(), _lavaRect[j][i], RGB(0, 0, 0));
				}
			}
		}
		if (_buttonOn == OBJECT_BUTTON)
		{
			IMAGEMANAGER->findImage("안부서지는오브젝트")->render(getMemDC(), _objectRect[0][0].left, _objectRect[0][0].top);
			IMAGEMANAGER->findImage("상호작용오브젝트")->render(getMemDC(), _newObjectRect[0][0].left, _newObjectRect[0][0].top);

			for (int i = 0; i < 3; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					FrameRect(getMemDC(), _objectRect[j][i], RGB(0, 0, 0));
				}
			}
			for (int i = 0; i < 3; i++)
			{
				FrameRect(getMemDC(), _newObjectRect[0][i], RGB(0, 0, 0));
			}
		}
		if (_buttonOn == ENEMY_BUTTON)
		{
			IMAGEMANAGER->findImage("에너미타일")->render(getMemDC(), _enemyRect[0][0].left, _enemyRect[0][0].top);

			for (int i = 0; i < 1; i++)
			{
				for (int j = 0; j < 6; j++)
				{
					FrameRect(getMemDC(), _enemyRect[j][i], RGB(0, 0, 0));
				}
			}

			IMAGEMANAGER->findImage("보스버튼")->render(getMemDC(), _bossRect.left, _bossRect.top);
			FrameRect(getMemDC(), _bossRect, RGB(0, 0, 0));
		}

		_tileImage->render(getMemDC(), _tileButton.left, _tileButton.top);
		_lavaImage->render(getMemDC(), _lavaButton.left, _lavaButton.top);
		_objectImage->render(getMemDC(), _objectButton.left, _objectButton.top);
		_enemyImage->render(getMemDC(), _enemyButton.left, _enemyButton.top);

		_saveImage->render(getMemDC(), _saveButton.left, _saveButton.top);
		_loadImage->render(getMemDC(), _loadButton.left, _loadButton.top);
		_clearImage->render(getMemDC(), _clearButton.left, _clearButton.top);

		if (_isSelectTileOn)
		{
			if (_buttonOn == TILE_BUTTON)
			{
				_defaultTileSelectImage->frameRender(getMemDC(), _selectTile.pos.x, _selectTile.pos.y, _selectTile.frameX, _selectTile.frameY);
			}
			if (_buttonOn == LAVA_BUTTON)
			{
				_laveTileSelctImage->frameRender(getMemDC(), _selectTile.pos.x, _selectTile.pos.y, _selectTile.frameX, _selectTile.frameY);
			}
			if (_buttonOn == OBJECT_BUTTON)
			{
				if (_selectTile.objectType == DOOR)
				{
					_intersectObjectSelectImage->frameRender(getMemDC(), _selectTile.pos.x, _selectTile.pos.y, _selectTile.frameX, _selectTile.frameY);
				}
				else if (_selectTile.objectType == POND)
				{
					_intersectObjectSelectImage->scaleFrameRender(getMemDC(), _selectTile.pos.x-180, _selectTile.pos.y-188, _selectTile.frameX, _selectTile.frameY, 4.13f);
				}
				else if (_selectTile.objectType == CAMP)
				{
					_intersectObjectSelectImage->scaleFrameRender(getMemDC(), _selectTile.pos.x-128, _selectTile.pos.y-104, _selectTile.frameX, _selectTile.frameY, 2.84f);
				}
				else
				{
					_unbreakableSelectImage->frameRender(getMemDC(), _selectTile.pos.x, _selectTile.pos.y, _selectTile.frameX, _selectTile.frameY);
				}
			}
			if (_buttonOn == ENEMY_BUTTON)
			{
				_enemySelectImage->frameRender(getMemDC(), _selectTile.pos.x, _selectTile.pos.y, _selectTile.frameX, _selectTile.frameY);
			}
		}

		if (!_isBossPlaced && _bossOn)
		{
			IMAGEMANAGER->findImage("보스방선택")->render(getMemDC(), WINSIZEX / 2 - 174, WINSIZEY / 2 - 21);
		}

	}
	else {}

}
