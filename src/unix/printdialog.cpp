/**
 *  \brief A PrintDialog class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/prkintdialog.cpp
 */

#include <chrono>
#include <thread>
#include <string>
#include <sstream>
#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "printdialog.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    constexpr int MINIMUMCOPIES = 1;
    constexpr int MAXIMUMCOPIES = 100;

    PrintDialog::PrintDialog(form& parent, PrintSettings& settings)
        : form(parent, {750, 500}, appear::decorate<>()), m_settings(settings),
             m_dialogSettings(m_settings), m_layout(*this), m_basic(*this), 
             m_basicLayout(m_basic),
             m_tabbar(*this)
    {
        caption(u8"Print");
        m_layout.div(string("vert gap=10 margin=5") +
            "<<tab> weight=20>" +
            "<<tabframe> weight=88%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><print> weight=10%>");


        m_tabbar.append(u8"Basic", m_basic);
        m_layout["tab"] << m_tabbar;
        buildBasicTab();
        m_layout["tabframe"] << m_basic;
        m_layout.collocate();
    }

    void PrintDialog::buildBasicTab()
    {
        m_basicLayout.div(string("horizontal gap=10") +
            "<weight=10><column1 weight=48%><><column2 weight=48%><weight=10>");

        buildBasicColumn1();
        m_basicLayout["column1"] << m_basicColumn1;
        buildBasicColumn2();
        m_basicLayout["column2"] << m_basicColumn2;
        m_basicLayout.collocate();

        m_printerCombox.option(m_dialogSettings.get_printer());
    }

    void PrintDialog::buildBasicColumn1()
    {
        m_basicColumn1.create(m_basic);
        m_column1Layout.bind(m_basicColumn1);
        m_column1Layout.div(string("vertical gap=10") +
            "<printerGroup weight=65%><weight=10><range weight=30%>");

        buildPrinterGroup();
        m_column1Layout["printerGroup"] << m_printerGroup;
        buildRangeGroup();
        m_column1Layout["range"] << m_rangeGroup;
    }

    void PrintDialog::buildBasicColumn2()
    {
        m_basicColumn2.create(m_basic);
        m_column2Layout.bind(m_basicColumn2);
        m_column2Layout.div(string("vertical gap=10") +
            "<paperGroup weight=38%><weight=10><misc weight=57%>");

        buildPaperGroup();
        m_column2Layout["paperGroup"] << m_paperGroup;
        buildMiscGroup();
        m_column2Layout["misc"] << m_miscGroup;
    }

    void PrintDialog::buildPrinterGroup()
    {
        m_printerGroup.create(m_basicColumn1);
        m_printerGroup.caption(u8"Printer");

        auto div = string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><printerLabel weight=30%><><printerCombox weight=64%><> weight=25>" +
            "<<weight=10><statusLabel weight=30%><><printerStatus weight=64%><> weight=45>" +
            "<<weight=10><typeLabel weight=30%><><printerType weight=64%><> weight=25>" +
            "<<weight=10><locationLabel weight=30%><><printerLocation weight=64%><> weight=25>" +
            "<<weight=10><commentLabel weight=30%><><printerComment weight=64%><> weight=80>";
        m_printerGroup.div(div.c_str());

            buildPrinterLabel();
            m_printerGroup["printerLabel"] << m_printerLabel;

            buildPrinterCombox();
            m_printerGroup["printerCombox"] << m_printerCombox;

            buildStatusLabel();
            m_printerGroup["statusLabel"] << m_statusLabel;

            buildPrinterStatus();
            m_printerGroup["printerStatus"] << m_printerStatus;

            buildPrinterTypeLabel();
            m_printerGroup["typeLabel"] << m_typeLabel;

            buildPrinterType();
            m_printerGroup["printerType"] << m_printerType;

            buildLocationLabel();
            m_printerGroup["locationLabel"] << m_locationLabel;

            buildPrinterLocation();
            m_printerGroup["printerLocation"] << m_printerLocation;

            buildCommentLabel();
            m_printerGroup["commentLabel"] << m_commentLabel;

            buildPrinterComment();
            m_printerGroup["printerComment"] << m_printerComment;
    }

    void PrintDialog::buildPrinterLabel()
    {
        m_printerLabel.create(m_printerGroup);
        m_printerLabel.caption(u8"Printer:");
    }

    void PrintDialog::buildPrinterCombox()
    {
        m_printerCombox.create(m_printerGroup);
        m_printerCombox.editable(false);
        auto printers = m_settings.getPrinters();
        for (auto& printer: printers)
        {
            m_printerCombox.push_back(printer->getName());
        }

        m_printerCombox.events().selected( [this](const arg_combox& ar_cbx) {
            printer_selected(m_printerCombox.option());
        });
   }

    void PrintDialog::buildStatusLabel()
    {
        m_statusLabel.create(m_printerGroup);
        m_statusLabel.caption(u8"Status:");
        m_statusLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterStatus()
    {
        // Caption is set when printer is selected.
        m_printerStatus.create(m_printerGroup);
        m_printerStatus.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterTypeLabel()
    {
        m_typeLabel.create(m_printerGroup);
        m_typeLabel.caption("Type:");
        m_typeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterType()
    {
        // Caption is set when printer is selected.
        m_printerType.create(m_printerGroup);
        m_printerType.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildLocationLabel()
    {
        m_locationLabel.create(m_printerGroup);
        m_locationLabel.caption(u8"Location:");
        m_locationLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterLocation()
    {
        // Caption is set when printer is selected.
        m_printerLocation.create(m_printerGroup);
        m_printerLocation.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildCommentLabel()
    {
        m_commentLabel.create(m_printerGroup);
        m_commentLabel.caption(u8"Comment:");
        m_commentLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterComment()
    {
        // Caption is set when printer is selected.
        m_printerComment.create(m_printerGroup);
        m_printerComment.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPaperGroup()
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

        buildMediaTypeLabel();
        m_paperGroup["mediaTypeLabel"] << m_mediaTypeLabel;

        buildMediaTypeCombox();
        m_paperGroup["mediaTypeCombox"] << m_mediaTypeCombox;

        buildPrintQualityLabel();
        m_paperGroup["qualityLabel"] << m_printQualityLabel;

        buildPrintQualityCombox();
        m_paperGroup["qualityCombox"] << m_printQualityCombox;

        buildPaperSizeLabel();
        m_paperGroup["sizeLabel"] << m_paperSizeLabel;

        buildPaperSizeCombox();
        m_paperGroup["sizeCombox"] << m_paperSizeCombox;
        
        buildBorderlessCheckbox();
        m_paperGroup["borderlessCheckbox"] << m_borderlessCheckbox;
    }

    void PrintDialog::buildBorderlessCheckbox()
    {
        m_borderlessCheckbox.create(m_paperGroup);
        m_borderlessCheckbox.caption(u8"Borderless papers");
        // checkbox is enabled/disabled when printer is selected.
    }

    void PrintDialog::buildMediaTypeLabel()
    {
        m_mediaTypeLabel.create(m_paperGroup);
        m_mediaTypeLabel.caption(u8"Media Type:");
        m_mediaTypeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildMediaTypeCombox()
    {
        m_mediaTypeCombox.create(m_paperGroup);
        m_mediaTypeCombox.editable(false);
        // Media types loaded when printer is selected.
    }

    void PrintDialog::buildPrintQualityLabel()
    {
        m_printQualityLabel.create(m_paperGroup);
        m_printQualityLabel.caption(u8"Print Quality:");
        m_printQualityLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrintQualityCombox()
    {
        m_printQualityCombox.create(m_paperGroup);
        m_printQualityCombox.editable(false);
        // Print qualitys loaded when printer is selected
    }

    void PrintDialog::buildPaperSizeLabel()
    {
        m_paperSizeLabel.create(m_paperGroup);
        m_paperSizeLabel.caption(u8"Paper Size:");
        m_paperSizeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPaperSizeCombox()
    {
        m_paperSizeCombox.create(m_paperGroup);
        m_paperSizeCombox.editable(false);
        // Paper sizes are loaded when printer is selected.
    }

    void PrintDialog::printer_selected(size_t pos)
    {
        m_dialogSettings.set_printer(pos);
        auto printer = m_settings.getPrinters()[m_dialogSettings.get_printer()];
        updatePrinterGroup(*printer);
        updatePaperGroup(*printer);
        updateMiscGroup(*printer);
    }

    void PrintDialog::updatePrinterGroup(Printer& printer)
    {
        m_printerStatus.caption(printer.get_printer_state());
        m_printerType.caption(printer.get_printer_make_and_model());
        m_printerLocation.caption(printer.get_printer_location());
        m_printerComment.caption(printer.get_printer_info());
    }

    void PrintDialog::updatePaperGroup(Printer& printer)
    {
        m_borderlessCheckbox.enabled(printer.getMediaSizes().contains_borderless_paper());
        updateMediaTypeCombox(printer);
        updatePrintQualityCombox(printer);
        updatePaperSizeCombox(printer);
    }

    void PrintDialog::updateMediaTypeCombox(Printer& printer)
    {
        m_mediaTypeCombox.clear();
        auto mediaTypes = printer.getMediaTypes().getMediaTypes();
        auto hasMediaTypes = mediaTypes.size() > 0;
        m_mediaTypeCombox.enabled(hasMediaTypes);
        auto selectedMediaType = m_dialogSettings.get_media_type();
        size_t optionNumber = 0;
        if (hasMediaTypes)
        {
            for (auto mediaNum = 0; mediaNum < mediaTypes.size(); ++mediaNum)
            {
                auto mediaType = mediaTypes[mediaNum];
                m_mediaTypeCombox.push_back(mediaType->getType());
                if (mediaType->getType() == selectedMediaType.getType())
                {
                    optionNumber = mediaNum;
                }
            }
            m_mediaTypeCombox.option(optionNumber);
        }
    }

    void PrintDialog::updatePrintQualityCombox(Printer& printer)
    {
        m_printQualityCombox.clear();
        auto qualities = printer.getPrintQualities().getPrintQualities();
        auto hasPrintQualities = qualities.size() > 0;
        m_printQualityCombox.enabled(hasPrintQualities);
        auto selectedPrintQuality = m_dialogSettings.get_print_quality();
        if (hasPrintQualities)
        {
            size_t optionNumber = 0;
            for (auto qualityNum = 0; qualityNum < qualities.size(); ++qualityNum)
            {
                auto quality = qualities[qualityNum]->getPrintQuality();
                m_printQualityCombox.push_back(quality);
                if (quality == selectedPrintQuality.getPrintQuality())
                {
                    optionNumber = qualityNum;
                }
            }
            m_printQualityCombox.option(optionNumber);
        }
    }

    void PrintDialog::updatePaperSizeCombox(Printer& printer)
    {
        m_paperSizeCombox.clear();

        auto paperSizes = printer.getMediaSizes().getMediaSizes();
        auto hasPaperSizes = paperSizes.size() > 0;
        m_paperSizeCombox.enabled(hasPaperSizes);
        if (hasPaperSizes)
        {
            bool borderless = m_borderlessCheckbox.checked();
            for (size_t i = 0; i < paperSizes.size(); ++i)
            {
                auto mediaSize = paperSizes[i];
                if (mediaSize->isBorderless() == borderless)
                {
                    m_paperSizeCombox.push_back(mediaSize->getTranslatedName());
                }
            }

            auto selectedPaperSize = m_dialogSettings.get_media_size();
            size_t optionNumber = 0;
            for (auto sizeNum = 0; sizeNum < paperSizes.size(); ++sizeNum)
            {
                auto size = paperSizes[sizeNum]->getTranslatedName();
                m_paperSizeCombox.push_back(size);
                if(size == selectedPaperSize.getTranslatedName())
                {
                    m_paperSizeCombox.option(sizeNum);
                }
            }
        }
    }

    void PrintDialog::updateMiscGroup(Printer& printer)
    {
        updateOrientationGroup(printer);
    }

    void PrintDialog::updateOrientationGroup(Printer& printer)
    {
        disableOrientationCheckboxes();
        uncheckOrientationCheckboxes();

        auto orientations = printer.getOrientations().getOrientations();
        for (auto orientation: orientations)
        {
            enableOrientationCheckbox(*orientation);
        }
        auto orientation = m_settings.get_page_orientation();
        if(orientation)
        {
            selectOrientationCheckbox(*orientation);
        }
        else
        {
            selectOrientationCheckbox(PageOrientation(PORTRAIT));
        }
        
    }

    void PrintDialog::enableOrientationCheckbox(const PageOrientation& orientation)
    {
        auto numOrientation = orientation.getOrientationNumber();
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

    void PrintDialog::disableOrientationCheckboxes()
    {
        m_portrait.enabled(false);
        m_landscape.enabled(false);
        m_revLandscape.enabled(false);
        m_revPortrait.enabled(false);
    }

    // Argument must be one of Portrait, Landscape, Reverse Portrait, or Reverse Landscape.
    // Check this before calling this method.
    void PrintDialog::selectOrientationCheckbox(const PageOrientation& orientation)
    {
        auto numOrientation = orientation.getOrientationNumber();
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

    void PrintDialog::uncheckOrientationCheckboxes()
    {
        m_portrait.check(false);
        m_landscape.check(false);
        m_revLandscape.check(false);
        m_revPortrait.check(false);
    }

    void PrintDialog::buildRangeGroup()
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
        buildAllPagesCheckbox();
        m_rangeLayout["allPages"] << m_allPages;
        buildCurrentPageCheckbox();
        m_rangeLayout["currentPage"] << m_currentPage;
        buildSelectionCheckbox();
        m_rangeLayout["selection"] << m_selection;
        buildPagesCheckbox();
        m_rangeLayout["pages"] << m_pages;
        buildPagesBox();
        m_rangeLayout["pagesList"] << m_pagesBox;
    }

    void PrintDialog::buildAllPagesCheckbox()
    {
        m_allPages.create(m_rangeGroup);
        m_allPages.caption(u8"All Pages");
        m_allPages.enabled(true);
        m_rangeRadioGroup.add(m_allPages);
    }

    void PrintDialog::buildCurrentPageCheckbox()
    {
        m_currentPage.create(m_rangeGroup);
        m_currentPage.caption(u8"Current Page");
        m_currentPage.enabled(false);
        m_rangeRadioGroup.add(m_currentPage);
    }

    void PrintDialog::buildSelectionCheckbox()
    {
        m_selection.create(m_rangeGroup);
        m_selection.caption(u8"Selection");
        m_selection.enabled(false);
        m_rangeRadioGroup.add(m_selection);
    }

    void PrintDialog::buildPagesCheckbox()
    {
        m_pages.create(m_rangeGroup);
        m_pages.caption(u8"Pages:");
        m_pages.enabled(true);
        m_rangeRadioGroup.add(m_pages);
    }

    void PrintDialog::buildPagesBox()
    {
        m_pagesBox.create(m_rangeGroup);
        m_pagesBox.editable(true);
        m_pagesBox.multi_lines(false);
        m_pagesBox.indention(false);
    }

    void PrintDialog::buildMiscGroup()
    {
        m_miscGroup.create(m_basicColumn2);

        m_miscGroup.caption(u8"Miscellaneous");
        string layout(string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><orientationGroup weight=95%><> weight=60%>" +
            "<weight=10>" +
            "<<weight=10><copies weight=35%><copiesBox weight=15%><weight=45%> weight=25>" +
            "<weight=2>" +
            "<<weight=10><weight=35%><collate weight=60%> weight=25>");
        m_miscGroup.div(layout.c_str());

        buildOrientationGroup();
        m_miscGroup["orientationGroup"] << m_orientationGroup;
        buildCopiesLabel();
        m_miscGroup["copies"] << m_copiesLabel;
        buildCopiesSpinbox();
        m_miscGroup["copiesBox"] << m_copiesSpinbox;
        buildCollateCheckbox();
        m_miscGroup["collate"] << m_collateCheckbox;
    }

    void PrintDialog::buildOrientationGroup()
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

        buildPortraitCheckbox();
        m_orientationGroup["portrait"] << m_portrait;

        buildLandscapeCheckbox();
        m_orientationGroup["landscape"] << m_landscape;

        buildReversePortraitCheckbox();
        m_orientationGroup["portraitReverse"] << m_revPortrait;

        buildReverseLandscapeCheckbox();
        m_orientationGroup["landscapeReverse"] << m_revLandscape;
    }

    void PrintDialog::buildPortraitCheckbox()
    {
        m_portrait.create(m_orientationGroup);
        m_portrait.caption(u8"Portrait");
        m_orientationRadioGroup.add(m_portrait);
    }

    void PrintDialog::buildLandscapeCheckbox()
    {
        m_landscape.create(m_orientationGroup);
        m_landscape.caption(u8"Landscape");
        m_orientationRadioGroup.add(m_landscape);
    }

    void PrintDialog::buildReversePortraitCheckbox()
    {
        m_revPortrait.create(m_orientationGroup);
        m_revPortrait.caption(u8"Reverse Portrait");
        m_orientationRadioGroup.add(m_revPortrait);
    }

    void PrintDialog::buildReverseLandscapeCheckbox()
    {
        m_revLandscape.create(m_orientationGroup);
        m_revLandscape.caption(u8"Reverse Landscape");
        m_orientationRadioGroup.add(m_revLandscape);
    }

    void PrintDialog::buildCopiesLabel()
    {
        m_copiesLabel.create(m_miscGroup);
        m_copiesLabel.caption(u8"Copies:");
        m_copiesLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildCopiesSpinbox()
    {
        m_copiesSpinbox.create(m_miscGroup);
        m_copiesSpinbox.range(MINIMUMCOPIES, MAXIMUMCOPIES, 1);
        m_copiesSpinbox.editable(true);
        stringstream ss;
        ss << "Value must be between " << MINIMUMCOPIES << " and " << MAXIMUMCOPIES;
        m_copiesSpinbox.tooltip(ss.str());
        m_copiesSpinbox.events().key_release( [&](const arg_keyboard& arg) {
            validateCopies(); });
        m_copiesSpinbox.events().mouse_enter( [&]() {
            stringstream ss;
            ss << "Value must be between " << MINIMUMCOPIES << " and " << MAXIMUMCOPIES;
            m_copiesSpinbox.tooltip(ss.str());
        });
    }

    void PrintDialog::buildCollateCheckbox()
    {
        m_collateCheckbox.create(m_miscGroup);
        m_collateCheckbox.caption(u8"Collate");
        m_collateCheckbox.enabled(false);
    }

    void PrintDialog::validateCopies()
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

    void PrintDialog::run()
    {
        modality();
    }
}
