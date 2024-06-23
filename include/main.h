/**
 * @file main.h
 * @author Captain Kitty Cat (youtube.com/@captainkittyca2)
 * @brief
 * @version 1
 * @date 2024-06-23
 *
 * @copyright Copyright (c) 2024
 *
 */
#pragma once
#include <display/console.h>
#include <tp/d_meter2.h>

#include <cinttypes>

namespace mod
{
    void main();
    class Mod
    {
       public:
        Mod();
        void init();

       private:
        // Console
        libtp::display::Console c;
        void ( *onUI)(libtp::tp::d_meter2_draw::dMeter2Draw_c* dMeterDrawPtr) = nullptr;

        void UICheck(libtp::tp::d_meter2_draw::dMeter2Draw_c* dMeterDrawPtr);
    };
}     // namespace mod