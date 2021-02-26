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
        cout << "Printer: " << printer->get_name() << '\n';
        cout << "    Name = " << printer->get_name() << '\n';
        cout << "    Is default: " << (printer->is_default() ? "true" : "false") << '\n';
        if (printer->canPrintMultipleCopies())
        {
            cout << "    Can print multiple copies\n";
        }

        cout << "Supported ";
        const finishings& finishes = printer->get_finishings();
        cout << finishes;

        cout << "Default ";
        finishings defaultFinishings = printer->get_default_finishings();
        cout << defaultFinishings;

        cout << "Supported ";
        auto mediaSources = printer->get_media_sources();
        cout << mediaSources;

        cout << "Default Media Source:\n";
        auto defaultMediaSource = printer->get_default_media_source();
        cout << "    ";
        cout << ((defaultMediaSource) ? defaultMediaSource.value().get_value() : "None") << "\n";

        cout << "Supported ";
        auto mediaTypes = printer->get_media_types();
        cout << mediaTypes;

        cout << "Default Media Type:\n";
        auto defaultMediaType = printer->get_default_media_type();
        cout << "    ";
        cout << ((defaultMediaType) ? defaultMediaType.value().get_value() : "None") << "\n";

        auto orientations = printer->get_orientations();
        cout << orientations;
                 
        cout << "Default Orientation:\n";
        auto defOrientation = printer->get_default_orientation();
        if (defOrientation)
        {
            cout << defOrientation.value();
        }
        else
        {
            cout << "    None\n";
        }

        cout << "Supported ";
        auto colorModes = printer->get_color_modes();
        cout << colorModes;
       
        cout << "Default Color Mode:\n";
        auto defaultColorMode = printer->get_default_color_mode();
        cout << "    ";
        cout << ((defaultColorMode) ? defaultColorMode.value().get_value() : "None") << "\n";

        auto printQualities = printer->get_print_qualities();
        cout << printQualities;

        cout << "Default Print Quality:\n";
        auto printQuality = printer->get_default_print_quality();
        cout << "    ";
        cout << ((printQuality) ? printQuality.value().get_value() : "None") << '\n';

        cout << "Supported ";
        auto sides = printer->get_sides();
        cout << sides;

        cout << "Default Side\n";
        auto side = printer->get_default_side();
        cout << "    ";
        cout << ((side) ? side.value().get_value() : "None") << '\n';

        cout << "    Options: " << '\n';
        for (auto option : printer->getOptions())
        {
            cout << "        " << option.first <<  ":  " << option.second << '\n';
        }

        cout << printer->get_media_sizes();

        cout << "Default Media Size:\n";
        auto defaultSize = printer->get_default_media_size();
        cout << ((defaultSize) ? defaultSize.value().get_translated_name() : "None") << "\n"; 
 
        cout << endl;
    }

    return 0;
}