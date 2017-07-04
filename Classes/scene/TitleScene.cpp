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
	
	//////////////////////////////
	// 2. set sprite
	this->addChild(simple::getSprite("res/system/title_back.png", 225, 400));
	auto above_title = simple::getSprite("res/system/title_above.png", 225, 800, 1.0f, 255, Vec2::ANCHOR_MIDDLE_BOTTOM);
	auto under_title = simple::getSprite("res/system/title_under.png", 225, 0, 1.0f, 255, Vec2::ANCHOR_MIDDLE_TOP);
	this->addChild(above_title);
	this->addChild(under_title);

	above_title->runAction(Sequence::create(
		EaseSineIn::create(MoveTo::create(1.0f, Vec2(225, 400))),
		Spawn::create(
			EaseSineInOut::create(RotateBy::create(3.0f, 360)),
			Repeat::create(Sequence::create(
				EaseCircleActionIn::create(ScaleTo::create(0.6f, 1.1f)),
				EaseCircleActionOut::create(ScaleTo::create(0.6f, 0.9f)),
				NULL
			), 3),
			NULL
		),
		EaseExponentialInOut::create(ScaleTo::create(0.3f, 1.0f)),
		NULL
	));
	under_title->runAction(Sequence::create(
		EaseSineIn::create(MoveTo::create(1.0f, Vec2(225, 400))),
		Spawn::create(
			EaseSineInOut::create(RotateBy::create(3.0f, 360)),
			Repeat::create(Sequence::create(
				EaseCircleActionIn::create(ScaleTo::create(0.6f, 1.1f)),
				EaseCircleActionOut::create(ScaleTo::create(0.6f, 0.9f)),
				NULL
			), 3),
			NULL
		),
		EaseExponentialInOut::create(ScaleTo::create(0.3f, 1.0f)),
		NULL
	));


	//////////////////////////////

	// 3. set listener
	auto lis = simple::setEventListener(this);
	lis->onTouchBegan = [] (Touch* touch, Event* event){
//		Director::getInstance()->replaceScene(Formation::createScene());
		Director::getInstance()->pushScene(Formation::createScene());
		return true;
	};

	UnitManager::getInstance()->loadUnitData();
	TeamManager::getInstance()->loadAllTeamData();
		
    return true;
}
