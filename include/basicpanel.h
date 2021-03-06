#ifndef NANAPRINT_BASICPANEL_H
#define NANAPRINT_BASICPANEL_H

/**
 *  \file basicpanel.h
 *  \brief This file provides BasicPanel class used in the PrintDialog class
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020-2021 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 */

#include <nana/gui.hpp>
#include <nana/gui/place.hpp>
#include <nana/gui/widgets/tabbar.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include <nana/gui/widgets/button.hpp>
#include <nana/gui/widgets/panel.hpp>
#include <nana/gui/widgets/textbox.hpp>
#include <nana/gui/widgets/spinbox.hpp>
#include "nanaprint.h"
#include "printsettings.h"
#include "printdialogsettings.h"
#include "printers.h"

namespace nanaprint
{
    class basic_panel : public nana::panel<false>
    {
        public:
            basic_panel(print_settings& settings, PrintDialogSettings& dialogSettings);
            virtual ~basic_panel() {}
            bool create(nana::form& parent);

        private:
            void build_basic_column1();
            void build_basic_column2();

            void build_printer_group();
            void build_printer_label();
            void build_printer_combox();
            void build_printer_status_label();
            void build_printer_status();
            void build_printer_type_label();
            void build_printer_type();
            void build_location_label();
            void build_printer_location();
            void build_comment_label();
            void build_printer_comment();

            void build_paper_group();
            void build_borderless_checkbox();
            void build_media_type_label();
            void build_media_type_combox();
            void build_print_quality_label();
            void build_print_quality_combox();
            void build_paper_size_label();
            void build_paper_size_combox();

            void build_range_group();
            void printer_selected(size_t pos);
            void update_printer_group(printer& prtr);
            void update_paper_group(printer& prtr);
            void update_media_type_combox(printer& prtr);
            void update_print_quality_combox(printer& prtr);
            void update_paper_size_combox(printer& prtr);
            void update_misc_group(printer& prtr);
            void update_orientation_group(printer& prtr);
            void enable_orientation_checkbox(const page_orientation& orientation);
            void select_orientation_checkbox(const page_orientation& orientation);
            void disable_orientation_checkboxes();
            void uncheck_orientation_checkboxes();
            void validate_copies();
            void update_2_sided_combox(printer& prtr);

            void build_all_pages_checkbox();
            void build_current_page_checkbox();
            void build_selection_checkbox();
            void build_pages_checkbox();
            void build_pages_box();

            void build_misc_group();
            void build_orientation_group();
            void build_portrait_checkbox();
            void build_landscape_checkbox();
            void build_reverse_portrait_checkbox();
            void build_reverse_landscape_checkbox();
            void build_copies_label();
            void build_copies_spinbox();
            void build_collate_checkbox();
            void build_reverse_order_checkbox();
            void build_2_sided_label();
            void build_2_sided_combox();

            print_settings& m_settings;
            PrintDialogSettings& m_dialogSettings;

            nana::place m_basicLayout;

            nana::panel<false> m_basicColumn1;
            nana::place m_column1Layout;

            nana::panel<false> m_basicColumn2;
            nana::place m_column2Layout;

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
            nana::checkbox m_revPortrait;
            nana::checkbox m_revLandscape;
            nana::label m_copiesLabel;
            nana::spinbox m_copiesSpinbox;
            nana::checkbox m_collateCheckbox;
            nana::checkbox m_reverseOrderCheckbox;
            nana::label m_2SidedLabel;
            nana::combox m_2SidedCombox;
        };
    }

    #endif  // NANAPRINT_BASICPANEL_H