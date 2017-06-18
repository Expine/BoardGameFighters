#include "FormationScene.h"

USING_NS_CC;

Scene* Formation::createScene()
{
    auto scene = Scene::create();    
    auto layer = Formation::create();
    scene->addChild(layer);
    return scene;
}

bool Formation::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
