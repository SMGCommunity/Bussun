#pragma once
#include "hooks.h"
#include "revolution/types.h"
template<bool> struct StaticAssert;
template<> struct StaticAssert<true> {static const bool result = true;};
const bool size_of_pointer_must_be_4 = StaticAssert<sizeof(void*) == 4>::result;
const bool size_of_long_must_be_4 = StaticAssert<sizeof(long) == 4>::result;
#ifndef __COUNTER__
#error __COUNTER__ is NOT defined! This will cause issues!
#endif
typedef unsigned long size_t;