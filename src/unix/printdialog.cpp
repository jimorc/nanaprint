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

#include <string>
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
    PrintDialog::PrintDialog(form& parent, PrintSettings& settings)
        : form(parent, {750, 500}, appear::decorate<>()), m_settings(settings),
             m_dialogSettings(m_settings), m_layout(*this), m_basic(*this), 
             m_basicLayout(m_basic),
             m_tabbar(*this), m_printerGroup(m_basic),
             m_printerLabel(m_printerGroup), m_printerCombox(m_printerGroup),
             m_statusLabel(m_printerGroup), m_printerStatus(m_printerGroup),
             m_typeLabel(m_printerGroup), m_printerType(m_printerGroup),
             m_locationLabel(m_printerGroup), m_printerLocation(m_printerGroup),
             m_commentLabel(m_printerGroup), m_printerComment(m_printerGroup),
             m_paperGroup(m_basic), m_borderlessCheckbox(m_paperGroup),
             m_mediaTypeLabel(m_paperGroup), m_mediaTypeCombox(m_paperGroup),
             m_printQualityLabel(m_paperGroup), m_printQualityCombox(m_paperGroup),
             m_paperSizeLabel(m_paperGroup), m_paperSizeCombox(m_paperGroup),
             m_rangeGroup(m_basic),
             m_rangeLayout(m_rangeGroup),
             m_allPages(m_rangeGroup), m_currentPage(m_rangeGroup),
             m_selection(m_rangeGroup), m_pages(m_rangeGroup),
             m_pagesBox(m_rangeGroup),
             m_miscGroup(m_basic)
             // Cannot create m_orientationGroup and its contents here because the group is
             // within m_miscGroup and this calls the group copy constructor. This is incorrect.
             // Linking m_orientationGroup to m_miscGroup is done below.
    {
        caption(u8"Print");
        m_layout.div(string("vert gap=10 margin=5") +
            "<<tab> weight=20>" +
            "<<tabframe> weight=88%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><print> weight=10%>");

        m_orientationGroup.create(m_miscGroup);
        m_portrait.create(m_orientationGroup);
        m_landscape.create(m_orientationGroup);

        m_tabbar.append(u8"Basic", m_basic);
        m_layout["tab"] << m_tabbar;
        buildBasicTab();
        m_layout["tabframe"] << m_basic;
        m_layout.collocate();
    }

    void PrintDialog::buildBasicTab()
    {
        m_basicLayout.div(string("vertical gap=10") +
            "<<printerGroup weight=48%><weight=10><paperGroup weight=48%> weight=55%>" +
            "<weight=10>" +
            "<<range weight=48%><weight=10><misc weight=48%> weight=22%>");

        buildPrinterGroup();
        m_basicLayout["printerGroup"] << m_printerGroup;

        buildPaperGroup();
        m_basicLayout["paperGroup"] << m_paperGroup;
        
        buildRangeGroup();
        m_basicLayout["range"] << m_rangeGroup;

        buildMiscGroup();
        m_basicLayout["misc"] << m_miscGroup;


        m_basicLayout.collocate();

        m_printerCombox.option(m_dialogSettings.get_printer());
    }

    void PrintDialog::buildPrinterGroup()
    {
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
        m_printerLabel.caption(u8"Printer:");
    }

    void PrintDialog::buildPrinterCombox()
    {
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
        m_statusLabel.caption(u8"Status:");
        m_statusLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterStatus()
    {
        // Caption is set when printer is selected.
        m_printerStatus.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterTypeLabel()
    {
        m_typeLabel.caption("Type:");
        m_typeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterType()
    {
        // Caption is set when printer is selected.
        m_printerType.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildLocationLabel()
    {
        m_locationLabel.caption(u8"Location:");
        m_locationLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterLocation()
    {
        // Caption is set when printer is selected.
        m_printerLocation.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildCommentLabel()
    {
        m_commentLabel.caption(u8"Comment:");
        m_commentLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrinterComment()
    {
        // Caption is set when printer is selected.
        m_printerComment.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPaperGroup()
    {
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
        m_borderlessCheckbox.caption(u8"Borderless papers");
        // checkbox is enabled/disabled when printer is selected.
    }

    void PrintDialog::buildMediaTypeLabel()
    {
        m_mediaTypeLabel.caption(u8"Media Type:");
        m_mediaTypeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildMediaTypeCombox()
    {
        m_mediaTypeCombox.editable(false);
        // Media types loaded when printer is selected.
    }

    void PrintDialog::buildPrintQualityLabel()
    {
        m_printQualityLabel.caption(u8"Print Quality:");
        m_printQualityLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPrintQualityCombox()
    {
        m_printQualityCombox.editable(false);
        // Print qualitys loaded when printer is selected
    }

    void PrintDialog::buildPaperSizeLabel()
    {
        m_paperSizeLabel.caption(u8"Paper Size:");
        m_paperSizeLabel.text_align(align::left, align_v::center);
    }

    void PrintDialog::buildPaperSizeCombox()
    {
        m_paperSizeCombox.editable(false);
        // Paper sizes are loaded when printer is selected.
    }

    void PrintDialog::printer_selected(size_t pos)
    {
        m_dialogSettings.set_printer(pos);
        auto printer = m_settings.getPrinters()[m_dialogSettings.get_printer()];
        updatePrinterGroup(*printer);
        updatePaperGroup(*printer);
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

    void PrintDialog::buildRangeGroup()
    {
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
        m_allPages.caption(u8"All Pages");
        m_allPages.enabled(true);
        m_rangeRadioGroup.add(m_allPages);
    }

    void PrintDialog::buildCurrentPageCheckbox()
    {
        m_currentPage.caption(u8"Current Page");
        m_currentPage.enabled(false);
        m_rangeRadioGroup.add(m_currentPage);
    }

    void PrintDialog::buildSelectionCheckbox()
    {
        m_selection.caption(u8"Selection");
        m_selection.enabled(false);
        m_rangeRadioGroup.add(m_selection);
    }

    void PrintDialog::buildPagesCheckbox()
    {
        m_pages.caption(u8"Pages:");
        m_pages.enabled(true);
        m_rangeRadioGroup.add(m_pages);
    }

    void PrintDialog::buildPagesBox()
    {
        m_pagesBox.editable(true);
        m_pagesBox.multi_lines(false);
        m_pagesBox.indention(false);
    }

    void PrintDialog::buildMiscGroup()
    {
        m_miscGroup.caption(u8"Miscellaneous");
        string layout(string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><orientationGroup weight=95%><> weight=20%>");
        m_miscGroup.div(layout.c_str());

        buildOrientationGroup();
        m_miscGroup["orientationGroup"] << m_orientationGroup;
    }

    void PrintDialog::buildOrientationGroup()
    {
        m_orientationGroup.caption(u8"Orientation");
        string layout(string("vertical gap=10") +
            "<weight=10>" +
            "<<weight=10><portrait weight=48%><><landscape weight=48%><> weight=25>" +
            "<weight=10>" +
            "<<weight=10><portraitReverse weight=48%><><landscapeReverse weight=48%><> weight=25>");
        m_orientationGroup.div(layout.c_str());

        buildPortraitCheckbox();
        m_orientationGroup["portrait"] << m_portrait;

        buildLandscapeCheckbox();
        m_orientationGroup["landscape"] << m_landscape;
    }

    void PrintDialog::buildPortraitCheckbox()
    {
        m_portrait.caption(u8"Portrait");
        m_portrait.enabled(true);
        m_orientationRadioGroup.add(m_portrait);
    }

    void PrintDialog::buildLandscapeCheckbox()
    {
        m_landscape.caption(u8"Landscape");
        m_landscape.enabled(true);
        m_orientationRadioGroup.add(m_landscape);
    }

    void PrintDialog::run()
    {
        modality();
    }
}
