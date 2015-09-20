#ifndef DUSK_COLLECTIONS_ARRAY_LIST_HPP
#define DUSK_COLLECTIONS_ARRAY_LIST_HPP

#include <Tracking/ITrackedObject.hpp>

#include <vector>

namespace dusk
{

template <class T>
class ArrayList :
	public ITrackedObject,
	public std::vector<T>
{
public:

	virtual inline string GetClassName() const { return "Array List"; }

	inline void add(const T& item)
	{ 
		push_back(item);
	}

	inline bool contains(const T& item) const
	{
		return (empty() ? false : find(cbegin(), cend(), item) != cend());
	}

	inline bool has_index(const unsigned int& index) const
	{
		return (empty() ? false : (index >= 0 && index <= size() - 1));
	}

	inline unsigned int index_of(const T& item) const
	{
		return find(begin(), end(), item) - begin();
	}

	inline bool erase_next(const T& item)
	{
		auto it = find(begin(), end(), item);
		
		if (it != end()) 
		{
			erase(it);
			return true;
		}

		return false;
	}

	inline bool erase_all(const T& item)
	{
		auto it = find(begin(), end(), item);
		
		if (it == end())
			return false;

		while (it != end()) 
		{
			erase(it);
			it = find(begin(), end(), item);
		}

		return true;
	}

	inline bool erase_at(const unsigned int& index)
	{
		if (has_index(index))
		{
			erase(begin() + index);
			return true;
		}

		return false;
	}

}; // class ArrayList

} // namespace dusk

#endif // DUSK_COLLECTIONS_ARRAY_LIST_HPP