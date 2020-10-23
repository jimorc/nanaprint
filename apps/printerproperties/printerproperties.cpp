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
        cout << "    Options: " << '\n';
        for (auto option : printer->getOptions())
        {
            if(option.first == string("printer-state"))
            {
                int state = atoi(option.second.c_str());
                cout << "        " << "printer-state: ";
                switch(state)
                {
                    case 3:
                        cout << "Idle\n";
                        break;
                    case 4:
                        cout << "Printing\n";
                        break;
                    case 5:
                        cout << "Stopped\n";
                        break;
                    default:
                        cout << "Unknown state: " << option.second << '\n';
                }
            }
            else
            {
                cout << "        " << option.first <<  ":  " << option.second << '\n';
            }
        }

        cout << endl;
    }

    return 0;
}