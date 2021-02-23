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
        string s = printer->get_printer_state();
        cout << "Printer: " << printer->getName() << '\n';
        cout << "    Name = " << printer->getName() << '\n';
        cout << "    Is default: " << (printer->isDefault() ? "true" : "false") << '\n';
        if (printer->canPrintMultipleCopies())
        {
            cout << "    Can print multiple copies\n";
        }

        cout << "Supported ";
        const finishings& finishes = printer->getFinishings();
        cout << finishes;

        cout << "Default ";
        finishings defaultFinishings = printer->getDefaultFinishings();
        cout << defaultFinishings;

        cout << "Supported ";
        auto mediaSources = printer->getMediaSources();
        cout << mediaSources;

        cout << "Default Media Source:\n";
        auto defaultMediaSource = printer->getDefaultMediaSource();
        cout << "    ";
        cout << ((defaultMediaSource) ? defaultMediaSource.value().get_value() : "None") << "\n";

        cout << "Supported ";
        auto mediaTypes = printer->getMediaTypes();
        cout << mediaTypes;

        cout << "Default Media Type:\n";
        auto defaultMediaType = printer->getDefaultMediaType();
        cout << "    ";
        cout << ((defaultMediaType) ? defaultMediaType.value().get_value() : "None") << "\n";

        auto orientations = printer->getOrientations();
        cout << orientations;
                 
        cout << "Default Orientation:\n";
        auto defOrientation = printer->getDefaultOrientation();
        if (defOrientation)
        {
            cout << defOrientation.value();
        }
        else
        {
            cout << "    None\n";
        }

        cout << "Supported ";
        auto colorModes = printer->getColorModes();
        cout << colorModes;
       
        cout << "Default Color Mode:\n";
        auto defaultColorMode = printer->getDefaultColorMode();
        cout << "    ";
        cout << ((defaultColorMode) ? defaultColorMode.value().get_value() : "None") << "\n";

        auto printQualities = printer->getPrintQualities();
        cout << printQualities;

        cout << "Default Print Quality:\n";
        auto printQuality = printer->getDefaultPrintQuality();
        cout << "    ";
        cout << ((printQuality) ? printQuality.value().get_value() : "None") << '\n';

        cout << "Supported ";
        auto sides = printer->getSides();
        cout << sides;

        cout << "Default Side\n";
        auto side = printer->getDefaultSide();
        cout << "    ";
        cout << ((side) ? side.value().getSide() : "None") << '\n';

        cout << "    Options: " << '\n';
        for (auto option : printer->getOptions())
        {
            cout << "        " << option.first <<  ":  " << option.second << '\n';
        }

        cout << printer->getMediaSizes();

        cout << "Default Media Size:\n";
        auto defaultSize = printer->getDefaultMediaSize();
        cout << ((defaultSize) ? defaultSize.value().get_translated_name() : "None") << "\n"; 
 
        cout << endl;
    }

    return 0;
}