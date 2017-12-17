#ifndef __TEAM_H__
#define __TEAM_H__

#include "cocos2d.h"

class Unit;

// maximum number of teams
constexpr int MAX_TEAM_NUMBER = 5;
// maximum number of team member
constexpr int MAX_MEMVER_NUMBER = 100;

// maximum cost
constexpr int TEAM_MAX_COST = 100;

/**
 * Team composed of units
 * 
 */
class Team : public cocos2d::Ref
{
public:
	std::vector<Unit*> _units;

protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Team);
	/*
	 * Get summation of cost of units
	 */
	int getAllCost();

	/*
	 * Save team data
	 * @param no Team number
	 */
	void saveTeamData(int no);

	/*
	 * Load team data
	 * Clear unit data and reload unit data by userdefault
	 * @param no Team number
	 */
	void loadTeamData(int no);

	/*
	 * This instance to string data.
	 */
	std::string toString();
};

/**
 * Singleton for managing team
 */
class TeamManager {
	// protected for singleton
protected:
	TeamManager() {};
	~TeamManager() {};
public:
	/** List of team */
	cocos2d::Vector<Team*> _teams;

	/*
	 * Save all team data
	 */
	void saveAllTeamData()
	{
		for (unsigned int i = 0; i < _teams.size(); ++i)
			_teams.at(i)->saveTeamData(i);
	};

	/*
	 * Load all team data
	 */
	void loadAllTeamData()
	{
		// Set team instance
		if (_teams.size() == 0)
			for (int i = 0; i < MAX_TEAM_NUMBER; ++i)
				_teams.pushBack(Team::create());
		// Load team
		for (unsigned int i = 0; i < _teams.size(); ++i)
			_teams.at(i)->loadTeamData(i);
	};

	/*
	 * Get instance for singleton
	 * With loading all team data
	 */
	static TeamManager* getInstance() { 
		static TeamManager instance; 
		instance.loadAllTeamData();
		return &instance; 
	};
};


#endif // __TEAM_H__