#ifndef DUSK_COLLECTIONS_HASH_MAP_HPP
#define DUSK_COLLECTIONS_HASH_MAP_HPP

#include <Dusk/Tracking/TrackedObject.hpp>

#include <unordered_map>

/// \addtogroup Collections
/// @{

namespace dusk
{

////////////////////////////////////////////////////////////
/// \class HashMap HashMap.hpp <Dusk/Collections/HashMap.hpp>
///
/// \brief A templated hash map. Based on std::unordered_map
///
////////////////////////////////////////////////////////////
template <class KeyType, class ValueType, 
            typename Hasher = std::hash<KeyType>,
            typename KeyEqual = std::equal_to<KeyType>,
            typename Alloc = std::allocator<std::pair<KeyType, ValueType>>>
class HashMap :
    public TrackedObject,
    public std::unordered_map<KeyType, ValueType, Hasher, KeyEqual, Alloc>
{
public:

    typedef std::unordered_map<KeyType, ValueType, Hasher, KeyEqual, Alloc> STLType;

    virtual inline string GetClassName() const override { return "Hash Map"; }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new item to the collection. Alias for insert()
    ///
    /// \param pair A new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(std::pair<KeyType, ValueType> pair)
    {
        STLType::insert(pair);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new pair to the collection. Alias for insert(pair(key, value))
    ///
    /// \param key The key of the new item to add to the collection
    /// \param value The value of the new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(const KeyType& key, const ValueType& item)
    {
        STLType::insert(std::pair<KeyType, ValueType>(key, item));
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check if the collection contains a key
    ///
    /// \param key The key to check against the collection
    ///
    /// \returns True if the collection contains that key, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool contains_key(const KeyType& key) const
    {
        return (STLType::find(key) != STLType::cend());
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
        auto it = STLType::begin();

        while (it != STLType::end())
        {
            if (it->second == item)
            {
                STLType::erase(it);
                return true;
            }
            ++it;
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
        auto it = STLType::begin();
        bool found = false;

        while (it != STLType::end())
        {
            if (it->second == item)
            {
                it = STLType::erase(it);
                found = true;
            }
            else
            {
                ++it;
            }
        }

        return found;
    }

}; // class HashMap

} // namespace dusk

  /// @}

#endif // DUSK_COLLECTIONS_HASH_MAP_HPP
