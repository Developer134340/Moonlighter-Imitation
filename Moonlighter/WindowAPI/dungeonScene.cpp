#include "stdafx.h"
#include "dungeonScene.h"

HRESULT dungeonScene::init()
{
	_useMap = new useMap;
	_useMap->init();

	_player = new player;
	_player->init({ WINSIZEX/2-50, WINSIZEY-200 });
	_player->setPlayerLocation(DUNGEON);
	_gameClear = false;

	_count = 0;

	SOUNDMANAGER->addSound("DUNGEON_BGM", "gameSound/dungeonBGM.mp3");
	SOUNDMANAGER->play("DUNGEON_BGM");
	
	_enemyManager = new enemyManager;
	_enemyManager->init();
	_isNewRoom = true;
	_isGameOn = true;

	_isBossRoom = false;

	this->useMapLoad();
	_useMap->setRoomIndex(0);

	_player->setEMLink(_enemyManager);
	_enemyManager->setPlayerLink(_player);

	_player->getUserInterface()->getInventory()->load();

	return S_OK;
}

void dungeonScene::release()
{
	_useMap->release();
	SAFE_DELETE(_player);
	_enemyManager->release();
}

void dungeonScene::update()
{
	if (_isGameOn)
	{

		_count++;
		//========================================보스맵 시작=====================================

		if (_isBossRoom)
		{

			//==================보스맵 초기화============

			if (_isNewRoom)
			{
				_player->init({ WINSIZEX / 2 - 49, WINSIZEY - 150 });
				_player->setImagePosition({ -540, 0 });
				_player->setPixelMap(IMAGEMANAGER->findImage("BOSS_BACKGROUND"));

				//			_bossWall[0] = 
				//			_bossWall[1] = { -840, -526, 94, 1558 };
				//			_bossWall[2] = 
				//			_bossWall[3] = { -840, -526, 94, 1558 };

				_enemyManager->addEnemy();
				_isNewRoom = false;
				
			}

			//=================보스맵 초기화 종료===========


			_player->setPlayerPositionBefore(_player->getPlayerPosition());
			_player->update();
			_player->camMove(IMAGEMANAGER->findImage("BOSS_BACKGROUND"));
			_enemyManager->update();
			if (_enemyManager->getEnemyVector().size())
			{
				_enemyManager->getEnemyVector()[0]->setImagePositionNow(_player->getImagePosition());
			}
			_enemyManager->playerBossAttack();

			//=======================플레이어 무브========================
			_player->setDirectionMoveUp(true);
			_player->setDirectionMoveLeft(true);
			_player->setDirectionMoveDown(true);
			_player->setDirectionMoveRight(true);

			for (int i = 0; i < 4; i++)
			{

				RECT temp;

				if (IntersectRect(&temp, &_bossWall[0], _player->getPlayerDirectionRcAddress(0)))
				{
					_player->setDirectionMoveUp(false);
					break;
				}

				if (IntersectRect(&temp, &_bossWall[1], _player->getPlayerDirectionRcAddress(1)))
				{
					_player->setDirectionMoveLeft(false);
					break;
				}

				if (IntersectRect(&temp, &_bossWall[2], _player->getPlayerDirectionRcAddress(2)))
				{
					_player->setDirectionMoveDown(false);
					break;
				}

				if (IntersectRect(&temp, &_bossWall[3], _player->getPlayerDirectionRcAddress(3)))
				{
					_player->setDirectionMoveRight(false);
					break;
				}

				for (int j = 0; j < _enemyManager->getEnemyVector().size(); j++)
				{
					if (_enemyManager->getEnemyVector()[j]->getEnemyName() == "MAGICIANPUPPET") {}
					else
					{
						if (IntersectRect(&temp, &_bossWall[0], _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(0)))
						{
							_enemyManager->getEnemyVector()[j]->setDirectionMoveUp(false);
							break;
						}

						if (IntersectRect(&temp, &_bossWall[1], _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(1)))
						{
							_enemyManager->getEnemyVector()[j]->setDirectionMoveLeft(false);
							break;
						}

						if (IntersectRect(&temp, &_bossWall[2], _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(2)))
						{
							_enemyManager->getEnemyVector()[j]->setDirectionMoveDown(false);
							break;
						}

						if (IntersectRect(&temp, &_bossWall[3], _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(3)))
						{
							_enemyManager->getEnemyVector()[j]->setDirectionMoveRight(false);
							break;
						}
					}
				}


			}

			//=====================================벽 충돌검사 종료=========================

			if (!_enemyManager->getEnemyVector().size())
			{
				_gameClear = true;
			}

			if (_gameClear)
			{
				_goToVillage = RectMakeCenter(WINSIZEX / 2 + 10, WINSIZEY / 2 + 110, 120, 45);
			}

			if (_gameClear && PtInRect(&_goToVillage, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
			{
				SCENEMANAGER->loadScene("타이틀");
				SOUNDMANAGER->stop("DUNGEON_BGM");
			}


		}//============================보스맵 종료=====================================
		else
		{
			//========================================새로운 방으로 이동시 초기화==================
			_player->update();
			_useMap->update();

			if (_isNewRoom)
			{
				_vUnbreakableTile.clear();
				_vHoleTile.clear();
				_vLavaTile.clear();
				_useMap->getUseMapRoom(_useMap->getRoomIndex())->setIsOnGame(true);

				for (int j = 0; j < MAXTILEX*MAXTILEY; j++)
				{
					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTile(j).objectType == UNBREAKBLE)
					{
						_vUnbreakableTile.push_back(j);
					}

					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTile(j).objectType == HOLE)
					{
						_vHoleTile.push_back(j);
					}

					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTile(j).objectType == LAVA)
					{
						_vLavaTile.push_back(j);
					}

					if (_enemyManager->getEnemyVector().size())
					{
						for (int i = 0; i < 4; i++)
						{
							if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).isOpen)
							{
								_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorIsOpen(i, false);
								_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorTileFrameX(i, 0);
							}
						}
					}

					//=====================================에너미 출력============================================


				//1.슬라임

					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).frameX == 0)
					{
						_enemyManager->addEnemy(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.x, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.y), 0);
					}

					//2.Patrol Golem

					else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).frameX == 1)
					{
						_enemyManager->addEnemy(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.x, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.y), 1);
					}


					//3.Mimic

					else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).frameX == 2)
					{
						_enemyManager->addEnemy(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.x, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.y), 2);
					}

					//4.Magician Puppet

					else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).frameX == 3)
					{
						_enemyManager->addEnemy(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.x, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getEnemyTile(j).pos.y), 3);
					}

					//6.boss...?

				}

				_isNewRoom = false;
			}

			//==========================================================초기화 끝================================

			//=======================플레이어 무브========================
			_player->setDirectionMoveUp(true);
			_player->setDirectionMoveLeft(true);
			_player->setDirectionMoveDown(true);
			_player->setDirectionMoveRight(true);

			_enemyManager->update();
			_enemyManager->playerEnemyAttack();

			for (int j = 0; j < _enemyManager->getEnemyVector().size(); j++)
			{
				_enemyManager->getEnemyVector()[j]->setDirectionMoveUp(true);
				_enemyManager->getEnemyVector()[j]->setDirectionMoveLeft(true);
				_enemyManager->getEnemyVector()[j]->setDirectionMoveDown(true);
				_enemyManager->getEnemyVector()[j]->setDirectionMoveRight(true);
			}

			//==============플레이어 충돌 검사============

			for (int j = 0; j < _vUnbreakableTile.size(); j++)
			{
				RECT temp;

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _player->getPlayerDirectionRcAddress(0)))
				{
					_player->setDirectionMoveUp(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _player->getPlayerDirectionRcAddress(1)))
				{
					_player->setDirectionMoveLeft(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _player->getPlayerDirectionRcAddress(2)))
				{
					_player->setDirectionMoveDown(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _player->getPlayerDirectionRcAddress(3)))
				{
					_player->setDirectionMoveRight(false);
				}

			}

			//========================에너미 충돌검사===================

			for (int i = 0; i < _enemyManager->getEnemyVector().size(); i++)
			{
				for (int j = 0; j < _vUnbreakableTile.size(); j++)
				{
					RECT temp;
			
					if (_enemyManager->getEnemyVector()[i]->getEnemyName() == "MAGICIANPUPPET") {}
					else
					{
						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(0)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveUp(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(1)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveLeft(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(2)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveDown(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getObjectTileRectAddress(_vUnbreakableTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(3)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveRight(false);
						}
					}
				}
			}

			//======================================구멍 충돌 검사==========================

						//==============플레이어 충돌 검사============

			for (int j = 0; j < _vHoleTile.size(); j++)
			{
				RECT temp;

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _player->getPlayerDirectionRcAddress(0)))
				{
					_player->setDirectionMoveUp(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _player->getPlayerDirectionRcAddress(1)))
				{
					_player->setDirectionMoveLeft(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _player->getPlayerDirectionRcAddress(2)))
				{
					_player->setDirectionMoveDown(false);
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _player->getPlayerDirectionRcAddress(3)))
				{
					_player->setDirectionMoveRight(false);
				}

			}

			//========================에너미 충돌검사===================

			for (int i = 0; i < _enemyManager->getEnemyVector().size(); i++)
			{
				for (int j = 0; j < _vHoleTile.size(); j++)
				{
					RECT temp;

					if (_enemyManager->getEnemyVector()[i]->getEnemyName() == "MAGICIANPUPPET") {}
					else
					{
						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(0)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveUp(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(1)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveLeft(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(2)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveDown(false);
						}

						if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDefaultTileRectAddress(_vHoleTile[j]), _enemyManager->getEnemyVector()[i]->getDirectionRcAddress(3)))
						{
							_enemyManager->getEnemyVector()[i]->setDirectionMoveRight(false);
						}
					}
				}
			}


			//=============================================================용암 충돌 검사========================================

			for (int j = 0; j < _vLavaTile.size(); j++)
			{
				RECT temp;

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getLavaTileRectAddress(_vLavaTile[j]), _player->getPlayerRcAddress()))
				{
					_player->setPlayerAttacked(3);
				}


			}


			if (KEYMANAGER->isOnceKeyDown('Q'))
			{
				SOUNDMANAGER->stop("DUNGEON_BGM");
				_player->getUserInterface()->getInventory()->save();
				SCENEMANAGER->loadScene("상점씬");
			}

			if (KEYMANAGER->isOnceKeyDown('C'))
			{
				SOUNDMANAGER->stop("DUNGEON_BGM");
				_player->getUserInterface()->getInventory()->save();
				SCENEMANAGER->loadScene("타이틀");
			}

			//==================================벽 충돌검사===========================



			for (int i = 0; i < 4; i++)
			{

				RECT temp;

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _player->getPlayerDirectionRcAddress(0)))
				{
					_player->setDirectionMoveUp(false);
					break;
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _player->getPlayerDirectionRcAddress(1)))
				{
					_player->setDirectionMoveLeft(false);
					break;
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _player->getPlayerDirectionRcAddress(2)))
				{
					_player->setDirectionMoveDown(false);
					break;
				}

				if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _player->getPlayerDirectionRcAddress(3)))
				{
					_player->setDirectionMoveRight(false);
					break;
				}

				for (int j = 0; j < _enemyManager->getEnemyVector().size(); j++)
				{

					if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(0)))
					{
						_enemyManager->getEnemyVector()[j]->setDirectionMoveUp(false);
						break;
					}

					if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(1)))
					{
						_enemyManager->getEnemyVector()[j]->setDirectionMoveLeft(false);
						break;
					}

					if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(2)))
					{
						_enemyManager->getEnemyVector()[j]->setDirectionMoveDown(false);
						break;
					}

					if (IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getWallTileRectAddress(i), _enemyManager->getEnemyVector()[j]->getDirectionRcAddress(3)))
					{
						_enemyManager->getEnemyVector()[j]->setDirectionMoveRight(false);
						break;
					}
				}


			}

			//=======================플레이어 무브 종료========================
			//========================문 이동하기===========================

			for (int i = 0; i < 4; i++)
			{
				RECT temp;

				if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).isOpen && _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).placed && IntersectRect(&temp, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTileRectAddress(i), _player->getPlayerRcAddress()))
				{

					if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).isBossRoom == true)
					{
						_isBossRoom = true;
						_isNewRoom = true;
					}
					else
					{
						if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).doorDirection == DOOR_UP)
						{
							_player->setPlayerPosition(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i + 2).rc.left + 50, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i + 2).rc.top - 100));
						}
						else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).doorDirection == DOOR_LEFT)
						{
							_player->setPlayerPosition(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i + 2).rc.left - 50, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i + 2).rc.top + 50));
						}
						else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).doorDirection == DOOR_DOWN)
						{
							_player->setPlayerPosition(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i - 2).rc.left + 50, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i - 2).rc.bottom + 100));
						}
						else if (_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).doorDirection == DOOR_RIGHT)
						{
							_player->setPlayerPosition(PointMake(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i - 2).rc.right + 50, _useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i - 2).rc.top + 50));
						}

						_useMap->setRoomIndex(_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).roomIndex);
						_isNewRoom = true;
					}
				}
			}

			//========================문 이동하기 종료======================
			//========================문 닫혀있다가 열기====================

			if (!_enemyManager->getEnemyVector().size())
			{
				for (int i = 0; i < 4; i++)
				{
					if (!_useMap->getUseMapRoom(_useMap->getRoomIndex())->getDoorTile(i).isOpen)
					{
						_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorIsOpen(i, true);
						_useMap->getUseMapRoom(_useMap->getRoomIndex())->setDoorTileFrameX(i, 0);
					}
				}
			}

			//========================문 열기 종료===========================
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_player->getUserInterface()->setInventoryOn(true);
			_isGameOn = false;
		}

		if (_player->getPlayerHp() <= 0)
		{
			_goToVillage = RectMakeCenter(WINSIZEX / 2+10, WINSIZEY / 2 + 110, 120, 45);
		}

		if (_player->getPlayerHp() <= 0 && PtInRect(&_goToVillage, _ptMouse) && KEYMANAGER->isOnceKeyDown(VK_LBUTTON))
		{
			_player->getUserInterface()->getInventory()->save();
			SCENEMANAGER->loadScene("상점씬");
			SOUNDMANAGER->stop("DUNGEON_BGM");
		}

	}
	else
	{
		if (_player->getUserInterface()->getInventoryOn())
		{
			if (!_player->getUserInterface()->getInventory()->getInventoryAppeared())
			{
				_player->getUserInterface()->getInventory()->inventoryAppear();
			}
			_player->getUserInterface()->getInventory()->update();
	
			if (KEYMANAGER->isOnceKeyDown('L'))
			{
				_player->getUserInterface()->setInvenAnimationOn(true);
			}
	
			if (_player->getUserInterface()->getInvenAnimationOn())
			{
				_player->getUserInterface()->getInventory()->inventoryDisappear();
	
				if (!_player->getUserInterface()->getInventory()->getInventoryAppeared())
				{
					_isGameOn = true;
					_player->getUserInterface()->setInventoryOn(false);
					_player->getUserInterface()->setInvenAnimationOn(false);
				}
			}
		}
	}

}



void dungeonScene::render()
{

	if (_isBossRoom)
	{
		IMAGEMANAGER->findImage("BOSS_BACKGROUND")->render(getMemDC(), _player->getImagePosition().x, _player->getImagePosition().y - (IMAGEMANAGER->findImage("BOSS_BACKGROUND")->getHeight() - WINSIZEY));
	}
	else
	{
		_useMap->render();
	}

	for (int i = 0; i < _enemyManager->getItemVector().size(); i++)
	{
		_enemyManager->getItemVector()[i]->render();
	}

	for (int i = 0; i < _enemyManager->getItemVector().size(); i++)
	{
		IMAGEMANAGER->findImage(_enemyManager->getItemVector()[i]->getItemKey())->render(getMemDC(), _enemyManager->getItemVector()[i]->getItemRc().left, _enemyManager->getItemVector()[i]->getItemRc().top);
	}

	if (_enemyManager->getEnemyVector().size())
	{
		for (int i = 0; i < _enemyManager->getEnemyVector().size(); i++)
		{
			if (_enemyManager->getEnemyVector()[i]->getEnemyPos().y > _player->getPlayerRc().top)
			{
				_player->render();
				_enemyManager->getEnemyVector()[i]->render();
			}
			else
			{
				_enemyManager->getEnemyVector()[i]->render();
				_player->render();
				
			}
		}
	}
	else
	{
		_player->render();
	}

	if (_player->getUserInterface()->getInventoryOn())
	{
		_player->getUserInterface()->getInventory()->render();
	}

	if (_player->getPlayerHp() <= 0)
	{
		IMAGEMANAGER->findImage("DIE")->render(getMemDC(), WINSIZEX / 2 - 225, WINSIZEY / 2 - 225);
		FrameRect(getMemDC(), _goToVillage, RGB(100, 100, 100));
	}

	if (_gameClear)
	{
		IMAGEMANAGER->findImage("DIE2")->render(getMemDC(), WINSIZEX / 2 - 225, WINSIZEY / 2 - 225);
		FrameRect(getMemDC(), _goToVillage, RGB(100, 100, 100));
	}

}

void dungeonScene::useMapLoad()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("save.map", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _useMap, sizeof(useMap), &read, NULL);
	CloseHandle(file);

}
