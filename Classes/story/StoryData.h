#ifndef __STORY_DATA_H__
#define __STORY_DATA_H__

#include "cocos2d.h"

class StoryData : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(StoryData);
};

#endif // __STORY_DATA_H__
