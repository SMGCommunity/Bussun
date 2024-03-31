#pragma once
#include "Bussun.h"
#include "revolution/types.h"

struct KamekHeader
{
    u32 magic1;
    u16 magic2;
    u16 version;
    u32 bssSize;
    u32 codeSize;

    size_t HeaderSize() const {
        if (version == 2)
            return 32;
        else if (version == 1)
            return 16;
        else
            return (size_t)-1;
    }
};
