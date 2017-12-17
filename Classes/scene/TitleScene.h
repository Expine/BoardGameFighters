#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

constexpr int TITLE_MENU_NUMBER = 5;

class Title : public cocos2d::Layer
{
public:
    CREATE_FUNC(Title);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __TITLE_SCENE_H__
