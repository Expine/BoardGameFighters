#ifndef __TEAM_H__
#define __TEAM_H__

#include "cocos2d.h"

// maximum number of teams
constexpr int MAX_TEAM_NUMBER = 5;
// maximum number of team member
constexpr int MAX_MEMVER_NUMBER = 100;

class Team : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Team);
};

class TeamManager {
protected:
	TeamManager() {};
	~TeamManager() {};
public:
	cocos2d::Vector<Team*> _teams;

	/*
	 * Get instance for singleton
	 */
	static TeamManager* getInstance() { static TeamManager instance; return &instance; };
	/*
	 * Load unit data by reading file
	 */
	void loadTeamData();
};


#endif // __TEAM_H__