#pragma once
#include "Bussun.h"

//!NOTE: I had to do this because there are a ton of unresolved symbols 
//! if I include Game/NameObj/NameObjFactory.hpp

class NameObj;

typedef NameObj* (*CreationFuncPtr)(const char *);

class NameObjFactory {
    public:
    struct Name2CreateFunc {
        const char* mName;                          // _0
        NameObj* (*mCreationFunc)(const char *);    // _4
        const char* mArchiveName;                   // _8
    };
    static CreationFuncPtr getCreator(const char *);
};

namespace {
    const NameObjFactory::Name2CreateFunc cNewCreateNameObjTable[] = {"Fake", NULL, NULL};

    const int cNewCreateNameObjTableCount = sizeof(cNewCreateNameObjTable) / 12;
}