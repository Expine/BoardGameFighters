#include "TitleScene.h"

#include "system/Util.h"
#include "system/MultiListener.h"

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

	auto next = EventListenerTouchOneByOne::create();
        
    return true;
}
