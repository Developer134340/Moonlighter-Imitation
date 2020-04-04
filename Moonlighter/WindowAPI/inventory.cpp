#include "stdafx.h"
#include "inventory.h"

HRESULT inventory::init()
{
	_appear = WINSIZEY;
	_appearA = 0;

	_isItemSelected = false;
	_itemName = RectMake(WINSIZEX / 2 - 155, _appear + 630, 310, 34);
	_selectItem = 0;
	_inventoryAppeared = false;
	ZeroMemory(&_selectedItem, sizeof(INVEN));

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				_inventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _appear + 194+50 + (72 * j), 52, 52);
			}
			else
			{
				_inventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _appear + 208+50 + (72 * j), 52, 52);
			}
		}
	}

	_equipmentRc[0] = RectMake(746, _appear + 80 + 50, 52, 52);
	_equipmentRc[1] = RectMake(920, _appear + 80 + 50, 52, 52);
	_equipmentRc[2] = RectMake(734, _appear + 242 + 50, 52, 52);
	_equipmentRc[3] = RectMake(662, _appear + 170 + 50, 52, 52);
	_equipmentRc[4] = RectMake(662, _appear + 242 + 50, 52, 52);
	_equipmentRc[5] = RectMake(662, _appear + 314 + 50, 52, 52);

	for (int i = 0; i < 20; i++)
	{
		_itemArray[i]._item = NULL;
		_itemArray[i]._itemIs = false;
		_itemArray[i]._num = 0;
		_itemArray[i]._rc = _inventoryRc[i];
	}

	for (int i = 0; i < 6; i++)
	{
		_equipmentArray[i]._item = NULL;
		_equipmentArray[i]._itemIs = false;
		_equipmentArray[i]._num = 0;
		_equipmentArray[i]._rc = _equipmentRc[i];
	}

	item* temp1;
	temp1 = new item;
	temp1->init("훈련용단검");
	_equipmentArray[0]._item = temp1;
	_equipmentArray[0]._itemIs = true;
	_equipmentArray[0]._num = 1;

	item* temp2;
	temp2 = new item;
	temp2->init("훈련용활");
	_equipmentArray[1]._item = temp2;
	_equipmentArray[1]._itemIs = true;
	_equipmentArray[1]._num = 1;

	return S_OK;
}

void inventory::release()
{
}

void inventory::update()
{

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				_inventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _appear + 84+ 50+ (72 * j), 52, 52);
			}
			else
			{
				_inventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _appear + 98 + 50+ (72 * j), 52, 52);
			}
		}
	}

	_equipmentRc[0] = RectMake(746, _appear + 80 + 50, 52, 52);
	_equipmentRc[1] = RectMake(920, _appear + 80 + 50, 52, 52);
	_equipmentRc[2] = RectMake(734, _appear + 242 + 50, 52, 52);
	_equipmentRc[3] = RectMake(662, _appear + 170 + 50, 52, 52);
	_equipmentRc[4] = RectMake(662, _appear + 242 + 50, 52, 52);
	_equipmentRc[5] = RectMake(662, _appear + 314 + 50, 52, 52);

	_itemName = RectMake(WINSIZEX / 2 - 155, _appear + 630, 310, 34);


	for (int i = 0; i < 20; i++)
	{
		_itemArray[i]._rc = _inventoryRc[i];
	}

	for (int i = 0; i < 6; i++)
	{
		_equipmentArray[i]._rc = _equipmentRc[i];
	}
	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		switch(_selectItem)
		{
		case 0:
			_selectItem = 21;
			break;
		case 5:
			_selectItem = 23;
			break;
		case 10:
			_selectItem = 22;
			break;
		case 15:
			_selectItem = 25;
			break;
		case 20:
			_selectItem = 4;
			break;
		case 22:
			_selectItem = 24;
			break;
		case 23:
			_selectItem = 9;
			break;
		case 24:
			_selectItem = 14;
			break;
		case 25:
			_selectItem = 23;
			break;
		default:
			_selectItem--;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		switch (_selectItem)
		{
		case 4:
			_selectItem = 20;
			break;
		case 9:
			_selectItem = 23;
			break;
		case 14:
			_selectItem = 24;
			break;
		case 19:
			_selectItem = 25;
			break;
		case 21:
			_selectItem = 0;
			break;
		case 22:
			_selectItem = 10;
			break;
		case 23:
			_selectItem = 5;
			break;
		case 24:
			_selectItem = 22;
			break;
		case 25:
			_selectItem = 15;
			break;
		default:
			_selectItem++;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('W'))
	{
		switch (_selectItem)
		{
		case 0:
			_selectItem = 15;
			break;
		case 1:
			_selectItem = 16;
			break;
		case 2:
			_selectItem = 17;
			break;
		case 3:
			_selectItem = 18;
			break;
		case 4:
			_selectItem = 19;
			break;
		case 20:
			_selectItem = 25;
			break;
		case 21:
			_selectItem = 22;
			break;
		case 22:
			_selectItem = 20;
			break;
		case 23:
			_selectItem = 20;
			break;
		case 24:
			_selectItem = 23;
			break;
		case 25:
			_selectItem = 24;
			break;
		default:
			_selectItem-=5;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))
	{
		switch (_selectItem)
		{
		case 15:
			_selectItem = 0;
			break;
		case 16:
			_selectItem = 1;
			break;
		case 17:
			_selectItem = 2;
			break;
		case 18:
			_selectItem = 3;
			break;
		case 19:
			_selectItem = 4;
			break;
		case 20:
			_selectItem = 23;
			break;
		case 21:
			_selectItem = 22;
			break;
		case 22:
			_selectItem = 20;
			break;
		case 23:
			_selectItem = 24;
			break;
		case 24:
			_selectItem = 25;
			break;
		case 25:
			_selectItem = 20;
			break;
		default:
			_selectItem += 5;
			break;
		}
	}

	if (_itemArray[_selectItem]._itemIs)
	{
		sprintf(_nameStr, "%s", _itemArray[_selectItem]._item->getItemKey());
	}

	//========================아이템 선택하기===================


	//아이템이 있고, 아이템을 처음 선택할 때

	if (_itemArray[_selectItem]._itemIs && KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_isItemSelected)
		{
			_selectedItem = _itemArray[_selectItem];
			_selectedItem._num = 1;
			_isItemSelected = true;
			_itemArray[_selectItem]._num--;
		}
		else if (_isItemSelected && _itemArray[_selectItem]._item->getItemKey() == _selectedItem._item->getItemKey())
		{
			_itemArray[_selectItem]._num--;
			_selectedItem._num++;
		}
		//아이템을 선택한 상태에서, 아이템이 있는 곳에 아이템을 놓을 때
		else if (_isItemSelected && _itemArray[_selectItem]._item -> getItemKey() != _selectedItem._item -> getItemKey())
		{
			INVEN temp;
			temp = _itemArray[_selectItem];
			_itemArray[_selectItem] = _selectedItem;
			_selectedItem = temp;
		}
		
	}

	//아이템을 선택한 상태에서, 아이템이 없고, 거기 아이템을 놓을 때
	if (_isItemSelected && !_itemArray[_selectItem]._itemIs && KEYMANAGER->isOnceKeyDown('J'))
	{
		_itemArray[_selectItem] = _selectedItem;
		ZeroMemory(&_selectedItem, sizeof(INVEN));
		_selectedItem._itemIs = false;
		_isItemSelected = false;
	}

	if (_itemArray[_selectItem]._num == 0)
	{
		ZeroMemory(&_itemArray[_selectItem], sizeof(INVEN));
	}
	
	for (int i = 0; i < 20; i++)
	{
		sprintf(_itemArray[i]._printNum, "%d", _itemArray[i]._num);
	}

	sprintf(_selectedItem._printNum, "%d", _selectedItem._num);
	sprintf(_equipmentArray[2]._printNum, "%d", _equipmentArray[2]._num);
	_selectedItem._rc = { 0,0,0,0 };
}

void inventory::render()
{
	IMAGEMANAGER->findImage("검은색")->alphaRender(getMemDC(), 0, 0, 160);
	IMAGEMANAGER->findImage("인벤토리")->render(getMemDC(), 120, _appear+50);

	if (_selectItem < 20)
	{
		IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _inventoryRc[_selectItem].left - 10, _inventoryRc[_selectItem].top - 10);
	}
	else
	{
		IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _equipmentRc[_selectItem-20].left - 10, _equipmentRc[_selectItem-20].top - 10);
	}

	if (KEYMANAGER->isToggleKey('P'))
	{
		for (int i = 0; i < 20; i++)
		{
			Rectangle(getMemDC(), _inventoryRc[i]);
		}

		for (int i = 0; i < 6; i++)
		{
			Rectangle(getMemDC(), _equipmentRc[i]);
		}

		Rectangle(getMemDC(), _itemName);

	}

	SetTextColor(getMemDC(), RGB(0, 0, 0));
	SetBkMode(getMemDC(), TRANSPARENT);
	
	for (int i = 0; i < 20; i++)
	{
		if (_itemArray[i]._itemIs)
		{
			IMAGEMANAGER->findImage(_itemArray[i]._item->getItemKey())->render(getMemDC(), _itemArray[i]._rc.left, _itemArray[i]._rc.top);
			//이거 추가
			TextOut(getMemDC(), _itemArray[i]._rc.right - 10, _itemArray[i]._rc.bottom - 10, _itemArray[i]._printNum, lstrlen(_itemArray[i]._printNum));
		}
	}

	if (_equipmentArray[2]._itemIs)
	{
		TextOut(getMemDC(), _equipmentArray[2]._rc.right - 10, _equipmentArray[2]._rc.bottom - 10, _equipmentArray[2]._printNum, lstrlen(_equipmentArray[2]._printNum));
	}

	for (int i = 0; i < 6; i++)
	{
		if (_equipmentArray[i]._itemIs)
		{
			IMAGEMANAGER->findImage(_equipmentArray[i]._item->getItemKey())->render(getMemDC(), _equipmentArray[i]._rc.left, _equipmentArray[i]._rc.top);
		}
	}

	if (_itemArray[_selectItem]._itemIs)
	{
		IMAGEMANAGER->findImage("아이템이름")->render(getMemDC(), _itemName.left, _itemName.top);

		HFONT font, oldfont;

		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "PFStardust");
		oldfont = (HFONT)SelectObject(getMemDC(), font);
		DrawText(getMemDC(), _itemArray[_selectItem]._item->getItemKey(), -1, &_itemName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		SelectObject(getMemDC(), oldfont);
		DeleteObject(font);
	
	}

	//========================선택한 아이템 출력===========================

	if (_isItemSelected)
	{
		IMAGEMANAGER->findImage("선택한아이템")->render(getMemDC(), _inventoryRc[_selectItem].left-5, _inventoryRc[_selectItem].top - 85);
		IMAGEMANAGER->findImage(_selectedItem._item->getItemKey())->render(getMemDC(), _inventoryRc[_selectItem].left+7, _inventoryRc[_selectItem].top -74);
		TextOut(getMemDC(), _inventoryRc[_selectItem].right - 7, _inventoryRc[_selectItem].top - 15, _selectedItem._printNum, lstrlen(_selectedItem._printNum));
	}


}

void inventory::inventoryAppear()
{
	_appearA += 5;
	_appear -= _appearA;
	if (_appear <= 0)
	{
		_appear = 0;
		_appearA = 0;
		_inventoryAppeared = true;
	}

}

void inventory::inventoryDisappear()
{
	if (_inventoryAppeared)
	{
		_appearA += 5;
		_appear += _appearA;

		if (_appear >= WINSIZEY)
		{
			_appear = WINSIZEY;
			_appearA = 0;
			_inventoryAppeared = false;
		}
	}
}

void inventory::save()
{
	HANDLE file;
	DWORD write;

	file = CreateFile("invenSave.inv", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file, _itemArray, sizeof(INVEN)*20, &write, NULL);
	CloseHandle(file);

	HANDLE file2;
	DWORD write2;

	file2 = CreateFile("equipSave.inv", GENERIC_WRITE, 0, NULL, CREATE_ALWAYS,
		FILE_ATTRIBUTE_NORMAL, NULL);
	WriteFile(file2, _equipmentArray, sizeof(INVEN) * 6, &write, NULL);
	CloseHandle(file2);
}

void inventory::load()
{
	HANDLE file;
	DWORD read;

	file = CreateFile("invenSave.inv", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file, _itemArray, sizeof(INVEN) * 20, &read, NULL);
	CloseHandle(file);

	HANDLE file2;
	DWORD read2;

	file2 = CreateFile("equipSave.inv", GENERIC_READ, 0, NULL, OPEN_EXISTING,
		FILE_ATTRIBUTE_NORMAL, NULL);
	ReadFile(file2, _equipmentArray, sizeof(INVEN) * 6, &read, NULL);
	CloseHandle(file2);
}


