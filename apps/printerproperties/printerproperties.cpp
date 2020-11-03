/*
 *	A program for using and testing printer related librarites in
 *  the nanaprint C++ library. The libraries that are tested are OS 
 *  or print system specific (e.g. Win32 or CUPS).  
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *	@file: apps/printerproperties/printerproperties.cpp
 */

#include <iostream>
#include "printers.h"

using namespace std;
using namespace nanaprint;

int main()
{
    Printers printers;

    std::vector<std::shared_ptr<Printer>> pPrinters = printers.getPrinters();
    for(auto printer : pPrinters)
    {
        cout << "Printer: " << printer->getName() << '\n';
        cout << "    Name = " << printer->getName() << '\n';
        cout << "    Is default: " << (printer->isDefault() ? "true" : "false") << '\n';
        if (printer->canPrintMultipleCopies())
        {
            cout << "    Can print multiple copies\n";
        }

        cout << "    Supported finishings:\n";
        if (printer->noFinishings())
        {
            cout << "        None\n";
        }
        else
        {
            if (printer->canBind())
            {
                cout << "    Bind copies\n";
            }
            if (printer->canCoverOutput())
            {
                cout << "    Can cover output\n";
            }
            if (printer->canFold())
            {
                cout << "    Can fold output\n";
            }
            if (printer->canPunch())
            {
                cout << "    Can punch output\n";
            }
            if (printer->canStaple())
            {
                cout << "    Can staple copies\n";
            }
            if (printer->canTrim())
            {
                cout << "    Can trim output\n";
            }
        }

        cout << "    Default finishings:\n";
        if (printer->noDefaultFinishings())
        {
            cout << "        None\n";
        }
        else
        {
            if (printer->defaultBind())
            {
                cout << "        Bind copies\n";
            }
            if (printer->defaultCoverOutput())
            {
                cout << "        Cover output\n";
            }
            if (printer->defaultFold())
            {
                cout << "        Fold output\n";
            }
            if (printer->defaultPunch())
            {
                cout << "        Punch output\n";
            }
            if (printer->defaultStaple())
            {
                cout << "        Staple output\n";
            }
            if (printer->defaultTrim())
            {
                cout << "        Trim output\n";
            }
        }
        

        cout << "    Options: " << '\n';
        for (auto option : printer->getOptions())
        {
            cout << "        " << option.first <<  ":  " << option.second << '\n';
        }
        cout << "    Media Sizes:\n";
        for (auto size : printer->getMediaSizes())
        {
            cout << "        " << size->getTranslatedName();
            cout << "    " << (size->isBorderless() ? "Borderless" : "") << '\n';
            cout << "            width = " << size->getWidth() << ", height = " << size->getHeight();
            cout << "\n            top = " << size->getTop() << ", bottom = " << size->getBottom();
            cout << "\n            left = " << size->getLeft() << ", right = " << size->getRight() << '\n';
        }

        cout << endl;
    }

    return 0;
}