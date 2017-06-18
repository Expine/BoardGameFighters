#ifndef __DATA_MANAGER_H__
#define __DATA_MANAGER_H__

#include "cocos2d.h"

class DataManager : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(DataManager);
};

#endif // __DATA_MANAGER_H__
