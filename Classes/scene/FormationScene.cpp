#include "FormationScene.h"

#include "system/Util.h"
#include "system/MultiListener.h"
#include "unit/Unit.h"

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

	auto win_size = Director::getInstance()->getWinSize();

	auto side_skin = simple::createCutSkinSimply("res/system/window_2.png", 75, 400, 150, 800, 0);
	this->addChild(side_skin);

	auto pre_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 200, 300, 400, 0);
	this->addChild(pre_skin);

	auto post_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 600, 300, 400, 0);
	this->addChild(post_skin);

	auto sx = 50;
	auto x = sx;
	auto y = 50;
	auto dx = 70;
	auto dy = 70;
	for (auto unit : UnitManager::getInstance()->_units) {
		// set unit sprite
		auto sprite = simple::getSprite("res/unit/" + unit->getFileName(), x, y);
		pre_skin->addChild(sprite);

		// set long tap listener
		auto tap = simple::setSingleListener(sprite);
		tap->onLongTapBegan = [this, unit, sprite](Vec2 pos, Node* t) {
			auto sp = simple::getSprite("res/unit/" + unit->getFileName(), pos.x, pos.y, 1.0f, 128);
			auto lis = simple::setEventListener(sp);
			lis->onTouchMoved = [sp](Touch* touch, Event* event) {
				sp->setPosition(touch->getLocation());
			};
			this->addChild(sp);
		};

		// fix position
		x += dx;
		if (x > 300 - sx) {
			x = sx;
			y += dy;
		}
	}

	return true;
}

void Formation::popupUnit()
{
}