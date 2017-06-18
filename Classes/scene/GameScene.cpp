#include "GameScene.h"

USING_NS_CC;

Scene* Game::createScene()
{
    auto scene = Scene::create();    
    auto layer = Game::create();
    scene->addChild(layer);
    return scene;
}

bool Game::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
        return false;
        
    return true;
}
