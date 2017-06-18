#ifndef __TEAM_H__
#define __TEAM_H__

#include "cocos2d.h"

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

#endif // __TEAM_H__
