/*
  Elgar Game Engine
  Author: Joseph St. Pierre
  Year: 2018
*/

#ifndef _ELGAR_MACROS_HPP_
#define _ELGAR_MACROS_HPP_

// INCLUDES //

#include <cstdio>

// DEFINES //

#ifndef _RELEASE
#define LOG(x, ...) printf(x, ##__VA_ARGS__)
#else
#define LOG(x, ...)
#endif

#endif