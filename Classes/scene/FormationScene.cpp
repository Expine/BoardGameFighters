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
	_pre_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 200, 300, 400, 0);
	this->addChild(_pre_skin);
	_post_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 600, 300, 400, 0);
	this->addChild(_post_skin);

	// set team
	for (auto i = 0; i < MAX_TEAM_NUMBER; ++i) {
		auto team = simple::getLabel(StringUtils::format("Team %d", (i + 1)), 75, 160 - 35 * i, 20, Color3B::WHITE, Vec2::ANCHOR_MIDDLE_BOTTOM);
		team->setScale(i == 0 ? 1.2f : 0.8f);
		team_skin->addChild(team);
		_team_label.push_back(team);
	}
	setTeam(TeamManager::getInstance()->_teams.at(0));

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
		showUnit(_pre_skin, unit, x, y);

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
			// selected team is bigger than others
			for (auto team : _team_label)
				team->setScale(team == label ? 1.2f : 0.8f);

			// set team sprite
			setTeam(TeamManager::getInstance()->_teams.at(util::findIndex(_team_label, label)));
		};
	}

	return true;
}

void Formation::setTeam(Team* team)
{
	CCASSERT(team, "Team should be not null");

	// Set team number
	_now_team = team;
	_post_skin->removeAllChildren();

	// Set team sprite
	auto sx = 50;
	auto x = sx;
	auto y = 350;
	auto dx = 70;
	auto dy = -70;
	for (auto unit : _now_team->_units) {
		showUnit(_post_skin, unit, x, y);

		// fix position
		x += dx;
		if (x > 300 - sx) {
			x = sx;
			y += dy;
		}
	}
}

void Formation::showUnit(Node* base, Unit * unit, int x, int y)
{
	// set unit sprite
	auto sprite = simple::getSprite("res/unit/" + unit->getFileName(), x, y);
	base->addChild(sprite);

	// set long tap listener
	auto tap = simple::setSingleListener(sprite);
	tap->onLongTapBegan = [this, unit, sprite](Vec2 pos, Node* t) {
		_now_unit = unit;
		// set selected unit sprite
		if (_pp_sp)
			_pp_sp->removeFromParent();
		_pp_sp = simple::getSprite("res/unit/" + unit->getFileName(), pos.x, pos.y, 1.0f, 128);
		this->addChild(_pp_sp);
	};
	tap->onLongTapEnd = [this, base](Vec2 pos, Node* t) {
		// remove selected unit sprite
		if (_pp_sp)
			_pp_sp->removeFromParent();

		// post -> pre is removing from team
		if (base == _post_skin && util::isTouchInEvent(pos, _pre_skin))
		{
			auto index = util::findIndex(_now_team->_units, _now_unit);
			if (index >= 0)
				_now_team->_units.erase(_now_team->_units.begin() + index);
		}
		// pre -> post is adding to team
		else if (base == _pre_skin && util::isTouchInEvent(pos, _post_skin))
			_now_team->_units.push_back(_now_unit);

		// redraw team
		setTeam(_now_team);

		_pp_sp = nullptr;
		_now_unit = nullptr;
	};
}
