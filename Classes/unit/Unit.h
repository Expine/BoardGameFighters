#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

/*
 * Unit data
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
	// File name for icon
	CC_SYNTHESIZE(std::string, _iconFileName, IconFileName);
	// File name for Drawing of a unit in a standing pose 
	CC_SYNTHESIZE(std::string, _standFileName, StandFileName);

	// Unit name
	CC_SYNTHESIZE(std::string, _name, Name);
	// Unit movement type
	CC_SYNTHESIZE(MoveType, _move_type, MoveType);
	// Amount of movement for unit
	CC_SYNTHESIZE(int, _move, Move);
	// Unit cost
	CC_SYNTHESIZE(int, _cost, Cost);
	// Unit hit point
	CC_SYNTHESIZE(int, _hp, HP);
	// Unit attack point
	CC_SYNTHESIZE(int, _attack, Attack);

	// list of skill
	std::vector<std::string> skills;

	/*
	 * This instance to string data.
	 */
	inline std::string toString() { return _name; };
};

/**
 * Singleton for managing unit
 */
class UnitManager {
	// protectef for singleton
protected:
	UnitManager() {};
	~UnitManager() {};
public:
	// List of unit
	cocos2d::Vector<Unit*> _units;

	/*
	 * Get instance for singleton
	 */
	static UnitManager* getInstance() { 
		static UnitManager instance; return &instance; 
	};
	/*
	 * Load unit data by reading file
	 */
	void loadUnitData();

	/*
	 * Unparse unit by string
	 * If not exists, return nullptr
	 * @param data Unit string data
	 */
	Unit* unparseUnit(std::string data);
};

#endif // __UNIT_H__
