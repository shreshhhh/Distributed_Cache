#include <gtest/gtest.h>
#include "cache/InMemoryCache.h"

class InMemoryCacheTest :public ::testing :: Test
{
protected:
    void SetUp() override {
        cache_ = std::make_unique<cache::InMemoryCache>() ;
    }
    std::unique_ptr<cache::InMemoryCache> cache_ ;
};

// Basic Operations 

TEST_F (InMemoryCacheTest , GetOnEmptyCacheReturnsNotFound )
{
    auto result = cache_ -> get( "nonexistent_key" ) ;
    EXPECT_EQ(result.status , cache::CacheStatus::NOT_FOUND) ;
    EXPECT_FALSE(result.value.has_value()) ;
}

TEST_F( InMemoryCacheTest , PutAndGetReturnsCorrectValue ) {

    cache_ -> put ( "user:123" , "Shrestha" ) ;

    auto result = cache_ -> get("user:123") ;

    EXPECT_TRUE(result.isOk()) ;
    EXPECT_EQ(result.value.value() , "Shrestha" ) ; 
}

TEST_F(InMemoryCacheTest , PutOverwritesExistingValue) {
    cache_ -> put ( "key" , "original" ) ;
    cache_ -> put ( "key" , "updated" ) ;

    auto result = cache_ -> get("key") ;

    EXPECT_EQ(result.value.value() , "updated" ) ;
}

TEST_F(InMemoryCacheTest , DeleteRemovesKey ) {
    cache_ -> put("key" , "value") ;
    cache_ -> remove("key") ;

    auto result = cache_ -> get("key") ;

    EXPECT_EQ(result.status , cache::CacheStatus::NOT_FOUND ) ; 
}

TEST_F( InMemoryCacheTest , DeleteNonexistentKeyIsIdempotent ) {
    EXPECT_NO_THROW ({
        auto result = cache_ -> remove("does_not_exist") ;
        EXPECT_TRUE(result.isOk()) ; 
    });
}

// ========= Size & Capacity ======
TEST_F( InMemoryCacheTest , SizeTracksInsertionsAndDeletions ) {
    EXPECT_EQ(cache_ -> size() , 0 ) ;

    cache_ -> put("a","1") ;
    EXPECT_EQ( cache_ -> size() , 1 ) ;

    cache_ -> put("b","2") ;
    EXPECT_EQ( cache_ -> size() , 2 ) ;

    cache_ -> remove("a") ; 
    EXPECT_EQ( cache_ -> size() , 1 ) ;
}

TEST_F(InMemoryCacheTest , CapacityLimitRejectsNewKeys  ) {
    auto limitedCache = cache::InMemoryCache(2) ; 

    limitedCache.put("a","1") ;
    limitedCache.put("b","2") ; 

    auto result = limitedCache.put("c" , "3") ;
    EXPECT_EQ(result.status , cache::CacheStatus::CAPACITY_FULL ) ;

    EXPECT_TRUE(limitedCache.get("a").isOk()) ; 
    EXPECT_TRUE(limitedCache.get("b").isOk()) ; 
}

TEST_F( InMemoryCacheTest , CapacityLimitAllowsUpdateOfExistingKey  ) {

    auto limitedCache = cache::InMemoryCache(2) ; 

    limitedCache.put("a","1") ;
    limitedCache.put("b","2") ; 

    auto result = limitedCache.put("a" , "Updated" ) ;
    EXPECT_TRUE(result.isOk()) ;
    EXPECT_EQ( limitedCache.get("a").value.value() , "Updated" ) ; 
}

// ===========Edge Cases =========

TEST_F( InMemoryCacheTest , EmptyStringKeyAndValue ) {
    cache_ -> put( "" , "" ) ;
    auto result = cache_->get("") ;
    EXPECT_TRUE(result.isOk()) ;
    EXPECT_EQ( result.value.value() , "" ) ; 
}

TEST_F(InMemoryCacheTest , LargeValueStored ) {
    std::string largeValue(1024*1024 , 'x' ) ;
    cache_ -> put("large_key" , largeValue ) ;

    auto result = cache_ -> get("large_key") ;
    EXPECT_TRUE(result.isOk()) ;
    EXPECT_EQ( result.value.value().size() , 1024*1024 ) ; 

}





