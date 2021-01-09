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
            void buildBasicTab();

            void buildPrinterGroup();
            void buildPrinterLabel();
            void buildPrinterCombox();
            void buildStatusLabel();
            void buildPrinterStatus();
            void buildPrinterTypeLabel();
            void buildPrinterType();
            void buildLocationLabel();
            void buildPrinterLocation();
            void buildCommentLabel();
            void buildPrinterComment();

            void buildPaperGroup();
            void buildBorderlessCheckbox();
            void buildMediaTypeLabel();
            void buildMediaTypeCombox();
            void buildPrintQualityLabel();
            void buildPrintQualityCombox();
            void buildPaperSizeLabel();
            void buildPaperSizeCombox();

            void buildRangeGroup();
            void select_printer();
            void printer_selected(size_t pos);
            void updatePrinterGroup(Printer& printer);
            void updatePaperGroup(Printer& printer);
            void updateMediaTypeCombox(Printer& printer);
            void updatePrintQualityCombox(Printer& printer);
            void updatePaperSizeCombox(Printer& printer);
            void buildAllPagesCheckbox();
            void buildCurrentPageCheckbox();
            void buildSelectionCheckbox();
            void buildPagesCheckbox();
            void buildPagesBox();

            void buildMiscGroup();
            void buildOrientationGroup();
            void buildPortraitCheckbox();
            void buildLandscapeCheckbox();

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
            nana::label m_commentLabel;
            nana::label m_printerComment;

            nana::group m_paperGroup;
            nana::checkbox m_borderlessCheckbox;
            nana::label m_mediaTypeLabel;
            nana::combox m_mediaTypeCombox;
            nana::label m_printQualityLabel;
            nana::combox m_printQualityCombox;
            nana::label m_paperSizeLabel;
            nana::combox m_paperSizeCombox;

            nana::group m_rangeGroup;
            nana::place m_rangeLayout;
            nana::radio_group m_rangeRadioGroup;
            nana::checkbox m_allPages;
            nana::checkbox m_currentPage;
            nana::checkbox m_selection;
            nana::checkbox m_pages;
            nana::textbox m_pagesBox;
            nana::tabbar<std::string> m_tabbar;

            nana::group m_miscGroup;
            nana::group m_orientationGroup;
            nana::radio_group m_orientationRadioGroup;
            nana::checkbox m_portrait;
            nana::checkbox m_landscape;
    };
}
