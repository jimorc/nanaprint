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

        cout << "    Media Sources: \n";
        auto mediaSources = printer->getMediaSources();
        if(mediaSources.size() == 0)
        {
            cout << "        None\n";
        }
        else
        {
            for (auto source: mediaSources)
            {
                cout << "        " << source << '\n';
            }
        }
        cout << "    Default Media Source:\n";
        auto defaultMediaSource = printer->getDefaultMediaSource();
        if (defaultMediaSource.size() == 0)
        {
            cout << "        None\n";
        }
        else
        {
            cout << "        " << defaultMediaSource << '\n';
        }   

        cout << "    Supported Media Types:\n";
        auto mediaTypes = printer->getMediaTypes();
        if(mediaTypes.size() == 0)
        {
            cout << "        None specified\n";
        }     
        else
        {
            for (auto type: mediaTypes)
            {
                cout << "        " << type << '\n';
            }
        }
        cout << "    Default Media Type:\n";
        auto defaultMediaType = printer->getDefaultMediaType();
        if (defaultMediaType.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            cout << "        " << defaultMediaType << '\n';
        }

        cout << "    Orientations:\n";
        auto orientations = printer->getOrientations();
        if(orientations.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            for (auto orientation: orientations)
            {
                cout << "        " << orientation << '\n';
            }
        }
        
        cout << "    Default Orientation:\n";
        auto orientation = printer->getDefaultOrientation();
        if(orientation.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            cout << "        " << orientation << '\n';
        }

        cout << "    Color Modes:\n";
        auto colorModes = printer->getColorModes();
        if (colorModes.size() == 0)
        {
            cout << "        None specified\n";
        }
        else
        {
            for (auto colorMode: colorModes)
            {
                cout << "        " << colorMode << '\n';
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