/**
 * @file main.cpp
 * @author Captain Kitty Cat (youtube.com/@captainkittyca2)
 * @brief
 * @version 1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#include <display/console.h>     // Contains a very neat helper class to print to the console
#include <main.h>
#include <patch.h>     // Contains code for hooking into a function
#include <cstdio>
#include <tp/d_meter2.h>
#include <tp/d_meter2_info.h>
#include <Z2AudioLib/Z2SeMgr.h>

namespace mod
{
    Mod* gMod = nullptr;

    void main()
    {
        Mod* mod = new Mod();
        mod->init();
    }

    void exit() {}

    Mod::Mod(): c( 0 )
    {
    }

    void BeSilent(void* aa) {
        (void)aa;
    }

    void Mod::init()
    {
        libtp::display::setConsole(true, 25);
        libtp::display::setConsoleColor(0, 0, 0, 0);

        *reinterpret_cast<uint32_t*>(0x800c32f0) = 0x38800019;
        *reinterpret_cast<uint32_t*>(0x800c330c) = 0x38800019;
        *reinterpret_cast<uint32_t*>(0x800c3378) = 0x38800019;

        onUI =
            libtp::patch::hookFunction(libtp::tp::d_meter2_draw::setAlphaLifeAnimeMax, [](libtp::tp::d_meter2_draw::dMeter2Draw_c* dMeterDrawPtr) { return gMod->UICheck(dMeterDrawPtr);});
        libtp::patch::hookFunction(libtp::z2audiolib::z2semgr::heartGaugeOn, BeSilent);
        gMod = this;
    }

    void Mod::UICheck(libtp::tp::d_meter2_draw::dMeter2Draw_c* dMeterDraw_c) {
        if (libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentHealth > 1)
            libtp::tp::d_com_inf_game::dComIfG_gameInfo.save.save_file.player.player_status_a.currentHealth = 1;
        return onUI(dMeterDraw_c);
    }
}     // namespace mod