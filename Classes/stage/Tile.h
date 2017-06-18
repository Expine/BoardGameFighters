#ifndef __TILE_H__
#define __TILE_H__

#include "cocos2d.h"

class Tile : public cocos2d::Ref
{
protected:
	/*
	 * Initialization
	 */
	bool init();
public:
	CREATE_FUNC(Tile);
};

#endif // __TILE_H__
