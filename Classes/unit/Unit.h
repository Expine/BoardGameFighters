#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

/*
 * Unit data
 * 
 */
class Unit : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	/*
	 * Move tyep of unit
	 */
	enum class MoveType { line, warp, knight };


	CREATE_FUNC(Unit);
	CC_SYNTHESIZE(std::string, _iconFileName, IconFileName);
	CC_SYNTHESIZE(std::string, _standFileName, StandFileName);
	CC_SYNTHESIZE(std::string, _name, Name);
	CC_SYNTHESIZE(MoveType, _move_type, MoveType);
	CC_SYNTHESIZE(int, _cost, Cost);
	// amount of movement
	CC_SYNTHESIZE(int, _move, Move);
	CC_SYNTHESIZE(int, _hp, HP);
	CC_SYNTHESIZE(int, _attack, Attack);
	// list of skill
	std::vector<std::string> skills;
};

class UnitManager {
protected:
	UnitManager() {};
	~UnitManager() {};
public:
	cocos2d::Vector<Unit*> _units;

	/*
	 * Get instance for singleton
	 */
	static UnitManager* getInstance() { static UnitManager instance; return &instance; };
	/*
	 * Load unit data by reading file
	 */
	void loadUnitData();
};

#endif // __UNIT_H__
