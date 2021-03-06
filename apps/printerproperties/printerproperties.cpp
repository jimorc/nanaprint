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

#ifdef WIN32
    #define WIN32_LEAN_AND_MEAN
    #include <windows.h>
#endif
#include <iostream>
#include "printers.h"

using namespace std;
using namespace nanaprint;

int main()
{
    printers printers;
    cout << printers;

    return 0;
}