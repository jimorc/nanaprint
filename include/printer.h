#ifndef NANAPRINT_PRINTER_H
#define NANAPRINT_PRINTER_H
/**
 *  \file printer.h
 *  \brief This file provides printer class and data structures required by nanaprint
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

#include <iostream>
#include <memory>
#include <string>
#include <map>
#include <optional>
#include <cups/cups.h>
#include "mediasizes.h"
#include "pageorientation.h"
#include "printquality.h"
#include "finishings.h"
#include "mediasource.h"
#include "mediatype.h"
#include "colormode.h"
#include "side.h"

namespace nanaprint
{
#ifdef WIN32
#else       // WIN32
    typedef cups_dest_t* handle;
#endif      // WIN32
    class printer
    {
        public:
            printer(const printer&) = delete;
            printer(printer&&) = default;
            printer& operator=(const printer&) = delete;
            printer& operator=(printer&&) = delete;
            virtual ~printer();
            static std::shared_ptr<printer> create(handle handle);

            handle get_handle() const noexcept;
            const std::string get_name() const;
            bool is_default() const noexcept;
            std::map<std::string, std::string> get_options() const;
            const media_sizes& get_media_sizes() const noexcept;
            const std::optional<media_size>& get_default_media_size() const noexcept;
            bool can_print_multiple_copies() const;
            const finishings& get_finishings() const noexcept;
            const finishings& get_default_finishings() const noexcept;
            const media_sources get_media_sources() const noexcept;
            const std::optional<media_source>& get_default_media_source() const noexcept;
            const media_types& get_media_types() const noexcept;
            const std::optional<media_type>& get_default_media_type() const noexcept;
            const page_orientations& get_orientations() const noexcept;
            const std::optional<page_orientation>& get_default_orientation() const noexcept;
            const color_modes& get_color_modes() const noexcept;
            const std::optional<color_mode>& get_default_color_mode() const noexcept;
            const print_qualities& get_print_qualities() const noexcept;
            const std::optional<print_quality>& get_default_print_quality() const noexcept;
            const sides& get_sides() const noexcept;
            const std::optional<side>& get_default_side() const noexcept;

            const std::string get_printer_state() const;
            const std::string get_printer_make_and_model() const;
            const std::string get_printer_location() const;
            const std::string get_printer_info() const;

        protected:
            printer(handle dest);

        private:
            class impl;     // forward declaration
            std::unique_ptr<impl> m_pImpl;
    };

    std::ostream& operator<<(std::ostream& os, const printer& prtr);
}

#endif      // NANAPRINT_PRINTER_H