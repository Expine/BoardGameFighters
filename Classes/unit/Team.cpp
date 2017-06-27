#include "Team.h"

#include "Unit.h"

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

/******************************************** TeamManager ********************************************/


void TeamManager::loadTeamData()
{
	for(auto i = 0; i < MAX_TEAM_NUMBER; i++)
		_teams.pushBack(Team::create());
}