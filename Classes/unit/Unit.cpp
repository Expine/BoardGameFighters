#include "Unit.h"

#include "system/Util.h"
bool Unit::init()
{
	return true;
}

/******************************************** UnitManager ********************************************/

/*
 * Convert movable directon data
 * 123  -> 000000111
 * 2468 -> 010101010
 */
int convertMovable(std::string m) {
	int result = 0;
	for (auto c : m)
		result |= 1 << ((int)(c - '0') - 1);
	return result;
}


void UnitManager::loadUnitData()
{
	std::map<std::string, Unit::MoveType> type_map;
	type_map["line"] = Unit::MoveType::line;
	type_map["warp"] = Unit::MoveType::warp;
	type_map["knight"] = Unit::MoveType::knight;

	
	for (auto line : util::splitFile("data/unit.csv")) {
		auto data = util::splitString(line, ',');
		// Minimum number is 6
		if (data.size() < 6)
			continue;
		// Comment
		if (util::startWith(data[0], "/") || data[0] == "")
			continue;

		auto unit = Unit::create();
		unit->setIconFileName(data[0]);
		unit->setStandFileName(data[1]);
		unit->setName(data[2]);
		unit->setCost(atoi(data[3].c_str()));
		unit->setMoveType(type_map[data[4]]);
		unit->setMove(convertMovable(data[5]));
		unit->setHP(atoi(data[6].c_str()));
		unit->setAttack(atoi(data[7].c_str()));
		for (unsigned int i = 8; i < data.size(); i++)
			unit->skills.push_back(data[i]);
		_units.pushBack(unit);
	}
}
