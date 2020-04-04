#include "stdafx.h"
#include "player.h"
#include "enemyManager.h"


HRESULT player::init(POINT pos)
{
	_userInterface = new userInterface;
	_userInterface->init();

	_maxHp = 200;
	_hp = 200;
	_atk = 10;

	_nowEquip = _userInterface->getNowEquip();

	_isAttacked = false;
	_pos = { pos.x, pos.y };
	_rc = RectMakeCenter(_pos.x, _pos.y, 40, 40);
	_directionRc[0] = RectMake(_rc.left+5, _rc.top, 30, 5); //UP
	_directionRc[1] = RectMake(_rc.left, _rc.top + 5, 5, 30); //LEFT
	_directionRc[2] = RectMake(_rc.left+5, _rc.bottom-5, 30, 5); //DOWN
	_directionRc[3] = RectMake(_rc.right-5, _rc.top + 5, 5, 30); //RIGHT
	_direction = LEFT;
	_state = IDLE;
	_combo = COMBO1;

	if (_location == SHOP)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_SHOP_IDLE");
	}
	else
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_DUNGEON_IDLE");
		_playerWhite = "WILL_DUNGEON_IDLE_WHITE";
	}

	SOUNDMANAGER->addSound("WILL_BOWATTACK", "gameSound/will_bowAttack.mp3");
	SOUNDMANAGER->addSound("WILL_DEATH", "gameSound/will_death.mp3");
	SOUNDMANAGER->addSound("WILL_ROLL", "gameSound/will_roll.mp3");
	SOUNDMANAGER->addSound("WILL_SHORTSWORDATTACK", "gameSound/will_shortSwordAttack.mp3");
	SOUNDMANAGER->addSound("WILL_DEATH", "gameSound/will_death.mp3");

	_speed = 5; 
	_indexX = _indexY = _count = _saveCount = _attackedCount = 0;

	_imagePosition = { 0, 0 };
	_imagePositionBefore = { 0,0 };
	_positionBefore = { pos.x, pos.y };
	_vectorX = 0.0f;
	_vectorY = 0.0f;

	for (int i = 0; i < 4; i++)
	{
		_directionMove[i] = true;
	}

	return S_OK;
}

void player::release()
{
}

void player::update()
{
	this->imageChange();
	_count++;
	_userInterface->update();
	this->move();

	if (KEYMANAGER->isOnceKeyDown('E'))
	{
		if (_userInterface->getInventory()->getInventoryItem(22)._itemIs)
		{
			_userInterface->getInventory()->setInvenItemNum(22, _userInterface->getInventory()->getInvenItemNum(22) - 1);
			if (_userInterface->getInventory()->getInvenItemNum(22) == 0)
			{
				INVEN temp;
				temp._item = NULL;
				temp._itemIs = false;
				temp._num = 0;
				_userInterface->getInventory()->setInventoryItem(22, temp);
			}
			_hp += 40;
			if (_hp > _maxHp)
			{
				_hp = _maxHp;
			}
		}
		else {}
	}

	_userInterface->setHp(_hp, _maxHp);

	if (KEYMANAGER->isOnceKeyDown(VK_SPACE))
	{
		SOUNDMANAGER->play("WILL_ROLL");
		_indexX = 0;
		_state = JUMP;
	}

	if (_location != SHOP && KEYMANAGER->isOnceKeyDown('K'))
	{
		_indexX = 0;
	}

	_nowEquip = _userInterface->getNowEquip();

	//======================================활일때==================================

	if (_nowEquip->getItemType() == "활")
	{
		if ( (_location == VILLAGE || _location == DUNGEON) && KEYMANAGER->isOnceKeyDown('J'))
		{
			SOUNDMANAGER->play("WILL_BOWATTACK");
			_state = BOW_ATTACK;
			_indexX = 0;
			_saveCount = _count;
			_imagePositionBefore = _imagePosition;

			tagAttack temp;
			switch (_indexY)
			{
			case 0:
				temp.rc = RectMake(_rc.right-8, _rc.top - 40, 16, 48);
				temp.is2nd = false;
				break;
			case 1:
				temp.rc = RectMake(_rc.left-45, _rc.top, 48, 16);
				temp.is2nd = false;
				break;
			case 2:
				temp.rc = RectMake(_rc.left, _rc.bottom-10, 16, 48);
				temp.is2nd = false;
				break;
			case 3:
				temp.rc = RectMake(_rc.left, _rc.top, 48, 16);
				temp.is2nd = false;
				break;
			}
			_vAttack.push_back(temp);
		}

		if ((_state == IDLE || _state == WALK ) && (_location == VILLAGE || _location == DUNGEON) && KEYMANAGER->isStayKeyDown('K'))
		{
			_state = BOW_ATTACK_SECOND_PREP;
			_indexX = 0;
			_saveCount = _count;
		}

		if (_state == BOW_ATTACK_SECOND_PREP && KEYMANAGER->isOnceKeyUp('K'))
		{
			_state = IDLE;
		}

		if (_state == BOW_ATTACK_SECOND_READY && KEYMANAGER->isOnceKeyUp('K'))
		{
			SOUNDMANAGER->play("WILL_BOWATTACK");
			_state = BOW_ATTACK_SECOND_SHOOT;
			_saveCount = _count;

		}

		if (_state == BOW_ATTACK_SECOND_SHOOT && _count - _saveCount == 22)
		{
			tagAttack temp;
			switch (_indexY)
			{
			case 0:
				temp.rc = RectMake(_rc.right - 8, _rc.top - 40, 16, 48);
				temp.is2nd = true;
				break;
			case 1:
				temp.rc = RectMake(_rc.left - 45, _rc.top, 48, 16);
				temp.is2nd = true;
				break;
			case 2:
				temp.rc = RectMake(_rc.left, _rc.bottom - 10, 16, 48);
				temp.is2nd = true;
				break;
			case 3:
				temp.rc = RectMake(_rc.left, _rc.top, 48, 16);
				temp.is2nd = true;
				break;
			}
			_vAttack.push_back(temp);

		}

		for (int i = 0; i < _vAttack.size(); i++)
		{
			if (!_vAttack[i].is2nd)
			{
				for (int i = 0; i < _vAttack.size(); i++)
				{
					switch (_indexY)
					{
					case 0:
						_vAttack[i].rc.top -= 20;
						//	_vAttack[i].rc.top += _imagePosition.y - _imagePositionBefore.y;
						_vAttack[i].rc.bottom = _vAttack[i].rc.top + 48;

						break;
					case 1:
						_vAttack[i].rc.left -= 20;
						//	_vAttack[i].rc.left += _imagePosition.y - _imagePositionBefore.y;
						_vAttack[i].rc.right = _vAttack[i].rc.left + 48;
						break;
					case 2:
						_vAttack[i].rc.top += 20;
						//	_vAttack[i].rc.top += _imagePosition.y - _imagePositionBefore.y;
						_vAttack[i].rc.bottom = _vAttack[i].rc.top + 48;
						break;
					case 3:
						_vAttack[i].rc.left += 20;
						//	_vAttack[i].rc.left += _imagePosition.x - _imagePositionBefore.x;
						_vAttack[i].rc.right = _vAttack[i].rc.left + 48;
						break;
					}
				}
			}

			if (_vAttack[i].is2nd)
			{
				switch (_indexY)
				{
				case 0:
					_vAttack[i].rc.top -= 20;
					_vAttack[i].rc.left -= 2;
					//	_vAttack[i].rc.top += _imagePosition.y - _imagePositionBefore.y;
					_vAttack[i].rc.bottom = _vAttack[i].rc.top + 48;
					_vAttack[i].rc.right = _vAttack[i].rc.left + 16;
					break;
				case 1:
					_vAttack[i].rc.left -= 20;
					_vAttack[i].rc.top += 2;
					//	_vAttack[i].rc.left += _imagePosition.y - _imagePositionBefore.y;
					_vAttack[i].rc.right = _vAttack[i].rc.left + 48;
					_vAttack[i].rc.bottom = _vAttack[i].rc.top + 16;
					break;
				case 2:
					_vAttack[i].rc.top += 20;
					_vAttack[i].rc.left += 2;
					//	_vAttack[i].rc.top += _imagePosition.y - _imagePositionBefore.y;
					_vAttack[i].rc.bottom = _vAttack[i].rc.top + 48;
					_vAttack[i].rc.right = _vAttack[i].rc.left + 16;
					break;
				case 3:
					_vAttack[i].rc.left += 20;
					_vAttack[i].rc.top += 2;
					//	_vAttack[i].rc.left += _imagePosition.x - _imagePositionBefore.x;
					_vAttack[i].rc.right = _vAttack[i].rc.left + 48;
					_vAttack[i].rc.bottom = _vAttack[i].rc.top + 16;
					break;
				}
			}

			
		}

		for (int i = 0; i < _vAttack.size(); i++)
		{
			if (_vAttack[i].rc.left < 0 || _vAttack[i].rc.right > WINSIZEX || _vAttack[i].rc.top > WINSIZEY || _vAttack[i].rc.bottom < 0)
			{
				_vAttack.erase(_vAttack.begin() + i);
			}
		}

	}

	//=================================검일 때=================================
	

	if (_nowEquip->getItemType()=="단검")
	{
		if (_location != SHOP && _state != DEFFENSE_WALK && KEYMANAGER->isStayKeyDown('K'))
		{
			_state = DEFFENSE;
		}

		if (_location != SHOP && KEYMANAGER->isOnceKeyUp('K'))
		{
			_indexX = 4;
			_state = DEFFENSE_RELEASE;
		}


		if ((_state == WALK || _state == IDLE) && (_location == VILLAGE || _location == DUNGEON) && KEYMANAGER->isOnceKeyDown('J'))
		{
			SOUNDMANAGER->play("WILL_SHORTSWORDATTACK");
			_state = SHORTSWORD_ATTACK;
			_indexX = 0;
			_saveCount = _count;

			tagAttack temp;
			switch (_indexY)
			{
			case 0:
				temp.rc = RectMake(_rc.left - 40, _rc.top - 40, 120, 70);
				temp.is2nd = false;
				break;
			case 1:
				temp.rc = RectMake(_rc.left - 50, _rc.top - 25, 90, 110);
				temp.is2nd = false;
				break;
			case 2:
				temp.rc = RectMake(_rc.left - 40, _rc.bottom-40, 120, 80);
				temp.is2nd = false;
				break;
			case 3:
				temp.rc = RectMake(_rc.right-40, _rc.top-30, 90, 110);
				temp.is2nd = false;
				break;
			}
			_vAttack.push_back(temp);

		}

		if (_state == SHORTSWORD_ATTACK && _combo == COMBO1 && _indexX == 4 && KEYMANAGER->isOnceKeyDown('J'))
		{
			SOUNDMANAGER->play("WILL_SHORTSWORDATTACK");
			_saveCount = _count;
			_combo = COMBO2;
		}

		if (_state == SHORTSWORD_ATTACK && _combo == COMBO2 && _indexX == 8 && KEYMANAGER->isOnceKeyDown('J'))
		{
			SOUNDMANAGER->play("WILL_SHORTSWORDATTACK");
			_saveCount = _count;
			_combo = COMBO3;
		}


	}

	_rc = RectMakeCenter(_pos.x, _pos.y, 40, 40);
	_directionRc[0] = RectMake(_rc.left + 5, _rc.top, 30, 5); //UP
	_directionRc[1] = RectMake(_rc.left, _rc.top + 5, 5, 30); //LEFT
	_directionRc[2] = RectMake(_rc.left + 5, _rc.bottom - 5, 30, 5); //DOWN
	_directionRc[3] = RectMake(_rc.right - 5, _rc.top + 5, 5, 30); //RIGHT


	sprintf(test1, "HP : %d", _hp);

	sprintf(test5, "imagePosition_  x : %d,  y : %d", _imagePosition.x, _imagePosition.y);
	sprintf(test6, "playerDirection_ x : %d", _direction);


	if (_isAttacked)
	{
		if (_count - _attackedCount < 5)
		{
			_playerImage = IMAGEMANAGER->findImage(_playerWhite);

		}

		if (_count - _attackedCount > 20)
		{
			_isAttacked = false;
		}
	}

}

void player::render()
{
	if (KEYMANAGER->isToggleKey('P'))
	{
		FrameRect(getMemDC(), _rc, RGB(0, 255, 0));
	}

	if (KEYMANAGER->isToggleKey('M'))
	{
		for (int i = 0; i < 4; i++)
		{
			FrameRect(getMemDC(), _directionRc[i], RGB(0, 0, 0));
		}

		for (int i = 0; i < _vAttack.size(); i++)
		{
			FrameRect(getMemDC(), _vAttack[i].rc, RGB(125, 125, 125));
		}
	}

	if (_location == SHOP)
	{
		_playerImage->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight());
	}
	else
	{
		_playerImage->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight() + 53);

		if (_state == SHORTSWORD_ATTACK)
		{
			IMAGEMANAGER->findImage("WILL_SHORTSWORD_ATTACK_SWORD")->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight() + 53, _indexX, _indexY);
		}

		if (_state == DEFFENSE || _state == DEFFENSE_RELEASE || _state == DEFFENSE_WALK)
		{
			IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight() + 53);
		}

		if (_state == BOW_ATTACK)
		{
			IMAGEMANAGER->findImage("WILL_BOW_ATTACK_BOW")->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight() + 53);
			
			for (int i = 0; i < _vAttack.size(); i++)
			{

				switch (_indexY)
				{
				case 0:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left-19, _vAttack[i].rc.top);
					break;
				case 1:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left, _vAttack[i].rc.top-19);
					break;
				case 2:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left - 19, _vAttack[i].rc.top);
					break;
				case 3:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left, _vAttack[i].rc.top - 19);
					break;
				}
			}
		}

		if (_state == BOW_ATTACK_SECOND_PREP || _state == BOW_ATTACK_SECOND_READY || _state == BOW_ATTACK_SECOND_SHOOT)
		{
			IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->frameRender(getMemDC(), (_rc.left + _rc.right - _playerImage->getFrameWidth()) / 2, _rc.bottom - _playerImage->getFrameHeight() + 53);
		
			for (int i = 0; i < _vAttack.size(); i++)
			{
				switch (_indexY)
				{
				case 0:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left - 19, _vAttack[i].rc.top);
					break;
				case 1:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left, _vAttack[i].rc.top - 19);
					break;
				case 2:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left - 19, _vAttack[i].rc.top);
					break;
				case 3:
					IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->frameRender(getMemDC(), _vAttack[i].rc.left, _vAttack[i].rc.top - 19);
					break;
				}
			}
		
		}
	}




	_userInterface->render();

}

//=====================================무브무브무브무브무브무브무브무브무브무브================================
//=====================================무브무브무브무브무브무브무브무브무브무브================================
//=====================================무브무브무브무브무브무브무브무브무브무브================================

void player::move()
{
	if ( (_state == WALK || _state == IDLE || _state == DEFFENSE || _state == DEFFENSE_WALK) && _directionMove[0] && KEYMANAGER->isStayKeyDown('W'))
	{
		_pos.y -= _speed;
		_direction = UP;
		if (GetAsyncKeyState('K') & 0x8001)
		{
			_state = DEFFENSE_WALK;
		}
		else
		{
			_state = WALK;
		}
	}
	if ((_state == WALK || _state == IDLE || _state == DEFFENSE || _state == DEFFENSE_WALK) && _directionMove[1] && KEYMANAGER->isStayKeyDown('A'))
	{
		_pos.x -= _speed;
		_direction = LEFT;
		if (GetAsyncKeyState('K') & 0x8001)
		{
			_state = DEFFENSE_WALK;
		}
		else
		{
			_state = WALK;
		}
	}
	if ((_state == WALK || _state == IDLE || _state == DEFFENSE || _state == DEFFENSE_WALK) && _directionMove[2] && KEYMANAGER->isStayKeyDown('S'))
	{
		_pos.y += _speed;
		_direction = DOWN;
		if (GetAsyncKeyState('K') & 0x8001)
		{
			_state = DEFFENSE_WALK;
		}
		else

		{
			_state = WALK;
		}
	}
	if ((_state == WALK || _state == IDLE || _state == DEFFENSE || _state == DEFFENSE_WALK) && _directionMove[3] && KEYMANAGER->isStayKeyDown('D'))
	{
		_pos.x += _speed;
		_direction = RIGHT;
		if (GetAsyncKeyState('K') & 0x8001)
		{
			_state = DEFFENSE_WALK;
		}
		else
		{
			_state = WALK;
		}
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyDown('W'))
	{
		_direction = UP;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyDown('A'))
	{
		_direction = LEFT;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyDown('S'))
	{
		_direction = DOWN;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyDown('D'))
	{
		_direction = RIGHT;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyUp('W'))
	{
		_state = IDLE;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyUp('A'))
	{
		_state = IDLE;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyUp('S'))
	{
		_state = IDLE;
	}

	if ((_state == WALK || _state == IDLE) && KEYMANAGER->isOnceKeyUp('D'))
	{
		_state = IDLE;
	}
}

//+++++++++++++++++++++++++++++++++++++++여기 수정 중++++++++++++++++++++++++++++++++++++++++++++

void player::imageChange()
{

	if (_direction == UP)
	{
		_indexY = 0;
	}
	else if (_direction == LEFT)
	{
		_indexY = 1;
	}
	else if (_direction == DOWN)
	{
		_indexY = 2;
	}
	else if (_direction == RIGHT)
	{
		_indexY = 3;
	}

	//===========idle========
	if (_state == IDLE)
	{
		if (_location == SHOP)
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_SHOP_IDLE");
		}
		else
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_DUNGEON_IDLE");
		}

		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 9)
			{
				_indexX = 0;
			}

		}
	}

	//=================WALK===========

	if (_state == WALK)
	{
		if (_location == SHOP)
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_SHOP_WALK");
		}
		else
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_DUNGEON_WALK");	
			_playerWhite = "WILL_DUNGEON_WALK_WHITE";
		}

		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 7)
			{
				_indexX = 0;
			}

		}
	}

	//====================JUMP

	if (_state == JUMP)
	{
		if (_location == SHOP)
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_SHOP_JUMP");
		}
		else
		{
			_playerImage = IMAGEMANAGER->findImage("WILL_DUNGEON_JUMP");
		}

		if (_direction == LEFT)
		{
			if (!_directionMove[3]) {}
			else
			{
				_pos.x -= _speed * 1.5;
			}
		}
		else if (_direction == RIGHT)
		{
			if (!_directionMove[1]) {}
			else
			{
				_pos.x += _speed * 1.5;
			}
		}
		else if (_direction == UP)
		{
			if (!_directionMove[2]) {}
			else
			{
				_pos.y -= _speed * 1.5;
			}

		}
		else if (_direction == DOWN)
		{
			if (!_directionMove[0]) {}
			else
			{
				_pos.y += _speed * 1.5;
			}
		}

		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 7)
			{
				_state = IDLE;
			}

		}
	}

	//====================SHORTSWORD_ATTACK

	if (_state == SHORTSWORD_ATTACK) //단검일때만
	{
		
		_playerImage = IMAGEMANAGER->findImage("WILL_SHORTSWORD_ATTACK");
		_playerWhite = "WILL_SHORTSWORD_ATTACK_WHITE";
		
		if (_count % 5 == 0)
		{
			_indexX++;

			if (_combo == COMBO1 && _indexX > 3)
			{
				_indexX = 4;
				if (_count - _saveCount > 30)
				{
					_state = IDLE;
					_vAttack.clear();
				}
			}

			if (_combo == COMBO2 && _indexX > 7)
			{
				_indexX = 8;
				if (_count - _saveCount > 30)
				{
					_combo = COMBO1;
					_state = IDLE;
					_vAttack.clear();
				}
			}
			
			if (_combo == COMBO3 && _indexX > 17)
			{
				_combo = COMBO1;
				_state = IDLE;
				_vAttack.clear();
			}

		}
	}

	//===================DEFFENSE=================


	if (_state == DEFFENSE)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE");
		_playerWhite = "WILL_SHORTSWORD_DEFFENSE_WHITE";

		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 4)
			{
				_indexX = 4;
			}
		}

		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameY(_indexY);
	}
	
	if (_state == DEFFENSE_RELEASE)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE");
		_playerWhite = "WILL_SHORTSWORD_DEFFENSE_WHITE";
		if (_count % 5 == 0)
		{
			_indexX--;
			if (_indexX < 0)
			{
				_indexX = 0;
				_state = IDLE;
			}
		}
		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameY(_indexY);
	}

	if (_state == DEFFENSE_WALK)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE");
		_playerWhite = "WILL_SHORTSWORD_DEFFENSE_WHITE";
		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 12)
			{
				_indexX = 5;
			}
		}
		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_SHORTSWORD_DEFFENSE_SHIELD")->setFrameY(_indexY);
	}

	if (_state == DEAD)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_DEATH");

		SOUNDMANAGER->play("WILL_DEATH");

		_indexY = 0;
		
		if (_count % 5 == 0)
		{
			_indexX++;
			
			if (_indexX > 10)
			{
				_indexX = 10;
			}
		}

	}
	

	//===========활일때===============

	if (_state == BOW_ATTACK)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_BOW_ATTACK");
		_playerWhite = "WILL_BOW_ATTACK_WHITE";
		
		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 5)
			{
				_indexX = 5;
			}

			if (_count - _saveCount > 30)
			{
				_state = IDLE;
			}
		}


		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_BOW")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_BOW")->setFrameY(_indexY);

		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->setFrameX(0);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->setFrameY(_indexY);
	}

	if (_state == BOW_ATTACK_SECOND_PREP)
	{
		_playerImage = IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND");
		_playerWhite = "WILL_BOW_ATTACK_SECOND_WHITE";
		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 11)
			{
				_state = BOW_ATTACK_SECOND_READY;
			}
		}

		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameY(_indexY);
	}

	if (_state == BOW_ATTACK_SECOND_READY)
	{
		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 17)
			{
				_indexX = 12;
			}
		}
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameY(_indexY);
	}

	if (_state == BOW_ATTACK_SECOND_SHOOT)
	{
		if (_count % 5 == 0)
		{
			_indexX++;
			if (_indexX > 26)
			{
				_state = IDLE;
			}
		}
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_SECOND_BOW")->setFrameY(_indexY);

		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->setFrameX(_indexX);
		IMAGEMANAGER->findImage("WILL_BOW_ATTACK_ARROW")->setFrameY(_indexY);
	}


	_playerImage->setFrameX(_indexX);
	_playerImage->setFrameY(_indexY);
	
}

void player::camMove(image * bgImg)
{
	if (_positionBefore.x == _pos.x) {}
	else if (_pos.x < _imagePosition.x + (WINSIZEX / 2) - 49) { _imagePosition.x = 0; }
	else if (_pos.x > _imagePosition.x + bgImg->getWidth() - (WINSIZEX / 2)-49) { _imagePosition.x = WINSIZEX - bgImg->getWidth(); }
	else
	{
		_vectorX = _positionBefore.x - _pos.x;
		_imagePosition.x += _vectorX;
		_pos.x = _positionBefore.x;
	}

	if (_positionBefore.y == _pos.y) {}
	else if (_pos.y > _imagePosition.y + (WINSIZEY / 2) - 49) { _imagePosition.y = 0; }
	else if (_pos.y < _imagePosition.y - bgImg->getHeight() + (3 * (WINSIZEY / 2))- 49) { _imagePosition.y = bgImg->getHeight() - WINSIZEY; }
	else
	{ 
		_vectorY = _positionBefore.y - _pos.y;
		_imagePosition.y += _vectorY;
		_pos.y = _positionBefore.y;
	}

}


//==============================픽셀충돌============================
void player::pixelCollision()
{

//왼쪽

	for (int i = _pos.y + 1; i < _pos.y + 48; i++)
	{
		COLORREF color = GetPixel(_pixelMap->getMemDC(), _pos.x - _imagePosition.x - 21, i - _imagePosition.y + (_pixelMap->getHeight() - WINSIZEY) -21);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_directionMove[1] = false;
			_pos.x++;
			break;
		}
		else
		{
			_directionMove[1] = true;
		}
	}

	//오른쪽

	for (int i = _pos.y + 1; i < _pos.y + 48; i++)
	{
		COLORREF color = GetPixel(_pixelMap->getMemDC(), _pos.x + 40 - _imagePosition.x - 21, i - _imagePosition.y + (_pixelMap->getHeight() - WINSIZEY) - 21);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_directionMove[3] = false;
			_pos.x--;
			break;
		}
		else
		{
			_directionMove[3] = true;
		}
	}

	//위쪽

	for (int i = _pos.x+1; i < _pos.x + 48; i++)
	{

		COLORREF color = GetPixel(_pixelMap->getMemDC(), i - _imagePosition.x - 21, _pos.y - _imagePosition.y + (_pixelMap->getHeight() - WINSIZEY) - 21);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_directionMove[0] = false;
			_pos.y++;
			break;

		}
		else
		{
			_directionMove[0] = true;
		}

	}

	//아래쪽

	for (int i = _pos.x+1; i < _pos.x + 48; i++)
	{

		COLORREF color = GetPixel(_pixelMap->getMemDC(), i - _imagePosition.x - 21, _pos.y + 40 - _imagePosition.y + (_pixelMap->getHeight() - WINSIZEY) - 21);
		int r = GetRValue(color);
		int g = GetGValue(color);
		int b = GetBValue(color);

		if (r == 255 && g == 0 && b == 0)
		{
			_directionMove[2] = false;
			_pos.y--;
			break;
		}
		else
		{
			_directionMove[2] = true;
		}
	}
}

void player::setPlayerAttacked(int tempDmg)
{
	if (_state == JUMP) {}
	else
	{
		if (!_isAttacked)
		{
			_attackedCount = _count;
			_hp = _hp - tempDmg;
			_isAttacked = true;
		}

		if (_state != DEAD && _hp <= 0)
		{
			_indexX = 0;
		}

		if (_hp <= 0)
		{
			_hp = 0;
			_state = DEAD;
		}
	}
}
