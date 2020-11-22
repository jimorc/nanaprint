#ifndef PRINTERS_H
#define PRINTERS_H

/**
 *  \brief A Printers class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printers/
 */

#include <vector>
#include <memory>
#include <cups/cups.h>
#include "printer.h"


namespace nanaprint
{
    typedef struct
    {
        int num_dests;
        cups_dest_t *dests;
    } user_data_t;

   class Printers
    {
        public:
            Printers();
            virtual ~Printers();
            std::vector<std::shared_ptr<Printer>> getPrinters() const { return m_printers; }
            size_t getDefaultPrinterNumber() const;
            size_t get_printer_number(const std::string& printerName) const;

        private:
            void enumeratePrinters();

            std::vector<std::shared_ptr<Printer>> m_printers;
    };
}

extern "C" int enumPrintersCallBack(nanaprint::user_data_t* userData, unsigned flags,
    cups_dest_t *dest);

#endif      // PRINTERS_H