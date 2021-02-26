/**
 *  \brief A Printers class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printers.cpp
 */

#include "printers.h"
#include <vector>

using namespace nanaprint;

namespace nanaprint
{
    Printers::Printers()
    {
        enumeratePrinters();
    }

    Printers::~Printers() 
    {
        std::vector<cups_dest_t*> dests;
        for (size_t i = 0; i < m_printers.size(); ++i)
        {
            cups_dest_t* dest = m_printers[i]->get_dest();
            dests.push_back(dest);
        }
        cupsFreeDests(dests.size(), *dests.data());
    }

    void Printers::enumeratePrinters()
    {
        cups_dest_t* dests;
        int destinations = cupsGetDests2(CUPS_HTTP_DEFAULT, &dests);
        // return printers array
        m_printers.clear();
        for(int i = 0; i < destinations; ++i)
        {
            auto printer = Printer::create(&dests[i]);
            m_printers.push_back(printer);
        }
    }

    size_t Printers::getDefaultPrinterNumber() const
    {
        size_t printerNum = 0;
        for(size_t i = 0; i < m_printers.size(); ++i)
        {
            if (m_printers[i]->is_default())
            {
                printerNum = i;
                break;
            }
        }
        return printerNum;
    }

    size_t Printers::get_printer_number(const std::string& printerName) const
    {
        size_t printerNum = 0;
        for( size_t i = 0; i < m_printers.size(); ++i)
        {
            if (m_printers[i]->get_name() == printerName)
                printerNum = i;
        }
        return printerNum;
    }

    std::ostream& operator<<(std::ostream& os, const Printers& prtrs)
    {
        auto prntrs = prtrs.getPrinters();
        if (prntrs.size() == 0)
        {
            os << "No printers found.\n";
        }
        else
        {
            for(auto prntr : prntrs)
            {
                os << *prntr;
            }
        }
    }
}
