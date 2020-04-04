#include "stdafx.h"
#include "useMapRoom.h"

HRESULT useMapRoom::init()
{
	_wholeRect = RectMake(150, 88, 980, 539);

	_campIndex = _pondIndex = -1;
	_count = 0;
	_isOnGame = false;

	for (int i = 0; i < MAXTILEY; i++)
	{
		for (int j = 0; j < MAXTILEX; j++)
		{
			_defaultTile[i*MAXTILEX + j].pos = PointMake(150 + (49 * j), 90 + (49 * i));
			_defaultTile[i*MAXTILEX + j].rc = RectMake(_defaultTile[i*MAXTILEX + j].pos.x, _defaultTile[i*MAXTILEX + j].pos.y, 49, 49);
			_defaultTile[i*MAXTILEX + j].frameX = 0;
			_defaultTile[i*MAXTILEX + j].frameY = 0;
			_defaultTile[i*MAXTILEX + j].objectType = TERRAIN;
		}
	}

	for (int i = 0; i < MAXTILEY; i++)
	{
		for (int j = 0; j < MAXTILEX; j++)
		{
			_lavaTile[i*MAXTILEX + j].pos = PointMake(150 + (49 * j), 90 + (49 * i));
			_lavaTile[i*MAXTILEX + j].rc = RectMake(_lavaTile[i*MAXTILEX + j].pos.x, _lavaTile[i*MAXTILEX + j].pos.y, 49, 49);
			_lavaTile[i*MAXTILEX + j].frameX = 6;
			_lavaTile[i*MAXTILEX + j].frameY = 4;
			_lavaTile[i*MAXTILEX + j].objectType = NONE;
		}
	}

	for (int i = 0; i < MAXTILEY; i++)
	{
		for (int j = 0; j < MAXTILEX; j++)
		{
			_objectTile[i*MAXTILEX + j].pos = PointMake(150 + (49 * j), 90 + (49 * i));
			_objectTile[i*MAXTILEX + j].rc = RectMake(_lavaTile[i*MAXTILEX + j].pos.x, _lavaTile[i*MAXTILEX + j].pos.y, 49, 49);
			_objectTile[i*MAXTILEX + j].frameX = 5;
			_objectTile[i*MAXTILEX + j].frameY = 1;
			_objectTile[i*MAXTILEX + j].objectType = NONE;
		}
	}

	for (int i = 0; i < MAXTILEY; i++)
	{
		for (int j = 0; j < MAXTILEX; j++)
		{
			_enemyTile[i*MAXTILEX + j].pos = PointMake(150 + (49 * j), 90 + (49 * i));
			_enemyTile[i*MAXTILEX + j].rc = RectMake(_lavaTile[i*MAXTILEX + j].pos.x, _lavaTile[i*MAXTILEX + j].pos.y, 49, 49);
			_enemyTile[i*MAXTILEX + j].frameX = 6;
			_enemyTile[i*MAXTILEX + j].frameY = 1;
			_enemyTile[i*MAXTILEX + j].objectType = NONE;
		}
	}

	_doorTile[0].pos = { 562, -24 };				//UP
	_doorTile[1].pos = { 34, 282 };					//LEFT
	_doorTile[2].pos = { 562, WINSIZEY-116 + 24};	//DOWN
	_doorTile[3].pos = { WINSIZEX-116 - 34, 282 };	//RIGHT

	_doorTile[0].rc = RectMake(_doorTile[0].pos.x, _doorTile[0].pos.y, 156, 116);
	_doorTile[1].rc = RectMake(_doorTile[1].pos.x, _doorTile[1].pos.y, 116, 156);
	_doorTile[2].rc = RectMake(_doorTile[2].pos.x, _doorTile[2].pos.y, 156, 116);
	_doorTile[3].rc = RectMake(_doorTile[3].pos.x, _doorTile[3].pos.y, 116, 156);

	_doorTile[0].doorDirection = DOOR_UP;
	_doorTile[1].doorDirection = DOOR_LEFT;
	_doorTile[2].doorDirection = DOOR_DOWN;
	_doorTile[3].doorDirection = DOOR_RIGHT;

	_doorTile[0].frameX = 23;
	_doorTile[1].frameX = 23;
	_doorTile[2].frameX = 23;
	_doorTile[3].frameX = 23;

	_doorTile[0].frameY = 0;
	_doorTile[1].frameY = 2;
	_doorTile[2].frameY = 4;
	_doorTile[3].frameY = 6;

	_doorTile[0].doorDirection = DOOR_UP;
	_doorTile[1].doorDirection = DOOR_LEFT;
	_doorTile[2].doorDirection = DOOR_DOWN;
	_doorTile[3].doorDirection = DOOR_RIGHT;
	

	_wall[0] = RectMake(0, 0, WINSIZEX, 85);
	_wall[1] = RectMake(0, 0, 140, WINSIZEY);
	_wall[2] = RectMake(0, WINSIZEY-85, WINSIZEX, 85);
	_wall[3] = RectMake(WINSIZEX-140, 0, 140, WINSIZEY);


	for (int i = 0; i < 4; i++)
	{
		_doorTile[i].isOpen = false;	
		_doorTile[i].placed= false;
		_doorTile[i].isBossRoom = false;
	}

	_defaultTileImage = IMAGEMANAGER->findImage("사막바닥타일");
	_laveTileImage = IMAGEMANAGER->findImage("사막용암타일");
	_unbreakableImage = IMAGEMANAGER->findImage("안부서지는오브젝트");
	_enemyImage = IMAGEMANAGER->findImage("에너미타일");

	_campImage = IMAGEMANAGER->findImage("캠프");
	_healingpoolImage = IMAGEMANAGER->findImage("회복샘");
	_doorImage = IMAGEMANAGER->findImage("문");
	_wallImage = IMAGEMANAGER->findImage("사막벽1"); 

	return S_OK;
}

void useMapRoom::release()
{
}

void useMapRoom::update()
{

	_count++;

	for (int i = 0; i < 4; i++)
	{
		if (_doorTile[i].isOpen)
		{
			switch (i)
			{
			case 0:
				_doorTile[i].frameY = 0;
				break;
			case 1:
				_doorTile[i].frameY = 2;
				break;
			case 2:
				_doorTile[i].frameY = 4;
				break;
			case 3:
				_doorTile[i].frameY = 6;
				break;
			}

			if (_count % 5 == 0)
			{

				_doorTile[i].frameX++;

				if (_doorTile[i].frameX > 23)
				{
					_doorTile[i].frameX = 23;
				}
			}
			
		}
		else if (!_doorTile[i].isOpen)
		{
			switch (i)
			{
			case 0:
				_doorTile[i].frameY = 1;
				break;
			case 1:
				_doorTile[i].frameY = 3;
				break;
			case 2:
				_doorTile[i].frameY = 5;
				break;
			case 3:
				_doorTile[i].frameY = 7;
				break;
			}

			if (_doorTile[i].frameY == 7)
			{
				if (_count % 5 == 0)
				{

					_doorTile[i].frameX--;

					if (_doorTile[i].frameX < 20)
					{
						_doorTile[i].frameX = 23;
					}
				}
			}
			else
			{
				if (_count % 5 == 0)
				{

					_doorTile[i].frameX++;

					if (_doorTile[i].frameX > 23)
					{
						_doorTile[i].frameX = 15;
					}
				}
			}

		}
	}


}

void useMapRoom::render()
{
	Rectangle(getMemDC(), _wholeRect);

	for (int i = 0; i < MAXTILEX * MAXTILEY; i++)
	{
		_defaultTileImage->frameRender(getMemDC(), _defaultTile[i].pos.x, _defaultTile[i].pos.y, _defaultTile[i].frameX, _defaultTile[i].frameY);
		_laveTileImage->frameRender(getMemDC(), _lavaTile[i].pos.x, _lavaTile[i].pos.y, _lavaTile[i].frameX, _lavaTile[i].frameY);
		_unbreakableImage->frameRender(getMemDC(), _objectTile[i].pos.x, _objectTile[i].pos.y-39, _objectTile[i].frameX, _objectTile[i].frameY);
	
		if (!_isOnGame)
		{
			_enemyImage->frameRender(getMemDC(), _enemyTile[i].pos.x - 5, _enemyTile[i].pos.y - 39, _enemyTile[i].frameX, _enemyTile[i].frameY);
		}
	}

	for (int i = 0; i < MAXTILEX * MAXTILEY; i++)
	{
		if (i == _campIndex)
		{
			_campImage->render(getMemDC(), _objectTile[i - 22].rc.left, _objectTile[i - 22].rc.top);
		}

		if (i == _pondIndex)
		{
			_healingpoolImage->frameRender(getMemDC(), _objectTile[i - 63].rc.left, _objectTile[i - 63].rc.top, 0, 0);
		}
	}

	_wallImage->render(getMemDC(), 0, 0);


	if (_doorTile[0].placed)
	{
		_doorImage->frameRender(getMemDC(), _doorTile[0].pos.x, _doorTile[0].pos.y, _doorTile[0].frameX, _doorTile[0].frameY);
	}
	else {}

	if (_doorTile[1].placed)
	{
		_doorImage->frameRender(getMemDC(), _doorTile[1].pos.x, _doorTile[1].pos.y, _doorTile[1].frameX, _doorTile[1].frameY);
	}
	else {}

	if (_doorTile[2].placed)
	{
		_doorImage->frameRender(getMemDC(), _doorTile[2].pos.x, _doorTile[2].pos.y - 40, _doorTile[2].frameX, _doorTile[2].frameY);
	}
	else {}

	if (_doorTile[3].placed)
	{
		_doorImage->frameRender(getMemDC(), _doorTile[3].pos.x - 40, _doorTile[3].pos.y, _doorTile[3].frameX, _doorTile[3].frameY);
	}
	else {}

}

void useMapRoom::unbreakableRender()
{
	for (int i = 0; i < MAXTILEX * MAXTILEY; i++)
	{
		_unbreakableImage->frameRender(getMemDC(), _objectTile[i].pos.x, _objectTile[i].pos.y - 39, _objectTile[i].frameX, _objectTile[i].frameY);
	}
}
