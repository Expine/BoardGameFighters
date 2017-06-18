#include "StoryScene.h"

USING_NS_CC;

Scene* Story::createScene()
{
    auto scene = Scene::create();    
    auto layer = Story::create();
    scene->addChild(layer);
    return scene;
}

bool Story::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
