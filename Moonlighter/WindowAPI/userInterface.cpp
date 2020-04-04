#include "stdafx.h"
#include "userInterface.h"

HRESULT userInterface::init()
{

	_whiteGauge = _hpGauge;
	_inventoryOn = false;
	_invenAnimationOn = false;
	//_money = 100;
	_inventory = new inventory;
	_inventory->init();

	_nowEquip = _inventory->getEquipment(0)._item;

	_equipChange0 = WINSIZEX - 120;
	_equipChange1 = WINSIZEX - 100;
	_changeOn = false;

	_money = PLAYERDATA->getMoney();

	return S_OK;
}

void userInterface::release()
{
	_inventory->release();
}

void userInterface::update()
{
	PLAYERDATA->setMoney(_money);

	//=====================체력======================

	_hpGauge = 128 * ((float)_nowHp / (float)_maxHp);
	_whiteGauge -= 0.2f ;
	if (_whiteGauge < _hpGauge)
	{
		_whiteGauge = _hpGauge;
	}

	//==============================장비 바꾸기======================

	if (KEYMANAGER->isOnceKeyDown('Z'))
	{
		if (_nowEquip == _inventory->getEquipment(0)._item)
		{
			_nowEquip = _inventory->getEquipment(1)._item;
		}
		else
		{
			_nowEquip = _inventory->getEquipment(0)._item;
		}
		
		_changeOn = true;
	}

	if (_changeOn)
	{
		_equipChange0++;
		_equipChange1--;

		if (_equipChange0 == _equipChange1)
		{
			_changeOn = false;
		}
	}

	if (!_changeOn)
	{
		_equipChange0--;
		_equipChange1++;

		if (_equipChange0 <= WINSIZEX - 120)
		{
			_equipChange0 = WINSIZEX - 120;
		}
		if (_equipChange1 >= WINSIZEX - 100)
		{
			_equipChange1 = WINSIZEX - 100;
		}
	}

	sprintf(_printMoney, "%d", _money);

}

void userInterface::render()
{

	IMAGEMANAGER->findImage("UI돈배경")->render(getMemDC(), _equipChange0, 40);
	IMAGEMANAGER->findImage("UI써클")->render(getMemDC(), _equipChange1, 40);
	IMAGEMANAGER->findImage("UI써클")->render(getMemDC(), WINSIZEX - 100, 140);
	IMAGEMANAGER->findImage("UI가방")->render(getMemDC(), WINSIZEX - 84, 154);

	IMAGEMANAGER->findImage(_nowEquip->getItemKey())->render(getMemDC(), _equipChange1 + 12, 50);
	IMAGEMANAGER->findImage("UI2")->render(getMemDC(), _equipChange0-25, 40);
	IMAGEMANAGER->findImage("UI1")->render(getMemDC(), _equipChange1-20, 40);

	IMAGEMANAGER->findImage("UI돈배경")->render(getMemDC(), 30, 20);
	IMAGEMANAGER->findImage("UI돈주머니")->render(getMemDC(), 46, 32);
	IMAGEMANAGER->findImage("UI체력바완성")->render(getMemDC(), 120, 30);
	IMAGEMANAGER->findImage("UI체력바흰색")->render(getMemDC(), 174, 44, 0, 0, _whiteGauge, 24);
	IMAGEMANAGER->findImage("UI체력바체력")->render(getMemDC(), 174, 44, 0, 0, _hpGauge, 24);
	IMAGEMANAGER->findImage("UI코인")->render(getMemDC(), 25, 100);
	
//	HFONT font, oldfont;

//	font = CreateFont(20, 0, 0, 0, 0, 0, 0, 0, HANGEUL_CHARSET, 3, 2, 1,
//		VARIABLE_PITCH | FF_ROMAN, "궁서");
	SetTextColor(getMemDC(), RGB(255, 255, 255));
	SetBkMode(getMemDC(), TRANSPARENT);
//	oldfont = (HFONT)SelectObject(getMemDC(), font);
	TextOut(getMemDC(), 50, 101, _printMoney, lstrlen(_printMoney));
//	SelectObject(getMemDC(), oldfont);
//	DeleteObject(font);
}
