#ifndef NANAPRINT_PRINTSETTINGS_H
#define NANAPRINT_PRINTSETTINGS_H

/**
 *  \file printsettings.h
 *  \brief This file provides a PrintSettings class required by nanaprint
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

#include <vector>
#include <memory>
#include "printers.h"
#include "mediasize.h"

namespace nanaprint
{
    class PrintSettings
    {
        public:
            // PrintSettings set up for default printer (or first printer if no default)
            PrintSettings(const Printers& printers);
            virtual ~PrintSettings() {}
            const std::vector<std::shared_ptr<Printer>>& getPrinters() const
                { return m_printers; }
            void set_printer(int printer);
            int get_printer() const { return m_printer; }
            void set_media_size(const MediaSize& mediaSize);
            const MediaSize& get_media_size() const { return m_mediaSize; }
            void set_finishings(const Finishings& finishings);
            const Finishings& get_finishings() const { return m_finishings; }
            void set_media_source(const MediaSource& source);
            const MediaSource& get_media_source() { return m_mediaSource; }
            void set_media_type(const MediaType& mediaType);
            const MediaType& get_media_type() { return m_mediaType; }
            void set_page_orientation(const PageOrientation& orientation);
            const PageOrientation& get_page_orientation() const { return m_orientation; }
            void set_color_mode(const ColorMode& colorMode);
            const ColorMode& get_color_mode() const { return m_colorMode; }
            void set_print_quality(const PrintQuality& quality);
            const PrintQuality& get_print_quality() const { return m_printQuality; }
            void set_side(const Side& side);
            const Side& get_side() const { return m_side; }
            bool can_print_multiple_copies() { return m_canPrintMultipleCopies; }
        protected:
            int get_default_printer_number() const;
            void set_default_settings(int printerNum);
            std::vector<std::shared_ptr<Printer>> m_printers;
            int m_printer;
            MediaSize m_mediaSize;
            Finishings m_finishings;
            MediaSource m_mediaSource;
            MediaType m_mediaType;
            PageOrientation m_orientation;
            ColorMode m_colorMode;
            PrintQuality m_printQuality;
            Side m_side;
            bool m_canPrintMultipleCopies;
    };
}

#endif       // NANAPRINT_PRINTSETTINGS_H