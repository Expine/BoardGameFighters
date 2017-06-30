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

	this->addChild(simple::getSprite("res/system/title.png", 225, 400));

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
