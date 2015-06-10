// Eggs.Variant
//
// Copyright Agustin K-ballo Berge, Fusion Fenix 2014-2015
//
// Distributed under the Boost Software License, Version 1.0. (See accompanying
// file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt)

#ifndef EGGS_VARIANT_TEST_EXPLICIT_HPP
#define EGGS_VARIANT_TEST_EXPLICIT_HPP

struct Explicit
{
    std::string x;

    explicit Explicit(char const* str) : x(str) {}
};

#endif /*EGGS_VARIANT_TEST_EXPLICIT_HPP*/
