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
        std::vector<handle> handles;
        for (size_t i = 0; i < m_printers.size(); ++i)
        {
            handle handle = m_printers[i]->get_handle();
            handles.push_back(handle);
        }
        cupsFreeDests(handles.size(), *handles.data());
    }

    void Printers::enumeratePrinters()
    {
        handle handles;
        int destinations = cupsGetDests2(CUPS_HTTP_DEFAULT, &handles);
        // return printers array
        m_printers.clear();
        for(int i = 0; i < destinations; ++i)
        {
            auto prtr = printer::create(&handles[i]);
            m_printers.push_back(prtr);
        }
    }

    size_t Printers::get_default_printer_number() const
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
        auto prntrs = prtrs.get_printers();
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
        return os;
    }
}
