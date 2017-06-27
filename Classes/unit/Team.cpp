#include "Team.h"

bool Team::init()
{
	return true;
}

/******************************************** TeamManager ********************************************/


void TeamManager::loadTeamData()
{
	for(auto i = 0; i < MAX_TEAM_NUMBER; i++)
		_teams.pushBack(Team::create());
}