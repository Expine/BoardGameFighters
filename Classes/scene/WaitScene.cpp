#include "WaitScene.h"

USING_NS_CC;

Scene* Wait::createScene()
{
    auto scene = Scene::create();    
    auto layer = Wait::create();
    scene->addChild(layer);
    return scene;
}

bool Wait::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
