#include "stdafx.h"
#include "villageScene.h"

HRESULT villageScene::init()
{
	_player = new player;
	_player->init({WINSIZEX/2-49, WINSIZEY/2-49});
	_player->setImagePosition({ -1050, 1100 });
	_player->setPixelMap(IMAGEMANAGER->findImage("마을픽셀"));
	_player->setPlayerLocation(VILLAGE);
	_witchTalkOn = false;
	_witchStoreOn = false;
	_player->getUserInterface()->getInventory()->load();

	_enterShop = RectMake(600, 180, 80, 50);
	_enterDungeon = RectMake(1520, 307, 50, 120);
	_witchTalk = RectMake(_player->getImagePosition().x + 200, _player->getImagePosition().y + 220, 400, 250);
	_witchTalkIndex =  _witchSelectItem = 0;

	SOUNDMANAGER->addSound("TOWN_BGM", "gameSound/townBGM.mp3");
	SOUNDMANAGER->play("TOWN_BGM");


	_isGameOn = true;

	for (int i = 0; i < 2; i++)
	{
		_indexX[i] = 0;
		_indexY[i] = 0;
		_actCount[i] = 0;
	}


	return S_OK;
}

void villageScene::release()
{
	SAFE_DELETE(_player);
}

void villageScene::update()
{
	if (_isGameOn)
	{
		_count++;
		_player->setPlayerPositionBefore(_player->getPlayerPosition());
		_player->update();
		_player->pixelCollision();
		_player->camMove(IMAGEMANAGER->findImage("마을"));

		RECT temp;

		_enterShop = RectMake(600 + 1050 + _player->getImagePosition().x, -1100 + 180 + _player->getImagePosition().y, 80, 50);
		_enterDungeon = RectMake(1520 + 1050 + _player->getImagePosition().x, -1100 + 307 + _player->getImagePosition().y, 50, 120);
		_witchTalk = RectMake(_player->getImagePosition().x + 200, _player->getImagePosition().y + 220, 400, 250);

		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_enterShop))
		{
			_player->getUserInterface()->getInventory()->save();

			SOUNDMANAGER->stop("TOWN_BGM");
			SCENEMANAGER->loadScene("상점씬");
		}

		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_enterDungeon))
		{
			_player->getUserInterface()->getInventory()->save();

			SOUNDMANAGER->stop("TOWN_BGM");
			SCENEMANAGER->loadScene("던전씬");
		}

		if (KEYMANAGER->isOnceKeyDown('I'))
		{
			_player->getUserInterface()->setInventoryOn(true);
			_isGameOn = false;
		}

		//===========================NPC 배치=========================
		//마녀
		
		if (_indexY[0] == 0)
		{
			if (_count % 400 == 0)
			{
				_actCount[0]++;
				switch (_actCount[0] % 3)
				{
				case 0:
					_indexY[0] = 1;
					break;
				case 1:
					_indexY[0] = 2;
					break;
				case 2:
					_indexY[0] = 3;
					break;
				}
			}

			if (_count % 50 == 0)
			{
				_indexX[0] = 1;
			}
			
			if (_indexX[0] == 1 && _count % 15 == 0)
			{
				_indexX[0] = 0;
			}

		}
		else if (_indexY[0] == 1)
		{
			if (_count % 5 == 0)
			{
				_indexX[0]++;

				if (_indexX[0] > 23)
				{
					_indexX[0] = 0;
					_indexY[0] = 0;
				}
			}
		}
		else if (_indexY[0] == 2)
		{
			if (_count % 5 == 0)
			{
				_indexX[0]++;

				if (_indexX[0] > 10)
				{
					_indexX[0] = 0;
					_indexY[0] = 0;
				}
			}
		}
		else if (_indexY[0] == 3)
		{
			if (_count % 5 == 0)
			{
				_indexX[0]++;

				if (_indexX[0] > 25)
				{
					_indexX[0] = 0;
					_indexY[0] = 0;
				}
			}
		}

		//마녀끝
		//대장장이

		if (_indexY[1] == 0)
		{
			if (_count % 400 == 0)
			{
				_actCount[1]++;
				switch (_actCount[1] % 3)
				{
				case 0:
					_indexY[1] = 1;
					break;
				case 1:
					_indexY[1] = 2;
					break;
				case 2:
					_indexY[1] = 3;
					break;
				}
			}

			if (_count % 50 == 0)
			{
				_indexX[1] = 1;
			}

			if (_indexX[1] == 1 && _count % 15 == 0)
			{
				_indexX[1] = 0;
			}

		}
		else if (_indexY[1] == 1)
		{
			if (_count % 5 == 0)
			{
				_indexX[1]++;

				if (_indexX[1] > 12)
				{
					_indexX[1] = 0;
					_indexY[1] = 0;
				}
			}
		}
		else if (_indexY[1] == 2)
		{
			if (_count % 5 == 0)
			{
				_indexX[1]++;

				if (_indexX[1] > 17)
				{
					_indexX[1] = 0;
					_indexY[1] = 0;
				}
			}
		}
		else if (_indexY[1] == 3)
		{
			if (_count % 20 == 0)
			{
				_indexX[1]++;

				if (_indexX[1] > 2)
				{
					_indexX[1] = 0;
					_indexY[1] = 0;
				}
			}
		}

		//대장장이끝
		

		//===========================NPC 배치=========================

		if (IntersectRect(&temp, &_witchTalk, _player->getPlayerRcAddress()))
		{
			_witchTalkOn = true;
		}
		else {}

		if (_witchTalkOn)
		{
			if (_count % 5 == 0)
			{
				_witchTalkIndex++;
				if (_witchTalkIndex > 2)
				{
					_witchTalkIndex = 2;
				}
			}
		}

		if (_witchTalkOn && KEYMANAGER->isOnceKeyDown('U'))
		{
			_witchStoreOn = true;
			_isGameOn = false;
		}

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

		if (_witchStoreOn)
		{
			_player->getUserInterface()->update();
			for (int i = 0; i < 8; i++)
			{
				if (i < 4)
				{
					_witchSellRect[i] = RectMake(498 + (73 * i), 193, 60, 60);
				}
				else
				{
					_witchSellRect[i] = RectMake(498 + (73 * (i-4)), 266, 60, 60);
				}
			}

			if (KEYMANAGER->isOnceKeyDown('A'))
			{
				_witchSelectItem--;
				if (_witchSelectItem < 0)
				{
					_witchSelectItem = 7;
				}
			}
			else if (KEYMANAGER->isOnceKeyDown('D'))
			{
				_witchSelectItem++;
				if (_witchSelectItem > 7)
				{
					_witchSelectItem = 0;
				}

			}
			else if (KEYMANAGER->isOnceKeyDown('W'))
			{
				if (_witchSelectItem < 4)
				{
					_witchSelectItem += 4;
				}
				else
				{
					_witchSelectItem -= 4;
				}
			}
			else if (KEYMANAGER->isOnceKeyDown('S'))
			{
				if (_witchSelectItem < 4)
				{
					_witchSelectItem += 4;
				}
				else
				{
					_witchSelectItem -= 4;
				}
			}

			if (_witchSelectItem == 3 && KEYMANAGER->isOnceKeyDown('J'))
			{
				_player->getUserInterface()->setMoney(_player->getUserInterface()->getMoney() - 10);
				item* tempPotion;
				tempPotion = new item;
				tempPotion->init("포션");
				_player->getUserInterface()->getInventory()->addPotionInventory(tempPotion);
			}

			switch (_witchSelectItem)
			{
			case 0:
				sprintf(_itemName, "HP물약1");
				sprintf(_itemIntro, "체력을 10 회복");
				sprintf(_itemNum, "%d", 0);
				break;
			case 1:
				sprintf(_itemName, "HP물약2");
				sprintf(_itemIntro, "체력을 20 회복");
				sprintf(_itemNum, "%d", 0);
				break;
			case 2:
				sprintf(_itemName, "HP물약3");
				sprintf(_itemIntro, "체력을 30 회복");
				sprintf(_itemNum, "%d", 0);
				break;
			case 3:
				sprintf(_itemName, "HP물약4");
				sprintf(_itemIntro, "체력을 40 회복");
				if (_player->getUserInterface()->getInventory()->getEquipment(2)._itemIs)
				{
					sprintf(_itemNum, "%d", _player->getUserInterface()->getInventory()->getEquipment(2)._num);
				}
				else
				{
					sprintf(_itemNum, "%d", 0);
				}
				break;
			default:
				sprintf(_itemName, "");
				sprintf(_itemIntro, "");
				sprintf(_itemNum, "");
				break;
			}

			_printName = RectMake(873, 17, 298, 32);
			_printIntro = RectMake(912, 174, 247, 92);
			

			if (KEYMANAGER->isOnceKeyDown('L'))
			{
				_witchStoreOn = false;
				_isGameOn = true;
			}
		}
	}
}

void villageScene::render()
{

	IMAGEMANAGER->findImage("마을")->render(getMemDC(), _player->getImagePosition().x, _player->getImagePosition().y - (IMAGEMANAGER->findImage("마을")->getHeight() - WINSIZEY));

	if (KEYMANAGER->isToggleKey('P'))
	{
		IMAGEMANAGER->findImage("마을픽셀")->render(getMemDC(), _player->getImagePosition().x, _player->getImagePosition().y - (IMAGEMANAGER->findImage("마을")->getHeight() - WINSIZEY));
		Rectangle(getMemDC(), _enterShop);
		Rectangle(getMemDC(), _enterDungeon);
		FrameRect(getMemDC(), _witchTalk, RGB(255, 100, 255));
	}

	IMAGEMANAGER->findImage("마녀")->frameRender(getMemDC(), _player->getImagePosition().x + 300, _player->getImagePosition().y + 220, _indexX[0], _indexY[0]);
	IMAGEMANAGER->findImage("대장장이")->frameRender(getMemDC(), _player->getImagePosition().x + 1050 + 1040, _player->getImagePosition().y -1100 + 535 , _indexX[1], _indexY[1]);

	if (_witchTalkOn)
	{
		IMAGEMANAGER->findImage("말하기")->frameRender(getMemDC(), _player->getImagePosition().x + 400, _player->getImagePosition().y + 220, _witchTalkIndex, 0);
	}

	_player->render();

	if (_player->getUserInterface()->getInventoryOn())
	{
		_player->getUserInterface()->getInventory()->render();
	}

	if (_witchStoreOn)
	{
		IMAGEMANAGER->findImage("검은색")->alphaRender(getMemDC(), 0, 0, 160);
		IMAGEMANAGER->findImage("마녀UI")->render(getMemDC(), 0, 0);
		IMAGEMANAGER->findImage("아이템선택")->render(getMemDC(), _witchSellRect[_witchSelectItem].left - 4, _witchSellRect[_witchSelectItem].top - 4);

		HFONT font, oldfont;

		font = CreateFont(20, 0, 0, 0, 600, 0, 0, 0, HANGEUL_CHARSET, 0, 0, 0, 0, "PFStardust");
		oldfont = (HFONT)SelectObject(getMemDC(), font);
		DrawText(getMemDC(), _itemName, -1, &_printName, DT_CENTER | DT_VCENTER | DT_SINGLELINE);
		DrawText(getMemDC(), _itemIntro, -1, &_printIntro, DT_WORDBREAK);
		TextOut(getMemDC(), 956, 146, _itemNum, lstrlen(_itemNum));
		SelectObject(getMemDC(), oldfont);
		DeleteObject(font);
	}


}
