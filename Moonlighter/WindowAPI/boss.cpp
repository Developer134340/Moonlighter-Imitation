#include "stdafx.h"
#include "boss.h"

HRESULT boss::init(POINT tempImagePosition)
{

	_imagePositionBefore = tempImagePosition;

	for (int i = 0; i < WORMMAX; i++)
	{
		tagWorm _temp;
		_temp.radius = 70;
		_temp.speed = 5.0f;
		_temp.angle = (i == 0) ? RND->range(2 * PI) : _worm[i - 1].angle;
		_temp.x = (i == 0) ? WINSIZEX / 2 :
			_worm[i - 1].x - cosf(_temp.angle) * (_temp.radius * 2);
		_temp.y = (i == 0) ? WINSIZEY / 2 :
			_worm[i - 1].y - (-sinf(_temp.angle)) * (_temp.radius * 2);
		_temp.indexX = _temp.indexY = 0;
		_temp.alpha = 0;
		_worm.push_back(_temp);
		_vAttackRc.push_back(_worm[i].rc);
		_isDead[i] = false;
	}

	_isAttacked = false;
	_enemyState = E_WALK;
	_maxHp = 500;
	_nowHp = 500;
	_atk = 10;

	_worm[0].indexY = 3;

	_worm[0].image = IMAGEMANAGER->findImage("HEAD_ATTACK");
	_worm[1].image = IMAGEMANAGER->findImage("CIRCLE");
	_worm[2].image = IMAGEMANAGER->findImage("RHOMBUS");
	_worm[3].image = IMAGEMANAGER->findImage("TRIANGLE");
	_worm[4].image = IMAGEMANAGER->findImage("SQUARE");

	return S_OK;
}

void boss::release()
{
}

void boss::update()
{
	_count++;

	enemyDirectionChange();

	if (!_isDead[0])
	{
		if (_enemyDirection == E_UP)
		{
			_worm[0].image->setFrameY(0);
		}
		else if (_enemyDirection == E_LEFT)
		{
			_worm[0].image->setFrameY(1);
		}
		else if (_enemyDirection == E_DOWN)
		{
			_worm[0].image->setFrameY(2);
		}
		else if (_enemyDirection == E_RIGHT)
		{
			_worm[0].image->setFrameY(3);
		}
	}




	_hpGauge = 800 * ((float)_nowHp / (float)_maxHp);
	_whiteGauge -= 0.5f;
	if (_whiteGauge <= _hpGauge)
	{
		_whiteGauge = _hpGauge;
	}

	this->wormMove();

	if (_nowHp > 400 )
	{
		
	}
	else if (_nowHp > 300 && _nowHp <= 400)
	{
		if (!_isDead[4])
		{
			_worm[4].indexY = 2;

			if (_count % 5 == 0)
			{
				_worm[4].indexX++;
			}
	
			if (_worm[4].indexX > 20)
			{
				_worm[4].indexX = 20;
			}
			_worm[4].alpha += 5;
			
			if (_worm[4].alpha > 255)
			{
	
				_worm.erase(_worm.begin() + 4);
				_vAttackRc.erase(_vAttackRc.begin() + 4);
				_isDead[4] = true;
			}
		}
	}
	else if (_nowHp > 200 && _nowHp <= 300)
	{
		if (!_isDead[3])
		{
			_worm[3].indexY = 2;

			if (_count % 5 == 0)
			{
				_worm[3].indexX++;
			}

			if (_worm[3].indexX > 20)
			{
				_worm[3].indexX = 20;
			}
			_worm[3].alpha += 5;

			if (_worm[3].alpha > 255)
			{
				_worm.erase(_worm.begin() + 3);
				_vAttackRc.erase(_vAttackRc.begin() + 3);
				_isDead[3] = true;
			}
		}
	}
	else if (_nowHp > 100 && _nowHp <= 200)
	{
		if (!_isDead[2])
		{
			_worm[2].indexY = 2;

			if (_count % 5 == 0)
			{
				_worm[2].indexX++;
			}

			if (_worm[2].indexX > 20)
			{
				_worm[2].indexX = 20;
			}
			_worm[2].alpha += 5;

			if (_worm[2].alpha > 255)
			{
				_worm.erase(_worm.begin() + 2);
				_vAttackRc.erase(_vAttackRc.begin() + 2);
				_isDead[2] = true;
			}
		}
	}
	else if (_nowHp > 0 && _nowHp <= 100)
	{
		if (!_isDead[1])
		{
			_worm[1].indexY = 2;

			if (_count % 5 == 0)
			{
				_worm[1].indexX++;
			}

			if (_worm[1].indexX > 20)
			{
				_worm[1].indexX = 20;
			}
			_worm[1].alpha += 5;

			if (_worm[1].alpha > 255)
			{
				_worm.erase(_worm.begin() + 1);
				_vAttackRc.erase(_vAttackRc.begin() + 1);
				_isDead[1] = true;
			}
		}
	}
	else
	{
		if (!_isDead[0])
		{
			_worm[0].alpha += 5;
	
			if (_worm[0].alpha > 255)
			{
	
				_worm.clear();
				_vAttackRc.clear();
				_isDead[0] = true;
				_enemyState = E_REMOVED;
			}
		}
	}



	if (_isAttacked)
	{

		if (_count - _attackedCount > 20)
		{
			_isAttacked = false;
		}

		if (_count - _attackedCount > 0 && _count - _attackedCount < 5)
		{
			if (!_isDead[0])
			{
				_worm[0].image = IMAGEMANAGER->findImage("HEAD_ATTACK_RED");
			}
			if (!_isDead[1])
			{
				_worm[1].image = IMAGEMANAGER->findImage("CIRCLE_RED");
			}
			if (!_isDead[2])
			{
				_worm[2].image = IMAGEMANAGER->findImage("RHOMBUS_RED");
			}
			if (!_isDead[3])
			{
				_worm[3].image = IMAGEMANAGER->findImage("TRIANGLE_RED");
			}
			if (!_isDead[4])
			{
				_worm[4].image = IMAGEMANAGER->findImage("SQUARE_RED");
			}
		}
		else if (_count - _attackedCount >= 5 && _count - _attackedCount < 10)
		{
			if (!_isDead[0])
			{
				_worm[0].image = IMAGEMANAGER->findImage("HEAD_ATTACK_WHITE");
			}
			if (!_isDead[1])
			{
				_worm[1].image = IMAGEMANAGER->findImage("CIRCLE_WHITE");
			}
			if (!_isDead[2])
			{
				_worm[2].image = IMAGEMANAGER->findImage("RHOMBUS_WHITE");
			}
			if (!_isDead[3])
			{
				_worm[3].image = IMAGEMANAGER->findImage("TRIANGLE_WHITE");
			}
			if (!_isDead[4])
			{
				_worm[4].image = IMAGEMANAGER->findImage("SQUARE_WHITE");
			}
		}
		else
		{

			if (!_isDead[0])
			{
				_worm[0].image = IMAGEMANAGER->findImage("HEAD_ATTACK");
			}
			if (!_isDead[1])
			{
				_worm[1].image = IMAGEMANAGER->findImage("CIRCLE");
			}
			if (!_isDead[2])
			{
				_worm[2].image = IMAGEMANAGER->findImage("RHOMBUS");
			}
			if (!_isDead[3])
			{
				_worm[3].image = IMAGEMANAGER->findImage("TRIANGLE");
			}
			if (!_isDead[4])
			{
				_worm[4].image = IMAGEMANAGER->findImage("SQUARE");
			}

		}
	}
}

void boss::render()
{

	if (_enemyState == E_REMOVED) {	}
	else
	{
		IMAGEMANAGER->findImage("체력바배경_보스")->render(getMemDC(), 100, WINSIZEY - 100);
		IMAGEMANAGER->findImage("체력바흰색_보스")->render(getMemDC(), 100, WINSIZEY - 100, 0, 0, _whiteGauge, 30);
		IMAGEMANAGER->findImage("체력바체력_보스")->render(getMemDC(), 100, WINSIZEY - 100, 0, 0, _hpGauge, 30);
	}

	for (int i = 1; i < _worm.size(); i++)
	{
		if (!_isDead[i])
		{
			_worm[i].image->alphaFrameRender(getMemDC(), _worm[i].rc.left - 60, _worm[i].rc.top - 60, _worm[i].indexX, _worm[i].indexY, _worm[i].alpha);
		}
	}

	if (_nowHp>0)
	{
		_worm[0].image->rotateFrameRender(getMemDC(), _worm[0].rc.left + 100, _worm[0].rc.top + 40, _worm[0].indexX, _worm[0].indexY, _worm[0].angle);
	}
	else
	{
		if(_enemyState == E_REMOVED)
		{ }
		else
		{
			_worm[0].image->alphaFrameRender(getMemDC(), _worm[0].rc.left + 100, _worm[0].rc.top + 40, _worm[0].indexX, _worm[0].indexY, _worm[0].alpha);
		}
	}


	for (int i = 0; i < _worm.size(); i++)
	{
	//	EllipseMakeCenter(getMemDC(), _worm[i].addx, _worm[i].addy, _worm[i].radius * 2, _worm[i].radius * 2);
		FrameRect(getMemDC(), _worm[i].rc, RGB(100, 100, 0));
	}

}

void boss::wormMove()
{

	for (int i = 0; i < _worm.size(); i++)
	{
		if (i == 0) //머리냐?
		{
			_worm[i].x += cosf(_worm[i].angle) * _worm[i].speed;
			_worm[i].y += -sinf(_worm[i].angle) * _worm[i].speed;

			//왼쪽
			if (_worm[i].x - _worm[i].radius < _imagePositionNow.x-_imagePositionBefore.x + 80)
			{
				_worm[i].x++;
				_worm[i].angle = PI - _worm[i].angle;
			}
			//오른쪽
			if (_worm[i].x + _worm[i].radius > _imagePositionNow.x - _imagePositionBefore.x + 2304 - 80)
			{
				_worm[i].x--;
				_worm[i].angle = PI - _worm[i].angle;
			}
			//위
			if (_worm[i].y - _worm[i].radius < _imagePositionNow.y - _imagePositionBefore.y - WINSIZEY + 100)
			{
				_worm[i].y++;
				_worm[i].angle = 2 * PI - _worm[i].angle;
			}
			//아래
			if (_worm[i].y + _worm[i].radius > _imagePositionNow.y - _imagePositionBefore.y + 1558 - WINSIZEY - 100)
			{
				_worm[i].y--;
				_worm[i].angle = 2 * PI - _worm[i].angle;
			}
		}
		else//몸통이냐?
		{
			float distance = getDistance(_worm[i].x, _worm[i].y, _worm[i - 1].x, _worm[i - 1].y);

			//거리가 벌어졌다는 의미는
			//각도가 달라졌다는 말임
			//각도가 달라졌으니 앞의 각도를 전달해주자
			if (_worm[i].radius * 2 < distance)
			{
				_worm[i].angle = getAngle(_worm[i].x, _worm[i].y, _worm[i - 1].x, _worm[i - 1].y);
				//위치를 살짝 보정해주기
				_worm[i].x = _worm[i - 1].x - cosf(_worm[i].angle) * (_worm[i].radius * 2);
				_worm[i].y = _worm[i - 1].y - (-sinf(_worm[i].angle)) * (_worm[i].radius * 2);
			}

			_worm[i].x += cosf(_worm[i].angle) * _worm[i].speed;
			_worm[i].y += -sinf(_worm[i].angle) * _worm[i].speed;
		}

		_worm[i].addx = _worm[i].x + _imagePositionNow.x - _imagePositionBefore.x;
		_worm[i].addy = _worm[i].y + _imagePositionNow.y - _imagePositionBefore.y;
		_worm[i].rc = RectMakeCenter(_worm[i].addx, _worm[i].addy, 140, 140);
		_vAttackRc[i] = _worm[i].rc;
	}//end of for (int i = 0; i < WORMMAX; i++)

}

