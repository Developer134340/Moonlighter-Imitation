#include "stdafx.h"
#include "playerData.h"

HRESULT playerData::init()
{
	_money = 100;
	return S_OK;
}

void playerData::release()
{
}
