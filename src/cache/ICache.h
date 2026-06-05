// abstract Interface 
// any class that wants to be a cache must provide these functions 

#pragma once

#include <string>
#include <optional>
#include "../common/CacheResult.h"

// D in SOLID 
// High level module should depend on abstractions , not concrete implementations
// Suppose we change module there is no need to modify high level module 
// user should not depend on DB

namespace cache {
    class ICache
    {

    public:
        virtual ~ICache() = default;

        virtual CacheResult get( const std:: string & key ) const = 0 ;
        // PUT - inserts or overwrites a key-value pair 
        // returns ok on success
        // avoids copying the string into the function

        virtual CacheResult put (
            const std::string & key , const std::string& value 
        ) = 0 ;

        // DELETE - removes a key , returns ok even if it doesn't exist 

        virtual CacheResult remove ( 
            const std :: string & key 
        ) = 0 ; 

        // Returns current number of entries
        virtual size_t size() const = 0;

        // CLEAR all entries 
        virtual void clear() = 0 ;

    };
}