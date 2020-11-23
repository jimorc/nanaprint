#pragma(once)
/**
 *  \file pagesetup.h
 *  \brief This file provides a page setup dialog required by nanaprint
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

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nanaprint.h>
#include "printsettings.h"
#include "printers.h"


namespace nanaprint
{
    class PageSetup : public nana::form
    {
        public:
            PageSetup(nana::form& parent, PrintSettings settings);
            virtual ~PageSetup() {}
            nanaprint::DialogStatus run();
        private:
            void setupFormatForLabel();
            void setupPrinterComBox();
            void setupPaperSizeLabel();
            void setupPaperSizeComBox();
            void printer_selected(const nana::arg_combox &ar_cbx);

            Printers m_printers;
            PrintSettings& m_settings;
            std::string m_layoutString;
            nana::place m_layout;
            nana::label m_formatForLabel;
            nana::combox m_printerCombox;
            nana::label m_paperSizeLabel;
            nana::combox m_paperSizeCombox;
    };
}

