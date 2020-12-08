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
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/place.hpp>
#include <nanaprint.h>
#include "printsettings.h"
#include "printers.h"


namespace nanaprint
{
    class PageSetup : public nana::form
    {
        public:
            PageSetup(nana::form& parent, PrintSettings& settings);
            virtual ~PageSetup() {}
            nanaprint::DialogStatus run();
        private:
            void buildPrinterGroup();
            void buildPrinterNameLabel();
            void buildPrinterCombox();
            void buildPrinterStatusLabel();
            void buildPrinterStatus(size_t printer);
            void buildPrinterTypeLabel();
            void buildPrinterType(size_t printer);
            void buildPrinterWhereLabel();
            void buildPrinterWhere(size_t printer);
            void buildPrinterCommentLabel();
            void buildPrinterComment(size_t printer);

            void buildPaperGroup();
            void buildBorderlessCheckbox();
            void buildPaperSizeLabel();
            void buildPaperSizeCombox();
            void populatePaperSizeCombox(size_t printer);
            void printer_selected(const nana::arg_combox &ar_cbx);
            void updatePaperGroup(size_t printer);

            void on_borderlessChecked(const nana::arg_checkbox& arg);
            void paper_size_selected(const nana::arg_combox &ar_cbx);

            Printers m_printers;
            PrintSettings& m_settings;
            nana::place m_layout;
            nana::group m_printerGroup;
            nana::label m_printerNameLabel;
            nana::combox m_printerCombox;
            nana::label m_printerStatusLabel;
            nana::label m_printerStatus;
            nana::label m_printerTypeLabel;
            nana::label m_printerType;
            nana::label m_printerWhereLabel;
            nana::label m_printerWhere;
            nana::label m_printerCommentLabel;
            nana::label m_printerComment;

            nana::group m_paperGroup;
            nana::checkbox m_borderlessCheckbox;
            nana::label m_paperSizeLabel;
            nana::combox m_paperSizeCombox;
            nana::label m_paperSize;
            nana::label m_paperSourceLabel;
            nana::label m_paperSourceCombox;
    };
}

