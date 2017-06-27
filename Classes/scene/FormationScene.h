#ifndef __FORMATION_SCENE_H__
#define __FORMATION_SCENE_H__

#include "cocos2d.h"

class Team;
class Unit;

class Formation : public cocos2d::Layer
{
private:
	Team* _now_team;
	Unit* _now_unit;
	cocos2d::Sprite* _pp_sp;
	cocos2d::Node* _pre_skin;
	cocos2d::Node* _post_skin;
	std::vector<cocos2d::Label*> _team_label;
private:
	/*
	 * Set team sprite by team data
	 * @param team Team data
	 */
	void setTeam(Team* team);

	/*
	 * Show unit sprite
	 * @param base Base node where sprite put
	 * @param unit Unit showed for sprite
	 * @param x Sprite x position
	 * @param y Sprite y position
	 */
	void showUnit(Node* base, Unit* unit, int x, int y);
protected:
	Formation() : _now_team(nullptr), _now_unit(nullptr), _pp_sp(nullptr), _pre_skin(nullptr), _post_skin(nullptr)
	{};
	~Formation() 
	{
		_now_team = nullptr;
		_now_unit = nullptr;
		_pp_sp = nullptr;
		_pre_skin = _post_skin = nullptr;
	};
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
