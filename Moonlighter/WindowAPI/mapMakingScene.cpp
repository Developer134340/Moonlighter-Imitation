#include "stdafx.h"
#include "mapMakingScene.h"

HRESULT mapMakingScene::init()
{
	_mapToolBox = new mapToolBox;
	_mapToolBox->init();

	_useMap = new useMap;
	_useMap->init();

	_maxMapIndex = 0;
	_title = RectMake(20, 20, 120, 45);

	_canMakeMap = true;
	_canMakeBoss = true;

	_arrow[0] = RectMakeCenter(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(0).rc.left + 78, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(0).rc.top + 78-20, 70, 70);
	_arrow[1] = RectMakeCenter(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(1).rc.left + 78-24, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(1).rc.top + 78, 70, 70);
	_arrow[2] = RectMakeCenter(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(2).rc.left + 78, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(2).rc.top + 78-20, 70, 70);
	_arrow[3] = RectMakeCenter(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(3).rc.left + 78, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(3).rc.top + 78, 70, 70);

	_count = _saveCount = 0;

	for (int i = 0; i < 4; i++)
	{
		_arrowOn[i] = false;
	}

	return S_OK;

}

void mapMakingScene::release()
{
	_mapToolBox->release();
	_useMap->release();
}

void mapMakingScene::update()
{
	_count++;
	_useMap->update();
	_mapToolBox->update();
	if (PtInRect(&_title, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		SCENEMANAGER->loadScene("타이틀");
	}

	//맵 이동하기


	for (int i = 0; i < 4; i++)
	{
		if (_arrowOn[i] && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed && PtInRect(&_arrow[i], _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).isBossRoom) {}
			else
			{
				_useMap->setRoomIndex(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).roomIndex);
			}
		}

		if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed)
		{
			_arrowOn[i] = true;
		}
		else
		{
			_arrowOn[i] = false;
		}
	}

	//맵 이동하기 종료


	//========================================타일 놓기==============================================
	for (int i = 0; i < MAXTILEX * MAXTILEY; i++)
	{
		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == TILE_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON))
		{
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDefaultTileFrameX(i, _mapToolBox->getSelectTile().frameX);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDefaultTileFrameY(i, _mapToolBox->getSelectTile().frameY);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDefaultTileType(i, _mapToolBox->getSelectTile().objectType);
		}

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == LAVA_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType != HOLE)
		{
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setLavaTileFrameX(i, _mapToolBox->getSelectTile().frameX);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setLavaTileFrameY(i, _mapToolBox->getSelectTile().frameY);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setLavaTileType(i, _mapToolBox->getSelectTile().objectType);
		}

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == OBJECT_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType != HOLE && (_mapToolBox->getSelectTile().objectType == BREAKBLE || _mapToolBox->getSelectTile().objectType == UNBREAKBLE))
		{
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileFrameX(i, _mapToolBox->getSelectTile().frameX);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileFrameY(i, _mapToolBox->getSelectTile().frameY);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileType(i, _mapToolBox->getSelectTile().objectType);
		}
		//==================큰 오브젝트 놓기 ===============

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == OBJECT_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType != HOLE && _mapToolBox->getSelectTile().objectType == CAMP)
		{
			for (int j = 0; j < MAXTILEX * MAXTILEY; j++)
			{
				if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(i).objectType == CAMP)
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileType(j, NONE);
				}

				RECT temp;
				if (IntersectRect(&temp, _mapToolBox->getSelectTileRectAddress(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(j)))// && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(i).objectType != NONE)
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileType(j, CAMP);
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setCampIndex(i);
				}
			}
		}

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == OBJECT_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType != HOLE && _mapToolBox->getSelectTile().objectType == POND)
		{
			for (int j = 0; j < MAXTILEX * MAXTILEY; j++)
			{
				if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(j).objectType == POND)
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileType(j, NONE);
				}

				RECT temp;
				if (getDistance(_ptMouse.x, _ptMouse.y, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(j).rc.left, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(j).rc.top) < 191)
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setObjectTileType(j, POND);
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setPondIndex(i);
				}
			}
		}

		//================큰 오브젝트 놓기 종료==============

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == ENEMY_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTileRectAddress(i), _ptMouse)
			&& KEYMANAGER->isStayKeyDown(VK_LBUTTON) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType != HOLE)
		{
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setEnemyTileFrameX(i, _mapToolBox->getSelectTile().frameX);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setEnemyTileFrameY(i, _mapToolBox->getSelectTile().frameY);
			_useMap->getUseMapRoom(_useMap->getRoomIndex())->setEnemyTileType(i, _mapToolBox->getSelectTile().objectType);
		}
	}

	//================================타일 놓기 종료=======================================

	for (int i = 0; i < 4; i++)
	{
		//===================문 놓기====================

		if (!_canMakeMap)
		{
			if (_count - _saveCount > 50)
			{
				_canMakeMap = true;
			}
		}

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == OBJECT_BUTTON && _mapToolBox->getIsSelectTileOn() && PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _ptMouse)
			&& !_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed && KEYMANAGER->isOnceKeyDown(VK_LBUTTON) && _mapToolBox->getSelectTile().objectType == DOOR)
		{
			if (_maxMapIndex > 8)
			{
				_canMakeMap = false;
				_saveCount = _count;
			}
			else
			{
				if (_maxMapIndex == 0)
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorTileIsPlaced(i, true);
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorRoomIndex(i, _useMap->getRoomIndex() + 1);

					if (i >= 2)
					{
						_useMap->getUseMapRoom(_useMap->getRoomIndex() + 1)->setDoorTileIsPlaced(i - 2, true);
						_useMap->getUseMapRoom(_useMap->getRoomIndex() + 1)->setDoorRoomIndex(i - 2, _useMap->getRoomIndex());
					}
					else
					{
						_useMap->getUseMapRoom(_useMap->getRoomIndex() + 1)->setDoorTileIsPlaced(i + 2, true);
						_useMap->getUseMapRoom(_useMap->getRoomIndex() + 1)->setDoorRoomIndex(i + 2, _useMap->getRoomIndex());
					}

					_maxMapIndex += 1;
				}
				else
				{
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorTileIsPlaced(i, true);
					_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorRoomIndex(i, _maxMapIndex + 1);

					if (i >= 2)
					{
						_useMap->getUseMapRoom(_maxMapIndex + 1)->setDoorTileIsPlaced(i - 2, true);
						_useMap->getUseMapRoom(_maxMapIndex + 1)->setDoorRoomIndex(i - 2, _useMap->getRoomIndex());
					}
					else
					{
						_useMap->getUseMapRoom(_maxMapIndex + 1)->setDoorTileIsPlaced(i + 2, true);
						_useMap->getUseMapRoom(_maxMapIndex + 1)->setDoorRoomIndex(i + 2, _useMap->getRoomIndex());
					}
					_maxMapIndex += 1;
				}
			}
		}

		//==================문 놓기 종료===================
		//==================보스 방 만들기==================

		if (!_mapToolBox->getIsOnMapToolBox() && _mapToolBox->getButtonOn() == ENEMY_BUTTON && _mapToolBox->getBossOn()
			&& PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _ptMouse)
			&& !_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_saveCount = _count;

			if (_mapToolBox->getIsBossPlaced())
			{
				_canMakeBoss = false;
			}
			else
			{
				_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorTileIsPlaced(i, true);
				_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorRoomIndex(i, 0);
				_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorIsBossRoom(i, true);
				_mapToolBox->setIsBossPlaced(true);
			}
		}

		//===============보스 방 만들기 종료
	}

	if (!_canMakeBoss && (_count - _saveCount > 50))
	{
		_canMakeBoss = true;
	}

	//==================================세이브, 로드, 클리어======================//
	if (PtInRect(&_mapToolBox->getSaveRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		this->save();
	}

	if (PtInRect(&_mapToolBox->getLoadRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		this->load();
	}

	if (PtInRect(&_mapToolBox->getClearRect(), _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
	{
		this->clear();
	}
	//=====================================세이브, 로드, 클리어 종료==================//
	
	sprintf(test2, "roomIndex : %d", _useMap->getRoomIndex());

}

void mapMakingScene::render()
{
	_useMap->render();

	if (KEYMANAGER->isToggleKey('I'))
	{
		for (int i = 0; i < MAXTILEX * MAXTILEY; i++)
		{
			if (_mapToolBox->getButtonOn() == TILE_BUTTON)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(i), _ptMouse))
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).rc, RGB(0, 255, 0));
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).rc, RGB(0, 0, 0));
				}
			}
			if (_mapToolBox->getButtonOn() == LAVA_BUTTON)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTileRectAddress(i), _ptMouse))
				{
					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType == HOLE)
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTile(i).rc, RGB(255, 0, 0));
					}
					else
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTile(i).rc, RGB(0, 255, 0));
					}
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTile(i).rc, RGB(0, 0, 0));
				}
			}
			if (_mapToolBox->getButtonOn() == OBJECT_BUTTON)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(i), _ptMouse))
				{
					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType == HOLE)
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(i).rc, RGB(255, 0, 0));
					}
					else
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(i).rc, RGB(0, 255, 0));
					}
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(i).rc, RGB(0, 0, 0));
				}
			}
			if (_mapToolBox->getButtonOn() == ENEMY_BUTTON)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTileRectAddress(i), _ptMouse))
				{
					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(i).objectType == HOLE)
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(i).rc, RGB(255, 0, 0));
					}
					else
					{
						FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(i).rc, RGB(0, 255, 0));
					}
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(i).rc, RGB(0, 0, 0));
				}
			}
		}

		//============================================문 렉트 출력========================================

		if (_mapToolBox->getButtonOn() == OBJECT_BUTTON)
		{
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _ptMouse))
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).rc, RGB(0, 255, 0));
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).rc, RGB(0, 0, 0));
				}
			}
		}

		if (_mapToolBox->getBossOn() && _mapToolBox->getButtonOn() == ENEMY_BUTTON)
		{
			for (int i = 0; i < 4; i++)
			{
				if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _ptMouse))
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).rc, RGB(0, 255, 0));
				}
				else
				{
					FrameRect(getMemDC(), _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).rc, RGB(0, 0, 0));
				}
			}
		}

		FrameRect(getMemDC(), _mapToolBox->getSelectTile().rc, RGB(255, 100, 100));

		for (int i = 0; i < 4; i++)
		{
			FrameRect(getMemDC(), _arrow[i], RGB(0, 0, 0));
		}
	}

	for (int i = 0; i < 4; i++)
	{
		if (PtInRect(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _ptMouse) && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed)
		{
			switch (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).doorDirection)
			{
			case 1:
				IMAGEMANAGER->findImage("화살표")->frameRender(getMemDC(), _arrow[i].left, _arrow[i].top, 0, 0);
				break;
			case 2:
				IMAGEMANAGER->findImage("화살표")->frameRender(getMemDC(), _arrow[i].left, _arrow[i].top, 1, 0);
				break;
			case 3:
				IMAGEMANAGER->findImage("화살표")->frameRender(getMemDC(), _arrow[i].left, _arrow[i].top, 2, 0);
				break;
			case 4:
				IMAGEMANAGER->findImage("화살표")->frameRender(getMemDC(), _arrow[i].left, _arrow[i].top, 3, 0);
				break;
			}
		}
	}

	if (!_canMakeMap)
	{
		IMAGEMANAGER->findImage("맵생성불가")->render(getMemDC(), WINSIZEX / 2 - 193, WINSIZEY / 2 - 25);
	}

	if (!_canMakeBoss)
	{
		IMAGEMANAGER->findImage("보스하나")->render(getMemDC(), WINSIZEX / 2 - 174, WINSIZEY / 2 - 21);
	}

	_mapToolBox->render();

	IMAGEMANAGER->findImage("타이틀")->render(getMemDC(), _title.left, _title.top);

	TextOut(getMemDC(), 0, 120, test2, lstrlen(test2));
}


void mapMakingScene::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("save.map", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _useMap, sizeof(useMap), &write, NULL);
	CloseHandle(file);

}

void mapMakingScene::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _useMap, sizeof(useMap), &read, NULL);
	CloseHandle(file);

}

void mapMakingScene::clear()
{
	this->init();
}
