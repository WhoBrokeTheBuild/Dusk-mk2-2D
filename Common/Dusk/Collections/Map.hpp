#ifndef DUSK_COLLECTIONS_MAP_HPP
#define DUSK_COLLECTIONS_MAP_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <map>

namespace dusk
{

template <class K, class T, typename Sort = std::less<K>>
class Map :
	public ITrackedObject,
	public std::map<K, T, Sort>
{
public:

	virtual inline string GetClassName() const { return "Map"; }

	inline void add(std::pair<K, T> pair)
	{
		std::map<K, T, Sort>::insert(pair);
	}

	inline void add(const K& key, const T& item)
	{
		std::map<K, T, Sort>::insert(std::pair<K, T>(key, item)); 
	}

	inline bool contains_key(const K& key) const
	{
		return (std::map<K, T, Sort>::find(key) != std::map<K, T, Sort>::cend()); 
	}

	inline bool erase_next(const T& item)
	{
		auto it = std::map<K, T, Sort>::begin();

		while (it != std::map<K, T, Sort>::end()) 
		{
			if (it->second == item) 
			{
				std::map<K, T, Sort>::erase(it);
				return true;
			}
			++it;
		}

		return false;
	}

	inline bool erase_all(const T& item)
	{
		auto it = std::map<K, T, Sort>::begin();
		bool found = false;

		while (it != std::map<K, T, Sort>::end())
		{
			if (it->second == item)
			{
				it = std::map<K, T, Sort>::erase(it);
				found = true;
			}
			else 
			{
				++it;
			}
		}

		return found;
	}

}; // class Map<T, K, Sort>

} // namespace dusk

#endif // DUSK_COLLECTIONS_MAP_HPP
