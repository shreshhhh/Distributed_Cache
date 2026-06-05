// How the functions actually works after declaring and existing

//-------------------------------//
// InMemoryCache.h
// What the class can do

// InMemoryCache.cpp
// How the class does it
//-------------------------------//

#include "InMemoryCache.h"
#include <stdexcept>

namespace cache
{
    // Constructor
    // Intializer list is preferred over assignment in Constructor body .
    //                                                   (    initializer list    )
    InMemoryCache ::InMemoryCache(size_t maxCapacity) : maxCapacity_(maxCapacity)
    // this is a contructor with an initializer list
    // InMemoryCache accepts a parameter named maxCapacity || like InMemoryCache(100) || InMemoryCache = 100
    // Initilaizer list = construct maxCapacity_ with the value stored on maxCapacity
    // Same time par member initialize bhi ho jaata hai
    {
        // Reserve space in hashmap

        if (maxCapacity_ > 0)
        {
            store_.reserve(maxCapacity_); // store_ = hashmap
        }
    }

    // We are defining the get() function that belongs to the InMemoryCache class.
    // (return type = CacheResult ) ( const so that string do not get modified )
    CacheResult InMemoryCache::get(const std ::string &key) const
    {
        // - operator[] INSERTS a default value if key is missing (dangerous in const context, and surprising behavior)
        // - find() returns end() iterator if not found — safe and explicit

        auto it = store_.find(key);

        if (it == store_.end())
        {
            // if key not found . Return a NOT_FOUND result .
            return CacheResult::not_found();
        }
        // it->second
        return CacheResult::ok(it->second);
        // it returns
        // {
        //     CacheStatus::OK,
        //     "Shrestha"
        // }
    }

    CacheResult InMemoryCache::put(const std::string &key, const std::string &value)
    {
        if (maxCapacity_ > 0 && store_.size() >= maxCapacity_)
        {
            if (store_.find(key) == store_.end())
            {
                return {CacheStatus::CAPACITY_FULL, std::nullopt};
            }
        }
        store_[key] = value;
        return CacheResult::ok(value);
    }

    CacheResult InMemoryCache ::remove(const std ::string &key)
    {
        store_.erase(key);
        return CacheResult::ok("");
    }

    size_t InMemoryCache::size() const
    {
        return store_.size();
    }

    bool InMemoryCache::isFull() const
    {
        return maxCapacity_ > 0 && store_.size() >= maxCapacity_;
    }

    void InMemoryCache::clear()
    {
        store_.clear();
    }
} // namespace cache
