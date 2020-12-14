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
        : form(parent, {500, 500}), m_settings(settings), m_layout(*this),
            m_printerGroup(*this), m_printerNameLabel(m_printerGroup), m_printerCombox(m_printerGroup),
            m_printerStatusLabel(m_printerGroup), m_printerStatus(m_printerGroup),
            m_printerTypeLabel(m_printerGroup), m_printerType(m_printerGroup),
            m_printerWhereLabel(m_printerGroup), m_printerWhere(m_printerGroup),
            m_printerCommentLabel(m_printerGroup), m_printerComment(m_printerGroup),
            m_paperGroup(*this), m_borderlessCheckbox(m_paperGroup), 
            m_paperSizeLabel(m_paperGroup), m_paperSizeCombox(m_paperGroup),
            m_paperSize(m_paperGroup), m_paperSourceLabel(m_paperGroup),
            m_paperSourceCombox(m_paperGroup), m_orientationLabel(m_paperGroup)

    {
        caption(u8"Page Setup");
        m_layout.div(string("vert gap=10 margin=5") +
            "<printer weight=50%>" +
            "<paper weight = 25%>");

        buildPrinterGroup();
        m_layout["printer"] << m_printerGroup;
        buildPaperGroup();
        m_layout["paper"] << m_paperGroup;
        
        m_layout.collocate();

        // Must set default printer after paper group is created.
        // Otherwise, paper size is not set for default paper size.
        size_t defaultPrinter = m_printers.getDefaultPrinterNumber();
        m_printerCombox.option(defaultPrinter);
     }

    void PageSetup::buildPrinterGroup()
    {
        m_printerGroup.caption("Printer");
        string groupDiv = string("vert gap=5 margin=0 ") +
            "<<weight=10><name weight=20%><printerCombox><weight=10> weight=30>" +
            "<<weight=10><status weight=20%><printerStatus><weight=10> weight=30>" +
            "<<weight=10><type weight=20%><printerType><weight=10> weight=30>" +
            "<<weight=10><where weight=20%><printerWhere><weight=10> weight=30>" +
            "<<weight=10><comment weight=20%><printerComment><weight=10> weight=40>";        
        m_printerGroup.div(groupDiv.c_str());

        buildPrinterNameLabel();
        m_printerGroup["name"] << m_printerNameLabel;

        buildPrinterCombox();
        m_printerGroup["printerCombox"] << m_printerCombox;

        buildPrinterStatusLabel();
        m_printerGroup["status"] << m_printerStatusLabel;

        buildPrinterTypeLabel();
        m_printerGroup["type"] << m_printerTypeLabel;

        buildPrinterWhereLabel();
        m_printerGroup["where"] << m_printerWhereLabel;

        buildPrinterCommentLabel();
        m_printerGroup["comment"] << m_printerCommentLabel;
}

    void PageSetup::buildPrinterNameLabel()
    {
        m_printerNameLabel.caption("Name:");
        m_printerNameLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCombox()
    {
        m_printerCombox.editable(false);
        auto printers = m_printers.getPrinters();
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

    void PageSetup::buildPrinterStatus(size_t printer)
    {
        m_printerStatus.caption(m_printers.getPrinters()[printer]->get_printer_state());
        m_printerStatus.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterTypeLabel()
    {
        m_printerTypeLabel.caption("Type:");
        m_printerTypeLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterType(size_t printer)
    {
        m_printerType.caption(m_printers.getPrinters()[printer]->get_printer_make_and_model());
        m_printerType.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhereLabel()
    {
        m_printerWhereLabel.caption("Location:");
        m_printerWhereLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterWhere(size_t printer)
    {
        m_printerWhere.caption(m_printers.getPrinters()[printer]->get_printer_location());
        m_printerWhere.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterCommentLabel()
    {
        m_printerCommentLabel.caption("Comment:");
        m_printerCommentLabel.text_align(align::left, align_v::center);
    }

    void PageSetup::buildPrinterComment(size_t printer)
    {
        m_printerComment.caption(m_printers.getPrinters()[printer]->get_printer_info());
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

    void PageSetup::populatePaperSizeCombox(size_t printer)
    {
        auto ptr = m_printers.getPrinters()[printer];
        auto paperSizes = ptr->getMediaSizes();
        m_paperSizeCombox.clear();
        bool borderless = m_borderlessCheckbox.checked();
        for (size_t i = 0; i < paperSizes.getSize(); ++i)
        {
            auto mediaSize = paperSizes.getMediaSizes()[i];
            if (mediaSize->isBorderless() == borderless)
            {
                m_paperSizeCombox.push_back(mediaSize->getTranslatedName());
            }
        }
        auto mediaSize = m_settings.get_media_size().getTranslatedName();
        size_t option = 0;
        for (option = 0; m_paperSizeCombox.the_number_of_options(); ++option)
        {
            if (m_paperSizeCombox.text(option) == mediaSize)
                break;
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

    void PageSetup::setAllowableOrientations(size_t printer)
    {
        // disable all orientations
        for (auto orient: m_orientations)
        {
            orient->enabled(false);
        }
        // enable orientations supported by the printer
        auto ptr = m_printers.getPrinters()[printer];
        auto orientations = ptr->getOrientations();
        for (auto orientation: orientations.getOrientations())
        {
            auto orientationNum = orientation->getOrientationNumber();
            auto orientationCheckboxNum = orientationNum - PORTRAIT;
            m_orientations[orientationCheckboxNum]->enabled(true);
        }

        // set default orientation button
        auto defOrientation = m_settings.get_page_orientation();
        if (defOrientation)
        {
            auto defOrientationNum = defOrientation->getOrientationNumber();
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

    void PageSetup::populatePaperSourceCombox(size_t printer)
    {
        auto ptr = m_printers.getPrinters()[printer];
        auto paperSources = ptr->getMediaSources();
        auto sources = paperSources.getSources();
        auto mediaSource = m_settings.get_media_source();
        m_paperSourceCombox.clear();
        if (sources.size() < 0) {
            m_paperSourceCombox.enabled(true);
            size_t source = 0;
            for (int src = 0; src < sources.size(); ++src)
            {
                m_paperSourceCombox.push_back(sources[src]->getSource());
                if (mediaSource.getSource() == sources[src]->getSource())
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
        size_t printer = m_printerCombox.option();
        m_settings.set_printer(printer);
        buildPrinterStatus(printer);
        m_printerGroup["printerStatus"] << m_printerStatus;
        buildPrinterType(printer);
        m_printerGroup["printerType"] << m_printerType;
        buildPrinterWhere(printer);
        m_printerGroup["printerWhere"] << m_printerWhere;
        buildPrinterComment(printer);
        m_printerGroup["printerComment"] << m_printerComment;

        updatePaperGroup(printer);
    }

    void PageSetup::updatePaperGroup(size_t printer)
    {
        auto mediaSizes = m_printers.getPrinters()[printer]->getMediaSizes();
        m_borderlessCheckbox.enabled(mediaSizes.contains_borderless_paper());
        if (printer == m_settings.get_printer())
        {
            m_borderlessCheckbox.check(m_settings.get_borderless());
        }
        else
        {
            m_borderlessCheckbox.check(false);
        }
        populatePaperSizeCombox(printer);
        populatePaperSourceCombox(printer);
        setAllowableOrientations(printer);

    }

    void PageSetup::on_borderlessChecked(const arg_checkbox& arg)
    {
        m_settings.set_borderless(arg.widget->checked());
        populatePaperSizeCombox(m_settings.get_printer());
    }

    void PageSetup::paper_size_selected(const nana::arg_combox &arg)
    {
        size_t option = m_paperSizeCombox.option();
        auto paperSizeTranslatedName = m_paperSizeCombox.text(option);
        auto mediaSizes = m_printers.getPrinters()[m_settings.get_printer()]
            ->getMediaSizes();

        auto mediaSize = mediaSizes.getMediaSizeByTranslatedNameAndBorder(
            paperSizeTranslatedName, m_borderlessCheckbox.checked());
        if(mediaSize)
        {
            m_settings.set_media_size(mediaSize.value());
            stringstream ss;
            ss << mediaSize.value().getWidth() / 100 << " x " 
                << mediaSize.value().getHeight()  / 100 << " mm";
            m_paperSize.caption(ss.str());
        }
    }

    void PageSetup::paper_source_selected(const nana::arg_combox &ar_cbx)
    {
        size_t option = m_paperSourceCombox.option();
        auto source = m_paperSourceCombox.text(option);
        m_settings.set_media_source(source);
    }

    DialogStatus PageSetup::run()
    {
         modality();
        return DialogStatus::apply;
    }
}