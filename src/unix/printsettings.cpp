/**
 *  \brief A PrintSettings class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printsettings.cpp
 */

#include <climits>
#include "printsettings.h"

using namespace std;
using namespace nanaprint;

namespace nanaprint
{
    print_settings::print_settings()
        : m_mediaSize({"None", 0, 0, 0, 0, 0, 0}), m_mediaSource("None"),
            m_mediaType("None"), m_borderless(false)
    {
        m_printer = m_printers.getDefaultPrinterNumber();
        set_default_settings(m_printer);
    }

    void print_settings::set_printer(int printer)
    {
        if(printer == m_printer)
            return;
        set_default_settings(printer);
    }

    // get the index of the default printer, or return 0 if there is no default
    int print_settings::get_default_printer_number() const
    {
        int printerNum = 0;
        auto printers = m_printers.getPrinters();
        for (printerNum = 0; printerNum < printers.size(); ++printerNum)
        {
            if (printers[printerNum]->is_default())
            {
                return printerNum;
            }
        }
        return printerNum;
    }

    // fill the print settings with the printer's defaults
    void print_settings::set_default_settings(int printerNum)
    {
        m_printer = printerNum;
        auto printers = m_printers.getPrinters();
        set_borderless(false);
        set_media_size(printers[m_printer]->get_default_media_size());
        set_finishings(printers[m_printer]->get_default_finishings());
        set_media_source(printers[m_printer]->get_default_media_source());
        set_media_type(printers[m_printer]->get_default_media_type()),
        set_page_orientation(printers[m_printer]->get_default_orientation());
        set_color_mode(printers[m_printer]->get_default_color_mode());
        set_print_quality(printers[m_printer]->get_default_print_quality());
        set_side(printers[m_printer]->get_default_side());
        m_canPrintMultipleCopies = printers[m_printer]->canPrintMultipleCopies();
    }

    void print_settings::set_borderless(bool borderless)
    {
        m_borderless = borderless;
    }

    void print_settings::set_media_size(const std::optional<media_size>& mediaSize)
    {
        m_mediaSize = mediaSize;
    }

    void print_settings::set_finishings(const finishings finishings)
    {
        m_finishings = finishings;
    }

    void print_settings::set_media_source(const std::optional<media_source>& source)
    {
        m_mediaSource = source;
    }

    void print_settings::set_media_source(const std::string& source)
    {
        m_mediaSource = source;
    }
    
    void print_settings::set_media_type(const std::optional<media_type>& mediaType)
    {
        m_mediaType = mediaType;
    }

    void print_settings::set_page_orientation(const optional<page_orientation>& orientation)
    {
        m_orientation = orientation;
    }

    void print_settings::set_color_mode(const std::optional<color_mode>& colorMode)
    {
        m_colorMode = colorMode;
    }

    void print_settings::set_print_quality(const std::optional<print_quality>& quality)
    {
        m_printQuality = quality;
    }

    void print_settings::set_side(const std::optional<side>& sid)
    {
        m_side = sid;
    }
}
