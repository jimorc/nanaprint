/*
 *	A program for using and testing 
 *  the nanaprint C++ library. The libraries that are tested are OS 
 *  or print system specific (e.g. Win32 or CUPS).  
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *	@file: apps/printmain/printmain.cpp
 */

#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/menu.hpp>
#include "printers.h"
#include "pagesetup.h"

using namespace nana;
using namespace nanaprint;
using namespace std;

Printers printers;

int main()
{
    form mainForm;
    mainForm.caption(u8"Print Test Program");
    menubar mainMenu(mainForm);

    mainMenu.events().mouse_up([](const arg_mouse& arg) {
        if(mouse::left_button != arg.button)
        return;
    });

    mainMenu.push_back("&File");
    auto& fileMenu = mainMenu.at(0);
    fileMenu.append("Page Setup...", [&](menu::item_proxy& ip) {
        PageSetup setup(mainForm, printers);
    });

    fileMenu.append("Print...", [](menu::item_proxy& ip) {
        msgbox msg("Print clicked");
        msg << ip.text();
        msg.show();
    });

    mainForm.show();
    exec();
    return 0;
}
