# Copyright 2018 Mike Dev
# Distributed under the Boost Software License, Version 1.0.
# See accompanying file LICENSE_1_0.txt or copy at http://www.boost.org/LICENSE_1_0.txt
#
# NOTE: CMake support for Boost.Integer is currently experimental at best
#       and the interface is likely to change in the future

cmake_minimum_required(VERSION 3.5)

project(BoostInteger LANGUAGES CXX)

add_library(boost_integer INTERFACE)
add_library(Boost::integer ALIAS boost_integer)

target_include_directories(boost_integer INTERFACE include)

target_link_libraries(boost_integer
    INTERFACE
        Boost::assert
        Boost::config
        Boost::core
        Boost::static_assert
)

