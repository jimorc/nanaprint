/**
 *  \brief A PrintSettings class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printsettings.cpp
 */

#include "printsettings.h"

namespace nanaprint
{
    PrintSettings::PrintSettings(const Printers& printers)
        : m_printers(printers.getPrinters())
    {
        int printerNum = get_default_printer_number();
        set_printer(printerNum);
    }

    void PrintSettings::set_printer(int printer)
    {
        if(printer == m_printer)
            return;
        m_printer = printer;
        // set settings to the defaults for the printer
    }

    // get the index of the default printer, or return 0 if there is no default
    int PrintSettings::get_default_printer_number() const
    {
        int printerNum = 0;
        for (printerNum = 0; printerNum < m_printers.size(); ++printerNum)
        {
            if (m_printers[printerNum]->isDefault())
            {
                return printerNum;
            }
        }
        return printerNum;
    }
}
