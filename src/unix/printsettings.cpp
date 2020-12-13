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
    PrintSettings::PrintSettings(const Printers& printers)
        : m_printers(printers.getPrinters()), m_printer(INT_MAX),
            m_mediaSize({"None", 0, 0, 0, 0, 0, 0}), m_mediaSource("None"),
            m_mediaType("None"), m_borderless(false)
    {

    }

    void PrintSettings::set_printer(int printer)
    {
        if(printer == m_printer)
            return;
        set_default_settings(printer);
    }

    // get the index of the default printer, or return 0 if there is no default
    int PrintSettings::get_default_printer_number() const
    {
        int printerNum = 0;
        for (printerNum = 0; printerNum < m_printers.size(); ++printerNum)
        {
            if (m_printers[printerNum]->isDefault())
            {
                return printerNum;
            }
        }
        return printerNum;
    }

    // fill the print settings with the printer's defaults
    void PrintSettings::set_default_settings(int printerNum)
    {
        m_printer = printerNum;
        set_borderless(false);
        set_media_size(m_printers[m_printer]->getDefaultMediaSize());
        set_finishings(m_printers[m_printer]->getDefaultFinishings());
        set_media_source(m_printers[m_printer]->getDefaultMediaSource());
        set_media_type(m_printers[m_printer]->getDefaultMediaType()),
        set_page_orientation(m_printers[m_printer]->getDefaultOrientation());
        set_color_mode(m_printers[m_printer]->getDefaultColorMode());
        set_print_quality(m_printers[m_printer]->getDefaultPrintQuality());
        set_side(m_printers[m_printer]->getDefaultSide());
        m_canPrintMultipleCopies = m_printers[m_printer]->canPrintMultipleCopies();
    }

    void PrintSettings::set_borderless(bool borderless)
    {
        m_borderless = borderless;
    }

    void PrintSettings::set_media_size(const MediaSize& mediaSize)
    {
        m_mediaSize = mediaSize;
    }

    void PrintSettings::set_finishings(const Finishings& finishings)
    {
        m_finishings = finishings;
    }

    void PrintSettings::set_media_source(const MediaSource& source)
    {
        m_mediaSource = source;
    }

    void PrintSettings::set_media_source(const std::string& source)
    {
        m_mediaSource = source;
    }
    
    void PrintSettings::set_media_type(const MediaType& mediaType)
    {
        m_mediaType = mediaType;
    }

    void PrintSettings::set_page_orientation(const optional<PageOrientation>& orientation)
    {
        m_orientation = orientation;
    }

    void PrintSettings::set_color_mode(const ColorMode& colorMode)
    {
        m_colorMode = colorMode;
    }

    void PrintSettings::set_print_quality(const PrintQuality& quality)
    {
        m_printQuality = quality;
    }

    void PrintSettings::set_side(const Side& side)
    {
        m_side = side;
    }
}
