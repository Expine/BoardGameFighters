#ifndef __STAGE_H__
#define __STAGE_H__

#include "cocos2d.h"

class Stage : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Stage);
};

#endif // __STAGE_H__
