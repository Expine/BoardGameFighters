#ifndef __WAIT_SCENE_H__
#define __WAIT_SCENE_H__

#include "cocos2d.h"

class Wait : public cocos2d::Layer
{
public:
    CREATE_FUNC(Wait);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __WAIT_SCENE_H__
