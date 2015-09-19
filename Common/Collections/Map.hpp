#ifndef DUSK_COLLECTIONS_MAP_HPP
#define DUSK_COLLECTIONS_MAP_HPP

#include <Tracking/ITrackedObject.hpp>

#include <map>

namespace Dusk
{

template <class K, class T, typename Sort = std::less<K>>
class Map :
	public ITrackedObject,
	public std::map<K, T, Sort>
{
public:

	virtual inline string GetClassName( void ) const { return "Map"; }

	inline void add(std::pair<K, T> pair)
	{
		insert(pair);
	}

    inline void add( const K& key, const T& item )
    { 
		insert(std::pair<K, T>(key, item)); 
	}

    inline bool contains_key( const K& key ) const
	{
		return (find(key) != cend()); 
	}

	inline bool erase_next(const T& item)
	{
		auto it = begin();

		while (it != end()) 
		{
			if (it->second == item) 
			{
				erase(it);
				return true;
			}
			++it;
		}

		return false;
	}

	inline bool erase_all(const T& item)
	{
		auto it = begin();
		bool found = false;

		while (it != end())
		{
			if (it->second == item)
			{
				it = erase(it);
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

} // namespace Dusk

#endif // DUSK_COLLECTIONS_MAP_HPP
