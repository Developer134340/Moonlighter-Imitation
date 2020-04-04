#include "stdafx.h"
#include "item.h"

HRESULT item::init(const char* key)
{
	_name = key;
	//_image = IMAGEMANAGER->findImage(_name);
	_rc = { 0,0,0,0 };

	if (_name == "훈련용단검")
	{
		_type = "단검";
		_cost = 100;
	}
	else if (_name == "훈련용활")
	{
		_type = "활";
		_cost = 100;
	}
	else if (_name == "포션")
	{
		_type = "포션";
		_cost = 10;
	}
	else if (_name == "강화석")
	{
		_cost = 10;
	}
	else if (_name == "냉각된용암")
	{
		_cost = 10;

	}
	else if (_name == "반자성모래")
	{
		_cost = 20;

	}
	else if (_name == "사막강철주괴")
	{
		_cost = 100;
	}
	else if (_name == "사막강철판금")
	{
		_cost = 150;
	}
	else if (_name == "사막밧줄")
	{
		_cost = 50;
	}
	else if (_name == "사막석")
	{
		_cost = 70;
	}
	else if (_name == "열자기엔진")
	{
		_cost = 300;
	}
	else if (_name == "풍부한젤리")
	{
		_cost = 10;
	}


	return S_OK;
}

void item::release()
{
}

void item::update()
{
}

void item::render()
{
	//_image->render(getMemDC(), _rc.left, _rc.top);
}
 