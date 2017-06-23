#include "FormationScene.h"

#include "system/Util.h"
#include "system/MultiListener.h"
#include "unit/Unit.h"
#include "unit/Team.h"

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

	//////////////////////////////
	// 2. set sprite

	// set skins
	auto team_skin = simple::createCutSkinSimply("res/system/window_2.png", 75, 100, 150, 200, 0);
	this->addChild(team_skin);
	auto side_skin = simple::createCutSkinSimply("res/system/window_2.png", 75, 500, 150, 600, 0);
	this->addChild(side_skin);
	auto pre_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 200, 300, 400, 0);
	this->addChild(pre_skin);
	auto post_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 600, 300, 400, 0);
	this->addChild(post_skin);

	// set team
	for (auto i = 0; i < MAX_TEAM_NUMBER; ++i) {
		auto team = simple::getLabel(StringUtils::format("Team %d", (i + 1)), 75, 160 - 35 * i, 20, Color3B::WHITE, Vec2::ANCHOR_MIDDLE_BOTTOM);
		team->setScale(i == 0 ? 1.2f : 0.8f);
		team_skin->addChild(team);
		_team_label.push_back(team);
	}

	//////////////////////////////
	// 3. set listener

	// set move listener
	auto above = Node::create();
	this->addChild(above, 100);
	auto move = simple::setEventListener(above, false, true);
	move->onTouchMoved = [this](Touch* t, Event* e) {
		if (_pp_sp)
			_pp_sp->setPosition(t->getLocation());
	};

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
			if (_pp_sp)
				_pp_sp->removeFromParent();
			_pp_sp = simple::getSprite("res/unit/" + unit->getFileName(), pos.x, pos.y, 1.0f, 128);
			this->addChild(_pp_sp);
		};
		tap->onLongTapEnd = [this](Vec2 pos, Node* t) {
			if (_pp_sp)
				_pp_sp->removeFromParent();
			_pp_sp = nullptr;
		};

		// fix position
		x += dx;
		if (x > 300 - sx) {
			x = sx;
			y += dy;
		}
	}

	for (auto label : _team_label) {
		// set listener
		auto t_lis = simple::setSingleListener(label);
		t_lis->onTap = [this, label](Vec2 pos, Node* t) {
			for (auto team : _team_label)
				team->setScale(team == label ? 1.2f : 0.8f);
		};
	}

	return true;
}

void Formation::popupUnit()
{
}