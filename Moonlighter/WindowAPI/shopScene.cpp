#include "stdafx.h"
#include "shopScene.h"

HRESULT shopScene::init()
{
	_player = new player;
	_player->init({WINSIZEX/2-49, WINSIZEY-300});
	_player->setImagePosition({ 180, -100 });
	_player->setPixelMap(IMAGEMANAGER->findImage("상점픽셀"));
	_isShop = true;
	_npcGo = false;
	_player->setPlayerLocation(SHOP);
	_isPlaceJOn = false;
	_isSellJOn = false;
	_sellingStandOn = false;
	_standLocation = WINSIZEY;
	_standLocationA = 0;
	_sellingStandDisappear = false;
	_selectSellItem = 0;
	_shopOpen = false;
	_shopOpenJOn = false;
	_shopOpenIndexX = _shopLoadingIndexX = 0;
	_npcIs = false;

	SOUNDMANAGER->addSound("SHOP_BGM", "gameSound/shopBGM.mp3");
	SOUNDMANAGER->play("SHOP_BGM");

	_corridor = RectMake(530, 150, 100, 30);
	_shopDoor = RectMake(530, 444, 100, 30);
	_shopPosition = -100;
	_isGameOn = true;
	_count = 0;

	_sellRc[0] = RectMake(353, 291, 47, 46);
	_sellRc[1] = RectMake(400, 291, 47, 46);
	_sellRc[2] = RectMake(353, 337, 47, 46);
	_sellRc[3] = RectMake(400, 337, 47, 46);
	_counterRc = RectMake(520, 290, 200, 70);
	_sellRangeRc = RectMake(345, 280, 110, 110);

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				_sellInventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _standLocation + 164 + (72 * j), 52, 52);
			}
			else
			{
				_sellInventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _standLocation + 178 + (72 * j), 52, 52);
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_sellStandArray[i]._item = NULL;
		_sellStandArray[i]._itemIs = false;
		_sellStandArray[i]._num = 0;
		_sellStandArray[i]._rc = _sellRc[i];
	}

	_player->getUserInterface()->getInventory()->load();

	for (int i = 0; i < 20; i++)
	{
		_sellItemArray[i] = _player->getUserInterface()->getInventory()->getInventoryItem(i);
	}

	ZeroMemory(&_sellSelectedItem, sizeof(INVEN));
	_isSellItemSelected = false;

	item* temp3;
	temp3 = new item;
	temp3->init("사막강철판금");
	_player->getUserInterface()->getInventory()->addInventory(temp3);

	item* temp4;
	temp4 = new item;
	temp4->init("사막강철판금");
	_player->getUserInterface()->getInventory()->addInventory(temp4);



	return S_OK;
}

void shopScene::release()
{
	SAFE_DELETE(_player);
}

void shopScene::update()
{
	if (_isGameOn)
	{
		_count++;

		_player->update();
		_player->pixelCollision();
		_corridor = RectMake(_player->getImagePosition().x + 530 - 180, _player->getImagePosition().y + 100 + 150, 100, 30);
		_shopDoor = RectMake(_player->getImagePosition().x + 530 - 180, _player->getImagePosition().y + 444 + 150, 100, 30);

		_sellRc[0] = RectMake(_player->getImagePosition().x + 353 - 180, _player->getImagePosition().y + 100 + 291, 47, 46);
		_sellRc[1] = RectMake(_player->getImagePosition().x + 400 - 180, _player->getImagePosition().y + 100 + 291, 47, 46);
		_sellRc[2] = RectMake(_player->getImagePosition().x + 353 - 180, _player->getImagePosition().y + 100 + 337, 47, 46);
		_sellRc[3] = RectMake(_player->getImagePosition().x + 400 - 180, _player->getImagePosition().y + 100 + 337, 47, 46);
		_counterRc = RectMake(_player->getImagePosition().x + 525 - 180, _player->getImagePosition().y + 100 + 293, 192, 63);
		_sellRangeRc = RectMake(_player->getImagePosition().x - 180 + 345, _player->getImagePosition().y+100 + 280, 110, 110);

		RECT temp;

		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_corridor))
		{
			if (_isShop && _player->getPlayerDirection() == UP)
			{
				_isShop = false;
			}
			else if (!_isShop && _player->getPlayerDirection() == DOWN)
			{
				_isShop = true;
			}
		}

		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_shopDoor))
		{
			_shopOpenJOn = true;
		}
		else
		{
			_shopOpenJOn = false;
			_shopOpenIndexX = 0;
		}

		if (_shopOpenJOn)
		{
			if (_count % 10 == 0)
			{
				_shopOpenIndexX++;
			}

			if (_shopOpenIndexX > 8)
			{
				_shopOpenIndexX = 8;
			}
		}

		if (_isShop)
		{
			if (_shopPosition == -100) {}
			else
			{
				_shopPosition -= 4;
				_player->setPlayerPositionY(_player->getPlayerPosition().y - 4);
			}
			_player->setImagePosition({ 180, _shopPosition });
		}
		else
		{
			if (_shopPosition == 180) {}
			else
			{
				_shopPosition += 4;
				_player->setPlayerPositionY(_player->getPlayerPosition().y + 4);
			}
			_player->setImagePosition({ 180, _shopPosition });
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_player->getUserInterface()->setInventoryOn(true);
			_isGameOn = false;
		}


		//=====================================J 누르면 넘어가기===============================
	

		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_sellRangeRc))
		{
			_isPlaceJOn = true;
		}
		else
		{
			_isPlaceJOn = false;
		}

		if (_isPlaceJOn && KEYMANAGER->isOnceKeyDown('J'))
		{
			for (int i = 0; i < 20; i++)
			{
				_sellItemArray[i] = _player->getUserInterface()->getInventory()->getInventoryItem(i);
			}
			_sellingStandOn = true;
			_isGameOn = false;
		}

		if (!_shopOpen && _shopOpenJOn && KEYMANAGER->isStayKeyDown('J'))
		{
			_shopLoadingIndexX++;

			if (_shopLoadingIndexX > 39)
			{
				_shopLoadingIndexX = 39;
				_shopOpen = true;
				_shopOpenJOn = false;
			}
		}

		if (!_shopOpen && _shopOpenJOn && KEYMANAGER->isOnceKeyUp('J'))
		{
			_player->getUserInterface()->getInventory()->save();
			_shopOpenJOn = false;
			SCENEMANAGER->loadScene("마을씬");
			SOUNDMANAGER->stop("SHOP_BGM");
		}

		//===========================상점이 열리면==================
		//===========================상점이 열리면==================
		//===========================상점이 열리면==================

		if (_shopOpen)
		{

			if (!_npcIs)
			{
				for (int i = 0; i < 4; i++)
				{
					if (_sellStandArray[i]._itemIs)
					{
						break;
					}

					if (i == 3)
					{
						_shopOpen = false;
					}
				}

				_npc = new npc;

				switch (RND->range(3))
				{
				case 0:
					_npc->init("npc1");
					break;
				case 1:
					_npc->init("npc2");
					break;
				case 2:
					_npc->init("npc3");
					break;
				}

				if (!_shopOpen) {}
				else
				{
					while (1)
					{
						int tempInt = RND->range(4);
						if (_sellStandArray[tempInt]._itemIs)
						{
							_npc->setNPCgoingCell(tempInt);
							break;
						}
					}

					_npcIs = true;
				}

			}

			if (_npcIs)
			{
				_npc->update();

				if (_npc->getNPCstate() == N_BUYING)
				{
					switch (_npc->getNPCgoingCell())
					{
					case 0:
						if (_sellStandArray[0]._itemIs)
						{
							_tempCost = _sellStandArray[0]._item->getItemCost();
							_tempNum = _sellStandArray[0]._num;
							ZeroMemory(&_sellStandArray[0], sizeof(INVEN));
						}
						break;
					case 1:
						if (_sellStandArray[1]._itemIs)
						{
							_tempCost = _sellStandArray[1]._item->getItemCost();
							_tempNum = _sellStandArray[1]._num;
							ZeroMemory(&_sellStandArray[1], sizeof(INVEN));
						}
						break;
					case 2:
						if (_sellStandArray[2]._itemIs)
						{
							_tempCost = _sellStandArray[2]._item->getItemCost();
							_tempNum = _sellStandArray[2]._num;
							ZeroMemory(&_sellStandArray[2], sizeof(INVEN));
						}
						break;
					case 3:
						if (_sellStandArray[3]._itemIs)
						{
							_tempCost = _sellStandArray[3]._item->getItemCost();
							_tempNum = _sellStandArray[3]._num;
							ZeroMemory(&_sellStandArray[3], sizeof(INVEN));
						}
						break;
					}
				}

				if (_npc->getNPCstate() == N_WAITING && _isSellJOn && KEYMANAGER->isOnceKeyDown('J'))
				{
					_npc->setNPCdirection(N_DOWN);
					_npc->setNPCstate(N_BOUGHT);
					_npc->setNPCstop(false);
					_player->getUserInterface()->setMoney(_player->getUserInterface()->getMoney() +(_tempCost*_tempNum));

				}

				if (_npc->getNPCstate() == N_WAITING && IntersectRect(&temp, _player->getPlayerRcAddress(), &_counterRc))
				{
					_isSellJOn = true;
				}
				else
				{
					_isSellJOn = false;
				}

				if (_npc->getNPCstate() == N_FINISHED)
				{
					_npcGo = false;
					_npcIs = false;
				}

			}





		}

		//=====================================J 누르면 넘어가기 끝===============================
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

		if (_sellingStandOn)
		{
			this->sellingStand();
		}

	}
}

//===========================================렌더렌더렌더======================================
//===========================================렌더렌더렌더======================================
//===========================================렌더렌더렌더======================================

void shopScene::render()
{
	IMAGEMANAGER->findImage("상점")->render(getMemDC(), _player->getImagePosition().x, _player->getImagePosition().y - (IMAGEMANAGER->findImage("상점")->getHeight() - WINSIZEY));
	if (KEYMANAGER->isToggleKey('P'))
	{
		IMAGEMANAGER->findImage("상점픽셀")->render(getMemDC(), _player->getImagePosition().x, _player->getImagePosition().y - (IMAGEMANAGER->findImage("상점")->getHeight() - WINSIZEY));
		Rectangle(getMemDC(), _corridor);
		Rectangle(getMemDC(), _shopDoor);

	}
	if (KEYMANAGER->isToggleKey('P'))
	{
		FrameRect(getMemDC(), _counterRc, RGB(255, 100, 100));
		FrameRect(getMemDC(), _sellRangeRc, RGB(255, 100, 100));
	}
	for (int i = 0; i < 4; i++)
	{
		if (_sellStandArray[i]._itemIs)
		{
			IMAGEMANAGER->findImage(_sellStandArray[i]._item->getItemKey())->render(getMemDC(), _sellRc[i].left, _sellRc[i].top);
		}
	}

	if (_isPlaceJOn)
	{
		IMAGEMANAGER->findImage("배치")->render(getMemDC(), _sellRc[1].right, _sellRc[1].top - 50);
	}

	if (_isSellJOn)
	{
		IMAGEMANAGER->findImage("판매")->render(getMemDC(), (_counterRc.right + _counterRc.left) / 2, _counterRc.top - 50);
	}

	_player->render();

	IMAGEMANAGER->findImage("상점천장")->render(getMemDC(), _player->getImagePosition().x + 530 - 190, _player->getImagePosition().y + 100 + 112);

	if (_player->getUserInterface()->getInventoryOn())
	{
		_player->getUserInterface()->getInventory()->render();
	}

	if (_sellingStandOn)
	{
		IMAGEMANAGER->findImage("검은색")->alphaRender(getMemDC(), 0, 0, 160);
		IMAGEMANAGER->findImage("판매대")->render(getMemDC(), 120, _standLocation + 80);
		if (_selectSellItem < 20)
		{
			IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _sellInventoryRc[_selectSellItem].left - 10, _sellInventoryRc[_selectSellItem].top - 10);
		}
		else
		{
			IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _standItemRc[_selectSellItem - 20].left - 10, _standItemRc[_selectSellItem - 20].top - 10);
		}
		SetTextColor(getMemDC(), RGB(0, 0, 0));

		for (int i = 0; i < 20; i++)
		{
			if (_sellItemArray[i]._itemIs)
			{
				IMAGEMANAGER->findImage(_sellItemArray[i]._item->getItemKey())->render(getMemDC(), _sellItemArray[i]._rc.left, _sellItemArray[i]._rc.top);
				TextOut(getMemDC(), _sellItemArray[i]._rc.right - 10, _sellItemArray[i]._rc.bottom - 10, _sellItemArray[i]._printNum, lstrlen(_sellItemArray[i]._printNum));
			}

		}

		for (int i = 0; i < 4; i++)
		{
			if (_sellStandArray[i]._itemIs)
			{
				IMAGEMANAGER->findImage(_sellStandArray[i]._item->getItemKey())->render(getMemDC(), _sellStandArray[i]._rc.left, _sellStandArray[i]._rc.top);
				TextOut(getMemDC(), _sellStandArray[i]._rc.right - 10, _sellStandArray[i]._rc.bottom - 10, _sellStandArray[i]._printNum, lstrlen(_sellStandArray[i]._printNum));
			}
		}

		HFONT font, oldfont;
		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "PFStardust");
		oldfont = (HFONT)SelectObject(getMemDC(), font);

		if (_sellStandArray[0]._itemIs)
		{
			TextOut(getMemDC(), _sellStandArray[0]._rc.left + 70, _sellStandArray[0]._rc.bottom + 88, _printCost1, lstrlen(_printCost1));
			DrawText(getMemDC(), _sellStandArray[0]._item->getItemKey(), -1, &_sellingItemName[0], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (_sellStandArray[1]._itemIs)
		{
			TextOut(getMemDC(), _sellStandArray[1]._rc.left + 70, _sellStandArray[1]._rc.bottom + 88, _printCost2, lstrlen(_printCost2));
			DrawText(getMemDC(), _sellStandArray[1]._item->getItemKey(), -1, &_sellingItemName[1], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (_sellStandArray[2]._itemIs)
		{
			TextOut(getMemDC(), _sellStandArray[2]._rc.left + 70, _sellStandArray[2]._rc.bottom + 88, _printCost3, lstrlen(_printCost3));
			DrawText(getMemDC(), _sellStandArray[2]._item->getItemKey(), -1, &_sellingItemName[2], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		if (_sellStandArray[3]._itemIs)
		{
			TextOut(getMemDC(), _sellStandArray[3]._rc.left + 70, _sellStandArray[3]._rc.bottom + 88, _printCost4, lstrlen(_printCost4));
			DrawText(getMemDC(), _sellStandArray[3]._item->getItemKey(), -1, &_sellingItemName[3], DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		}
		SelectObject(getMemDC(), oldfont);
		DeleteObject(font);

	}

	//========================선택한 아이템 출력===========================

	if (_isSellItemSelected)
	{
		IMAGEMANAGER->findImage("선택한아이템")->render(getMemDC(), _sellInventoryRc[_selectSellItem].left - 5, _sellInventoryRc[_selectSellItem].top - 85);
		IMAGEMANAGER->findImage(_sellSelectedItem._item->getItemKey())->render(getMemDC(), _sellInventoryRc[_selectSellItem].left + 7, _sellInventoryRc[_selectSellItem].top - 74);
		TextOut(getMemDC(), _sellInventoryRc[_selectSellItem].right - 7, _sellInventoryRc[_selectSellItem].top - 15, _sellSelectedItem._printNum, lstrlen(_sellSelectedItem._printNum));
	}

	if (_shopOpenJOn && !_shopOpen)
	{
		IMAGEMANAGER->findImage("상점나가기버튼")->frameRender(getMemDC(), 630, 400, _shopOpenIndexX, 0);
		IMAGEMANAGER->findImage("버튼길게누르기")->frameRender(getMemDC(), 800, 500, _shopLoadingIndexX, 0);
	}

	if (_shopOpen)
	{
		_npc->render();
	}
}

void shopScene::sellingStand()
{


	if (_sellStandArray[0]._itemIs)
	{
		sprintf(_printCost1, "%d", _sellStandArray[0]._item->getItemCost() * _sellStandArray[0]._num);
	}
	if (_sellStandArray[1]._itemIs)
	{
		sprintf(_printCost2, "%d", _sellStandArray[1]._item->getItemCost() * _sellStandArray[1]._num);
	}
	if (_sellStandArray[2]._itemIs)
	{
		sprintf(_printCost3, "%d", _sellStandArray[2]._item->getItemCost() * _sellStandArray[2]._num);
	}
	if (_sellStandArray[3]._itemIs)
	{
		sprintf(_printCost4, "%d", _sellStandArray[3]._item->getItemCost() * _sellStandArray[3]._num);
	}


	if (!_sellingStandDisappear)
	{
		_standLocationA += 5;
		_standLocation -= _standLocationA;

		if (_standLocation <= 0)
		{
			_standLocation = 0;
			_standLocationA = 0;
		}
	}

	for (int i = 0; i < 5; i++)
	{
		for (int j = 0; j < 4; j++)
		{
			if (j == 0)
			{
				_sellInventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _standLocation + 164  + (72 * j), 52, 52);
			}
			else
			{
				_sellInventoryRc[j * 5 + i] = RectMake(219 + (71 * i), _standLocation + 178 + (72 * j), 52, 52);
			}
		}
	}

	_standItemRc[0] = RectMake(735, _standLocation + 144, 52, 52);
	_standItemRc[1] = RectMake(979, _standLocation + 144, 52, 52);
	_standItemRc[2] = RectMake(735, _standLocation + 374, 52, 52);
	_standItemRc[3] = RectMake(979, _standLocation + 374, 52, 52);

	if (_sellingStandOn && KEYMANAGER->isOnceKeyDown('L'))
	{
		_sellingStandDisappear = true;
	}

	//========================아이템 선택하기===================


//아이템이 있고, 아이템을 처음 선택할 때

	if (_sellItemArray[_selectSellItem]._itemIs && KEYMANAGER->isOnceKeyDown('J'))
	{
		if (!_isSellItemSelected)
		{
			_sellSelectedItem = _sellItemArray[_selectSellItem];
			_sellSelectedItem._num = 1;
			_isSellItemSelected = true;
			_sellItemArray[_selectSellItem]._num--;
		}
		else if (_isSellItemSelected && _sellItemArray[_selectSellItem]._item == _sellSelectedItem._item)
		{
			_sellItemArray[_selectSellItem]._num--;
			_sellSelectedItem._num++;
		}
		//아이템을 선택한 상태에서, 아이템이 있는 곳에 아이템을 놓을 때
		else if (_isSellItemSelected && _sellItemArray[_selectSellItem]._item != _sellSelectedItem._item)
		{
			INVEN temp;
			temp = _sellItemArray[_selectSellItem];
			_sellItemArray[_selectSellItem] = _sellSelectedItem;
			_sellSelectedItem = temp;
		}

	}

	//아이템을 선택한 상태에서, 아이템이 없고, 거기 아이템을 놓을 때
	if (_isSellItemSelected && !_sellItemArray[_selectSellItem]._itemIs && KEYMANAGER->isOnceKeyDown('J'))
	{
		_sellItemArray[_selectSellItem] = _sellSelectedItem;
		ZeroMemory(&_sellSelectedItem, sizeof(INVEN));
		_sellSelectedItem._itemIs = false;
		_isSellItemSelected = false;
	}

	if (_sellItemArray[_selectSellItem]._num == 0)
	{
		ZeroMemory(&_sellItemArray[_selectSellItem], sizeof(INVEN));
	}

	for (int i = 0; i < 20; i++)
	{
		sprintf(_sellItemArray[i]._printNum, "%d", _sellItemArray[i]._num);
	}

	for (int i = 0; i < 4; i++)
	{
		sprintf(_sellStandArray[i]._printNum, "%d", _sellStandArray[i]._num);
	}

	sprintf(_sellSelectedItem._printNum, "%d", _sellSelectedItem._num);
	_sellSelectedItem._rc = { 0,0,0,0 };

	for (int i = 0; i < 20; i++)
	{
		_sellItemArray[i]._rc = _sellInventoryRc[i];
	}

	for (int i = 0; i < 4; i++)
	{
		_sellStandArray[i]._rc = _standItemRc[i];
	}
	
	for (int i = 0; i < 20; i++)
	{
		_sellItemArray[i]._rc = _sellInventoryRc[i];
	}
	if (_sellingStandDisappear)
	{
		_standLocationA += 5;
		_standLocation += _standLocationA;

		if (_standLocation >= WINSIZEY)
		{
			_standLocation = WINSIZEY;
			_standLocationA = 0;
			_sellingStandOn = false;
			_sellingStandDisappear = false;
			_isGameOn = true;
			for (int i = 0; i < 20; i++)
			{
				_player->getUserInterface()->getInventory()->setInventoryItem(i, _sellItemArray[i]);
			}
		}
	}

	for (int i = 0; i < 4; i++)
	{
		_sellingItemName[i] = RectMake(_sellStandArray[i]._rc.left - 24, _sellStandArray[i]._rc.bottom + 25, 100, 60);
	}


	if (KEYMANAGER->isOnceKeyDown('A'))
	{
		switch (_selectSellItem)
		{
		case 0:
			_selectSellItem = 21;
			break;
		case 5:
			_selectSellItem = 21;
			break;
		case 10:
			_selectSellItem = 23;
			break;
		case 15:
			_selectSellItem = 23;
			break;
		case 20:
			_selectSellItem = 4;
			break;
		case 22:
			_selectSellItem = 14;
			break;
		default:
			_selectSellItem --;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('D'))
	{
		switch (_selectSellItem)
		{
		case 4:
			_selectSellItem = 20;
			break;
		case 9:
			_selectSellItem = 20;
			break;
		case 14:
			_selectSellItem = 22;
			break;
		case 19:
			_selectSellItem = 22;
			break;
		case 21:
			_selectSellItem = 0;
			break;
		case 23:
			_selectSellItem = 10;
			break;
		default:
			_selectSellItem++;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('W'))
	{
		switch (_selectSellItem)
		{
		case 0:
			_selectSellItem = 15;
			break;
		case 1:
			_selectSellItem = 16;
			break;
		case 2:
			_selectSellItem = 17;
			break;
		case 3:
			_selectSellItem = 18;
			break;
		case 4:
			_selectSellItem = 19;
			break;
		case 20:
			_selectSellItem = 22;
			break;
		case 21:
			_selectSellItem = 23;
			break;
		case 22:
			_selectSellItem = 20;
			break;
		case 23:
			_selectSellItem = 21;
			break;
		default:
			_selectSellItem -= 5;
			break;
		}
	}
	else if (KEYMANAGER->isOnceKeyDown('S'))
	{
		switch (_selectSellItem)
		{
		case 15:
			_selectSellItem = 0;
			break;
		case 16:
			_selectSellItem = 1;
			break;
		case 17:
			_selectSellItem = 2;
			break;
		case 18:
			_selectSellItem = 3;
			break;
		case 19:
			_selectSellItem = 4;
			break;
		case 20:
			_selectSellItem = 22;
			break;
		case 21:
			_selectSellItem = 23;
			break;
		case 22:
			_selectSellItem = 20;
			break;
		case 23:
			_selectSellItem = 21;
			break;
		default:
			_selectSellItem += 5;
			break;
		}
	}

}
