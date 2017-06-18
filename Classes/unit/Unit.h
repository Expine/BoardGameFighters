#ifndef __UNIT_H__
#define __UNIT_H__

#include "cocos2d.h"

class Unit : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Unit);
};

#endif // __UNIT_H__
