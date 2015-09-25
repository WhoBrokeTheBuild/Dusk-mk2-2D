#ifndef DUSK_COLLECTIONS_MAP_HPP
#define DUSK_COLLECTIONS_MAP_HPP

#include <Dusk/Tracking/ITrackedObject.hpp>

#include <map>

namespace dusk
{

////////////////////////////////////////////////////////////
/// \class Map Map.hpp <Dusk/Collections/Map.hpp>
///
/// \brief A templated map. Based on std::map
///
////////////////////////////////////////////////////////////
template <class K, class T, typename Sort = std::less<K>>
class Map :
    public ITrackedObject,
    public std::map<K, T, Sort>
{
public:

    virtual inline string GetClassName() const
    {
        return "Map";
    }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new item to the collection. Alias for insert()
    ///
    /// \param pair A new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(std::pair<K, T> pair)
    {
        std::map<K, T, Sort>::insert(pair);
    }

    ////////////////////////////////////////////////////////////
    /// \brief Add a new pair to the collection. Alias for insert(pair(key, value))
    ///
    /// \param key The key of the new item to add to the collection
    /// \param value The value of the new item to add to the collection
    ///
    ////////////////////////////////////////////////////////////
    inline void add(const K& key, const T& item)
    {
        std::map<K, T, Sort>::insert(std::pair<K, T>(key, item));
    }

    ////////////////////////////////////////////////////////////
    /// \brief Check if the collection contains a key
    ///
    /// \param key The key to check against the collection
    ///
    /// \returns True if the collection contains that key, false otherwise
    ///
    ////////////////////////////////////////////////////////////
    inline bool contains_key(const K& key) const
    {
        return (std::map<K, T, Sort>::find(key) != std::map<K, T, Sort>::cend());
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
