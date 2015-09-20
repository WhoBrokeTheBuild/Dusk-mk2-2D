#ifndef DUSK_COLLECTIONS_ARRAY_LIST_HPP
#define DUSK_COLLECTIONS_ARRAY_LIST_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <vector>
#include <algorithm>

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
		std::vector<T>::push_back(item);
	}

	inline bool contains(const T& item) const
	{
		return (std::vector<T>::empty() ? false : std::find(std::vector<T>::cbegin(), std::vector<T>::cend(), item) != std::vector<T>::cend());
	}

	inline bool has_index(const unsigned int& index) const
	{
		return (std::vector<T>::empty() ? false : (index >= 0 && index <= std::vector<T>::size() - 1));
	}

	inline unsigned int index_of(const T& item) const
	{
		return std::find(std::vector<T>::begin(), std::vector<T>::end(), item) - std::vector<T>::begin();
	}

	inline bool erase_next(const T& item)
	{
		auto it = std::find(std::vector<T>::begin(), std::vector<T>::end(), item);
		
		if (it != std::vector<T>::end()) 
		{
			std::vector<T>::erase(it);
			return true;
		}

		return false;
	}

	inline bool erase_all(const T& item)
	{
		auto it = std::find(std::vector<T>::begin(), std::vector<T>::end(), item);
		
		if (it == std::vector<T>::end())
			return false;

		while (it != std::vector<T>::end()) 
		{
			std::vector<T>::erase(it);
			it = find(std::vector<T>::begin(), std::vector<T>::end(), item);
		}

		return true;
	}

	inline bool erase_at(const unsigned int& index)
	{
		if (has_index(index))
		{
			std::vector<T>::erase(std::vector<T>::begin() + index);
			return true;
		}

		return false;
	}

}; // class ArrayList

} // namespace dusk

#endif // DUSK_COLLECTIONS_ARRAY_LIST_HPP
