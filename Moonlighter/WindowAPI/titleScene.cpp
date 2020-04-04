#include "stdafx.h"
#include "titleScene.h"


HRESULT titleScene::init()
{
	_camera = RectMake(0, 0, WINSIZEX, WINSIZEY);

	_jOn = false;
	_count = _frameIndex = _alpha = 0;
	IMAGEMANAGER->findImage("타이틀영상")->setFrameX(0);
	IMAGEMANAGER->findImage("타이틀영상")->setFrameY(0);
	IMAGEMANAGER->findImage("왼쪽문")->setX(_camera.left);
	IMAGEMANAGER->findImage("왼쪽문")->setY(_camera.top);
	IMAGEMANAGER->findImage("오른쪽문")->setX(_camera.left + 646);
	IMAGEMANAGER->findImage("오른쪽문")->setY(_camera.top);
	
	_titleSelect = 0;

	_doorLeftIndex = _doorLogX = _doorRightIndex = 0;

	return S_OK ;
}

void titleScene::release()
{
}

void titleScene::update()
{
	_count++;
	_alpha+=3;
	if (_alpha > 255)
	{
		_alpha = 255;
	}

	if (_count % 5 == 0)
	{
		_frameIndex++;

		if (_frameIndex > 15)
		{
			_frameIndex = 0;
		}
	}
	IMAGEMANAGER->findImage("타이틀영상")->setFrameX(_frameIndex);

	if (_jOn)
	{

		_doorLogX+=10;

		_doorLeftIndex = - 40 * log2(_doorLogX);
		_doorRightIndex = 40 * log2(_doorLogX);

		if (_doorLogX > 2000)
		{
			_doorLogX = 2000;
		}

		//=========================여기에 버튼 등 입력====================================

		_button[0] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 80 + 13, IMAGEMANAGER->findImage("게임시작")->getWidth(), IMAGEMANAGER->findImage("게임시작")->getHeight());
		_button[1] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 130 + 13, IMAGEMANAGER->findImage("불러오기")->getWidth(), IMAGEMANAGER->findImage("불러오기")->getHeight());
		_button[2] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 180 + 13, IMAGEMANAGER->findImage("맵툴")->getWidth(), IMAGEMANAGER->findImage("맵툴")->getHeight());
		_button[3] = RectMakeCenter(WINSIZEX / 2, WINSIZEY / 2 + 230 + 13, IMAGEMANAGER->findImage("옵션")->getWidth(), IMAGEMANAGER->findImage("옵션")->getHeight());
		
		if (KEYMANAGER->isOnceKeyDown('S'))
		{
			_titleSelect++;

			if (_titleSelect > 3)
			{
				_titleSelect = 0;
			}
		}
		else if (KEYMANAGER->isOnceKeyDown('W'))
		{
			_titleSelect--;

			if (_titleSelect < 0)
			{
				_titleSelect = 3;
			}
		}	

		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			switch (_titleSelect)
			{
			case 0:
				SOUNDMANAGER->stop("TITLE_BGM");
				SCENEMANAGER->loadScene("상점씬");
				break;
			case 1:
				break;
			case 2:
				SOUNDMANAGER->stop("TITLE_BGM");
				SCENEMANAGER->loadScene("맵제작");
				break;
			case 3:
				break;
			}
		}
	}
	else
	{
		if (KEYMANAGER->isOnceKeyDown('J'))
		{
			_jOn = true;
			SOUNDMANAGER->addSound("TITLE_BGM", "gameSound/introBGM.mp3");
			SOUNDMANAGER->play("TITLE_BGM");
		}
	}
}

void titleScene::render()
{
	IMAGEMANAGER->findImage("타이틀영상")->frameRender(getMemDC(), _camera.left, _camera.top);
	IMAGEMANAGER->findImage("왼쪽문")->render(getMemDC(), IMAGEMANAGER->findImage("왼쪽문")->getX() + _doorLeftIndex, IMAGEMANAGER->findImage("왼쪽문")->getY());
	IMAGEMANAGER->findImage("오른쪽문")->render(getMemDC(), IMAGEMANAGER->findImage("오른쪽문")->getX() + _doorRightIndex, IMAGEMANAGER->findImage("오른쪽문")->getY());

	if (!_jOn)
	{
		IMAGEMANAGER->findImage("시작글씨")->render(getMemDC(), _camera.left + WINSIZEX / 2 - 263, _camera.top + WINSIZEY / 2 - 17);
	}
	else
	{
		IMAGEMANAGER->findImage("로고")->alphaRender(getMemDC(), WINSIZEX / 2 - 176, WINSIZEY/2 - 250, _alpha);
		IMAGEMANAGER->findImage("게임시작")->alphaRender(getMemDC(), WINSIZEX / 2 -(IMAGEMANAGER->findImage("게임시작")->getWidth()/2), WINSIZEY / 2 + 80, _alpha);
		IMAGEMANAGER->findImage("불러오기")->alphaRender(getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("불러오기")->getWidth() / 2), WINSIZEY / 2 + 130, _alpha);
		IMAGEMANAGER->findImage("맵툴")->alphaRender(getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("맵툴")->getWidth() / 2), WINSIZEY / 2 + 180, _alpha);
		IMAGEMANAGER->findImage("옵션")->alphaRender(getMemDC(), WINSIZEX / 2 - (IMAGEMANAGER->findImage("옵션")->getWidth() / 2), WINSIZEY / 2 + 230, _alpha);

		if (KEYMANAGER->isToggleKey('P'))
		{
			for (int i = 0; i < 4; i++)
			{
				FrameRect(getMemDC(), _button[i], RGB(255, 0, 0));
			}
		}

		switch (_titleSelect)
		{
		case 0:
			IMAGEMANAGER->findImage("선택왼쪽")->render(getMemDC(), _button[0].left - 38, _button[0].top);
			IMAGEMANAGER->findImage("선택오른쪽")->render(getMemDC(), _button[0].right + 10, _button[0].top);
			break;
		case 1:
			IMAGEMANAGER->findImage("선택왼쪽")->render(getMemDC(), _button[1].left - 38, _button[1].top);
			IMAGEMANAGER->findImage("선택오른쪽")->render(getMemDC(), _button[1].right + 10, _button[1].top);
			break;
		case 2:
			IMAGEMANAGER->findImage("선택왼쪽")->render(getMemDC(), _button[2].left - 38, _button[2].top);
			IMAGEMANAGER->findImage("선택오른쪽")->render(getMemDC(), _button[2].right + 10, _button[2].top);
			break;
		case 3:
			IMAGEMANAGER->findImage("선택왼쪽")->render(getMemDC(), _button[3].left - 38, _button[3].top);
			IMAGEMANAGER->findImage("선택오른쪽")->render(getMemDC(), _button[3].right + 10, _button[3].top);
			break;
		}
	}

}
