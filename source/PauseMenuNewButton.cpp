#ifdef PMNB
#include "Bussun.h"
#include "Game/Screen/PauseMenu.h"

#if defined USA || defined JPN
#define REGION_MODIFIER 0
#elif PAL
#define REGION_MODIFIER 0x1C
#elif KOR
#define REGION_MODIFIER 0x154C
#endif

#ifdef KOR
kmWrite32(0x80361C28, 0x38600060);
#else
kmWrite32(0x80360f68 + REGION_MODIFIER, 0x38600060); // li r3, 0x60
#endif

const char* animNames[6] = {
    "ButtonAppear_restartbutton",
    "ButtonDecide_restartbutton",
    "ButtonEnd_restartbutton",
    "ButtonSelectIn_restartbutton",
    "ButtonSelectOut_restartbutton",
    "ButtonWait_restartbutton"
};

void setButtonAnimNames(ButtonPaneController* pButton) {
    pButton->mAnimNameAppear = animNames[0];
    pButton->mAnimNameDecide = animNames[1];
    pButton->mAnimNameEnd = animNames[2];
    pButton->mAnimNameSelectIn = animNames[3];
    pButton->mAnimNameSelectOut = animNames[4];
    pButton->mAnimNameWait = animNames[5];
}

void PauseMenuInitNewButton(PauseMenu* pPauseMenu, const Nerve* pNerve) {
    pPauseMenu->mIsNewButtonUsed = false;
    pPauseMenu->mButtonNew = 0;

    MR::createAndAddPaneCtrl(pPauseMenu, "NewButton", 1);

    if (!MR::isStageBeginPrologueEvent() && !MR::isStageAstroLocation()) {
        pPauseMenu->mButtonNew = new ButtonPaneController(pPauseMenu, "NBackNew", "BoxButton4", 0, 1);
        pPauseMenu->mButtonNew->_22 = false;
        
        MR::setTextBoxFormatRecursive(pPauseMenu, "Text4", L"Restart Stage");

        setButtonAnimNames(pPauseMenu->mButtonTop);
        setButtonAnimNames(pPauseMenu->mButtonMiddle);
        setButtonAnimNames(pPauseMenu->mButtonNew);
    }

    pPauseMenu->initNerve(pNerve);
}

kmCall(0x80374368 + REGION_MODIFIER, PauseMenuInitNewButton);

void PauseMenuAppearNewButton(PauseMenu* pPauseMenu) {
    pPauseMenu->mButtonTop->appear();

    if (pPauseMenu->mButtonNew)
        pPauseMenu->mButtonNew->appear();
}

kmWrite32(0x80374464 + REGION_MODIFIER, 0x7F63DB78); // mr r3, r27
kmCall(0x80374468 + REGION_MODIFIER, PauseMenuAppearNewButton);


void PauseMenuUpdateNewButton(PauseMenu* pPauseMenu) {
    pPauseMenu->mButtonTop->update();

    if (pPauseMenu->mButtonNew)
        pPauseMenu->mButtonNew->update();
}

kmWrite32(0x803745c0 + REGION_MODIFIER, 0x7FE3FB78); // mr r3, r31
kmCall(0x803745c4 + REGION_MODIFIER, PauseMenuUpdateNewButton);


void PauseMenuForceToWaitNewButton(PauseMenu* pPauseMenu) {
    pPauseMenu->mButtonTop->forceToWait();

    if (pPauseMenu->mButtonNew)
        pPauseMenu->mButtonNew->forceToWait();
}

kmWrite32(0x803749a8 + REGION_MODIFIER, 0x7FC3F378); // mr r3, r30
kmCall(0x803749ac + REGION_MODIFIER, PauseMenuForceToWaitNewButton);


bool PauseMenuIsNewButtonPointingTrigger(PauseMenu* pPauseMenu) {
    return (pPauseMenu->mButtonMiddle && pPauseMenu->mButtonMiddle->isPointingTrigger()) || (pPauseMenu->mButtonNew && pPauseMenu->mButtonNew->isPointingTrigger());
}

kmWrite32(0x80374a40 + REGION_MODIFIER, 0x7F63DB78); // mr r3, r27
kmCall(0x80374a50 + REGION_MODIFIER, PauseMenuIsNewButtonPointingTrigger);


bool PauseMenuNewButtonTrySelect(PauseMenu* pPauseMenu) {
    bool isPressed = false;

    if (pPauseMenu->mButtonMiddle && pPauseMenu->mButtonMiddle->trySelect()) {
        pPauseMenu->mIsNewButtonUsed = false;
        isPressed = true;
    }

    if (pPauseMenu->mButtonNew && pPauseMenu->mButtonNew->trySelect()) {
        pPauseMenu->mIsNewButtonUsed = true;
        isPressed = true;
    }

    return isPressed;
}

kmWrite32(0x80374ae8 + REGION_MODIFIER, 0x48000008); // b 0x8
kmWrite32(0x80374af0 + REGION_MODIFIER, 0x7F63DB78); // mr r3, r27
kmCall(0x80374af4 + REGION_MODIFIER, PauseMenuNewButtonTrySelect);


bool PauseMenuIsButtonTimingForSelectedSe(PauseMenu* pPauseMenu) {
    return (pPauseMenu->mButtonMiddle && pPauseMenu->mButtonMiddle->isTimingForSelectedSe()) || (pPauseMenu->mButtonNew && (pPauseMenu->mButtonNew->isTimingForSelectedSe()));
}

kmWrite32(0x80374d04 + REGION_MODIFIER, 0x7FA3EB78); // mr r3, r29
kmCall(0x80374d08 + REGION_MODIFIER, PauseMenuIsButtonTimingForSelectedSe);


bool PauseMenuValidateButton(PauseMenu* pPauseMenu) {
    return (pPauseMenu->mButtonMiddle && pPauseMenu->mButtonMiddle->_20) || (pPauseMenu->mButtonNew && pPauseMenu->mButtonNew->_20);
}

kmWrite32(0x80374cec + REGION_MODIFIER, 0x7FA3EB78); // mr r3, r29
kmCall(0x80374cf0 + REGION_MODIFIER, PauseMenuValidateButton);
kmWrite32(0x80374cf4 + REGION_MODIFIER, 0x2C030000); // cmpwi r3, 0
kmWrite32(0x80374cf8 + REGION_MODIFIER, 0x41820078); // beq 0x78
kmWrite32(0x80374cfc + REGION_MODIFIER, 0x48000008); // b 0x8

kmWrite32(0x80374d70 + REGION_MODIFIER, 0x807D0038); // lwz r3, 0x38(r29)


bool PauseMenuIsNewButtonDecidedWait(PauseMenu* pPauseMenu) {
    return (pPauseMenu->mButtonMiddle && pPauseMenu->mButtonMiddle->isDecidedWait()) || (pPauseMenu->mButtonNew && pPauseMenu->mButtonNew->isDecidedWait());
}

kmWrite32(0x80374d34 + REGION_MODIFIER, 0x7FA3EB78); // mr r3, r29
kmCall(0x80374d38 + REGION_MODIFIER, PauseMenuIsNewButtonDecidedWait);


void PauseMenuDisappearNewButton(PauseMenu* pPauseMenu) {

    pPauseMenu->mButtonTop->disappear();

    if (pPauseMenu->mButtonNew)
        pPauseMenu->mButtonNew->disappear();
}

kmWrite32(0x80374e38 + REGION_MODIFIER, 0x7FC3F378); // mr r3, r30
kmCall(0x80374e3c + REGION_MODIFIER, PauseMenuDisappearNewButton);


void PauseMenuSetInfoWindowStr(PauseMenu* pPauseMenu, const char* pStr) {
    pPauseMenu->mSysInfoWindow->appear(pStr, SysInfoWindow::SysInfoType_2, SysInfoWindow::SysInfoTextPos_0, SysInfoWindow::SysInfoMessageType_1);

    if (pPauseMenu->mIsNewButtonUsed)
        #if defined JPN || defined KOR
            MR::setTextBoxFormatRecursive(pPauseMenu->mSysInfoWindow, "TxtConfirm", L"Restart current stage?");
        #else
            MR::setTextBoxFormatRecursive(pPauseMenu->mSysInfoWindow, "TxtConfirm", L"             Restart current stage?");
        #endif
}

kmWrite32(0x80374f48 + REGION_MODIFIER, 0x7FE3FB78); // mr r3, r31
kmCall(0x80374f58 + REGION_MODIFIER, PauseMenuSetInfoWindowStr);


void PauseMenuDoNewButtonAction(bool isInvalidBackAstroDome, PauseMenu* pPauseMenu) {
    if (!pPauseMenu->mIsNewButtonUsed)
        isInvalidBackAstroDome ? MR::requestChangeSceneTitle() : MR::requestChangeStageGoBackAstroDome();
    else {
        MR::requestStartScenarioSelect(MR::getCurrentStageName());
        MR::requestChangeStageInGameMoving(MR::getCurrentStageName(), MR::getCurrentScenarioNo());
    }
}

kmWrite32(0x80374f88 + REGION_MODIFIER, 0x7FE4FB78); // mr r4, r31
kmCall(0x80374f8c + REGION_MODIFIER, PauseMenuDoNewButtonAction); // call
kmWrite32(0x80374f90 + REGION_MODIFIER, 0x60000000); // nop

#endif