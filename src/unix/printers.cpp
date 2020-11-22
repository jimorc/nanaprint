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

using namespace nanaprint;

namespace nanaprint
{

    constexpr int MAX_ENUM_TIME = 5000;     // max allowed time for printer enumeration in ms

    int enumPrintersCallBack(nanaprint::user_data_t* userData, unsigned flags,
            cups_dest_t *dest)
    {
        if(flags & CUPS_DEST_FLAGS_REMOVED)
        {
            // remove destination from array
            userData->num_dests = cupsRemoveDest(dest->name, dest->instance,
            userData->num_dests, &(userData->dests));
        }
        else
        {
            // add destination to array
            userData->num_dests = cupsCopyDest(dest, userData->num_dests,
            &(userData->dests));
        }

        return 1;
    }

    Printers::Printers()
    {
        enumeratePrinters();
    }

    Printers::~Printers() {}

    void Printers::enumeratePrinters()
    {
        cups_dest_t* dests;
        int destinations = cupsGetDests(&dests);
        user_data_t user_data = { 0, NULL };
        if(!cupsEnumDests(CUPS_DEST_FLAGS_NONE, MAX_ENUM_TIME, NULL, 
            0, 0,
            (cups_dest_cb_t)&enumPrintersCallBack, &user_data))
        {
            // an error occurred, so free all destinations and return
            m_printers.clear();
            return;
        }

        // return printers array
        m_printers.clear();
        for(int i = 0; i < user_data.num_dests; ++i)
        {
            auto printer = Printer::create(&user_data.dests[i]);
            m_printers.push_back(printer);
        }

    }

    size_t Printers::getDefaultPrinterNumber() const
    {
        size_t printerNum = 0;
        for(size_t i = 0; i < m_printers.size(); ++i)
        {
            if (m_printers[i]->isDefault())
            {
                printerNum = i;
                break;
            }
        }
        return printerNum;
    }
}
