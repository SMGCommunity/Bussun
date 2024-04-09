#pragma once
#include "hooks.h"
#include "revolution/types.h"
template<bool> struct StaticAssert;
template<> struct StaticAssert<true> {static const bool result = true;};
#ifdef __COUNTER__
#define CONCAT_IMPL( x, y ) x##y
#define MACRO_CONCAT( x, y ) CONCAT_IMPL( x, y )
#define STATIC_ASSERT(expr, msg) \
typedef StaticAssert<expr> msg; \
const bool MACRO_CONCAT(Assert, __COUNTER__) = msg::result
#endif
STATIC_ASSERT(sizeof(void*) == 4, size_of_pointer_must_be_4);
STATIC_ASSERT(sizeof(long) == 4, size_of_long_must_be_4);
typedef unsigned long size_t;