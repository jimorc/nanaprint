#ifndef NANAPRINT_PRINTDIALOGSETTINGS_H
#define NANAPRINT_PRINTDIALOGSETTINGS_H

/**
 *  \file printdialogsettings.h
 *  \brief This file provides a PrintDialogSettings class required by nanaprint
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
#include <optional>
#include "printers.h"
#include "mediasize.h"
#include "printsettings.h"

namespace nanaprint
{
    class PrintDialogSettings
    {
        public:
            // PrintSettings set up for default printer (or first printer if no default)
            PrintDialogSettings(print_settings& settings);
            virtual ~PrintDialogSettings() {}
            void set_printer(int printer);
            int get_printer() const { return m_printer; }
            void set_borderless(bool borderless);
            const bool get_borderless() const { return m_borderless; }
            void set_media_size(const std::optional<media_size>& mediaSize);
            const std::optional<media_size>& get_media_size() const { return m_mediaSize; }
            void set_finishings(const finishings finishings);
            const finishings& get_finishings() const { return m_finishings; }
            void set_media_source(const std::optional<media_source>& source);
            void set_media_source(const std::string& source);
            const std::optional<media_source>& get_media_source() { return m_mediaSource; }
            void set_media_type(const std::optional<media_type>& mediaType);
            const std::optional<media_type>& get_media_type() { return m_mediaType; }
            void set_page_orientation(const std::optional<page_orientation>& orientation);
            const std::optional<page_orientation>& get_page_orientation() const { return m_orientation; }
            void set_color_mode(const std::optional<color_mode>& colorMode);
            const std::optional<color_mode>& get_color_mode() const { return m_colorMode; }
            void set_print_quality(const std::optional<print_quality>& quality);
            const std::optional<print_quality>& get_print_quality() const { return m_printQuality; }
            void set_side(const std::optional<side>& side);
            const std::optional<side>& get_side() const { return m_side; }
            bool can_print_multiple_copies() const { return m_canPrintMultipleCopies; }
        protected:
            void set_default_settings(int printerNum);

            print_settings& m_settings;
            int m_printer;
            bool m_borderless;
            std::optional<media_size> m_mediaSize;
            finishings m_finishings;
            std::optional<media_source> m_mediaSource;
            std::optional<media_type> m_mediaType;
            std::optional<page_orientation> m_orientation;
            std::optional<color_mode> m_colorMode;
            std::optional<print_quality> m_printQuality;
            std::optional<side> m_side;
            bool m_canPrintMultipleCopies;
    };
}

#endif       // NANAPRINT_PRINTDIALOGSETTINGS_H