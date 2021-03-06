/**
 *  \brief BasicPanel class used by the PrintDialog class
 *
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020-2021 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/basicpanel.cpp
 */

#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "basicpanel.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    constexpr int MINIMUMCOPIES = 1;
    constexpr int MAXIMUMCOPIES = 100;

    basic_panel::basic_panel(print_settings& settings, PrintDialogSettings& dialogSettings)
        : m_settings(settings), m_dialogSettings(dialogSettings) {}

    bool basic_panel::create(nana::form& parent)
    {
        panel::create(parent);
        m_basicLayout.bind(*this);
        m_basicLayout.div(string("horizontal gap=10") +
            "<weight=10><column1 weight=48%><><column2 weight=48%><weight=10>");

        build_basic_column1();
        m_basicLayout["column1"] << m_basicColumn1;
        build_basic_column2();
        m_basicLayout["column2"] << m_basicColumn2;

        m_printerCombox.option(m_dialogSettings.get_printer());
        return true;
    }

    void basic_panel::build_basic_column1()
    {
        m_basicColumn1.create(*this);
        m_column1Layout.bind(m_basicColumn1);
        m_column1Layout.div(string("vertical gap=10") +
            "<printerGroup weight=67%><weight=10><range weight=28%>");

        build_printer_group();
        m_column1Layout["printerGroup"] << m_printerGroup;
        build_range_group();
        m_column1Layout["range"] << m_rangeGroup;
    }

    void basic_panel::build_basic_column2()
    {
        m_basicColumn2.create(*this);
        m_column2Layout.bind(m_basicColumn2);
        m_column2Layout.div(string("vertical gap=10") +
            "<paperGroup weight=38%><weight=10><misc weight=57%>");

        build_paper_group();
        m_column2Layout["paperGroup"] << m_paperGroup;
        build_misc_group();
        m_column2Layout["misc"] << m_miscGroup;
    }

    void basic_panel::build_printer_group()
    {
        m_printerGroup.create(m_basicColumn1);
        m_printerGroup.caption(u8"Printer");

        auto div = string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><printerLabel weight=30%><><printerCombox weight=64%><> weight=25>" +
            "<<weight=10><statusLabel weight=30%><><printerStatus weight=64%><> weight=45>" +
            "<<weight=10><typeLabel weight=30%><><printerType weight=64%><> weight=40>" +
            "<<weight=10><locationLabel weight=30%><><printerLocation weight=64%><> weight=25>" +
            "<<weight=10><commentLabel weight=30%><><printerComment weight=64%><> weight=120>";
        m_printerGroup.div(div.c_str());

            build_printer_label();
            m_printerGroup["printerLabel"] << m_printerLabel;

            build_printer_combox();
            m_printerGroup["printerCombox"] << m_printerCombox;

            build_printer_status_label();
            m_printerGroup["statusLabel"] << m_statusLabel;

            build_printer_status();
            m_printerGroup["printerStatus"] << m_printerStatus;

            build_printer_type_label();
            m_printerGroup["typeLabel"] << m_typeLabel;

            build_printer_type();
            m_printerGroup["printerType"] << m_printerType;

            build_location_label();
            m_printerGroup["locationLabel"] << m_locationLabel;

            build_printer_location();
            m_printerGroup["printerLocation"] << m_printerLocation;

            build_comment_label();
            m_printerGroup["commentLabel"] << m_commentLabel;

            build_printer_comment();
            m_printerGroup["printerComment"] << m_printerComment;
    }

    void basic_panel::build_printer_label()
    {
        m_printerLabel.create(m_printerGroup);
        m_printerLabel.caption(u8"Printer:");
    }

    void basic_panel::build_printer_combox()
    {
        m_printerCombox.create(m_printerGroup);
        m_printerCombox.editable(false);
        auto printers = m_settings.get_printers().get_printers();
        for (auto& printer: printers)
        {
            m_printerCombox.push_back(printer->get_name());
        }

        m_printerCombox.events().selected( [this](const arg_combox&) {
            printer_selected(m_printerCombox.option());
        });
   }

    void basic_panel::build_printer_status_label()
    {
        m_statusLabel.create(m_printerGroup);
        m_statusLabel.caption(u8"Status:");
        m_statusLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_printer_status()
    {
        // Caption is set when printer is selected.
        m_printerStatus.create(m_printerGroup);
        m_printerStatus.text_align(align::left, align_v::center);
    }

    void basic_panel::build_printer_type_label()
    {
        m_typeLabel.create(m_printerGroup);
        m_typeLabel.caption("Type:");
        m_typeLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_printer_type()
    {
        // Caption is set when printer is selected.
        m_printerType.create(m_printerGroup);
        m_printerType.text_align(align::left, align_v::center);
    }

    void basic_panel::build_location_label()
    {
        m_locationLabel.create(m_printerGroup);
        m_locationLabel.caption(u8"Location:");
        m_locationLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_printer_location()
    {
        // Caption is set when printer is selected.
        m_printerLocation.create(m_printerGroup);
        m_printerLocation.text_align(align::left, align_v::center);
    }

    void basic_panel::build_comment_label()
    {
        m_commentLabel.create(m_printerGroup);
        m_commentLabel.caption(u8"Comment:");
        m_commentLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_printer_comment()
    {
        // Caption is set when printer is selected.
        m_printerComment.create(m_printerGroup);
        m_printerComment.text_align(align::left, align_v::center);
    }

    void basic_panel::build_paper_group()
    {
        m_paperGroup.create(m_basicColumn2);
        m_paperGroup.caption(u8"Paper");

        auto div = string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><mediaTypeLabel weight=35%><><mediaTypeCombox weight=60%><> weight=25>" +
            "<weight=10>" +
            "<<weight=10><qualityLabel weight=35%><><qualityCombox weight=60%><> weight=25>" +
            "<weight=10>" +
            "<<weight=10><sizeLabel weight=35%><><sizeCombox weight=60%><> weight=25>" +
            "<weight=5>" +
            "<<weight=10><weight=35%><><borderlessCheckbox weight=60%><> weight=20>";
        m_paperGroup.div(div.c_str());

        build_media_type_label();
        m_paperGroup["mediaTypeLabel"] << m_mediaTypeLabel;

        build_media_type_combox();
        m_paperGroup["mediaTypeCombox"] << m_mediaTypeCombox;

        build_print_quality_label();
        m_paperGroup["qualityLabel"] << m_printQualityLabel;

        build_print_quality_combox();
        m_paperGroup["qualityCombox"] << m_printQualityCombox;

        build_paper_size_label();
        m_paperGroup["sizeLabel"] << m_paperSizeLabel;

        build_paper_size_combox();
        m_paperGroup["sizeCombox"] << m_paperSizeCombox;
        
        build_borderless_checkbox();
        m_paperGroup["borderlessCheckbox"] << m_borderlessCheckbox;
    }

    void basic_panel::build_borderless_checkbox()
    {
        m_borderlessCheckbox.create(m_paperGroup);
        m_borderlessCheckbox.caption(u8"Borderless papers");
        // checkbox is enabled/disabled when printer is selected.
    }

    void basic_panel::build_media_type_label()
    {
        m_mediaTypeLabel.create(m_paperGroup);
        m_mediaTypeLabel.caption(u8"Media Type:");
        m_mediaTypeLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_media_type_combox()
    {
        m_mediaTypeCombox.create(m_paperGroup);
        m_mediaTypeCombox.editable(false);
        // Media types loaded when printer is selected.
    }

    void basic_panel::build_print_quality_label()
    {
        m_printQualityLabel.create(m_paperGroup);
        m_printQualityLabel.caption(u8"Print Quality:");
        m_printQualityLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_print_quality_combox()
    {
        m_printQualityCombox.create(m_paperGroup);
        m_printQualityCombox.editable(false);
        // Print qualitys loaded when printer is selected
    }

    void basic_panel::build_paper_size_label()
    {
        m_paperSizeLabel.create(m_paperGroup);
        m_paperSizeLabel.caption(u8"Paper Size:");
        m_paperSizeLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_paper_size_combox()
    {
        m_paperSizeCombox.create(m_paperGroup);
        m_paperSizeCombox.editable(false);
        // Paper sizes are loaded when printer is selected.
    }


    void basic_panel::printer_selected(size_t pos)
    {
        m_dialogSettings.set_printer(pos);
        auto printers = m_settings.get_printers().get_printers();
        auto prtr = printers[m_dialogSettings.get_printer()];
        update_printer_group(*prtr);
        update_paper_group(*prtr);
        update_misc_group(*prtr);
    }

    void basic_panel::update_printer_group(printer& prtr)
    {
        m_printerStatus.caption(prtr.get_printer_state());
        m_printerType.caption(prtr.get_printer_make_and_model());
        m_printerLocation.caption(prtr.get_printer_location());
        m_printerComment.caption(prtr.get_printer_info());
    }

    void basic_panel::update_paper_group(printer& prtr)
    {
        m_borderlessCheckbox.enabled(prtr.get_media_sizes().contains_borderless_paper());
        update_media_type_combox(prtr);
        update_print_quality_combox(prtr);
        update_paper_size_combox(prtr);
    }

    void basic_panel::update_media_type_combox(printer& prtr)
    {
        m_mediaTypeCombox.clear();
        auto mediaTypes = prtr.get_media_types().get_values();
        auto hasMediaTypes = mediaTypes.size() > 0;
        m_mediaTypeCombox.enabled(hasMediaTypes);
        auto selectedMediaType = m_dialogSettings.get_media_type();
        size_t optionNumber = 0;
        if (hasMediaTypes)
        {
            for (size_t mediaNum = 0; mediaNum < mediaTypes.size(); ++mediaNum)
            {
                auto mediaType = mediaTypes[mediaNum];
                m_mediaTypeCombox.push_back(mediaType.get_value());
                if (selectedMediaType
                        && mediaType.get_value() == selectedMediaType.value().get_value())
                {
                    optionNumber = mediaNum;
                }
            m_mediaTypeCombox.option(optionNumber);
            }
        }
    }

    void basic_panel::update_print_quality_combox(printer& prtr)
    {
        m_printQualityCombox.clear();
        auto qualities = prtr.get_print_qualities().get_values();
        auto hasPrintQualities = qualities.size() > 0;
        m_printQualityCombox.enabled(hasPrintQualities);
        auto selectedPrintQuality = m_dialogSettings.get_print_quality();
        if (hasPrintQualities)
        {
            size_t optionNumber = 0;
            for (size_t qualityNum = 0; qualityNum < qualities.size(); ++qualityNum)
            {
                auto quality = qualities[qualityNum].get_value();
                m_printQualityCombox.push_back(quality);
                if (quality == selectedPrintQuality.value().get_value())
                {
                    optionNumber = qualityNum;
                }
            }
            m_printQualityCombox.option(optionNumber);
        }
    }

    void basic_panel::update_paper_size_combox(printer& prtr)
    {
        m_paperSizeCombox.clear();

        auto allPaperSizes = prtr.get_media_sizes();
        bool borderless = m_borderlessCheckbox.checked();
        auto paperSizes = allPaperSizes.get_media_size_translated_names_by_border(
                borderless);
        auto hasPaperSizes = paperSizes.size() > 0;
        m_paperSizeCombox.enabled(hasPaperSizes);
        if (hasPaperSizes)
        {
            
            for (auto& size : paperSizes)
            {
                m_paperSizeCombox.push_back(size);
            }

            size_t optionNumber = 0;
            auto selectedPaperSize = m_dialogSettings.get_media_size();
            if (selectedPaperSize)
            {
                auto translatedSelectedPaperSizeName = 
                    selectedPaperSize.value().get_translated_name();
                for (size_t sizeNum = 0; sizeNum < paperSizes.size(); ++sizeNum)
                {
                    auto size = paperSizes[sizeNum];
                    if(size == translatedSelectedPaperSizeName)
                    {
                        optionNumber = sizeNum;
                    }
                }
            }
            m_paperSizeCombox.option(optionNumber);

        }
    }

    void basic_panel::update_misc_group(printer& prtr)
    {
        update_orientation_group(prtr);
        update_2_sided_combox(prtr);
    }

    void basic_panel::update_orientation_group(printer& prtr)
    {
        disable_orientation_checkboxes();
        uncheck_orientation_checkboxes();

        auto orientations = prtr.get_orientations().get_values();
        for (auto orientation: orientations)
        {
            enable_orientation_checkbox(orientation);
        }
        auto orientation = m_dialogSettings.get_page_orientation();
        if(orientation)
        {
            select_orientation_checkbox(*orientation);
        }
        else
        {
            select_orientation_checkbox(page_orientation(PORTRAIT));
        }
        
    }

    void basic_panel::enable_orientation_checkbox(const page_orientation& orientation)
    {
        auto numOrientation = orientation.get_orientation_number();
        switch (numOrientation)
        {
            case PORTRAIT:
                m_portrait.enabled(true);
                break;
            case LANDSCAPE:
                m_landscape.enabled(true);
                break;
            case REVERSE_LANDSCAPE:
                m_revLandscape.enabled(true);
                break;
            case REVERSE_PORTRAIT:
                m_revPortrait.enabled(true);
                break;
        }
    }

    void basic_panel::disable_orientation_checkboxes()
    {
        m_portrait.enabled(false);
        m_landscape.enabled(false);
        m_revLandscape.enabled(false);
        m_revPortrait.enabled(false);
    }

    // Argument must be one of Portrait, Landscape, Reverse Portrait, or Reverse Landscape.
    // Check this before calling this method.
    void basic_panel::select_orientation_checkbox(const page_orientation& orientation)
    {
        auto numOrientation = orientation.get_orientation_number();
        switch (numOrientation)
        {
            case PORTRAIT:
                m_portrait.check(true);
                break;
            case LANDSCAPE:
                m_landscape.check(true);
                break;
            case REVERSE_PORTRAIT:
                m_revPortrait.check(true);
                break;
            case REVERSE_LANDSCAPE:
                m_revLandscape.check(true);
                break;
        }
    }

    void basic_panel::uncheck_orientation_checkboxes()
    {
        m_portrait.check(false);
        m_landscape.check(false);
        m_revLandscape.check(false);
        m_revPortrait.check(false);
    }

    void basic_panel::update_2_sided_combox(printer& prtr)
    {
        m_2SidedCombox.clear();
        auto sides = prtr.get_sides().get_values();
        auto defaultSide = m_dialogSettings.get_side();
        size_t opt = 0;
        if (defaultSide)
        {
            for (size_t side = 0; side < sides.size(); ++side)
            {
                auto text = sides[side].get_value();
                m_2SidedCombox.push_back(text);
                if (text.compare(defaultSide.value().get_value().c_str()) == 0)
                {
                    opt = side;
                }
            }
        }
        m_2SidedCombox.option(opt);
        
    }

    void basic_panel::build_range_group()
    {
        m_rangeGroup.create(m_basicColumn1);
        m_rangeLayout.bind(m_rangeGroup);

        m_rangeGroup.caption(u8"Range");
        string layout(string("vertical gap=10") +
            "<weight=25>" +
            "<<weight=30><allPages weight=35%><> weight=25>" +
            "<<weight=30><currentPage weight=35%><> weight=25> " +
            "<<weight=30><selection weight=35%><> weight=25>" +
            "<<weight=30><pages weight=35%><weight=10><pagesList weight=50%><> weight=25>");
        m_rangeLayout.div(layout.c_str());
        build_all_pages_checkbox();
        m_rangeLayout["allPages"] << m_allPages;
        build_current_page_checkbox();
        m_rangeLayout["currentPage"] << m_currentPage;
        build_selection_checkbox();
        m_rangeLayout["selection"] << m_selection;
        build_pages_checkbox();
        m_rangeLayout["pages"] << m_pages;
        build_pages_box();
        m_rangeLayout["pagesList"] << m_pagesBox;
    }

    void basic_panel::build_all_pages_checkbox()
    {
        m_allPages.create(m_rangeGroup);
        m_allPages.caption(u8"All Pages");
        m_allPages.enabled(true);
        m_rangeRadioGroup.add(m_allPages);
    }

    void basic_panel::build_current_page_checkbox()
    {
        m_currentPage.create(m_rangeGroup);
        m_currentPage.caption(u8"Current Page");
        m_currentPage.enabled(false);
        m_rangeRadioGroup.add(m_currentPage);
    }

    void basic_panel::build_selection_checkbox()
    {
        m_selection.create(m_rangeGroup);
        m_selection.caption(u8"Selection");
        m_selection.enabled(false);
        m_rangeRadioGroup.add(m_selection);
    }

    void basic_panel::build_pages_checkbox()
    {
        m_pages.create(m_rangeGroup);
        m_pages.caption(u8"Pages:");
        m_pages.enabled(true);
        m_rangeRadioGroup.add(m_pages);
    }

    void basic_panel::build_pages_box()
    {
        m_pagesBox.create(m_rangeGroup);
        m_pagesBox.editable(true);
        m_pagesBox.multi_lines(false);
        m_pagesBox.indention(false);
    }

    void basic_panel::build_misc_group()
    {
        m_miscGroup.create(m_basicColumn2);

        m_miscGroup.caption(u8"Miscellaneous");
        string layout(string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><orientationGroup weight=95%><> weight=40%>" +
            "<weight=10>" +
            "<<weight=10><copies weight=35%><copiesBox weight=15%><weight=45%> weight=25>" +
            "<weight=2>" +
            "<<weight=10><weight=35%><collate weight=60%> weight=25>" +
            "<<weight=10><weight=35%><reverseOrder weight=60%> weight=25>" +
            "<weight=10>" +
            "<<weight=10><twosidedLabel weight=35%><2twosidedCombox weight=60%><> weight=25>");
        m_miscGroup.div(layout.c_str());

        build_orientation_group();
        m_miscGroup["orientationGroup"] << m_orientationGroup;
        build_copies_label();
        m_miscGroup["copies"] << m_copiesLabel;
        build_copies_spinbox();
        m_miscGroup["copiesBox"] << m_copiesSpinbox;
        build_collate_checkbox();
        m_miscGroup["collate"] << m_collateCheckbox;
        build_reverse_order_checkbox();
        m_miscGroup["reverseOrder"] << m_reverseOrderCheckbox;
        build_2_sided_label();
        m_miscGroup["twosidedLabel"] << m_2SidedLabel;
        build_2_sided_combox();
        m_miscGroup["twosidedCombox"] << m_2SidedCombox;
    }

    void basic_panel::build_orientation_group()
    {
        m_orientationGroup.create(m_miscGroup);
        m_orientationGroup.caption(u8"Orientation");
        string layout(string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><portrait weight=48%><><landscape weight=48%><> weight=25>" +
            "<weight=10>" +
            "<<weight=10><portraitReverse weight=48%><><landscapeReverse weight=48%><> weight=25>" +
            "<weight=10>");
        m_orientationGroup.div(layout.c_str());

        build_portrait_checkbox();
        m_orientationGroup["portrait"] << m_portrait;

        build_landscape_checkbox();
        m_orientationGroup["landscape"] << m_landscape;

        build_reverse_portrait_checkbox();
        m_orientationGroup["portraitReverse"] << m_revPortrait;

        build_reverse_landscape_checkbox();
        m_orientationGroup["landscapeReverse"] << m_revLandscape;
    }

    void basic_panel::build_portrait_checkbox()
    {
        m_portrait.create(m_orientationGroup);
        m_portrait.caption(u8"Portrait");
        m_orientationRadioGroup.add(m_portrait);
    }

    void basic_panel::build_landscape_checkbox()
    {
        m_landscape.create(m_orientationGroup);
        m_landscape.caption(u8"Landscape");
        m_orientationRadioGroup.add(m_landscape);
    }

    void basic_panel::build_reverse_portrait_checkbox()
    {
        m_revPortrait.create(m_orientationGroup);
        m_revPortrait.caption(u8"Reverse Portrait");
        m_orientationRadioGroup.add(m_revPortrait);
    }

    void basic_panel::build_reverse_landscape_checkbox()
    {
        m_revLandscape.create(m_orientationGroup);
        m_revLandscape.caption(u8"Reverse Landscape");
        m_orientationRadioGroup.add(m_revLandscape);
    }

    void basic_panel::build_copies_label()
    {
        m_copiesLabel.create(m_miscGroup);
        m_copiesLabel.caption(u8"Copies:");
        m_copiesLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_copies_spinbox()
    {
        m_copiesSpinbox.create(m_miscGroup);
        m_copiesSpinbox.range(MINIMUMCOPIES, MAXIMUMCOPIES, 1);
        m_copiesSpinbox.editable(true);
        stringstream ss;
        ss << "Value must be between " << MINIMUMCOPIES << " and " << MAXIMUMCOPIES;
        m_copiesSpinbox.tooltip(ss.str());
        m_copiesSpinbox.events().key_release( [&](const arg_keyboard&) {
            validate_copies(); });
        m_copiesSpinbox.events().mouse_enter( [&]() {
            stringstream ss;
            ss << "Value must be between " << MINIMUMCOPIES << " and " << MAXIMUMCOPIES;
            m_copiesSpinbox.tooltip(ss.str());
        });
    }

    void basic_panel::build_collate_checkbox()
    {
        m_collateCheckbox.create(m_miscGroup);
        m_collateCheckbox.caption(u8"Collate");
        m_collateCheckbox.enabled(false);
    }

    void basic_panel::build_reverse_order_checkbox()
    {
        m_reverseOrderCheckbox.create(m_miscGroup);
        m_reverseOrderCheckbox.caption(u8"Reverse Order");
    }

    void basic_panel::build_2_sided_label()
    {
        m_2SidedLabel.create(m_miscGroup);
        m_2SidedLabel.caption(u8"2-sided/Booklet:");
        m_2SidedLabel.text_align(align::left, align_v::center);
    }

    void basic_panel::build_2_sided_combox()
    {
        m_2SidedCombox.create(m_miscGroup);
        m_2SidedCombox.editable(false);
        // contents of combox added when a printer is selected.
    }

    void basic_panel::validate_copies()
    {
        // This code is needed because of a bug in nana::spinbox. If a value is entered in
        // the spinbox's edit box that is larger than the maximum value, or smaller than
        // the minimum value, the spinbox will not accept the value, but the edit box still
        // displays it. This code changes the displayed value back to the previous value.
        m_copiesSpinbox.value(m_copiesSpinbox.value());
        // the displayed value is not updated until the spinbox loses focus.
        m_copiesLabel.focus();
        m_copiesSpinbox.focus();
    }
}
