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
	auto userDef = UserDefault::getInstance();
	auto data = userDef->getStringForKey(StringUtils::format("team_%d", no).c_str());
	for (auto it : util::splitString(data, ','))
	{
		if (it.length() > 0)
		{
			auto unit = UnitManager::getInstance()->unparseUnit(it);
			if (unit)
				_units.push_back(unit);
		}
	}
}

std::string Team::toString()
{
	return util::reduceLeft<Unit*, std::string>(_units, "", [](std::string s, Unit* u) { return s + u->toString() + ","; });
}

/******************************************** TeamManager ********************************************/
