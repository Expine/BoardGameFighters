#include "Team.h"

#include "Unit.h"
#include "system/Util.h"

USING_NS_CC;

bool Team::init()
{
	return true;
}

int Team::getAllCost()
{
	auto result = 0;
	for (auto unit : _units)
		result += unit->getCost();
	return result;
}

void Team::saveTeamData(int no)
{
	auto userDef = UserDefault::getInstance();
	userDef->setStringForKey(StringUtils::format("team_%d", no).c_str(), toString());
	userDef->flush();
}

void Team::loadTeamData(int no)
{
	_units.clear();

	Unit* unit;
	auto data = UserDefault::getInstance()->getStringForKey(StringUtils::format("team_%d", no).c_str());
	// Load data as csv
	for (auto it : util::splitString(data, ','))
		// Check unit name is enable
		if (it.length() > 0 && (unit = UnitManager::getInstance()->unparseUnit(it)))
			_units.push_back(unit);
}

std::string Team::toString()
{
	return util::reduceLeft<Unit*, std::string>(_units, "", [](std::string s, Unit* u) { return s + u->toString() + ","; });
}

/******************************************** TeamManager ********************************************/
