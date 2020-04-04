#include "stdafx.h"
#include "useMap.h"

HRESULT useMap::init()
{
	for (int i = 0; i < 10; i++)
	{
		_arrayRoom[i] = new useMapRoom;
		_arrayRoom[i]->init();
	}

	_roomIndex = 0;

	return S_OK;
}

void useMap::release()
{
//	for (int i = 0; i < 10; i++)
//	{
//		_arrayRoom[i]->release();
//	}

//	_bossRoom->release();
}

void useMap::update()
{

	_arrayRoom[_roomIndex]->update();

}

void useMap::render()
{

	_arrayRoom[_roomIndex]->render();


}


