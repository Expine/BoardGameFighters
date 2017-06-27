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
	cocos2d::Node* _team_skin;
	cocos2d::Node* _side_skin;
	cocos2d::Node* _pre_skin;
	cocos2d::Node* _post_skin;
	cocos2d::Label* _cost_string;
	cocos2d::Sprite* _unit_image;
	std::vector<cocos2d::Label*> _team_label;
private:
	/*
	 * Set team sprite by team data
	 * @param team Team data
	 */
	void setTeam(Team* team);

	/*
	 * Set now unit
	 * if null, reset unit data
	 */
	void setNowUnit(Unit* unit);

	/*
	 * Add unit to now team
	 */
	void addUnit(Unit* unit);

	/*
	 * Remove unit from now team
	 * Removed unit is last of team
	 */
	void removeUnit(Unit* unit);

	/*
	 * Show unit sprite
	 * @param base Base node where sprite put
	 * @param unit Unit showed for sprite
	 * @param x Sprite x position
	 * @param y Sprite y position
	 */
	void showUnit(Node* base, Unit* unit, int x, int y);
protected:
	Formation() : _now_team(nullptr), _now_unit(nullptr), 
		_pp_sp(nullptr), _team_skin(nullptr), _side_skin(nullptr),
		_pre_skin(nullptr), _post_skin(nullptr), _cost_string(nullptr), _unit_image(nullptr)
	{};
	~Formation() 
	{
		_now_team = nullptr;
		_now_unit = nullptr;
		_pp_sp = nullptr;
		_team_skin = _pre_skin = _post_skin = nullptr;
		_cost_string = nullptr;			 
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
