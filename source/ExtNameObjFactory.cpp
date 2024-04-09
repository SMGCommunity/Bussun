#include "ExtNameObjFactory.h"
#include "Game/Util/StringUtil.hpp"

namespace {
    void* getNameObjCreator(const char* pName) {
        void* creator = NameObjFactory::getCreator(pName);
        if (!creator) {
            for (int i = 0; i < cNewCreateNameObjTableCount; i++) {
                const NameObjFactory::Name2CreateFunc entry = cNewCreateNameObjTable[i];
                if (MR::isEqualString(entry.mName, pName)) {
                    creator = entry.mCreationFunc;
                    break;
                }
            }
        }
        return creator;
    }
    /// Redirection hooks
    #if defined USA || defined JPN // JPN and USA have the same spots, somehow.
    kmBranch(0x80341D5C, getNameObjCreator);
    kmCall(0x80347338, getNameObjCreator);
    #endif
    #ifdef KOR
    kmBranch(0x80342690, getNameObjCreator);
    kmCall(0x80347C6C, getNameObjCreator);
    #endif
    #ifdef PAL
    kmBranch(0x80341D78, getNameObjCreator);
    kmCall(0x80347354, getNameObjCreator);
    #endif
    /// Redirection hooks
}