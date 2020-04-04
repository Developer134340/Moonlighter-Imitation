#pragma once
#include "gameNode.h"
#include "item.h"

struct INVEN
{
	item* _item;
	RECT _rc;
	int _num;
	bool _itemIs;
	char _printNum[10];
};


class inventory :
	public gameNode
{
	INVEN _itemArray[20];
	INVEN _equipmentArray[6];

	RECT _inventoryRc[20];
	RECT _equipmentRc[6];
	int _selectItem;
	bool _isItemSelected;
	INVEN _selectedItem;
	

	int _alpha;
	int _alphaA;
	int _appear;
	int _appearA;

	RECT _itemName;

	char _nameStr[100];
	bool _inventoryAppeared;

public:
	HRESULT init();
	void release();
	void update();
	void render();

	INVEN getEquipment(int x) { return _equipmentArray[x]; }
	INVEN getInventoryItem(int x) { return _itemArray[x]; }
	void setInventoryItem(int x, INVEN _tempInven) { _itemArray[x] = _tempInven; }
	void addInventory(item* tempItem)
	{
		for (int i = 0; i < 20; i++)
		{
			if (!_itemArray[i]._itemIs)
			{
				_itemArray[i]._item = tempItem;
				_itemArray[i]._num = 1;
				_itemArray[i]._itemIs = true;
				break;
			}
			else if (_itemArray[i]._itemIs && _itemArray[i]._item->getItemKey() == tempItem->getItemKey())
			{
				_itemArray[i]._num++;
				break;
			}
		}
	}

	void addPotionInventory(item* tempItem)
	{
		if (!_equipmentArray[2]._itemIs)
		{
			_equipmentArray[2]._item = tempItem;
			_equipmentArray[2]._num = 1;
			_equipmentArray[2]._itemIs = true;
		}
		else
		{
			_equipmentArray[2]._num++;
		}
			
	}

	void inventoryAppear();
	void inventoryDisappear();
	bool getInventoryAppeared() { return _inventoryAppeared; }
	void setInvenItemNum(int x, int y) { _itemArray[x]._num = y; };
	int getInvenItemNum(int x) { return _itemArray[x]._num; }

	void save();
	void load();

	inventory() {}
	~inventory() {}
};

