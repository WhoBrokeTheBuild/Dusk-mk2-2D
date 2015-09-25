#ifndef DUSK_COLLECTIONS_ARRAY_LIST_HPP
#define DUSK_COLLECTIONS_ARRAY_LIST_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <vector>
#include <algorithm>

namespace dusk
{

////////////////////////////////////////////////////////////
/// \class ArrayList ArrayList.hpp <Dusk/Collections/ArrayList.hpp>
///
/// \brief A templated array-backed container. Based on std::vector
///
////////////////////////////////////////////////////////////
template <class T>
class ArrayList :
    public ITrackedObject,
    public std::vector<T>
{
public:

    virtual inline string GetClassName() const
    {
        return "Array List";
    }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new item to the collection. Alias for push_back()
    ///
    /// \param item A new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(const T& item)
    {
        std::vector<T>::push_back(item);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check whether an item exists in the collection
    ///
    /// \param item The item to search for
    ///
    /// \returns True if the item exists in the collection, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool contains(const T& item) const
    {
        return (std::vector<T>::empty() ? false : std::find(std::vector<T>::cbegin(), std::vector<T>::cend(), item) != std::vector<T>::cend());
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check whether an index exists in the collection
    ///
    /// \param index The index to check against the collection's bounds
    ///
    /// \returns True if the index exists in the collection, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool has_index(const unsigned int& index) const
    {
        return (std::vector<T>::empty() ? false : (index >= 0 && index <= std::vector<T>::size() - 1));
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the index of an item in the collection
    ///
    /// \param item The item to find the index of
    ///
    /// \returns The index of the item if it exists in the collection, -1 otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline unsigned int index_of(const T& item) const
    {
        return std::find(std::vector<T>::begin(), std::vector<T>::end(), item) - std::vector<T>::begin();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Remove the next occurrence of an item from the collection
    ///
    /// \param item The item to remove
    ///
    /// \returns True if an element was removed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
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
    
    ////////////////////////////////////////////////////////////
    /// \brief Remove all occurrences of an item from the collection
    ///
    /// \param item The item to remove
    ///
    /// \returns True if an element was removed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
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

    ////////////////////////////////////////////////////////////
    /// \brief Remove the item at a specified index
    ///
    /// \param index The index of the item to remove
    ///
    /// \returns True if an element was removed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
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
