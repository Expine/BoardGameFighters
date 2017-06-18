#ifndef __EVENT_H__
#define __EVENT_H__

#include "cocos2d.h"

class Event : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Event);
};

#endif // __EVENT_H__
