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

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif
#include <nana/gui.hpp>
#include <nana/gui/widgets/menubar.hpp>
#include <nana/gui/widgets/menu.hpp>
#include "printoperation.h"

using namespace nana;
using namespace nanaprint;
using namespace std;

int main()
{
    form mainForm;
    print_settings settings;
    PrintOperation printOper(mainForm, settings);
    mainForm.caption(u8"Print Test Program");
    menubar mainMenu(mainForm);

    mainMenu.push_back("&File");
    auto& fileMenu = mainMenu.at(0);
    fileMenu.append("Page Setup...", [&](menu::item_proxy&) {
        printOper.run_page_setup();
    });

    fileMenu.append("Print...", [&](menu::item_proxy&) {
        printOper.run_print();
    });

    mainForm.show();
    exec();
    return 0;
}
