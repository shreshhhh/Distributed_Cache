// Actual implementation of ICache
// actual class that will store data in memory 
// This class says that these funstions exist 

//-------------------------------//
// InMemoryCache.h
// What the class can do

// InMemoryCache.cpp
// How the class does it
//-------------------------------//

#pragma once

#include<unordered_map> // Hash collision is handled via chaining ( Linked List )
#include<string>
#include<optional>
#include "ICache.h" // abstraction function

namespace cache
{
    class InMemoryCache : public ICache
    {
        private :
            std::unordered_map<std::string ,std::string > store_ ;
            size_t maxCapacity_ ; 
        public:
            // Do not automatically convert other types into this class. Make me create the object explicitly.
            explicit InMemoryCache( size_t maxCapacity = 0 ) ; 

            // Override keyword is MANDATORY in production level C++
            
            CacheResult get( const std :: string & key ) const override ;
            CacheResult put( const std :: string & key , const std::string& value ) override ;
            CacheResult remove( const std :: string& key ) override ;
            size_t size() const override ;
            void clear() override ; 

            size_t capacity() const { return maxCapacity_ ; }
            bool isFull() const ; 
    };

} // namespace cache
