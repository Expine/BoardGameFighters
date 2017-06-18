#ifndef __STORY_SCENE_H__
#define __STORY_SCENE_H__

#include "cocos2d.h"

class Story : public cocos2d::Layer
{
public:
    CREATE_FUNC(Story);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __STORY_SCENE_H__