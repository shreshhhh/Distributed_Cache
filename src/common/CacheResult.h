// this file defines return type and error enumerations .
// well - designed system because it first defines the interface and then implemnts logic

#pragma once 

#include<string>
#include<optional>

// enum communicates clarity

namespace cache {
    enum class CacheStatus {
        OK ,          // operation succeeded
        NOT_FOUND ,   //  key does not exist 
        EXPIRED ,    // key existed but TTL has elapsed
        CAPACITY_FULL //cache is at its max capacity 
    };

    // simplified scenario of StatusOr<T>`

    struct CacheResult
    {
        CacheStatus status ; // obj
        std::optional<std::string> value  ;

        static CacheResult ok( std::string val) // ok = function name || it returns a cacheResult
        {
            return {CacheStatus :: OK , std::move(val)} ;
            ///     (     status    ) , (     val    )
            // Without move, C++ would copy the string — allocating new memory and duplicating every character. With std::move, it instead transfers ownership of the string's memory — no copy, no allocation. 

        }
        static CacheResult not_found()
        {
            return {CacheStatus::NOT_FOUND , std :: nullopt } ; 
        }

        static CacheResult expired() {
            return {CacheStatus :: EXPIRED , std :: nullopt } ;
        }
        
        bool isOk() const { return status == CacheStatus ::OK ; }

    };

}



