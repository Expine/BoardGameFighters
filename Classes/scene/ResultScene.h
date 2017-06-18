#ifndef __RESULT_SCENE_H__
#define __RESULT_SCENE_H__

#include "cocos2d.h"

class Result : public cocos2d::Layer
{
public:
    CREATE_FUNC(Result);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __RESULT_SCENE_H__
