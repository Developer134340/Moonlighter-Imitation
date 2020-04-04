#include "stdafx.h"
#include "npc.h"

HRESULT npc::init(const char* key)
{
	_name = key;
	_image = IMAGEMANAGER->findImage(_name);
	_nowX = _nowY = 5;
	_destX = _destY = 5;
	_npcState = N_NORMAL;

	_ncount = _indexX = _indexY = 0;
	_npcMove = N_UP;
	_stop = false;
	_speed = 1;
	_moveOk = false;
	this->astarInit();

	return S_OK;
}

void npc::release()
{
}

void npc::update()
{
	_ncount++;
	_rc = RectMake(_pos.x - 23, _pos.y - 45, 45, 45);

	if (_npcMove == N_UP)
	{
		_indexY = 0;
		if (!_stop)
		{
			_pos.y -= _speed;
		}
	}
	else if (_npcMove == N_LEFT)
	{
		_indexY = 1;
		if (!_stop)
		{
			_pos.x -= _speed;
		}
	}
	else if (_npcMove == N_DOWN)
	{
		_indexY = 2;
		if (!_stop)
		{
			_pos.y += _speed;
		}
	}
	else if (_npcMove == N_RIGHT)
	{
		_indexY = 3;
		if (!_stop)
		{
			_pos.x += _speed;
		}
	}

	if (!_stop)
	{
		if (_ncount % 5 == 0)
		{
			_indexX++;
			if (_indexX > 7)
			{
				_indexX = 0;
			}
		}
	}
	else
	{
		_indexX = 7;
	}

	//====================================인덱스 바꿔주기 끝

	if (_npcState == N_THINKING)
	{
		switch (_goingCell)
		{
		case 0:
			_npcMove = N_RIGHT;
			break;
		case 1:
			_npcMove = N_LEFT;
			break;
		case 2:
			_npcMove = N_RIGHT;
			break;
		case 3:
			_npcMove = N_LEFT;
			break;
		}

		if (_ncount - _nsaveCount > 150)
		{
			switch (_goingCell)
			{
			case 0:
				_npcMove = N_UP;
				break;
			case 1:
				_npcMove = N_RIGHT;
				break;
			case 2:
				_npcMove = N_UP;
				break;
			case 3:
				_npcMove = N_RIGHT;
				break;
			}
			_npcState = N_BUYING;
			_stop = false;
		}
	}

	if (_npcState == N_WAITING)
	{
		_npcMove = N_UP;

	}



	//=======================================에이스타=============================

		//시작, 종료노드 세팅하기
	if (_npcState == N_NORMAL)
	{
		_totalNode[5][5]->nodeState = NODE_START;
		_startNode = _totalNode[5][5];


		switch (_goingCell)
		{
		case 0:
			_totalNode[0][1]->nodeState = NODE_END;
			_endNode = _totalNode[0][1];
			break;
		case 1:
			_totalNode[3][1]->nodeState = NODE_END;
			_endNode = _totalNode[3][1];
			break;
		case 2:
			_totalNode[0][2]->nodeState = NODE_END;
			_endNode = _totalNode[0][2];
			break;
		case 3:
			_totalNode[3][2]->nodeState = NODE_END;
			_endNode = _totalNode[3][2];
			break;
		}

	}
	else if (_npcState == N_BUYING)
	{
		switch (_goingCell)
		{
		case 0:	
			_totalNode[0][1]->nodeState = NODE_START;
			_startNode = _totalNode[0][1];
			break;
		case 1:
			_totalNode[3][1]->nodeState = NODE_START;
			_startNode = _totalNode[3][1];
			break;
		case 2:
			_totalNode[0][2]->nodeState = NODE_START;
			_startNode = _totalNode[0][2];
			break;
		case 3:
			_totalNode[3][2]->nodeState = NODE_START;
			_startNode = _totalNode[3][2];
			break;
		}

		_totalNode[6][2]->nodeState = NODE_END;
		_endNode = _totalNode[6][2];
	}
	else if (_npcState == N_BOUGHT)
	{
		_totalNode[6][2]->nodeState = NODE_START;
		_startNode = _totalNode[6][2];

		_totalNode[5][5]->nodeState = NODE_END;
		_endNode = _totalNode[5][5];
	}

	_totalNode[1][1]->nodeState = NODE_WALL;
	_totalNode[2][1]->nodeState = NODE_WALL;
	_totalNode[1][2]->nodeState = NODE_WALL;
	_totalNode[2][2]->nodeState = NODE_WALL;
	_totalNode[1][3]->nodeState = NODE_WALL;
	_totalNode[2][3]->nodeState = NODE_WALL;
	_totalNode[5][1]->nodeState = NODE_WALL;
	_totalNode[6][1]->nodeState = NODE_WALL;
	_totalNode[7][1]->nodeState = NODE_WALL;
	_totalNode[8][1]->nodeState = NODE_WALL;

	this->pathFinding();

	if (_isFind)
	{
		for (int i = 0; i < _finalList.size(); i++)
		{
			if (_npcMove == N_UP)
			{
				if (_moveOk && _nowX - 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_LEFT;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY - 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_UP;
					break;
				}
				else if (_moveOk && _nowX + 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_RIGHT;
					break;
				}
			}
			else if (_npcMove == N_LEFT)
			{
				if (_moveOk && _nowX - 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_LEFT;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY - 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_UP;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY + 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_DOWN;
					break;
				}
			}
			else if (_npcMove == N_DOWN)
			{
				if (_moveOk && _nowX - 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_LEFT;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY + 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_DOWN;
					break;
				}
				else if (_moveOk && _nowX + 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_RIGHT;
					break;
				}
			}
			else if (_npcMove == N_RIGHT)
			{
				if (_moveOk && _nowX + 1 == _finalList[i]->idx && _nowY == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_RIGHT;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY - 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_UP;
					break;
				}
				else if (_moveOk && _nowX == _finalList[i]->idx && _nowY + 1 == _finalList[i]->idy)
				{
					_destX = _finalList[i]->idx;
					_destY = _finalList[i]->idy;
					_moveOk = false;
					_npcMove = N_DOWN;
					break;
				}
			}
		}


		if (_npcMove == N_UP)
		{
			if (_moveOk && _nowX - 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_LEFT;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY - 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_UP;
			}
			else if (_moveOk && _nowX + 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_RIGHT;
			}
		}
		else if (_npcMove == N_LEFT)
		{
			if (_moveOk && _nowX - 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_LEFT;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY - 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_UP;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY + 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_DOWN;

			}
		}
		else if (_npcMove == N_DOWN)
		{
			if (_moveOk && _nowX - 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_LEFT;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY + 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_DOWN;
			}
			else if (_moveOk && _nowX + 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_RIGHT;
			}
		}
		else if (_npcMove == N_RIGHT)
		{
			if (_moveOk && _nowX + 1 == _endNode->idx && _nowY == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_RIGHT;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY - 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_UP;
			}
			else if (_moveOk && _nowX == _endNode->idx && _nowY + 1 == _endNode->idy)
			{
				_destX = _endNode->idx;
				_destY = _endNode->idy;
				_moveOk = false;
				_npcMove = N_DOWN;
			}
		}

		if (_npcMove == N_UP)
		{
			if (_pos.y < _totalNode[_destX][_destY]->rc.bottom)
			{
				_nowX = _destX;
				_nowY = _destY;
				_moveOk = true;
			}
		}
		else if (_npcMove == N_LEFT)
		{
			if (_pos.x <= (_totalNode[_destX][_destY]->rc.left + _totalNode[_destX][_destY]->rc.right) / 2)
			{
				_nowX = _destX;
				_nowY = _destY;
				_moveOk = true;

			}
		}
		else if (_npcMove == N_DOWN)
		{
			if (_pos.y > _totalNode[_destX][_destY]->rc.bottom)
			{
				_nowX = _destX;
				_nowY = _destY;
				_moveOk = true;
			}
		}
		else if (_npcMove == N_RIGHT)
		{
			if (_pos.x >= (_totalNode[_destX][_destY]->rc.left + _totalNode[_destX][_destY]->rc.right) / 2)
			{
				_nowX = _destX;
				_nowY = _destY;
				_moveOk = true;
			}
		}

		if (_endNode->idx == _nowX && _endNode->idy == _nowY)
		{
			if (_npcState == N_NORMAL)
			{
				_npcState = N_THINKING;
				_nsaveCount = _ncount;
				this->astarInit();
				_openList.clear();
				_closeList.clear();
				_finalList.clear();
				_stop = true;
			}
			else if (_npcState == N_BUYING)
			{
				_npcState = N_WAITING;
				_nsaveCount = _ncount;
				this->astarInit();
				_openList.clear();
				_closeList.clear();
				_finalList.clear();
				_stop = true;
			}
			else if (_npcState == N_BOUGHT)
			{
				_npcState = N_FINISHED;
			}
		}
	}

	sprintf(testx, "_now : %d", _nowX);
	sprintf(testy, "_nowY : %d", _nowY);
	sprintf(testx1, "_destX : %d", _destX);
	sprintf(testy1, "_destY : %d", _destY);
}

void npc::render()
{

	if (KEYMANAGER->isToggleKey('O'))
	{

		//=================================에이스타===============================

		char str[128];
		for (int y = 0; y < MAX_Y; y++)
		{
			for (int x = 0; x < MAX_X; x++)
			{
				//전체노드 렉트 보여주기
				FrameRect(getMemDC(), _totalNode[x][y]->rc, RGB(255, 255, 255));

				if (_isFind)
				{
					//시작노드 보여주기
					if (_totalNode[x][y]->nodeState == NODE_START)
					{
						setNodeColor(_startNode, RGB(255, 0, 0));
						TextOut(getMemDC(), _startNode->rc.left + 100, _startNode->rc.top + 10, "[Start]", strlen("[Start]"));
					}
					//종료노드 보여주기
					if (_totalNode[x][y]->nodeState == NODE_END)
					{
						setNodeColor(_endNode, RGB(0, 0, 255));
						TextOut(getMemDC(), _endNode->rc.left + 100, _endNode->rc.top + 10, "[END]", strlen("[END]"));
					}
				}
				//벽노드 보여주기
				if (_totalNode[x][y]->nodeState == NODE_WALL)
				{
					setNodeColor(_totalNode[x][y], RGB(200, 150, 100));
					TextOut(getMemDC(), _totalNode[x][y]->rc.left + 100, _totalNode[x][y]->rc.top + 10, "[WALL]", strlen("[WALL]"));
				}

				//전체노드의 인덱스 보여주기(맨마지막에 출력)
				sprintf(str, "[%d, %d]", _totalNode[x][y]->idx, _totalNode[x][y]->idy);
				TextOut(getMemDC(), _totalNode[x][y]->rc.left + 10, _totalNode[x][y]->rc.top + 10, str, strlen(str));
			}
		}

		//길찾았을때 보여주기
		if (_isFind)
		{
			for (int i = 0; i < _finalList.size(); i++)
			{
				setNodeColor(_finalList[i], RGB(255, 255, 0));
				sprintf(str, "[%d, %d]      %d번 노드", _finalList[i]->idx, _finalList[i]->idy, i + 1);
				TextOut(getMemDC(), _finalList[i]->rc.left + 10, _finalList[i]->rc.top + 10, str, strlen(str));
				sprintf(str, "G: %d, H: %d, F: %d", _finalList[i]->G, _finalList[i]->H, _finalList[i]->F);
				TextOut(getMemDC(), _finalList[i]->rc.left + 10, _finalList[i]->rc.bottom - 30, str, strlen(str));
			}
		}

		TextOut(getMemDC(), 0, 200, testx, lstrlen(testx));
		TextOut(getMemDC(), 0, 220, testy, lstrlen(testy));
		TextOut(getMemDC(), 0, 240, testx1, lstrlen(testx1));
		TextOut(getMemDC(), 0, 260, testy1, lstrlen(testy1));

	}

	_image->frameRender(getMemDC(), _pos.x - 50, _pos.y - 80, _indexX, _indexY);

}

void npc::astarInit()
{

	//=============================에이스타==============================

	//	전체노드 초기화
	for (int y = 0; y < MAX_Y; y++)
	{
		for (int x = 0; x < MAX_X; x++)
		{
			//새로운 노드와 렉트위치 설정
			_totalNode[x][y] = new node(x, y);
			_totalNode[x][y]->rc = RectMake(310 + x * 45, 240 + y * 45, 45, 45);
		}
	}
	_pos = { (_totalNode[_nowX][_nowY]->rc.left + _totalNode[_nowX][_nowY]->rc.right) / 2 ,_totalNode[_nowX][_nowY]->rc.bottom };
	_rc = RectMake(_pos.x - 23, _pos.y - 45, 45, 45);
	//첫클릭이 짝수가 되게 하기위해서 -1로 초기화
	_count = -1;
	//길찾았냐?
	_isFind = false;
	_startNode = nullptr;
	_endNode = nullptr;
}

//노드 색채우기(편리성때문에 만든함수)
void npc::setNodeColor(node * node, COLORREF color)
{
	HBRUSH brush = CreateSolidBrush(color);
	FillRect(getMemDC(), &node->rc, brush);
	DeleteObject(brush);
	FrameRect(getMemDC(), node->rc, RGB(0, 0, 0));
}

//길찾기 함수
void npc::pathFinding()
{
	//시작노드 및 종료노드가 없는 경우 길찾기 못함
	if (!_startNode || !_endNode) return;

	//길찾기를 해보자!!
	//검색을 하려면 무조건 오픈리스트에 담아두고 
	//F와 H값 가장작은 놈을 찾아서 그놈을 현재노드로 변경하고
	//오픈리스트에서 현재노드는 삭제하고 
	//현재노드는 클로즈리스트에 담아둔다

	//1. 시작노드가 있어야 출발이 가능하니 
	//시작노드를 오픈리스트에 추가를 해줘야 한다
	_openList.push_back(_startNode);

	//2. 오픈리스트안에 담겨 있는 벡터를 검사해서 
	//종료노드에 도착할때까지 무한루프
	while (_openList.size() > 0)
	{
		_curNode = _openList[0];

		//오픈리스트 중 가장 F가 작거나 F가 같다면 
		//H가 작은 걸 현재노드로 하고
		//현재노드를 오픈리스트에서 클로즈리스트로 옮기기
		//비교를 하려고 하면 최소 시작노드에서 주변을 탐색한 이후
		//길찾기가 시작되니 1부터 시작하자
		for (int i = 1; i < _openList.size(); i++)
		{
			if (_openList[i]->F <= _curNode->F && _openList[i]->H < _curNode->H)
			{
				_curNode = _openList[i];
			}
		}

		//클로즈리스트에 넣어둔다
		for (int i = 0; i < _openList.size(); i++)
		{
			if (_curNode == _openList[i])
			{
				this->delOpenList(i);
				_closeList.push_back(_curNode);
			}
		}

		//현재노드가 마지막노드와 같냐? (길찾았냐?)
		if (_curNode == _endNode)
		{
			node* endNode = _endNode;
			vector<node*> tempNode;
			//마지막 노드로부터 시작노드까지 부모노드를 벡터에 담는다
			while (endNode != _startNode)
			{
				tempNode.push_back(endNode);
				endNode = endNode->parentNode;
			}

			//STL리스트를 이용하면 reverse()사용하거나, push_front()를 사용할 수 있지만,
			//우린 벡터를 이용하니 꺼꾸로 푸시백해준다
			for (int i = tempNode.size() - 1; i > 0; i--)
			{
				_finalList.push_back(tempNode[i]);
			}

			_isFind = true;
			//종료하고 빠져나온다
			return;
		}

		//상하좌우 (순서는 상괌없음 - 어짜피 주면 4개의 노드를 모두 오픈리스트에 넣어서 검사할 예정임)
		this->addOpenList(_curNode->idx, _curNode->idy - 1); //상
		this->addOpenList(_curNode->idx, _curNode->idy + 1); //하
		this->addOpenList(_curNode->idx - 1, _curNode->idy); //좌
		this->addOpenList(_curNode->idx + 1, _curNode->idy); //우

		//추후에 대각 4방향도 추가하면 대각선 이동 처리도 가능함
		//우상, 좌상, 우하, 좌하
		//예외처리만 잘해주면 된다
		//벽사이로 막가 안된다 등등

	}

}

//오픈리스트에 추가 함수
void npc::addOpenList(int idx, int idy)
{
	//예외처리
	//오픈리스트에 담을 노드가 전체노드 인덱스 밖으로 나가면 추가하지 못하게 처리한다(인덱스 범위는 0 ~ 4까지)
	if (idx < 0 || idx >= MAX_X || idy < 0 || idy >= MAX_Y) return;
	//장애물은 오픈리스트에 담을 수 없다
	if (_totalNode[idx][idy]->nodeState == NODE_WALL) return;
	//클로즈리스트에 있다면 이미 지나온길이니 오픈리스트에 담으면 안된다
	for (int i = 0; i < _closeList.size(); i++)
	{
		if (_totalNode[idx][idy] == _closeList[i]) return;
	}

	//여기까지 왔으면 문제가 없으며 이제 오픈리스트에 추가를 하자
	//현재노드의 4방향 노드를 이웃노드라고 하고 직선10, 대각은 14비용을 추가하기
	node* neighborNode = _totalNode[idx][idy];
	int moveCost = _curNode->G + ((_curNode->idx - idx == 0 || _curNode->idy - idy == 0) ? 10 : 14);

	//오픈리스트안에 이웃노드가 있으면 안된다
	for (int i = 0; i < _openList.size(); i++)
	{
		if (_openList[i] == neighborNode) return;
	}

	//마지막으로 오픈리스트에도 없는경우 
	//G, H, ParentNode 설정 후 오픈리스트에 추가
	neighborNode->G = moveCost;
	neighborNode->H = (abs(neighborNode->idx - _endNode->idx) + abs(neighborNode->idy - _endNode->idy)) * 10;
	neighborNode->F = neighborNode->G + neighborNode->H;
	neighborNode->parentNode = _curNode;
	_openList.push_back(neighborNode);
}

//오픈리스트 삭제
void npc::delOpenList(int index)
{
	_openList.erase(_openList.begin() + index);
}