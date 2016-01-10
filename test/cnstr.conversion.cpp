// Eggs.Variant
//
// Copyright Agustin K-ballo Berge, Fusion Fenix 2014-2015
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#include <eggs/variant.hpp>
#include <string>
#include <typeinfo>

#include <eggs/variant/detail/config/prefix.hpp>

#define CATCH_CONFIG_MAIN
#include "catch.hpp"
#include "constexpr.hpp"
#include "explicit.hpp"

EGGS_CXX11_STATIC_CONSTEXPR std::size_t npos = eggs::variant<>::npos;

TEST_CASE("variant<Ts...>::variant(T&&)", "[variant.cnstr]")
{
    eggs::variant<int, std::string> v(42);

    CHECK(bool(v) == true);
    CHECK(v.which() == 0u);
    REQUIRE(v.target<int>() != nullptr);
    CHECK(*v.target<int>() == 42);

#if EGGS_CXX98_HAS_RTTI
    CHECK(v.target_type() == typeid(int));
#endif

#if EGGS_CXX11_HAS_CONSTEXPR
    // constexpr
    {
        constexpr eggs::variant<int, Constexpr> v(Constexpr(42));
        constexpr bool vb = bool(v);
        constexpr std::size_t vw = v.which();
        constexpr bool vttb = v.target<Constexpr>()->x == 42;

#  if EGGS_CXX98_HAS_RTTI
        constexpr std::type_info const& vtt = v.target_type();
#  endif

#  if EGGS_CXX14_HAS_CONSTEXPR
        struct test { static constexpr int call()
        {
            eggs::variant<int, Constexpr> v(Constexpr(42));
            v.target<Constexpr>()->x = 43;
            return 0;
        }};
        constexpr int c = test::call();
#  endif
    }
#endif

    // conversion
    {
        eggs::variant<int, std::string> v("42");

        CHECK(bool(v) == true);
        CHECK(v.which() == 1u);
        REQUIRE(v.target<std::string>() != nullptr);
        CHECK(*v.target<std::string>() == "42");

#if EGGS_CXX98_HAS_RTTI
        CHECK(v.target_type() == typeid(std::string));
#endif

        // implicit conversion
        {
            eggs::variant<int, std::string> v = "42";

            CHECK(bool(v) == true);
            CHECK(v.which() == 1u);
            REQUIRE(v.target<std::string>() != nullptr);
            CHECK(*v.target<std::string>() == "42");

#if EGGS_CXX98_HAS_RTTI
            CHECK(v.target_type() == typeid(std::string));
#endif
        }

        // explicit conversion
        {
            eggs::variant<int, Explicit<std::string>> v("42");

            CHECK(bool(v) == true);
            CHECK(v.which() == 1u);
            REQUIRE(v.target<Explicit<std::string>>() != nullptr);
            CHECK(v.target<Explicit<std::string>>()->x == "42");

#if EGGS_CXX98_HAS_RTTI
            CHECK(v.target_type() == typeid(Explicit<std::string>));
#endif
        }
    }
}
