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

        cout << "Supported ";
        const Finishings& finishings = printer->getFinishings();
        cout << finishings;

        cout << "Default ";
        Finishings defaultFinishings = printer->getDefaultFinishings();
        cout << defaultFinishings;

        cout << "Supported ";
        auto mediaSources = printer->getMediaSources();
        cout << mediaSources;

        cout << "Default Media Source:\n";
        auto defaultMediaSource = printer->getDefaultMediaSource();
        cout << defaultMediaSource;

        cout << "Supported ";
        auto mediaTypes = printer->getMediaTypes();
        cout << mediaTypes;

        cout << "Default Media Type:\n";
        auto defaultMediaType = printer->getDefaultMediaType();
        cout << defaultMediaType;

        auto orientations = printer->getOrientations();
        cout << orientations;
                 
        cout << "Default Orientation:\n";
        cout << printer->getDefaultOrientation();
        
        cout << "Supported ";
        auto colorModes = printer->getColorModes();
        cout << colorModes;
       
        cout << "Default Color Mode:\n";
        auto defaultColorMode = printer->getDefaultColorMode();
        cout << defaultColorMode;

        auto printQualities = printer->getPrintQualities();
        cout << printQualities;

        cout << "Default Print Quality:\n";
        auto printQuality = printer->getDefaultPrintQuality();
        cout << "    " << printQuality << '\n';

        cout << "    Sides:\n";
        auto sides = printer->getSides();
        if(sides.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            for (auto side: sides)
            {
                cout << "        " << side << '\n';
            }
        }

        cout << "    Default Side\n";
        auto side = printer->getDefaultSide();
        if(side.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            cout << "        " << side << '\n';
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