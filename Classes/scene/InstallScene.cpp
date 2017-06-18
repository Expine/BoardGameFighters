#include "InstallScene.h"

USING_NS_CC;

Scene* Install::createScene()
{
    auto scene = Scene::create();    
    auto layer = Install::create();
    scene->addChild(layer);
    return scene;
}

bool Install::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
