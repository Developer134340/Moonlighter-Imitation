#pragma once
#include "gameNode.h"

#define MAX_X 9
#define MAX_Y 6


enum NPC_MOVE
{
	N_UP, N_LEFT, N_DOWN, N_RIGHT
};

enum NPC_STATE
{
	N_NORMAL, N_THINKING, N_BUYING, N_WAITING, N_BOUGHT, N_FINISHED
};

enum NODESTATE
{
	NODE_START,
	NODE_END,
	NODE_WALL,
	NODE_EMPTY
};

//노드 클래스
class node
{
	//에이스타에서 기억해야 할 2가지
	//1. 비용(F, G, H)
	//2. 부모노드 포인터(이전노드의 포인터)
public:
	RECT rc;				//렉트
	int idx, idy;			//인덱스 x, y
	int F, G, H;			//F = G + H //G = 시작 to 현재 //H = 현재 to 종료
	node* parentNode;		//부모를 가리킬 노드(이전노드)
	NODESTATE nodeState;	//노드의 상태(시작, 종료, 벽, 빈노드)
	//노드 생성자
	node() {}
	//생성자 오버로딩을 통한 초기화
	node(int _idx, int _idy)
	{
		idx = _idx;
		idy = _idy;
		F = G = H = 0;
		nodeState = NODE_EMPTY;
		parentNode = NULL;
	}
};

class npc :
	public gameNode
{
	const char* _name;
	image* _image;
	NPC_MOVE _npcMove;
	bool _stop;
	POINT _pos;
	RECT _rc;
	NPC_STATE _npcState;
	
	int _nowX, _nowY, _destX, _destY;
	//int _faceIndexX;

	int _nsaveCount;

	int _indexX;
	int _indexY;
	int _ncount;
	int _speed;

	int _goingCell;

	//======================에이스타================

	node* _totalNode[MAX_X][MAX_Y];		//전체노드 25개(보드판 역할)
	node* _startNode;					//시작노드
	node* _endNode;						//종료노드
	node* _curNode;						//현재노드

	vector<node*> _openList;			//오픈리스트(탐색할 노드들을 담아둘 벡터)
	vector<node*> _closeList;			//클로즈리스트 (오픈리스트의 최단거리 노드를 삭제후 클로즈리스트 벡터에 담는다)
	vector<node*> _finalList;			//파이널리스트 (길찾은 후 클로즈리스트에 담겨있는 노드들을 리버스시킬용도)

	int _count;							//시작, 종료노드 한번씩만 선택하기 위한 변수
	bool _isFind;						//길 찾았냐?

	bool _moveOk;

	char testx[10];
	char testy[10];
	char testx1[10];
	char testy1[10];


public:

	HRESULT init(const char* key);
	void release();
	void update();
	void render();

	void setNPCposition(POINT tempPos) { _pos = tempPos; }
	void setNPCdirection(NPC_MOVE npcMove) { _npcMove = npcMove; }
	void setNPCstop(bool tempStop) { _stop = tempStop; }
	void setNPCgoingCell(int x) { _goingCell = x; }

	int getNPCgoingCell() { return _goingCell; }
	bool getNPCstop() { return _stop; }
	void setNPCsaveCount() { _nsaveCount = _ncount; }
	NPC_STATE getNPCstate() { return _npcState; }
	POINT getNPCpos() { return _pos; }
	void setNPCstate(NPC_STATE npcState) { _npcState = npcState; }
	void astarInit();

	//=======================================에이스타
		//노드 색채우기(편리성때문에 만든함수)
		void setNodeColor(node* node, COLORREF color);

	/*중요함수*/
	//길찾기 함수
	void pathFinding();
	//오픈리스트에 추가 함수
	void addOpenList(int idx, int idy);
	//오픈리스트 삭제
	void delOpenList(int index);

	npc() : _startNode(NULL), _endNode(NULL) {}
	~npc() {}

};

