#include "stdafx.h"
#include "loadingScene.h"

HRESULT loadingScene::init()
{
	//로딩클래스 초기화
	_loading = new loading;
	_loading->init();

	//이미지 및 사운드 로딩
	this->loadingImage();
	this->loadingSound();

	return S_OK;
}

void loadingScene::release()
{
	//로딩클래스 해제
	_loading->release();
	SAFE_DELETE(_loading);
}

void loadingScene::update()
{
	//로딩클래스 업데이트
	_loading->update();

	//로딩완료후 화면 변경
	if (_loading->loadingDone())
	{
		SCENEMANAGER->loadScene("타이틀");
	}
}

void loadingScene::render()
{
	//로딩클래스 렌더
	_loading->render();
}

void loadingScene::loadingImage()
{
	//_loading->loadImage();
	//_loading->loadFrameImage();
	//_loading->loadSound();
	//IMAGEMANAGER->addImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
	//IMAGEMANAGER->addImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));
//	_loading->loadImage("mountain", "mountain.bmp", WINSIZEX, WINSIZEY, true, RGB(255, 0, 255));
//	_loading->loadImage("ball", "ball.bmp", 60, 60, true, RGB(255, 0, 255));

	_loading->loadImage("사막벽1", "images/map/사막벽1.bmp", 1280, 720, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사막바닥타일", "images/map/사막바닥타일.bmp", 392, 294, 8, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("사막용암타일", "images/map/사막용암타일.bmp", 343, 245, 7, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("안부서지는오브젝트", "images/object/안부서지는오브젝트.bmp", 294, 264, 6, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("에너미타일", "images/map/monster.bmp", 283, 87, 5, 1, true, RGB(255, 0, 255));
	_loading->loadImage("최소화", "images/map/MINI.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("이동", "images/map/MOVE.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("TILE", "images/map/TILE.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("OBJECT", "images/map/OBJECT.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("LAVA", "images/map/LAVA.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("ENEMY", "images/map/ENEMY.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadImage("SAVE", "images/map/SAVE.bmp", 100, 30, true, RGB(255, 0, 255));
	_loading->loadImage("LOAD", "images/map/LOAD.bmp", 100, 30, true, RGB(255, 0, 255));
	_loading->loadImage("CLEAR", "images/map/CLEAR.bmp", 100, 30, true, RGB(255, 0, 255));
	_loading->loadImage("OPEN", "images/map/OPEN.bmp", 80, 30, true, RGB(255, 0, 255));
	_loading->loadFrameImage("툴박스", "images/map/toolbox2.bmp", 5610, 500, 11, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("타이틀영상", "images/title/opening.bmp", 20467, 720, 16, 1, true, RGB(255, 0, 255));
	_loading->loadImage("오른쪽문", "images/title/오른쪽문.bmp", 636, 720, true, RGB(255, 0, 255));
	_loading->loadImage("왼쪽문", "images/title/왼쪽문.bmp", 632, 720, true, RGB(255, 0, 255));
	_loading->loadImage("시작글씨", "images/title/시작글씨.bmp", 527, 34, true, RGB(255, 0, 255));
	_loading->loadImage("로고", "images/title/로고.bmp", 352, 280, true, RGB(255, 0, 255));
	_loading->loadImage("게임시작", "images/title/게임시작.bmp", 99, 26, true, RGB(255, 0, 255));
	_loading->loadImage("불러오기", "images/title/불러오기.bmp", 98, 26, true, RGB(255, 0, 255));
	_loading->loadImage("옵션", "images/title/옵션.bmp", 47, 26, true, RGB(255, 0, 255));
	_loading->loadImage("맵툴", "images/title/맵툴.bmp", 48, 26, true, RGB(255, 0, 255));
	_loading->loadImage("선택왼쪽", "images/title/선택왼쪽.bmp", 30, 28, true, RGB(255, 0, 255));
	_loading->loadImage("선택오른쪽", "images/title/선택.bmp", 30, 28, true, RGB(255, 0, 255));
	_loading->loadImage("맵생성불가", "images/map/맵생성불가.bmp", 386, 50, true, RGB(255, 0, 255)); 
	_loading->loadImage("보스버튼", "images/boss/boss_button.bmp", 100, 70, true, RGB(255, 0, 255));
	_loading->loadImage("보스방선택", "images/map/보스방선택.bmp", 349, 42, true, RGB(255, 0, 255));
	_loading->loadImage("보스하나", "images/map/보스하나.bmp", 349, 42, true, RGB(255, 0, 255));

	_loading->loadFrameImage("상호작용오브젝트", "images/object/상호작용오브젝트.bmp", 90, 264, 1, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("문", "images/object/door.bmp", 3744, 1248, 24, 8, true, RGB(255, 0, 255));
	_loading->loadFrameImage("회복샘", "images/object/HealingPool.bmp", 2976, 382, 8, 1, true, RGB(255, 0, 255));
	_loading->loadImage("캠프", "images/object/camp.bmp", 256, 208, true, RGB(255, 0, 255));

	_loading->loadFrameImage("화살표", "images/map/화살표.bmp", 280, 70, 4, 1, true, RGB(255, 0, 255));
	_loading->loadImage("타이틀", "images/map/TITLE.bmp", 120, 45, true, RGB(255, 0, 255));
	_loading->loadImage("마을", "images/map/마을.bmp", 2610, 2140, true, RGB(255, 0, 255));
	_loading->loadImage("상점", "images/shop/shop.bmp", 678, 868, true, RGB(255, 0, 255));
	_loading->loadImage("마을픽셀", "images/map/마을_pixel.bmp", 2610, 2140, true, RGB(255, 0, 255));
	_loading->loadImage("상점픽셀", "images/shop/shop_pixel.bmp", 678, 868, true, RGB(255, 0, 255));
	_loading->loadImage("던전픽셀", "images/map/던전_pixel.bmp", 1280, 720, true, RGB(255, 0, 255));

	_loading->loadImage("UI가방", "images/UI/bag.bmp", 38, 44, true, RGB(255, 0, 255));
	_loading->loadImage("UI써클", "images/UI/circle.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->loadImage("UI1", "images/UI/ui_1.bmp", 22, 22, true, RGB(255, 0, 255));
	_loading->loadImage("UI2", "images/UI/ui_2.bmp", 22, 22, true, RGB(255, 0, 255));

	_loading->loadImage("UI돈주머니", "images/UI/UI_돈.bmp", 40, 46, true, RGB(255, 0, 255));
	_loading->loadImage("UI돈배경", "images/UI/UI_돈배경.bmp", 70, 70, true, RGB(255, 0, 255));
	_loading->loadImage("UI체력바완성", "images/UI/UI_체력바완성.bmp", 188, 60, true, RGB(255, 0, 255));
	_loading->loadImage("UI체력바흰색", "images/UI/UI_체력바흰색.bmp", 128, 24, true, RGB(255, 0, 255));
	_loading->loadImage("UI체력바체력", "images/UI/UI_체력바체력.bmp", 128,  24, true, RGB(255, 0, 255));

	_loading->loadImage("몬스터체력바", "images/UI/UI_체력바_몬스터.bmp", 80, 15, true, RGB(255, 0, 255));
	_loading->loadImage("몬스터체력바_흰색", "images/UI/UI_체력바흰색_몬스터.bmp", 80, 15, true, RGB(255, 0, 255));
	_loading->loadImage("몬스터체력바_체력", "images/UI/UI_체력바체력_몬스터.bmp", 80, 15, true, RGB(255, 0, 255));

	_loading->loadImage("UI코인", "images/UI/UI_코인.bmp", 18, 18, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_SHOP_IDLE", "images/will/WILL_SHOP_IDLE.bmp", 640, 336, 10, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHOP_WALK", "images/will/WILL_SHOP_WALK.bmp", 512, 336, 8, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHOP_JUMP", "images/will/WILL_SHOP_JUMP.bmp", 512, 336, 8, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_DUNGEON_IDLE", "images/will/WILL_DUNGEON_IDLE.bmp", 1800, 720, 10, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_DUNGEON_WALK", "images/will/WILL_DUNGEON_WALK.bmp", 1440, 720, 8, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_DUNGEON_JUMP", "images/will/WILL_DUNGEON_JUMP.bmp", 1440, 720, 8, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_DUNGEON_IDLE_WHITE", "images/will/WILL_DUNGEON_IDLE_WHITE.bmp", 1800, 720, 10, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_DUNGEON_WALK_WHITE", "images/will/WILL_DUNGEON_WALK_WHITE.bmp", 1440, 720, 8, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_SHORTSWORD_ATTACK", "images/will/WILL_SHORTSWORD_ATTACK.bmp", 3240, 720, 18, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHORTSWORD_DEFFENSE", "images/will/WILL_SHORTSWORD_DEFFENSE.bmp", 2340, 720, 13, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHORTSWORD_ATTACK_WHITE", "images/will/WILL_SHORTSWORD_ATTACK_WHITE.bmp", 3240, 720, 18, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHORTSWORD_DEFFENSE_WHITE", "images/will/WILL_SHORTSWORD_DEFFENSE_WHITE.bmp", 2340, 720, 13, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_SHORTSWORD_DEFFENSE_SHIELD", "images/will/WILL_SHORTSWORD_DEFFENSE_SHIELD.bmp", 2340, 720, 13, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_SHORTSWORD_ATTACK_SWORD", "images/will/WILL_SHORTSWORD_ATTACK_SWORD.bmp", 3240, 720, 18, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_BOW_ATTACK", "images/will/WILL_BOW_ATTACK.bmp", 1260, 720, 7, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_BOW_ATTACK_WHITE", "images/will/WILL_BOW_ATTACK_WHITE.bmp", 1260, 720, 7, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_BOW_ATTACK_BOW", "images/will/WILL_BOW_ATTACK_BOW.bmp", 1260, 720, 7, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_BOW_ATTACK_SECOND", "images/will/WILL_BOW_ATTACK_SECOND.bmp", 4860, 720, 27, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_BOW_ATTACK_SECOND_WHITE", "images/will/WILL_BOW_ATTACK_SECOND_WHITE.bmp", 4860, 720, 27, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_BOW_ATTACK_SECOND_BOW", "images/will/WILL_BOW_ATTACK_SECOND_BOW.bmp", 4860, 720, 27, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("WILL_BOW_ATTACK_ARROW", "images/will/WILL_BOW_ATTACK_ARROW.bmp", 288, 192, 6, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("WILL_DEATH", "images/will/WILL_DEATH.bmp", 1980, 180, 11, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("SLIME", "images/monsters/slime.bmp", 2160, 480, 18, 4, true, RGB(255, 255, 255));
	_loading->loadFrameImage("PATROLGOLEM", "images/monsters/patrolGolem.bmp", 5220, 900, 29, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MIMIC", "images/monsters/mimic.bmp", 4320, 1080, 24, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MAGICIANPUPPET", "images/monsters/magicianPuppet.bmp", 4780, 1080, 26, 6, true, RGB(255, 0, 255));

	_loading->loadFrameImage("SLIME_WHITE", "images/monsters/slime_white.bmp", 2160, 480, 18, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("PATROLGOLEM_WHITE", "images/monsters/patrolGolem_white.bmp", 5220, 900, 29, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MIMIC_WHITE", "images/monsters/mimic_white.bmp", 4320, 1080, 24, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MAGICIANPUPPET_WHITE", "images/monsters/magicianPuppet_white.bmp", 4780, 1080, 26, 6, true, RGB(255, 0, 255));

	_loading->loadFrameImage("SLIME_RED", "images/monsters/slime_red.bmp", 2160, 480, 18, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("PATROLGOLEM_RED", "images/monsters/patrolGolem_red.bmp", 5220, 900, 29, 5, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MIMIC_RED", "images/monsters/mimic_red.bmp", 4320, 1080, 24, 6, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MAGICIANPUPPET_RED", "images/monsters/magicianPuppet_red.bmp", 4780, 1080, 26, 6, true, RGB(255, 0, 255));

	_loading->loadFrameImage("MAGICIANPUPPET_EFFECT", "images/monsters/magicianPuppet_effect.bmp", 1080, 180, 6, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("MAGICIANPUPPET_ATTACK", "images/monsters/magicianPuppet_attack.bmp", 600, 60, 10, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("LAVE_BEAM_END", "images/monsters/lavaBeamEnd.bmp", 384, 256, 6, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("COIN", "images/monsters/coin.bmp", 90, 72, 5, 4, true, RGB(255, 0, 255));
	_loading->loadImage("LAVA_BEAM_1", "images/monsters/lavaBeam.bmp", 40, 12, true, RGB(255, 0, 255));
	_loading->loadImage("LAVA_BEAM_2", "images/monsters/lavaBeamLeft.bmp", 12, 40, true, RGB(255, 0, 255));
	_loading->loadImage("RAZOR", "images/monsters/razor.bmp", 400, 3, true, RGB(255, 0, 255));

	//===========================보스=====================

	_loading->loadImage("BOSS_BACKGROUND", "images/boss/boss_background.bmp", 2304, 1558, true, RGB(255, 0, 255));
	_loading->loadFrameImage("BOSS_APPEAR", "images/boss/보스나타남.bmp", 28160, 512, 55, 1, true, RGB(255, 0, 255));

	_loading->loadFrameImage("HEAD_ATTACK", "images/boss/boss_attack.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HEAD_CHARGE", "images/boss/boss_charge.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CIRCLE", "images/boss/circle.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("RHOMBUS", "images/boss/rhombus.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TRIANGLE", "images/boss/triangle.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SQUARE", "images/boss/square.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));

	_loading->loadFrameImage("HEAD_ATTACK_RED", "images/boss/boss_attack_red.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HEAD_CHARGE_RED", "images/boss/boss_charge_red.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CIRCLE_RED", "images/boss/circle_red.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("RHOMBUS_RED", "images/boss/rhombus_red.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TRIANGLE_RED", "images/boss/triangle_red.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SQUARE_RED", "images/boss/square_red.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));

	_loading->loadFrameImage("HEAD_ATTACK_WHITE", "images/boss/boss_attack_white.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("HEAD_CHARGE_WHITE", "images/boss/boss_charge_white.bmp", 10200, 1200, 34, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("CIRCLE_WHITE", "images/boss/circle_white.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("RHOMBUS_WHITE", "images/boss/rhombus_white.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("TRIANGLE_WHITE", "images/boss/triangle_white.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));
	_loading->loadFrameImage("SQUARE_WHITE", "images/boss/square_white.bmp", 16128, 768, 63, 3, true, RGB(255, 0, 255));

	_loading->loadImage("체력바배경_보스", "images/boss/체력바배경_보스.bmp", 800, 30, true, RGB(255, 0, 255));
	_loading->loadImage("체력바체력_보스", "images/boss/체력바체력_보스.bmp", 800, 30, true, RGB(255, 0, 255));
	_loading->loadImage("체력바흰색_보스", "images/boss/체력바흰색_보스.bmp", 800, 30, true, RGB(255, 0, 255));

	//================================아이템==============================

	_loading->loadImage("검은색", "images/item/검은색.bmp", 1280, 720, true, RGB(255, 0, 255));
	_loading->loadImage("인벤토리", "images/item/inventory.bmp", 1038, 548, true, RGB(255, 0, 255));
	_loading->loadImage("아이템선택", "images/item/아이템선택.bmp", 68, 68, true, RGB(255, 0, 255));
	_loading->loadImage("아이템이름", "images/item/아이템이름.bmp", 310, 34, true, RGB(255, 0, 255));

	_loading->loadImage("훈련용단검", "images/item/연습용단검.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("훈련용활", "images/item/연습용활.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("강화석", "images/item/강화석.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("냉각된용암", "images/item/냉각된용암.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("반자성모래", "images/item/반자성모래.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("사막강철주괴", "images/item/사막강철주괴.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("사막강철판금", "images/item/사막강철판금.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("사막밧줄", "images/item/사막밧줄.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("사막석", "images/item/사막석.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("열자기엔진", "images/item/열자기엔진.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("포션", "images/item/포션.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadImage("풍부한젤리", "images/item/풍부한젤리.bmp", 52, 52, true, RGB(255, 0, 255));
	_loading->loadFrameImage("NPC얼굴", "images/shop/visitor_face.bmp", 256, 32, 8, 1, true, RGB(255, 0, 255));

	//================================마을==================================

	_loading->loadFrameImage("마녀", "images/NPC/마녀.bmp", 2600, 400, 26, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("대장장이", "images/NPC/대장장이.bmp", 1800, 400, 18, 4, true, RGB(255, 0, 255));

	_loading->loadFrameImage("말하기", "images/shop/말하기.bmp", 363, 50, 3, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("npc1", "images/NPC/npc1.bmp", 800, 400, 8, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("npc2", "images/NPC/npc2.bmp", 800, 400, 8, 4, true, RGB(255, 0, 255));
	_loading->loadFrameImage("npc3", "images/NPC/npc3.bmp", 800, 400, 8, 4, true, RGB(255, 0, 255));
	_loading->loadImage("DIE", "images/monsters/DIE.bmp", 450, 450, true, RGB(255, 0, 255));
	_loading->loadImage("DIE2", "images/boss/DIE2.bmp", 450, 450, true, RGB(255, 0, 255));
	_loading->loadImage("마녀UI", "images/NPC/마녀ui.bmp", 1280, 722, true, RGB(255, 0, 255));

	//=================================상점====================================

	_loading->loadImage("상점천장", "images/shop/상점천장.bmp", 108, 96, true, RGB(255, 0, 255));
	_loading->loadImage("배치", "images/shop/배치.bmp", 126, 57, true, RGB(255, 0, 255));
	_loading->loadImage("판매", "images/shop/판매.bmp", 126, 57, true, RGB(255, 0, 255));
	_loading->loadImage("판매대", "images/shop/판매대.bmp", 1038, 548, true, RGB(255, 0, 255));
	_loading->loadImage("선택한아이템", "images/shop/선택한 아이템.bmp", 72, 72, true, RGB(255, 0, 255));

	_loading->loadFrameImage("버튼길게누르기", "images/shop_temp/button.bmp", 3400, 83, 40, 1, true, RGB(255, 0, 255));
	_loading->loadFrameImage("상점나가기버튼", "images/shop_temp/buttonUi.bmp", 1720, 100, 8, 1, true, RGB(255, 0, 255));
}

void loadingScene::loadingSound()
{
//	_loading->loadSound("DUNGEON_BGM", "gameSound/dungeonBGM.mp3", true, true);z
//	_loading->loadSound("TITLE_BGM", "gameSound/introBGM.mp3", true, true);
//	_loading->loadSound("SHOP_BGM", "gameSound/shopBGM.mp3", true, true);
//	_loading->loadSound("ENEMY_DEATH", "gameSound/enemy_death.mp3", true, true);
//	_loading->loadSound("SLIME_HIT", "gameSound/slime_hit.mp3", true, true);
//	_loading->loadSound("WILL_BOWATTACK", "gameSound/will_bowAttack.mp3", true, true);
//	_loading->loadSound("WILL_DAMAGED", "gameSound/will_damaged.mp3", true, true);
//	_loading->loadSound("WILL_DEATH", "gameSound/will_death.mp3", true, true);
//	_loading->loadSound("WILL_ROLL", "gameSound/will_roll.mp3", true, true);
//	_loading->loadSound("WILL_SHORTSWORDATTACK", "gameSound/will_shortSwordAttack.mp3", true, true);

}
