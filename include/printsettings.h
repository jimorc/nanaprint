#pragma(once)
/**
 *  \file printsettings.h
 *  \brief This file provides a PrintSettings class required by nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <vector>
#include <memory>
#include "printers.h"
#include "mediasize.h"

namespace nanaprint
{
    class PrintSettings
    {
        public:
            // PrintSettings set up for default printer (or first printer if no default)
            PrintSettings(const Printers& printers);
            virtual ~PrintSettings();
            const std::vector<std::shared_ptr<Printer>>& getPrinters() const
                { return m_printers; }
            void set_printer(int printer);
            int get_printer() const { return m_printer; }
            void set_media_size(const MediaSize& mediaSize);
            MediaSize get_media_size() const { return m_mediaSize; }
        protected:
            int get_default_printer_number() const;
            void set_default_settings(int printerNum);
            std::vector<std::shared_ptr<Printer>> m_printers;
            int m_printer;
            MediaSize m_mediaSize;
    };
}
