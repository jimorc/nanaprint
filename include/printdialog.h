#pragma(once)
/**
 *  \file printdialog.h
 *  \brief This file provides PrintDialog class required by nanaprint
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
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include "nanaprint.h"
#include "printsettings.h"
#include "printdialogsettings.h"
#include "printers.h"

namespace nanaprint
{
    class PrintDialog : nana::form
    {
        public:
            PrintDialog(nana::form& parent, PrintSettings& settings);
            virtual ~PrintDialog() {}
            void run();
        private:
            void buildGeneralTab();
            void buildPrinterGroup();
            void buildPrinterLabel();
            void buildPrinterCombox();
            void buildStatusLabel();
            void buildPrinterStatus();
            void buildPrinterTypeLabel();
            void buildPrinterType();
            void buildLocationLabel();
            void buildPrinterLocation();
            void buildRangeGroup();
            void select_printer();
            void printer_selected(size_t pos);
            void updatePrinterGroup();
            void buildAllPagesCheckbox();
            void buildCurrentPageCheckbox();
            void buildSelectionCheckbox();
            void buildPagesCheckbox();
            void buildPagesBox();

            PrintSettings m_settings;
            PrintDialogSettings m_dialogSettings;

            nana::place m_layout;
            nana::panel<false> m_basic;
            nana::place m_basicLayout;
            nana::group m_printerGroup;
            nana::label m_printerLabel;
            nana::combox m_printerCombox;
            nana::label m_statusLabel;
            nana::label m_printerStatus;
            nana::label m_typeLabel;
            nana::label m_printerType;
            nana::label m_locationLabel;
            nana::label m_printerLocation;
            nana::group m_rangeGroup;
            nana::place m_rangeLayout;
            nana::radio_group m_rangeRadioGroup;
            nana::checkbox m_allPages;
            nana::checkbox m_currentPage;
            nana::checkbox m_selection;
            nana::checkbox m_pages;
            nana::textbox m_pagesBox;
            nana::tabbar<std::string> m_tabbar;
    };
}
