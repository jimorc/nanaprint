/**
 *  \brief A PageSetup class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/pagesetup.cpp
 */

#include <nana/gui.hpp>
#include <nana/gui/widgets/label.hpp>
#include <nana/gui/widgets/combox.hpp>
#include <nana/gui/widgets/group.hpp>
#include "pagesetup.h"

using namespace std;
using namespace nana;
using namespace nanaprint;

namespace nanaprint
{
    PageSetup::PageSetup(nana::form& parent, PrintSettings& settings) 
        : form(parent, {500, 500}, appear::decorate<>()), m_settings(settings),
            m_printer(m_settings.get_printer()), m_layout(*this),
            m_printerGroup(*this), m_printerNameLabel(m_printerGroup), m_printerCombox(m_printerGroup),
            m_printerStatusLabel(m_printerGroup), m_printerStatus(m_printerGroup),
            m_printerTypeLabel(m_printerGroup), m_printerType(m_printerGroup),
            m_printerWhereLabel(m_printerGroup), m_printerWhere(m_printerGroup),
            m_printerCommentLabel(m_printerGroup), m_printerComment(m_printerGroup),
            m_paperGroup(*this), m_borderlessCheckbox(m_paperGroup), 
            m_paperSizeLabel(m_paperGroup), m_paperSizeCombox(m_paperGroup),
            m_paperSize(m_paperGroup), m_paperSourceLabel(m_paperGroup),
            m_paperSourceCombox(m_paperGroup), m_orientationLabel(m_paperGroup),
            m_cancel(*this), m_apply(*this)

    {
        caption(u8"Page Setup");
        m_layout.div(string("vert gap=10 margin=5") +
            "<printer weight=48%>" +
            "<paper weight = 42%>" +
            "<weight=5>" +
            "<gap=10 <weight=50%><cancel><weight=10><apply> weight=10%>");

        buildPrinterGroup();
        m_layout["printer"] << m_printerGroup;
        buildPaperGroup();
        m_layout["paper"] << m_paperGroup;
        buildButtons();
        m_layout["cancel"] << m_cancel;
        m_layout["apply"] << m_apply;
        
        m_layout.collocate();

        // Must set printer after paper group is created.
        // Otherwise, paper size is not set for default paper size.
         m_printerCombox.option(m_settings.get_printer());
     }

    void PageSetup::buildPrinterGroup()
    {
        m_printerGroup.caption("Printer");
        string groupDiv = string("vert gap=5 margin=0 ") +
            "<<weight=10><name weight=20%><printerCombox><weight=10> weight=30>" +
            "<<weight=10><status weight=20%><printerStatus><weight=10> weight=30>" +
            "<<weight=10><type weight=20%><printerType><weight=10> weight=30>" +
            "<<weight=10><where weight=20%><printerWhere><weight=10> weight=30>" +
            "<<weight=10><comment weight=20%><printerComment><weight=10> weight=60>";        
        m_printerGroup.div(groupDiv.c_str());

        buildPrinterNameLabel();
        m_printerGroup["name"] << m_printerNameLabel;

        buildPrinterCombox();
        m_printerGroup["printerCombox"] << m_printerCombox;

        buildPrinterStatus();
        m_printerGroup["printerStatus"] << m_printerStatus;

        buildPrinterStatusLabel();
        m_printerGroup["status"] << m_printerStatusLabel;

        buildPrinterTypeLabel();
        m_printerGroup["type"] << m_printerTypeLabel;

        buildPrinterType();
        m_printerGroup["printerType"] << m_printerType;

        buildPrinterWhereLabel();
        m_printerGroup["where"] << m_printerWhereLabel;

        buildPrinterWhere();
        m_printerGroup["printerWhere"] << m_printerWhere;

        buildPrinterCommentLabel();
        m_printerGroup["comment"] << m_printerCommentLabel;

        buildPrinterComment();
        m_printerGroup["printerComment"] << m_printerComment;
}

    void PageSetup::buildPrinterNameLabel()
    {
        m_printerNameLabel.caption("Name:");
        m_printerNameLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCombox()
    {
        m_printerCombox.editable(false);
        auto printers = m_settings.get_printers().getPrinters();
        for (auto& printer: printers)
        {
            m_printerCombox.push_back(printer->getName());
        }

        m_printerCombox.events().selected( [this](const arg_combox& ar_cbx) {
            printer_selected(ar_cbx);
        });
    }

    void PageSetup::buildPrinterStatusLabel()
    {
        m_printerStatusLabel.caption("Status:");
        m_printerStatusLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterStatus()
    {
       m_printerStatus.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterTypeLabel()
    {
        m_printerTypeLabel.caption("Type:");
        m_printerTypeLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterType()
    {
        m_printerType.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhereLabel()
    {
        m_printerWhereLabel.caption("Location:");
        m_printerWhereLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhere()
    {
        m_printerWhere.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCommentLabel()
    {
        m_printerCommentLabel.caption("Comment:");
        m_printerCommentLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterComment()
    {
        m_printerComment.text_align(align::left, align_v::center);
    }


    void PageSetup::buildPaperGroup()
    {
        m_paperGroup.caption("Paper");
        string groupDiv = string("vert gap=5 margin=0 ") +
            "<weight=10>" +
            "<<weight=10><borderless><weight=10> weight=20>" +
            "<weight=10>" +
            "<<weight=10><sizeLabel weight=20%><sizeCombox><weight=10> weight=30>" +
            "<<weight=10><weight=20%><size><weight=10> weight=15>" +
            "<weight=10>" +
            "<<weight=10><sourceLabel weight=20%><source><weight=10> weight=30>" +
            "<weight=10>" +
            "<<weight=10><orientationLabel weight=20%>"
                "<portrait weight=38%><weight=10><portraitReverse><weight=10> weight=20>" +
            "<weight=10>" +
            "<<weight=10><weight=20%>" +
                "<landscape weight=38%><weight=10><landscapeReverse><weight=10> weight=20>";

        m_paperGroup.div(groupDiv.c_str());

        buildBorderlessCheckbox();
        m_paperGroup["borderless"] << m_borderlessCheckbox;

        buildPaperSizeLabel();
        m_paperGroup["sizeLabel"] << m_paperSizeLabel;

        buildPaperSizeCombox();
        m_paperGroup["sizeCombox"] << m_paperSizeCombox;

        buildPaperSize();
        m_paperGroup["size"] << m_paperSize;

        buildPaperSourceLabel();
        m_paperGroup["sourceLabel"] << m_paperSourceLabel;

        buildPaperSourceCombox();
        m_paperGroup["source"] << m_paperSourceCombox;

        buildOrientationLabel();
        m_paperGroup["orientationLabel"] << m_orientationLabel;

        buildOrientationGroup();
    }

    void PageSetup::buildBorderlessCheckbox()
    {
        m_borderlessCheckbox.caption("Borderless papers");
        m_borderlessCheckbox.events().checked([this](const arg_checkbox& arg){
            on_borderlessChecked(arg);
        });
    }

    void PageSetup::buildPaperSizeLabel()
    {
        m_paperSizeLabel.caption("Size:");
        m_paperSizeLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPaperSizeCombox()
    {
        m_paperSizeCombox.editable(false);

        m_paperSizeCombox.events().selected( [this](const arg_combox& ar_cbx) {
            paper_size_selected(ar_cbx);});
    }

    void PageSetup::populatePaperSizeCombox()
    {
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto paperSizes = printer->getMediaSizes();
        m_paperSizeCombox.clear();
        bool borderless = m_borderlessCheckbox.checked();
        for (size_t i = 0; i < paperSizes.size(); ++i)
        {
            auto mediaSize = paperSizes[i];
            if (mediaSize.is_borderless() == borderless)
            {
                m_paperSizeCombox.push_back(mediaSize.get_translated_name());
            }
        }
        size_t option = 0;
        auto mediaSize = m_settings.get_media_size();
        if(mediaSize)
        {
            auto size = mediaSize.value().get_translated_name();
            for (size_t opt = 0; m_paperSizeCombox.the_number_of_options(); ++opt)
            {
                if (size.compare(m_paperSizeCombox.text(opt)) == 0)
                {
                    option = opt;
                    break;
                }
            }
        }
        m_paperSizeCombox.option(option);
    }

    void PageSetup::buildPaperSize()
    {
        m_paperSize.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPaperSourceLabel()
    {
        m_paperSourceLabel.caption("Source:");
        m_paperSourceLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPaperSourceCombox()
    {
        m_paperSourceCombox.editable(false);

        m_paperSourceCombox.events().selected( [this](const arg_combox& ar_cbx) {
            paper_source_selected(ar_cbx);});
    }

    void PageSetup::buildOrientationLabel()
    {
        m_orientationLabel.caption("Orientation:");
        m_orientationLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildOrientationGroup()
    {
        addOrientationCheckbox(string("Portrait"), string("portrait"));
        addOrientationCheckbox(string("Landscape"), string("landscape"));
        addOrientationCheckbox(string("Reverse Portrait"), string("portraitReverse"));
        addOrientationCheckbox(string("Reverse Landscape"), string("landscapeReverse"));
    }

    void PageSetup::addOrientationCheckbox(const std::string& label, 
        const std::string& groupLabel)
    {
        m_orientations.push_back(make_shared<checkbox>(m_paperGroup));
        m_orientations.back()->caption(label);
        m_paperGroup[groupLabel.c_str()] << *m_orientations.back();
        m_orientationGroup.add(*m_orientations.back());
    }

    void PageSetup::setAllowableOrientations()
    {
        // disable all orientations
        for (auto orient: m_orientations)
        {
            orient->enabled(false);
        }
        // enable orientations supported by the printer
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto orientations = printer->getOrientations();
        for (auto orientation: orientations.getOrientations())
        {
            auto orientationNum = orientation->get_orientation_number();
            auto orientationCheckboxNum = orientationNum - PORTRAIT;
            m_orientations[orientationCheckboxNum]->enabled(true);
        }

        // set default orientation button
        auto defOrientation = m_settings.get_page_orientation();
        if (defOrientation)
        {
            auto defOrientationNum = defOrientation->get_orientation_number();
            auto orientationCheckboxNum = defOrientationNum - PORTRAIT;
            m_orientations[orientationCheckboxNum]->check(true);
        }
        else
        {
            for (auto orientation: m_orientations)
            {
                if (orientation->enabled())
                {
                    orientation->check(true);
                    break;
                }
            }
        }
    }

    void PageSetup::populatePaperSourceCombox()
    {
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto paperSources = printer->getMediaSources();
        auto sources = paperSources.get_sources();
        auto mediaSource = m_settings.get_media_source();
        m_paperSourceCombox.clear();
        if (sources.size() < 0 && mediaSource) {
            m_paperSourceCombox.enabled(true);
            size_t source = 0;
            for (int src = 0; src < sources.size(); ++src)
            {
                m_paperSourceCombox.push_back(sources[src].get_source());
                if (mediaSource.value().get_source() == sources[src].get_source())
                {
                    source = src;
                }
            }
            m_paperSourceCombox.option(source);
        }
        else
        {
            m_paperSourceCombox.enabled(false);
        }
    }

    void PageSetup::printer_selected(const arg_combox &ar_cbx)
    {
        m_printer = m_printerCombox.option();
        updatePrinterGroup();
        updatePaperGroup();
    }

    void PageSetup::updatePrinterGroup()
    {
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        m_printerStatus.caption(printer->get_printer_state());
        m_printerType.caption(printer->get_printer_make_and_model());
        m_printerWhere.caption(printer->get_printer_location());
        m_printerComment.caption(printer->get_printer_info());
    }

    void PageSetup::updatePaperGroup()
    {
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto mediaSizes = printer->getMediaSizes();
        m_borderlessCheckbox.enabled(mediaSizes.contains_borderless_paper());
        if (m_printer == m_settings.get_printer())
        {
            m_borderlessCheckbox.check(m_settings.get_borderless());
        }
        else
        {
            m_borderlessCheckbox.check(false);
        }
        populatePaperSizeCombox();
        populatePaperSourceCombox();
        setAllowableOrientations();

    }

    void PageSetup::on_borderlessChecked(const arg_checkbox& arg)
    {
        populatePaperSizeCombox();
    }

    void PageSetup::paper_size_selected(const nana::arg_combox &arg)
    {
        size_t option = m_paperSizeCombox.option();
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto paperSizeTranslatedName = m_paperSizeCombox.text(option);
        auto mediaSizes = printer->getMediaSizes();

        auto mediaSize = mediaSizes.get_media_size_by_translated_name_and_border(
            paperSizeTranslatedName, m_borderlessCheckbox.checked());
        if(mediaSize)
        {
            stringstream ss;
            ss << mediaSize.value().get_width() / 100 << " x " 
                << mediaSize.value().get_height()  / 100 << " mm";
            m_paperSize.caption(ss.str());
        }
    }

    void PageSetup::paper_source_selected(const nana::arg_combox &ar_cbx)
    {
        size_t option = m_paperSourceCombox.option();
        auto source = m_paperSourceCombox.text(option);
    }

    void PageSetup::buildButtons()
    {
        buildCancelButton();
        buildApplyButton();

    }

    void PageSetup::buildCancelButton()
    {
        m_cancel.caption("Cancel");
        m_cancel.events().click([this](){close();});
    }

    void PageSetup::buildApplyButton()
    {
        m_apply.caption("Apply");
        m_apply.events().click([this]() {apply_clicked();});
    }

    void PageSetup::apply_clicked()
    {
        m_settings.set_printer(m_printer);
        m_settings.set_borderless(m_borderlessCheckbox.checked());
        auto sizeOption = m_paperSizeCombox.option();
        auto size = m_paperSizeCombox.text(sizeOption);
        auto printer = m_settings.get_printers().getPrinters()[m_printer];
        auto mediaSizes = printer->getMediaSizes();
        auto mediaSize = mediaSizes.get_media_size_by_translated_name_and_border(size,
            m_borderlessCheckbox.checked());
        if(mediaSize)
        {
            m_settings.set_media_size(mediaSize.value());
        }
        if(m_paperSourceCombox.enabled())
        {
            auto source = m_paperSourceCombox.option();
            m_settings.set_media_source(media_source(m_paperSourceCombox.text(source)));
        }
        auto orientation = m_orientationGroup.checked();
        m_settings.set_page_orientation(page_orientation(orientation + PORTRAIT));

        close();
    }

    DialogStatus PageSetup::run()
    {
         modality();
        return DialogStatus::apply;
    }
}