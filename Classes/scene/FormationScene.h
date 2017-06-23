#ifndef __FORMATION_SCENE_H__
#define __FORMATION_SCENE_H__

#include "cocos2d.h"

class Formation : public cocos2d::Layer
{
private:
	/*
	 * Popup unit by long tap
	 */
	void popupUnit();
public:
    CREATE_FUNC(Formation);
	/*
	 * Create title scene with init
	 */
    static cocos2d::Scene* createScene();

    /*
     * Initialization
     */
    virtual bool init();
};

#endif // __FORMATION_SCENE_H__
