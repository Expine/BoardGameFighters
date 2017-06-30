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
	_team_skin = simple::createCutSkinSimply("res/system/window_2.png", 75, 100, 150, 200, 0);
	this->addChild(_team_skin);
	_side_skin = simple::createCutSkinSimply("res/system/window_2.png", 75, 500, 150, 600, 0);
	this->addChild(_side_skin);
	_pre_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 200, 300, 400, 0);
	this->addChild(_pre_skin);
	_post_skin = simple::createCutSkinSimply("res/system/window_1.png", 300, 600, 300, 400, 0);
	this->addChild(_post_skin);

	// set team
	for (auto i = 0; i < MAX_TEAM_NUMBER; ++i) {
		auto team = simple::getLabel(StringUtils::format("Team %d", (i + 1)), 75, 160 - 35 * i, 20, Color3B::WHITE, Vec2::ANCHOR_MIDDLE_BOTTOM);
		team->setScale(i == 0 ? 1.2f : 0.8f);
		_team_skin->addChild(team);
		_team_label.push_back(team);
	}
	setTeam(TeamManager::getInstance()->_teams.at(0));

	// set command
	auto save = simple::getLabel("Save", 75, 580, 20, Color3B::WHITE, Vec2::ANCHOR_MIDDLE_TOP);
	_side_skin->addChild(save);
	auto lsn = simple::setEventListener(save);
	lsn->onTouchEnded= [this](Touch* t, Event* e) {
		TeamManager::getInstance()->loadAllTeamData();
	};


	// show unit
	auto sx = 40;
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
	// set remove listener
	auto remove = simple::setEventListener(this, false, true);
	remove->onTouchBegan = [this](Touch* t, Event* e) {
		setNowUnit(nullptr);
		return true;
	};

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

	if (_cost_string)
		_cost_string->removeFromParent();
	_cost_string = simple::getLabel(StringUtils::format("%d / %d", team->getAllCost(), TEAM_MAX_COST), 75, 570, 20, Color3B::WHITE, Vec2::ANCHOR_MIDDLE);
	_side_skin->addChild(_cost_string);

	// Set team number
	_now_team = team;
	_post_skin->removeAllChildren();

	// Set team sprite
	auto sx = 40;
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

void Formation::setNowUnit(Unit * unit)
{
	auto equal = unit && _now_unit && _now_unit->getStandFileName() == unit->getStandFileName();
	_now_unit = unit;

	// if smae unit, do not update
	if (equal)
		return;

	if (_unit_image)
		_unit_image->removeFromParent();

	if (unit)
	{
		_unit_image = simple::getSprite("res/unit/stand/" + unit->getStandFileName(), 75, 250, 0.20);
		_side_skin->addChild(_unit_image);
	}
	else
		_unit_image = nullptr;
}

void Formation::addUnit(Unit * unit)
{
	// If cost over, cannot add
	if (_now_team->getAllCost() + unit->getCost() > TEAM_MAX_COST)
		return;

	_now_team->_units.push_back(unit);
}

void Formation::removeUnit(Unit * unit)
{
	auto index = util::findIndex(_now_team->_units, unit);
	if (index >= 0)
		_now_team->_units.erase(_now_team->_units.begin() + index);
}

void Formation::showUnit(Node* base, Unit * unit, int x, int y)
{
	// set unit sprite
	auto sprite = simple::getSprite("res/unit/icon/" + unit->getIconFileName(), x, y);
	base->addChild(sprite);

	// set long tap listener
	auto tap = simple::setSingleListener(sprite);
	tap->onTap = [this, unit, sprite](Vec2 pos, Node* t) {
		setNowUnit(unit);
	};
	tap->onLongTapBegan = [this, unit, sprite](Vec2 pos, Node* t) {
		setNowUnit(unit);
		// set selected unit sprite
		if (_pp_sp)
			_pp_sp->removeFromParent();
		_pp_sp = simple::getSprite("res/unit/icon/" + unit->getIconFileName(), pos.x, pos.y, 1.0f, 128);
		this->addChild(_pp_sp);
	};
	tap->setLongTapThreshold(0.1f);
	tap->onLongTapEnd = [this, base](Vec2 pos, Node* t) {
		// remove selected unit sprite
		if (_pp_sp)
			_pp_sp->removeFromParent();

		// post -> pre is removing from team
		if (base == _post_skin && util::isTouchInEvent(pos, _pre_skin))
			removeUnit(_now_unit);
		// pre -> post is adding to team
		else if (base == _pre_skin && util::isTouchInEvent(pos, _post_skin))
			addUnit(_now_unit);
		
		// redraw team
		setTeam(_now_team);

		_pp_sp = nullptr;
	};
	tap->onFlick = [this, unit, base](Vec2 pos, Vec2 diff, float time) {
		// flick post -> pre
		if (base == _post_skin) 
			removeUnit(unit);
		// flick pre -> post
		else if (base == _pre_skin)
			addUnit(unit);

		// redraw team
		setTeam(_now_team);
	};
}
