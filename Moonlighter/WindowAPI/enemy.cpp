#include "stdafx.h"
#include "enemy.h"

HRESULT enemy::init(POINT pos, int frameX)
{
	SOUNDMANAGER->addSound("ENEMY_DEATH", "gameSound/enemy_death.mp3");
	SOUNDMANAGER->addSound("SLIME_HIT", "gameSound/slime_hit.mp3");

	_isAttacked = false;
	_indexX = _indexY = _count = _saveCount = _attackedCount = _alpha = 0;
	_x = pos.x;
	_y = pos.y;
	_effectOn = false;
	_playerMove = true;

	_vectorX = _vectorY = _angle = _distance = 0;
	_destination = { 0,0 };

	//이미지도 함께 추가
	
	switch (frameX)
	{
	case 0:
		_name = "SLIME";
		_image = IMAGEMANAGER->findImage("SLIME");
		_speed = 2;
		_rc = RectMake(_x+10, _y, 30, 35);
		_attackRangeRc = RectMakeCenter(_x+25, _y+25, 130, 130);
		_enemyState = E_WALK;
		_attackCount = 0;
		_atk = 5;
		_maxHp = 100;
		_nowHp = _maxHp;
		break;
	case 1:
		_name = "PATROLGOLEM";
		_image = IMAGEMANAGER->findImage("PATROLGOLEM");
		_rc = RectMake(_x-10 , _y-17, 67, 67);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 250, 250);
		_enemyState = E_IDLE;
		_enemyDirection = E_DOWN;
		_attackCount = 0;
		_speed = 3;
		_attackOn = false;
		_atk = 10;
		_maxHp = 150;
		_nowHp = _maxHp;
		break;
	case 2:
		_name = "MIMIC";
		_image = IMAGEMANAGER->findImage("MIMIC");
		_speed = 3;
		_rc = RectMake(_x - 5, _y - 17, 65, 50);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 350, 350);
		_enemyState = E_IDLE;
		_enemyDirection = E_DOWN;
		_attackCount = 0;
		_effectOn = false;
		_attackOn = false;
		_effectIndex = 0;
		_atk = 15;
		_maxHp = 200;
		_nowHp = _maxHp;
		break;
	case 3:
		_name = "MAGICIANPUPPET";
		_image = IMAGEMANAGER->findImage("MAGICIANPUPPET");
		_speed = 7;
		_rc = RectMake(_x, _y , 49, 49);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 350, 350);
		_enemyState = E_WALK;
		_enemyDirection = E_DOWN;
		_attackCount = 0;
		_effectOn = false;
		_attackOn = false;
		_effectIndex = 0;
		_attackAngle[0] = 0.f;
		_attackAngle[1] = 3.14f;
		_attackRadius = 1;
		_atk = 20;
		_maxHp = 200;
		_nowHp = _maxHp;
		break;

	}

	_directionRc[0] = RectMake(_rc.left + 5, _rc.top, _rc.right-_rc.left, 5); //UP
	_directionRc[1] = RectMake(_rc.left, _rc.top + 5, 5, _rc.bottom - _rc.top); //LEFT
	_directionRc[2] = RectMake(_rc.left + 5, _rc.bottom - 5, _rc.right - _rc.left, 5); //DOWN
	_directionRc[3] = RectMake(_rc.right - 5, _rc.top + 5, 5, _rc.bottom - _rc.top); //RIGHT

	return S_OK;
}

void enemy::release()
{
}

void enemy::update()
{
	_count++;

	_hpGauge = 80 * ((float)_nowHp / (float)_maxHp);
	_whiteGauge -= 0.2f;
	if (_whiteGauge <= _hpGauge)
	{
		_whiteGauge = _hpGauge;
	}
	
	//==================================슬라임===========================================

	if (_name == "SLIME")
	{
		_rc = RectMake(_x + 10, _y, 30, 35);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 130, 130);

		//============상태 변화===========

		RECT temp;

		if ((_enemyState != E_DEAD && _enemyState != E_REMOVED
	&& _enemyState != E_ABSORBED) && IntersectRect(&temp, &_attackRangeRc, _playerRc))
		{
			if (_attackCount == 2)
			{
				_saveCount = _count;
				_enemyState = E_ABSORBED;
				_indexX = 0;
				_attackCount = 0;
			}
			else
			{
				if (_nowHp <= 0)
				{
					_enemyState = E_DEAD;
				}
				else
				{
					_enemyState = E_ATTACK;
					RECT slimeAttack;
					slimeAttack = RectMakeCenter((_rc.right + _rc.left)/2, (_rc.top + _rc.bottom)/2, 120, 120);
					_vAttackRc.push_back(slimeAttack);
					SOUNDMANAGER->play("SLIME_HIT");
				}

			}
		}


		//===========상태 변화 종료========

		//=============이미지 변화=============
		if (_enemyState == E_WALK)
		{
			_indexY = 0;
			if (_count % 5 == 0)
			{
				_indexX++;
				if (_indexX > 7)
				{
					_indexX = 0;
				}
			}
		}
		else if (_enemyState == E_ATTACK)
		{
			_indexY = 1;
			if (_count % 5 == 0)
			{
				_indexX++;
				if (_indexX > 15)
				{
					_enemyState = E_WALK;
					_attackCount++;
					_indexX = 0;
					_vAttackRc.clear();
				}
			}
		}
		else if (_enemyState == E_ABSORBED)
		{

			if (_count - _saveCount == 200)
			{
				_indexX = 0;
			}

			else if (_count - _saveCount > 200)
			{
				_indexY = 3;
				if (_count % 5 == 0)
				{
					_indexX++;
					_x = _destination.x - 30;
					_y = _destination.y - 10;

					if (_indexX > 6)
					{
						_indexX = 0;
						_enemyState = E_WALK;
						_playerMove = true;
					}
				}
			}

			else
			{
				_indexY = 2;
				if (_count % 2 == 0)
				{
					_indexX++;

					if (_indexX > 8)
					{
						_playerMove = false;
						_x = _destination.x - 30;
						_y = _destination.y - 10;
					}
					if (_indexX > 17)
					{
						_indexX = 17;
					}
				}

			}

		}
		_image->setFrameX(_indexX);
		_image->setFrameY(_indexY);

		//==========이미지 변화 종료=========

		//============움직임=============

		_distance = getDistance(_x, _y, _destination.x, _destination.y);

		_vectorX = (_destination.x - _x)/ _distance;
		
		if ((_vectorX < 0 && !_directionMove[1])||(_vectorX >0 && !_directionMove[3])) {}
		else
		{
			_x += _speed * _vectorX;
		}

		if ((_vectorY < 0 && !_directionMove[0]) || (_vectorY > 0 && !_directionMove[2])) {}
		else
		{
			_vectorY = (_destination.y - _y) / _distance;
			_y += _speed * _vectorY;
		}


		//=========움직임 종료============

	}

	//==================================패트롤 골렘===========================================

	else if (_name == "PATROLGOLEM")
	{
	_rc = RectMake(_x - 10, _y - 17, 67, 67);
	_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 250, 250);

		//=======이미지 변화=======

		if (_enemyDirection == E_UP)
		{
			_indexY = 0;
		}
		else if (_enemyDirection == E_LEFT)
		{
			_indexY = 1;
		}
		else if (_enemyDirection == E_DOWN)
		{
			_indexY = 2;
		}
		else if (_enemyDirection == E_RIGHT)
		{
			_indexY = 3;
		}

		if (_enemyState == E_IDLE)
		{
			_angle = getAngle(_x, _y, _destination.x, _destination.y);

			this->enemyDirectionChange();
			RECT temp;

			if (_indexX == 0 && IntersectRect(&temp, _playerRc, &_attackRangeRc))
			{
				_enemyState = E_ATTACK;
			}

			if (_count % 5 == 0)
			{
				if (!_effectOn)
				{
					_indexX++;
					if (_indexX > 2)
					{
						_effectOn = true;
						_attackCount++;
					}
				}
				else
				{
					_indexX--;
					if (_indexX < 1)
					{
						_effectOn = false;
					}
				}

				if (_attackCount > 3)
				{
					_enemyState = E_WALK;
					_attackCount = 0;
				}
			}
		}
		else if (_enemyState == E_WALK)
		{
			if (_count % 5 == 0)
			{
				_indexX++;
			}

			if (_enemyDirection == E_UP)
			{
				if (_directionMove[0] == false)
				{
					_vAttackRc.clear();
					if (_indexX > 23)
					{
						_indexX = 1;
						_enemyState = E_IDLE;
					}
				}
				else
				{
					if (_indexX > 17)
					{
						_indexX = 12;
					}
					_y -= 2;

					if (_indexX == 11 && _count%5 == 0)
					{
						RECT temp;
						temp = { 0, _rc.top + 20, _rc.left-5, _rc.bottom - 7 };
						_vAttackRc.push_back(temp);

						RECT temp2;
						temp2 = { _rc.right, _rc.top + 20, WINSIZEX, _rc.bottom - 7 };
						_vAttackRc.push_back(temp2);
					}
				}


				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					_vAttackRc[i].top -= 2;
					_vAttackRc[i].bottom -= 2;
				}
					

			}
			else if (_enemyDirection == E_LEFT)
			{
				if (_directionMove[1] == false)
				{
					_vAttackRc.clear();
					if (_indexX > 23)
					{
						_indexX = 1;
						_enemyState = E_IDLE;
					}
				}
				else
				{
					if (_indexX > 17)
					{
						_indexX = 12;
					}
					_x -= 2;

					if (_indexX == 11 && _count % 5 == 0)
					{
						RECT temp;
						temp = { _rc.left+15, 0, _rc.right-12, _rc.top-5 };
						_vAttackRc.push_back(temp);

						RECT temp2;
						temp2 = { _rc.left+15, _rc.bottom-10, _rc.right-12, WINSIZEY };
						_vAttackRc.push_back(temp2);
					}
				}

				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					_vAttackRc[i].left -= 2;
					_vAttackRc[i].right -= 2;
				}

			}
			else if (_enemyDirection == E_DOWN)
			{
				if (_directionMove[2] == false)
				{
					_vAttackRc.clear();
					if (_indexX > 23)
					{
						_indexX = 1;
						_enemyState = E_IDLE;
					}
				}
				else
				{
					if (_indexX > 17)
					{
						_indexX = 12;
					}
					_y += 2;

					if (_indexX == 11 && _count % 5 == 0)
					{
						RECT temp;
						temp = { 0, _rc.top + 20, _rc.left-5, _rc.bottom - 7 };
						_vAttackRc.push_back(temp);

						RECT temp2;
						temp2 = { _rc.right, _rc.top + 20, WINSIZEX, _rc.bottom - 7 };
						_vAttackRc.push_back(temp2);
					}
				}

				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					_vAttackRc[i].top += 2;
					_vAttackRc[i].bottom += 2;
				}

			}
			else if (_enemyDirection == E_RIGHT)
			{
				if (_directionMove[3] == false)
				{
					_vAttackRc.clear();
					if (_indexX > 23)
					{
						_indexX = 1;
						_enemyState = E_IDLE;
					}
				}
				else
				{
					if (_indexX > 17)
					{
						_indexX = 12;
					}
					_x += 2;

					if (_indexX == 11 && _count % 5 == 0)
					{
						RECT temp;
						temp = { _rc.left + 15, 0, _rc.right - 12, _rc.top-5 };
						_vAttackRc.push_back(temp);

						RECT temp2;
						temp2 = { _rc.left + 15, _rc.bottom-10, _rc.right - 12, WINSIZEY };
						_vAttackRc.push_back(temp2);
					}

				}

				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					_vAttackRc[i].left += 2;
					_vAttackRc[i].right += 2;
				}

			}
		}
		else if (_enemyState == E_ATTACK)
		{
			if (!_attackOn)
			{
				if (_angle >= 0 && _angle < 1.57)
				{
					_angle = 0;
					_razorAngle = 0.78;
				}
				else if (_angle >= 1.57 && _angle < 3.14)
				{
					_angle = 1.57;
					_razorAngle = 2.35;
				}
				else if (_angle >= 3.14 && _angle < 4.71)
				{
					_angle = 3.14;
					_razorAngle = 3.92;
				}
				else
				{
					_angle = 4.71;
					_razorAngle = 5.49;
				}
				_attackOn = true;
			}

			_indexY = 4;

			_angle += 0.1f;

			if (_angle >= _razorAngle)
			{
				_angle = _razorAngle;
			}
	
			if (_count % 5 == 0)
			{
				_indexX++;
				if (_indexX > 28)
				{
					_indexX = 0;
					_enemyState = E_IDLE;
					_attackOn = false;
				}
			}
		}

		_image->setFrameX(_indexX);
		_image->setFrameY(_indexY);

		//=======이미지 변화 종료=======
	}

	//==================================미믹===========================================

	else if (_name == "MIMIC")
	{
		_rc = RectMake(_x - 5, _y - 17, 65, 50);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 350, 350);

		_angle = getAngle(_x, _y, _destination.x, _destination.y);


		if (!_effectOn)
		{
			_indexY = 5;
			_indexX = 0;

			RECT temp;

			if (IntersectRect(&temp, _playerRc, &_attackRangeRc))
			{
				_effectOn = true;
				_enemyState = E_IDLE;
			}
		}
		else
		{
			this->enemyDirectionChange();

			if (_enemyDirection == E_UP)
			{
				_indexY = 0;
			}
			else if (_enemyDirection == E_LEFT)
			{
				_indexY = 1;
			}
			else if (_enemyDirection == E_DOWN)
			{
				_indexY = 2;
			}
			else if (_enemyDirection == E_RIGHT)
			{
				_indexY = 3;
			}

			if (_count % 5 == 0)
			{
				_indexX++;
			}

			//===========방향 설정 끝========

			if (_enemyState == E_IDLE) //일어나는거 이걸로 만들기
			{
				_indexY = 5;

				if (_indexX > 12)
				{
					_indexX = 12;
					_enemyState = E_WALK;
				}

			}
			else if (_enemyState == E_WALK)
			{
				_indexY = 4;

				if (_directionMove[0] && _enemyDirection == E_UP)
				{
					_y -= _speed;
				}
				else if (_directionMove[1] && _enemyDirection == E_LEFT)
				{
					_x -= _speed;
				}
				else if (_directionMove[2] && _enemyDirection == E_DOWN)
				{
					_y += _speed;
				}
				else if (_directionMove[3] && _enemyDirection == E_RIGHT)
				{
					_x += _speed;
				}


				if (_indexX > 23)
				{

					_angle = getAngle(_x, _y, _destination.x, _destination.y);

					_indexX = 0;
					_enemyState = E_ATTACK;
					_attackOn = true;

					for (int i = 0; i < 50; i++)
					{
						_aCoin[i].angle = (RND->range(60) -30 + (_angle * 100))/100.0f;
						_aCoin[i].rc = RectMakeCenter((_rc.right + _rc.left) / 2, (_rc.top + _rc.bottom) / 2, 18, 18);
						_aCoin[i].indexX = rand()%5;
						_aCoin[i].speed = (RND->range(30) + 30)/10.0f;

						_vAttackRc.push_back(_aCoin[i].rc);
					}
				}
			}
			else if (_enemyState == E_ATTACK)
			{
				if (_attackOn == true)
				{
					for (int i = 0; i < _vAttackRc.size(); i++)
					{
						_vAttackRc[i].left += _aCoin[i].speed * cosf(_aCoin[i].angle);
						_vAttackRc[i].right = _vAttackRc[i].left + 18;
						_vAttackRc[i].top -= _aCoin[i].speed *sinf(_aCoin[i].angle);
						_vAttackRc[i].bottom = _vAttackRc[i].top + 18;
						_aCoin[i].indexX++;  

						if (_aCoin[i].indexX > 4)
						{
							_aCoin[i].indexX = 0;
						}
					}
				}
				

				if (_indexX > 21)
				{
					_indexX = 0;
					_enemyState = E_WALK;
					_attackOn = false;
					
					_vAttackRc.clear();
				}

			}
		}
		
		_image->setFrameX(_indexX);
		_image->setFrameY(_indexY);
	}

		else if (_name == "MAGICIANPUPPET")
	{
		_rc = RectMake(_x, _y, 49, 49);
		_attackRangeRc = RectMakeCenter(_x + 25, _y + 25, 350, 350);
	
		_angle = getAngle(_x, _y, _destination.x, _destination.y);
	

	
	//============에너미 방향 설정============

		//===========방향 설정 끝========



		if (_enemyState == E_IDLE) 
		{
			this->enemyDirectionChange();

			_indexY = 4;
			if (_count % 5 == 0)
			{
				_indexX++;
			}

			if (_indexX > 7)
			{
				_indexX = 0;
			}

			if (_count - _saveCount > 50)
			{
				_enemyState = E_ATTACK;
				_indexX = 0;
			}
		}
		else if (_enemyState == E_WALK)
		{
			if (_enemyDirection == E_UP)
			{
				_indexY = 0;
			
				if(_indexX == 7 || _indexX == 8)
				{
					_y -= _speed;
					if (!_effectOn)
					{
						_effectPosition = { PointMake(_x, _y) };
						_effectOn = true;
					}

					if (_count - _saveCount > 20)
					{
						_indexX++;
						_attackCount++;
						_saveCount = _count;

						this->enemyDirectionChange();

						if (_indexX > 8)
						{
							if (_attackCount > 1) {}
							else
							{
								_indexX = 7;
							}
						}
					}
				}
				else
				{
					if (_count % 5 == 0)
					{
						_indexX++;
						_saveCount = _count;
					}

					if (_indexX > 17)
					{
						_indexX = 0;
						_enemyState = E_IDLE;
						_attackCount = 0;
					}
				}
			}
			else if (_enemyDirection == E_LEFT)
			{
				_indexY = 1;
				if (_indexX == 7 || _indexX == 8)
				{
					_x -= _speed;
					if (!_effectOn)
					{
						_effectPosition = { PointMake(_x, _y) };
						_effectOn = true;
					}

					if (_count - _saveCount > 20)
					{
						_indexX++;
						_attackCount++;
						_saveCount = _count;

						this->enemyDirectionChange();

						if (_indexX > 8)
						{
							if (_attackCount > 1) {}
							else
							{
								_indexX = 7;
							}
						}
					}
				}
				else
				{
					if (_count % 5 == 0)
					{
						_indexX++;
						_saveCount = _count;
					}

					if (_indexX > 17)
					{
						_indexX = 0;
						_enemyState = E_IDLE;
						_attackCount = 0;
					}
				}
			}
			else if (_enemyDirection == E_DOWN)
			{
				_indexY = 2;
				if (_indexX == 7 || _indexX == 8)
				{
					_y += _speed;
					if (!_effectOn)
					{
						_effectPosition = { PointMake(_x, _y) };
						_effectOn = true;
					}

					if (_count - _saveCount > 20)
					{
						_indexX++;
						_attackCount++;
						_saveCount = _count;
						this->enemyDirectionChange();

						if (_indexX > 8)
						{
							if (_attackCount > 1) {}
							else
							{
								_indexX = 7;
							}
						}
					}
				}
				else
				{
					if (_count % 5 == 0)
					{
						_indexX++;
						_saveCount = _count;
					}

					if (_indexX > 17)
					{
						_indexX = 0;
						_enemyState = E_ATTACK;
						_attackCount = 0;
					}
				}
			}
			else if (_enemyDirection == E_RIGHT)
			{
				_indexY = 3;
				if (_indexX == 7 || _indexX == 8)
				{
					_x += _speed;
					if (!_effectOn)
					{
						_effectPosition = { PointMake(_x, _y) };
						_effectOn = true;
					}

					if (_count - _saveCount > 20)
					{
						_indexX++;
						_attackCount++;
						_saveCount = _count;
						this->enemyDirectionChange();

						if (_indexX > 8)
						{
							if (_attackCount > 1) {}
							else
							{
								_indexX = 7;
							}
						}
					}
				}
				else
				{
					if (_count % 5 == 0)
					{
						_indexX++;
						_saveCount = _count;
					}

					if (_indexX > 17)
					{
						_indexX = 0;
						_enemyState = E_IDLE;
						_attackCount = 0;
					}
				}
			}
		}
		else if (_enemyState == E_ATTACK)
		{

			_indexY = 5;
			
			if (_count % 5 == 0)
			{
				_indexX++;
	
				if (_indexX == 12 && _count % 5 == 0)
				{
					_effectPosition = PointMake((_rc.right + _rc.left) / 2, (_rc.top + _rc.bottom) / 2);
					for (int i = 0; i < 2; i++)
					{
						RECT temp = RectMakeCenter(_effectPosition.x, _effectPosition.y, 30, 30);
						_vAttackRc.push_back(temp);
					}
				}


				if (_indexX > 25)
				{
					_indexX = 0;
					_enemyState = E_WALK;
					_vAttackRc.clear();
					_attackAngle[0] = 0.f;
					_attackAngle[1] = 3.14f;
					_attackRadius = 1;
				}
			}

			if (_indexX >= 12)
			{
				_attackAngle[0] += 0.07f;
				_attackAngle[1] += 0.07f;
				_attackRadius += 2;

				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					_vAttackRc[i].left = _effectPosition.x - 15 + _attackRadius * cosf(_attackAngle[i]);
					_vAttackRc[i].top = _effectPosition.y - 15 + _attackRadius * sinf(_attackAngle[i]);
					_vAttackRc[i].right = _vAttackRc[i].left + 30;
					_vAttackRc[i].bottom = _vAttackRc[i].top + 30;
				}
			}
		}

		if (_effectOn)
		{

			if (_count % 5 == 0)
			{
				_effectIndex++;
			}
			if (_effectIndex > 5)
			{
				_effectOn = false;
				_effectIndex = 0;
			}
		}
	

	_image->setFrameX(_indexX);
	_image->setFrameY(_indexY);

	}



	_directionRc[0] = RectMake(_rc.left + 5, _rc.top, _rc.right - _rc.left-10, 5); //UP
	_directionRc[1] = RectMake(_rc.left, _rc.top + 5, 5, _rc.bottom - _rc.top-10); //LEFT
	_directionRc[2] = RectMake(_rc.left + 5, _rc.bottom - 5, _rc.right - _rc.left-10, 5); //DOWN
	_directionRc[3] = RectMake(_rc.right - 5, _rc.top + 5, 5, _rc.bottom - _rc.top-10); //RIGHT

	if (_enemyState == E_DEAD)	//죽었을 때의 인덱스
	{
		if (_name == "SLIME")
		{
			_indexX = 9;
			_indexY = 1;
		}
		else if (_name == "PATROLGOLEM")
		{
			_indexX = 0;
			_indexY = 0;
		}
		else if (_name == "MIMIC")
		{
			_indexX = 5;
			_indexY = 5;
		}
		else if (_name == "MAGICIANPUPPET")
		{
			_indexX = 0;
			_indexY = 0;
		}

		_alpha += 5;
		if (_alpha > 255)
		{
			_alpha = 255;
			_enemyState = E_REMOVED;
		}
	}

	sprintf(hp, "ENEMY HP : %d", _nowHp);
	sprintf(attacked, "ENEMY STATE : %d", _enemyState);

	if (_isAttacked)
	{
		_logIndex += 20;
		_logPos = 5 * log2(_logIndex);
		_vAttackRc.clear();

		switch (_enemyDirection)
		{
		case 0:		//위
			if (!_directionMove[2]) {}
			else
			{
				_y = _logPosBefore.y + _logPos;
			}
			break;
		case 1:		//왼쪽
			if (!_directionMove[3]) {}
			else
			{
				_x = _logPosBefore.x + _logPos;
			}
			break;
		case 2:		//아래
			if (!_directionMove[0]) {}
			else
			{
				_y = _logPosBefore.y - _logPos;
			}
			break;
		case 3:		//오른쪽
			if (!_directionMove[1]) {}
			else
			{
				_x = _logPosBefore.x - _logPos;
			}
			break;
		}

		if (_count - _attackedCount > 20)
		{
			_isAttacked = false;
		}

		if ( _count - _attackedCount > 0 && _count - _attackedCount < 5)
		{
			if (_name == "SLIME")
			{
				_image = IMAGEMANAGER->findImage("SLIME_RED");
			}
			else if (_name == "PATROLGOLEM")
			{
				_image = IMAGEMANAGER->findImage("PATROLGOLEM_RED");
			}
			else if (_name == "MIMIC")
			{
				_image = IMAGEMANAGER->findImage("MIMIC_RED");
			}
			else if (_name == "MAGICIANPUPPET")
			{
				_image = IMAGEMANAGER->findImage("MAGICIANPUPPET_RED");
			}
		}
		else if (_count - _attackedCount >= 5 && _count - _attackedCount < 10)
		{
			if (_name == "SLIME")
			{
				_image = IMAGEMANAGER->findImage("SLIME_WHITE");
			}
			else if (_name == "PATROLGOLEM")
			{
				_image = IMAGEMANAGER->findImage("PATROLGOLEM_WHITE");
			}
			else if (_name == "MIMIC")
			{
				_image = IMAGEMANAGER->findImage("MIMIC_WHITE");
			}
			else if (_name == "MAGICIANPUPPET")
			{
				_image = IMAGEMANAGER->findImage("MAGICIANPUPPET_WHITE");
			}
		}
		else
		{
			if (_name == "SLIME")
			{
				_image = IMAGEMANAGER->findImage("SLIME");
			}
			else if (_name == "PATROLGOLEM")
			{
				_image = IMAGEMANAGER->findImage("PATROLGOLEM");
			}
			else if (_name == "MIMIC")
			{
				_image = IMAGEMANAGER->findImage("MIMIC");
			}
			else if (_name == "MAGICIANPUPPET")
			{
				_image = IMAGEMANAGER->findImage("MAGICIANPUPPET");
			}
		}
	}


}

void enemy::render()
{

	IMAGEMANAGER->findImage("몬스터체력바")->render(getMemDC(), _x - 15, _y - 100);
	IMAGEMANAGER->findImage("몬스터체력바_흰색")->render(getMemDC(), _x - 15, _y - 100, 0, 0, _whiteGauge, 15);
	IMAGEMANAGER->findImage("몬스터체력바_체력")->render(getMemDC(), _x - 15, _y - 100, 0, 0, _hpGauge, 15);

	if (_name == "SLIME")
	{
		if (_enemyState == E_DEAD || _enemyState == E_REMOVED)
		{
			_image->alphaFrameRender(getMemDC(), _x - 35, _y - 52, _indexX, _indexY, _alpha);
		}
		else
		{
			_image->frameRender(getMemDC(), _x - 35, _y - 52, _indexX, _indexY);
		}
	}
	else if (_name == "PATROLGOLEM")
	{
		if (_enemyState == E_DEAD || _enemyState == E_REMOVED)
		{
			_image->alphaFrameRender(getMemDC(), _x - 65, _y - 80, _indexX, _indexY, _alpha);
		}
		else
		{
			_image->frameRender(getMemDC(), _x - 65, _y - 80, _indexX, _indexY);
		}

		if (_enemyState == E_WALK && _vAttackRc.size())
		{
			if (_enemyDirection == E_UP || _enemyDirection == E_DOWN)
			{
				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					for (int j = _vAttackRc[i].left; j < _vAttackRc[i].right; j += 12)
					{
						IMAGEMANAGER->findImage("LAVA_BEAM_2")->render(getMemDC(), j, _vAttackRc[i].top);
					}

				}
			}

			if (_enemyDirection == E_LEFT || _enemyDirection == E_RIGHT)
			{
				for (int i = 0; i < _vAttackRc.size(); i++)
				{
					for (int j = _vAttackRc[i].top; j < _vAttackRc[i].bottom; j += 12)
					{
						IMAGEMANAGER->findImage("LAVA_BEAM_1")->render(getMemDC(), _vAttackRc[i].left, j);
					}

				}
			}
		}

		if (_enemyState == E_ATTACK && _indexX > 7 && _indexX < 22)
		{
			IMAGEMANAGER->findImage("RAZOR")->rotateRender(getMemDC(), (_rc.right + _rc.left) / 2, _rc.top, _angle);
		}


	}
	else if (_name == "MIMIC")
	{
		if (_enemyState == E_DEAD || _enemyState == E_REMOVED)
		{
			_image->alphaFrameRender(getMemDC(), _x - 65, _y - 80, _indexX, _indexY, _alpha);
		}
		else
		{
			_image->frameRender(getMemDC(), _x - 65, _y - 80, _indexX, _indexY);
		}

		if (_enemyState == E_ATTACK && _vAttackRc.size())
		{
			for (int i = 0; i < _vAttackRc.size(); i++)
			{
				IMAGEMANAGER->findImage("COIN")->frameRender(getMemDC(), _vAttackRc[i].left, _vAttackRc[i].top, _aCoin[i].indexX, _indexY);
			}
		}

	}

	else if (_name == "MAGICIANPUPPET")
	{
		if (_effectOn)
		{
			IMAGEMANAGER->findImage("MAGICIANPUPPET_EFFECT")->frameRender(getMemDC(), _effectPosition.x - 72, _effectPosition.y - 120, _effectIndex, 0);
		}

		if (_enemyState == E_DEAD || _enemyState == E_REMOVED)
		{
			_image->alphaFrameRender(getMemDC(), _x - 72, _y - 120, _indexX, _indexY, _alpha);
		}
		else
		{
			_image->frameRender(getMemDC(), _x - 72, _y - 120, _indexX, _indexY);
		}

		if (_enemyState == E_ATTACK && _vAttackRc.size())
		{
			for (int i = 0; i < _vAttackRc.size(); i++)
			{
				IMAGEMANAGER->findImage("MAGICIANPUPPET_ATTACK")->frameRender(getMemDC(), _vAttackRc[i].left + 5, _vAttackRc[i].top + 5, _effectIndex, 0);
			}
		}

	}

	if (KEYMANAGER->isToggleKey('M'))
	{
		FrameRect(getMemDC(), _rc, RGB(0, 255, 255));
		FrameRect(getMemDC(), _attackRangeRc, RGB(255, 0, 0));

		for (int i = 0; i < 4; i++)
		{
			FrameRect(getMemDC(), _directionRc[i], RGB(255, 255, 0));
		}

		for (int i = 0; i < _vAttackRc.size(); i++)
		{
			FrameRect(getMemDC(), _vAttackRc[i], RGB(0, 255, 0));
		}
	}


}


void enemy::enemyDirectionChange()
{
	//============에너미 방향 설정============
	if (_angle >= 0.78 && _angle < 2.35)
	{
		_enemyDirection = E_UP;
	}
	else if (_angle >= 2.35 && _angle < 3.92)
	{
		_enemyDirection = E_LEFT;
	}
	else if (_angle >= 3.92 && _angle < 5.49)
	{
		_enemyDirection = E_DOWN;
	}
	else
	{
		_enemyDirection = E_RIGHT;
	}
}

void enemy::setEnemyAttacked(int tempDmg)
{
	if (!_isAttacked)
	{
		_attackedCount = _count;
		_nowHp = _nowHp - tempDmg;
		_logIndex = 0;
		_logPos = 0;
		_logPosBefore = PointMake(_x, _y);
		_isAttacked = true;
	}
	
	if (_enemyState != E_DEAD && _nowHp <= 0)
	{
		_saveCount = _count;
	}

	if ( _nowHp <= 0)
	{
		_nowHp = 0;
		_enemyState = E_DEAD;
		SOUNDMANAGER->play("ENEMY_DEATH");
	}

}


//내가 너무 멍청하고 아까워서 남겨놓는 코드....
/*
int a = (_rc.left + _rc.right) / 2;
int b = (_rc.top + _rc.bottom) / 2;

if (_enemyDirection == E_UP)
{
	for (int i = a - 200; i < a; i += 5)
	{
		RECT temp;
		temp = { i, 2 * i + b - 2 * a, 2 * a - i, -2 * a + 2 * i + b };
		_vAttackRc.push_back(temp);
	}
}
else if (_enemyDirection == E_LEFT)
{
	for (int i = a - 300; i < a; i += 5)
	{
		RECT temp;
		temp = { i, (int)((float)i / 2) + b - (int)((float)a / 2), i + 5, -(int)((float)i / 2) + b + (int)((float)a / 2) };
		_vAttackRc.push_back(temp);
	}
}
else if (_enemyDirection == E_DOWN)
{
	for (int i = a - 300; i < a; i += 5)
	{
		RECT temp;
		temp = { i, -2 * i + b + 2 * a, 2 * a - i, 2 * a - 2 * i + b };
		_vAttackRc.push_back(temp);
	}
}
else if (_enemyDirection == E_RIGHT)
{
	for (int i = a; i < a + 300; i += 5)
	{
		RECT temp;
		temp = { i, -(int)((float)i / 2) + b + (int)((float)a / 2), i + 5, (int)((float)i / 2) + b - (int)((float)a / 2) };
		_vAttackRc.push_back(temp);
	}
}
*/