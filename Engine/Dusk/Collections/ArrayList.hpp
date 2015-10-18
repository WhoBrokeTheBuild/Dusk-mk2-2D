#ifndef DUSK_COLLECTIONS_ARRAY_LIST_HPP
#define DUSK_COLLECTIONS_ARRAY_LIST_HPP

#include <Dusk/Tracking/TrackedObject.hpp>

#include <vector>
#include <algorithm>

/// \addtogroup Collections
/// @{

namespace dusk
{

////////////////////////////////////////////////////////////
/// \class ArrayList ArrayList.hpp <Dusk/Collections/ArrayList.hpp>
///
/// \brief A templated array-backed container. Based on std::vector
///
////////////////////////////////////////////////////////////
template <class ValueType, typename Alloc = std::allocator<ValueType>>
class ArrayList :
    public TrackedObject,
    public std::vector<ValueType, Alloc>
{
public:

    typedef std::vector<ValueType, Alloc> STLType;

    virtual inline string GetClassName() const override { return "Array List"; }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new item to the collection. Alias for push_back()
    ///
    /// \param item A new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(const ValueType& item)
    {
        STLType::push_back(item);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check whether an item exists in the collection
    ///
    /// \param item The item to search for
    ///
    /// \returns True if the item exists in the collection, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool contains(const ValueType& item) const
    {
        return (STLType::empty() ? false : std::find(STLType::cbegin(), STLType::cend(), item) != STLType::cend());
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
        return (STLType::empty() ? false : (index >= 0 && index <= STLType::size() - 1));
    }

    ////////////////////////////////////////////////////////////
    /// \brief Get the index of an item in the collection
    ///
    /// \param item The item to find the index of
    ///
    /// \returns The index of the item if it exists in the collection, -1 otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline unsigned int index_of(const ValueType& item) const
    {
        return std::find(STLType::begin(), STLType::end(), item) - STLType::begin();
    }

    ////////////////////////////////////////////////////////////
    /// \brief Remove the next occurrence of an item from the collection
    ///
    /// \param item The item to remove
    ///
    /// \returns True if an element was removed, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool erase_next(const ValueType& item)
    {
        auto it = std::find(STLType::begin(), STLType::end(), item);

        if (it != STLType::end())
        {
            STLType::erase(it);
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
    inline bool erase_all(const ValueType& item)
    {
        auto it = std::find(STLType::begin(), STLType::end(), item);

        if (it == STLType::end())
            return false;

        while (it != STLType::end())
        {
            STLType::erase(it);
            it = find(STLType::begin(), STLType::end(), item);
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
            STLType::erase(STLType::begin() + index);
            return true;
        }

        return false;
    }

}; // class ArrayList

} // namespace dusk

/// @}

#endif // DUSK_COLLECTIONS_ARRAY_LIST_HPP
