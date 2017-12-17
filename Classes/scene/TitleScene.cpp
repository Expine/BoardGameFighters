#include "TitleScene.h"

#include "scene/GameScene.h"
#include "scene/FormationScene.h"
#include "system/Util.h"
#include "system/MultiListener.h"

#include "unit/Unit.h"
#include "unit/Team.h"

USING_NS_CC;

Scene* Title::createScene()
{
    auto scene = Scene::create();    
    auto layer = Title::create();
    scene->addChild(layer);
    return scene;
}

bool Title::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
	
	auto winSize = Director::getInstance()->getWinSize();

	//////////////////////////////
	// 2. set sprite
	auto back = simple::getSprite("res/system/title/title_back.png", winSize.width / 2, winSize.height / 2);
	this->addChild(back);

	auto above_title = simple::getSprite("res/system/title/title_above.png", 225, 800, 1.0f, 255, Vec2::ANCHOR_MIDDLE_BOTTOM);
	auto under_title = simple::getSprite("res/system/title/title_under.png", 225, 0, 1.0f, 255, Vec2::ANCHOR_MIDDLE_TOP);
	back->addChild(above_title);
	back->addChild(under_title);

	std::vector<Sprite*> menu;
	for (unsigned int i = 0; i < TITLE_MENU_NUMBER; ++i) {
		auto item = simple::getSprite(StringUtils::format("res/system/title/title_%d.png", (i + 1)), 225, 600 - 100 * i, 0.0f, 0);
		menu.push_back(item);
		back->addChild(item);
	}


	above_title->runAction(Sequence::create(
		EaseSineIn::create(MoveTo::create(1.0f, Vec2(225, 400))),
		EaseSineOut::create(MoveTo::create(1.0f, Vec2(225, 600))),
		NULL
	));
	under_title->runAction(Sequence::create(
		EaseSineIn::create(MoveTo::create(1.0f, Vec2(225, 400))),
		EaseSineOut::create(MoveTo::create(1.0f, Vec2(225, 200))),
		NULL
	));
	for (auto element : menu)
		element->runAction(Sequence::create(
			DelayTime::create(1.0f),
			Spawn::create(
				FadeIn::create(1.0f),
				ScaleTo::create(1.0f, 0.8f),
				NULL
			),
			NULL
		));

	//////////////////////////////

	// 3. set listener
	auto lis = simple::setEventListener(this);
	lis->onTouchBegan = [] (Touch* touch, Event* event){
		Director::getInstance()->pushScene(Formation::createScene());
		return true;
	};

	// Translation to story mode
	auto story = simple::setSingleListener(menu[0]);
	story->onTap = [](Vec2 pos, Node* t) {
	};

	// Translation to buttle mode
	auto buttle = simple::setSingleListener(menu[1]);
	buttle->onTap = [](Vec2 pos, Node* t) {
	};

	// Translation to formation
	auto formation = simple::setSingleListener(menu[2]);
	formation->onTap = [](Vec2 pos, Node* t) {
	};

	// Translation to config
	auto config = simple::setSingleListener(menu[3]);
	config->onTap = [](Vec2 pos, Node* t) {
	};

	// Translation to shutdown
	auto shutdown = simple::setSingleListener(menu[4]);
	shutdown->onTap = [](Vec2 pos, Node* t) {
		Director::getInstance()->stop
	};

	UnitManager::getInstance()->loadUnitData();
	TeamManager::getInstance()->loadAllTeamData();
		
    return true;
}
