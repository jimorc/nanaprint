#ifndef PRINTER_H
#define PRINTER_H

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

#include <memory>
#include <string>
#include <map>
#include <cups/cups.h>
#include "mediasizes.h"

namespace nanaprint
{
    class Printer
    {
        public:
            virtual ~Printer() {}
            static std::shared_ptr<Printer> create(cups_dest_t* dest);

            std::string getName() { return std::string(m_dest->name); }
            bool isDefault() { return m_dest->is_default; }
            std::map<std::string, std::string> getOptions();
            std::vector<std::string> getMediaSizeNames();
            std::vector<std::shared_ptr<MediaSize>> getMediaSizes();
            bool canPrintMultipleCopies() const;
            bool noFinishings();
            bool canBind();
            bool canCoverOutput();
            bool canStaple();
            bool canFold();
            bool canPunch();
            bool canTrim();
            bool noDefaultFinishings();
            bool defaultBind();
            bool defaultCoverOutput();
            bool defaultFold();
            bool defaultPunch();
            bool defaultStaple();
            bool defaultTrim();
            std::vector<std::string>& getMediaSources();
            std::string& getDefaultMediaSource();
            std::vector<std::string>& getMediaTypes();
            std::string& getDefaultMediaType();
            std::vector<std::string>& getOrientations();
            std::string& getDefaultOrientation();
            std::vector<std::string>& getColorModes();
            std::string& getDefaultColorMode();
            std::vector<std::string>& getPrintQualities();

        protected:
            Printer(cups_dest_t* dest);

        private:
            std::string getPrinterStateString(std::string value);
            std::string getPrinterTypeString(const std::string value) const;
            void populateMediaSizes();
            void populateFinishings();
            void setFinishing(int finishing);
            void populateDefaultFinishings();
            void setDefaultFinishing(int finishing);
            void populateMediaSources();
            void populateDefaultMediaSource();
            void populateMediaTypes();
            void populateDefaultMediaType();
            void populateOrientations();
            void populateDefaultOrientation();
            void populateColorModes();
            void populateDefaultColorMode();
            void populatePrintQualities();

            cups_dest_t* m_dest;
            MediaSizes m_mediaSizes;

            bool m_gotMediaSources;
            std::vector<std::string> m_mediaSources;
            bool m_gotMediaTypes;
            std::vector<std::string> m_mediaTypes;
            bool m_gotOrientations;
            std::vector<std::string> m_orientations;
            bool m_gotColorModes;
            std::vector<std::string> m_colorModes;
            bool m_gotPrintQualities;
            std::vector<std::string> m_printQualities;
            bool m_gotFinishings;
            bool m_noFinishings;
            bool m_canBind;
            bool m_canCoverOutput;
            bool m_canFold;
            bool m_canPunch;
            bool m_canStaple;
            bool m_canTrim;

            bool m_gotDefaultMediaSource;
            std::string m_defaultMediaSource;
            bool m_gotDefaultMediaType;
            std::string m_defaultMediaType;
            bool m_gotDefaultOrientation;
            std::string m_defaultOrientation;
            bool m_gotDefaultColorMode;
            std::string m_defaultColorMode;
            bool m_gotDefaultFinishings;
            bool m_noDefaultFinishings;
            bool m_defaultBind;
            bool m_defaultCoverOutput;
            bool m_defaultFold;
            bool m_defaultPunch;
            bool m_defaultStaple;
            bool m_defaultTrim;

            static std::map<int, std::string> m_orientationMap;
            static std::map<int, std::string> m_qualityMap;
    };
}

#endif      // PRINTER_H