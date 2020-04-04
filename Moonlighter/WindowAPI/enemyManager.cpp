#include "stdafx.h"
#include "enemyManager.h"
#include "player.h"

HRESULT enemyManager::init()
{
	
	return S_OK;
}

void enemyManager::release()
{
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		SAFE_DELETE(_vEnemy[i]);
	}

	for (int i = 0; i < _vItem.size(); i++)
	{
		SAFE_DELETE(_vItem[i]);
	}

}

void enemyManager::update()
{
	slimeAbsorbedPlayer();
	enemyPlayerAttack();
	playerGetItem();

	for (int i = 0; i < _vItem.size(); i++)
	{
		_vItem[i]->update();
	}

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		_vEnemy[i]->setPlayerRc(_player->getPlayerRcAddress());
		_vEnemy[i]->setDestination(_player->getPlayerPosition());
		_vEnemy[i]->update();
	}


	sprintf(test, "enemySize : %d", _vEnemy.size());
}

void enemyManager::render()
{
	TextOut(getMemDC(), 0, 300, test, lstrlen(test));

}

void enemyManager::addEnemy()
{
	boss* temp;
	temp = new boss;
	temp->init(_player->getImagePosition());
	_vEnemy.push_back(temp);
}

void enemyManager::slimeAbsorbedPlayer()
{

	for (int i = 0; i < _vEnemy.size(); i++)
	{
		if (!_vEnemy[i]->getPlayerMove())
		{
			_player->setDirectionMoveDown(false);
			_player->setDirectionMoveUp(false);
			_player->setDirectionMoveLeft(false);
			_player->setDirectionMoveRight(false);
			break;
		}

		if (i == _vEnemy.size() - 1)
		{
			_player->setDirectionMoveDown(true);
			_player->setDirectionMoveUp(true);
			_player->setDirectionMoveLeft(true);
			_player->setDirectionMoveRight(true);
		}
	}
}

void enemyManager::playerEnemyAttack()
{
	RECT temp;

	for (int i = 0; i < _player->getPlayerAttack().size(); i++)
	{
		for (int j = 0; j < _vEnemy.size(); j++)
		{
			if (IntersectRect(&temp, &_player->getPlayerAttack()[i].rc, _vEnemy[j]->getEnemyRcAddress()))
			{
				_vEnemy[j]->setEnemyAttacked(_player->damage());
			}
		}
	}

	for (int j = 0; j < _vEnemy.size(); j++)
	{
		if (_vEnemy[j]->getEnemyState() == E_REMOVED)
		{
			const char* tempk;
			switch (RND->range(9))
			{
			case 0:
				tempk = "강화석";
				break;
			case 1:
				tempk = "냉각된용암";
				break;
			case 2:
				tempk = "반자성모래";
				break;
			case 3:
				tempk = "사막강철주괴";
				break;
			case 4:
				tempk = "사막강철판금";
				break;
			case 5:
				tempk = "사막밧줄";
				break;
			case 6:
				tempk = "사막석";
				break;
			case 7:
				tempk = "열자기엔진";
				break;
			case 8:
				tempk = "풍부한젤리";
				break;
			}
			item* temp;
			temp = new item;
			temp->init(tempk);
			temp->setItemPos(_vEnemy[j]->getEnemyPos());
			_vItem.push_back(temp);
			_vEnemy.erase(_vEnemy.begin() + j);
		}
	}
}

void enemyManager::enemyPlayerAttack()
{
	RECT temp;
	
	for (int i = 0; i < _vEnemy.size(); i++)
	{
		for (int j = 0; j < _vEnemy[i]->getEnemyAttackRc().size(); j++)
		{
			if (IntersectRect(&temp, &_vEnemy[i]->getEnemyAttackRc()[j], _player->getPlayerRcAddress()))
			{
				_player->setPlayerAttacked(_vEnemy[i]->damage());
			}
		}
	}
}

void enemyManager::playerGetItem()
{
	for (int i = 0; i < _vItem.size(); i++)
	{
		RECT temp;
		if (IntersectRect(&temp, _player->getPlayerRcAddress(), &_vItem[i]->getItemRc()))
		{
			_player->getUserInterface()->getInventory()->addInventory(_vItem[i]);
			_vItem.erase(_vItem.begin() + i);
			break;
		}
	}
}

void enemyManager::playerBossAttack()
{
	RECT temp;


	if (_vEnemy.size())
	{


	for (int i = 0; i < _player->getPlayerAttack().size(); i++)
	{
		for (int j = 0; j < _vEnemy[0]->getEnemyAttackRc().size() ;  j++)
		{
			if (IntersectRect(&temp, &_player->getPlayerAttack()[i].rc, &_vEnemy[0]->getEnemyAttackRc()[j]))
			{
				_vEnemy[0]->setEnemyAttacked(_player->damage());
			}
		}
	}

		if (_vEnemy[0]->getEnemyState() == E_REMOVED)
		{
			_vEnemy.clear();
		}
	}

}
