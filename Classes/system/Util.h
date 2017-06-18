#ifndef __UTIL_H__
#define __UTIL_H__

#include "cocos2d.h"

class StageTile;
class City;

USING_NS_CC;

/*********************************************************/
/*
 * Utility method
 */
namespace util
{
	// very small number
	constexpr float elim = 0.0000001f;

	// for creating skin cut right
	constexpr int CUT_MASK_RIGHT = 1;
	// for creating skin cut left
	constexpr int CUT_MASK_LEFT = 2;
	// for creating skin cut up
	constexpr int CUT_MASK_UP = 4;
	// for creating skin cut down
	constexpr int CUT_MASK_DOWN = 8;

	/*
	 * Load text file
	 */
	std::string loadText(const std::string &file);
	/*
	 * Input is splited by delimiter
	 */
	std::vector<std::string> splitString(const std::string& input, char delim);
	/*
	 * File is splited by \n and \r
	 * It is compatible for BOM
	 */
	std::vector<std::string> splitFile(const std::string &file);

	/*
	 * Checking node range contains point
	 * down_x or y is extension of left or lower
	 * append_x or y is extension of right or upper
	 */
	bool isTouchInEvent(Vec2 point, Node* t, int down_x, int down_y, int append_x, int append_y);
	/*
	 * Checking event range contains point
	 * down_x or y is extension of left or lower
	 * append_x or y is extension of right or upper
	 */
	inline bool isTouchInEvent(Touch* touch, Event* event, int down_x, int down_y, int append_x, int append_y) { return isTouchInEvent(touch->getLocation(), event->getCurrentTarget(), down_x, down_y, append_x, append_y); };
	/*
	 * Checking node range contains point
	 */
	inline bool isTouchInEvent(Vec2 point, Node* t) { return isTouchInEvent(point, t, 0, 0, 0, 0); };
	/*
	 * Checking event range contains point
	 */
	inline bool isTouchInEvent(Vec2 point, Event* event) { return isTouchInEvent(point, event->getCurrentTarget()); };
	/*
	 * Checking event range contains touch point
	 */
	inline bool isTouchInEvent(Touch* touch, Event* event) { return isTouchInEvent(touch->getLocation(), event->getCurrentTarget()); };

	/*
	 * Get coodinate in screen by target
	 */
	inline Vec2 getCoordinateInScreen(Vec2 pos, Node* target) { return target->convertToWorldSpace(pos); };

	/*
	 * Instanceof 
	 */
	template <typename Of, typename What>
	inline bool instanceof(const What w) { return dynamic_cast<const Of*>(w) != NULL; };

	/*
	 * Get instance 
	 */
	template <typename Of, typename What>
	inline Of* instance(const What w) { return dynamic_cast<Of*>(w); };

	/*
	 * Create frame by skin data
	 */
	Node* createCutSkin(const std::string &file, int w, int h, int cut_mask, int opacity = 255);
	/*
	 * Create frame by skin data with animation
	 */
	Node* createCutSkinAndAnimation(const std::string &file, int w, int h, int wnum, int hnum, int cut_mask, float duration, int opacity = 255);

	/*
	 * Find element in vec
	 * If vec has element, return true
	 */
	template<typename V>
	bool find(const std::vector<V>& vec, V element)
	{
		for (V comp : vec)
			if (comp == element)
				return true;
		return false;
	};

	/*
 	 * Find element satisfying condition in vec
	 * If vec has element satisfying condition, return true
	 */
	template<typename V, typename T>
	bool find(const std::vector<V>& vec, T element, std::function<bool(V, T)> cond)
	{
		for (V comp : vec)
			if (cond(comp, element))
				return true;
		return false;
	};

	/*
 	 * Find element satisfying condition in vec
	 * If vec has element satisfying condition, return it
	 * If not, return nullptr
 	 */
	template<typename V>
	V findElement(const std::vector<V>& vec, std::function<bool(V)> cond)
	{
		for (V comp : vec)
			if (cond(comp))
				return comp;
		return nullptr;
	};

	/*
	 * Collect element and return vector
	 */
	template<typename V>
	std::vector<V> collect(const std::vector<V>& vec, std::function<bool(V)> cond)
	{
		auto result = std::vector<V>();
		for (V comp : vec)
			if (cond(comp))
				result.push_back(comp);
		return result;
	};

	/*
	 * Sort map by value
	 */
	template<typename V, typename T>
	std::vector<std::pair<V, T>> sortMap(const std::map<V, T>& map, bool isGreater = true)
	{
		std::vector<std::pair<V, T>> arr;
		
		for (std::pair<V, T> pair : map)
			arr.push_back(pair);

		if (isGreater)
			std::sort(arr.begin(), arr.end(), [](const std::pair<V, T>& left, const std::pair<V, T> right) {return left.second > right.second; });
		else
			std::sort(arr.begin(), arr.end(), [](const std::pair<V, T>& left, const std::pair<V, T> right) {return left.second < right.second; });

		return arr;
	};

	/*
	 * Initialize random seed
	 */
	void initRand();

	/*
	 * Get random integer n
	 * min < n < max
	 */
	int getRand(int min, int max);

	/*
	 * Get random double n
	 * min < n < max
	 */
	double getRand(double min, double max);
}

#endif // __UTIL_H__