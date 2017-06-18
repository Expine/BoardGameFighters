#ifndef __INSTALL_SCENE_H__
#define __INSTALL_SCENE_H__

#include "cocos2d.h"

class Install : public cocos2d::Layer
{
public:
    CREATE_FUNC(Install);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __INSTALL_SCENE_H__
