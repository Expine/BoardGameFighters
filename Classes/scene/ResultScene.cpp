#include "ResultScene.h"

USING_NS_CC;

Scene* Result::createScene()
{
    auto scene = Scene::create();    
    auto layer = Result::create();
    scene->addChild(layer);
    return scene;
}

bool Result::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
