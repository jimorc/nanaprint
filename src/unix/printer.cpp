/**
 *  \brief A Printer class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printer.cpp
 */

#include <iostream>
#include <vector>
#include <string>
#include <regex>
#include <memory>
#include "printer.h"

using namespace std;
using namespace nanaprint;

constexpr size_t RESOURCE_SIZE = 200;          // sets size of resources returned by cupsConnectDest
constexpr int MAX_CONNECT_ATTEMPT_TIME = 5000; // max allowed time for printer connect in ms

namespace nanaprint
{
    Printer::Printer(cups_dest_t* dest)
        : m_dest(dest),
            m_defaultMediaSize(nullopt),
            m_defaultMediaType(nullopt),
            m_defaultMediaSource(media_source("None"))
    {
        populate_media_sizes();
        populate_default_media_size();
        populate_finishings();
        populate_default_finishings();
        populate_media_sources();
        populate_default_media_source();
        populate_media_types();
        populate_default_media_type();
        populate_orientations();
        populate_default_orientation();
        populate_color_modes();
        populate_default_color_mode();
        populate_print_qualities();
        populate_default_print_quality();
        populate_sides();
        populate_default_side();
    }

    std::shared_ptr<Printer> Printer::create(cups_dest_t *dest)
    {
        char resource[RESOURCE_SIZE];
        http_t *http = cupsConnectDest(dest, CUPS_DEST_FLAGS_DEVICE, MAX_CONNECT_ATTEMPT_TIME,
                                        NULL, resource, RESOURCE_SIZE, NULL, NULL);
        return std::make_shared<Printer>(Printer(dest));
    }

    std::map<std::string, std::string> Printer::get_options() const
    {
        map<string, string> opts;
        for (int i = 0; i < m_dest->num_options; ++i)
        {
            string option = string(m_dest->options[i].name);
            string value = string(m_dest->options[i].value);
            if (option == "printer-state")
            {
                opts[option] = get_printer_state_string(value);
            }
            else if (option == "printer-type")
            {
                opts[option] = get_printer_type_string(value);
            }
            else
            {
                opts[string(m_dest->options[i].name)] = value;
            }
        }
        return opts;
    }

    const string Printer::get_printer_state_string(string value) const
    {
        int intState = atoi(value.c_str());
        string state;
        switch (intState)
        {
        case 3:
            state = "Idle";
            break;
        case 4:
            state = "Printing";
            break;
        case 5:
            state = "Stopped";
            break;
        default:
            state = "Unknown state: " + value;
            break;
        }
        return state;
    }

    const string Printer::get_printer_type_string(const string& value) const
    {
        vector<string> types;
        int intValue = atoi(value.c_str());
        if (intValue & CUPS_PRINTER_FAX)
        {
            types.push_back("Fax");
        }
        if (intValue & CUPS_PRINTER_REMOTE)
        {
            types.push_back("Remote");
        }
        if (intValue & CUPS_PRINTER_DISCOVERED)
        {
            types.push_back("Networked");
        }
        if (intValue & CUPS_PRINTER_BW)
        {
            types.push_back("B&W");
        }
        if (intValue & CUPS_PRINTER_COLOR)
        {
            types.push_back("Color");
        }
        if (intValue & CUPS_PRINTER_DUPLEX)
        {
            types.push_back("Two-Sided Printing");
        }
        if (intValue & CUPS_PRINTER_STAPLE)
        {
            types.push_back("Can staple output");
        }
        if (intValue & CUPS_PRINTER_COLLATE)
        {
            types.push_back("Can collate copies");
        }
        if (intValue & CUPS_PRINTER_PUNCH)
        {
            types.push_back("Can punch output");
        }
        if (intValue & CUPS_PRINTER_COVER)
        {
            types.push_back("Can cover output");
        }
        if (intValue & CUPS_PRINTER_BIND)
        {
            types.push_back("Can bind output");
        }
        if (intValue & CUPS_PRINTER_SORT)
        {
            types.push_back("Can sort output");
        }
        if (intValue & CUPS_PRINTER_SMALL)
        {
            types.push_back("Can print on Letter/Legal/A4-size media");
        }
        if (intValue & CUPS_PRINTER_MEDIUM)
        {
            types.push_back("Can print on Tabloid/B/C/A3/A2-size media");
        }
        if (intValue & CUPS_PRINTER_LARGE)
        {
            types.push_back("Can print on D/E/A1/A0-size media");
        }
        if (intValue & CUPS_PRINTER_VARIABLE)
        {
            types.push_back("Can print on rolls and custom-size media");
        }
        string type;
        for (auto printerType : types)
        {
            if(type.size() != 0)
            {
                type += ", ";
            }
            type += printerType;
        }
        return type;
    }

    void Printer::populate_media_sizes()
    {
        if(m_mediaSizes.size() == 0)
        {
            cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
            int mSizeCount = cupsGetDestMediaCount(CUPS_HTTP_DEFAULT, m_dest, info, 0);
            cups_size_t size;
            for(int i = 0; i < mSizeCount; ++i)
            {
                int result = cupsGetDestMediaByIndex(CUPS_HTTP_DEFAULT, m_dest, info, i, 0, &size);
                m_mediaSizes.push_back((media_size(
                    size.media, size.width, size.length, size.bottom, size.left,
                    size.right, size.top)));
            }
        }
    }

    const media_sizes& Printer::get_media_sizes() const noexcept
    {
        return m_mediaSizes;
    }

    void Printer::populate_default_media_size()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        cups_size_t size;
        int result = cupsGetDestMediaDefault(CUPS_HTTP_DEFAULT, m_dest, info, 0, &size);
        if(result)
        {
            m_defaultMediaSize = media_size(size.media, size.width, size.length,
                size.bottom, size.left, size.right, size.top);
        }
        else
        {
            m_defaultMediaSize = nullopt;
        }
    }

    const std::optional<media_size>& Printer::get_default_media_size() const noexcept
        {
            return m_defaultMediaSize;
        }

    const finishings& Printer::get_finishings() const noexcept
    {
        return m_finishings;
    }

    const finishings& Printer::get_default_finishings() const noexcept
    {
        return m_defaultFinishings;        
    }

    bool Printer::can_print_multiple_copies() const
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        return cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest,
            info, CUPS_COPIES, NULL);
    }

    void Printer::populate_finishings()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_FINISHINGS, NULL))
        {
            ipp_attribute_t *finishings = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_FINISHINGS);
            int count = ippGetCount(finishings);
            for (int i = 0; i < count; ++i)
            {
                int finish = ippGetInteger(finishings, i);
                set_finishing(finish);
            }
        }
    }

    void Printer::set_finishing(int finish)
    {
        char fin[10];       // should only need to be 2 or 3 characters long
        sprintf(fin, "%d", finish);
        m_finishings.set_finishing(fin);
    }

    void Printer::populate_media_sources()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_FINISHINGS, NULL))
        {
            ipp_attribute_t *source = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_MEDIA_SOURCE);
            int count = ippGetCount(source);
            for (int i = 0; i < count; ++i)
            {
                const char *src = ippGetString(source, i, NULL);
                m_mediaSources.push_back(media_source(src));
            }
        }   
    }

    const media_sources Printer::get_media_sources() const noexcept
    {
        return m_mediaSources;
    }

    void Printer::populate_default_finishings()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);

        const char *defaultFinishings =
            cupsGetOption(CUPS_FINISHINGS, m_dest->num_options,
                m_dest->options);
        ipp_attribute_t *defaultFinishings2 =
            cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_FINISHINGS);
        
        if(defaultFinishings != NULL)
        {
            regex rgx("[0-9]*");
            smatch match;

            string finishings = defaultFinishings;
            if( regex_search(finishings, match, rgx))
            {
                for (auto m: match)
                {
                    m_defaultFinishings.set_finishing(m);
                }
            }
        }
        else
        {
            int count = ippGetCount(defaultFinishings2);
            for (int i = 0; i < count; ++i)
            {
                int finish = ippGetInteger(defaultFinishings2, i);
                char fin[10];       // 2 or 3 would be enough
                sprintf(fin, "%d", finish);
                m_defaultFinishings.set_finishing(fin);
            }
        }
    }

    void Printer::populate_default_media_source()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultSource =
            cupsGetOption(CUPS_MEDIA_SOURCE, m_dest->num_options, m_dest->options);
        if (defaultSource != nullptr)
        {
            m_defaultMediaSource = media_source(defaultSource);
        }
        else
        {
            ipp_attribute_t *source = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_MEDIA_SOURCE);
            int count = ippGetCount(source);
            if (count != 0)
            {
                const char *src = ippGetString(source, 0, NULL);
                m_defaultMediaSource = media_source(src);
            }
            else
            {
                m_defaultMediaSource = nullopt;
            }
        }
    }

    const std::optional<media_source>& Printer::get_default_media_source() const noexcept
    {
        return m_defaultMediaSource;
    }

    void Printer::populate_media_types()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_MEDIA_TYPE, NULL))
        {
            ipp_attribute_t *type = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_MEDIA_TYPE);
            int count = ippGetCount(type);
            for (int i = 0; i < count; ++i)
            {
                const char *mediaType = ippGetString(type, i, NULL);
                m_mediaTypes.push_back(media_type(mediaType));
            }
        }
    }

    const media_types& Printer::get_media_types() const noexcept
    {
        return m_mediaTypes;
    }

    void Printer::populate_default_media_type()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultType =
            cupsGetOption(CUPS_MEDIA_TYPE, m_dest->num_options, m_dest->options);
        if(defaultType != nullptr)
        {
            m_defaultMediaType = media_type(defaultType);
        }
        else
        {
            ipp_attribute_t *type = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_MEDIA_TYPE);
            int count = ippGetCount(type);
            if (count != 0)
            {
                const char *defaultType = ippGetString(type, 0, NULL);
                m_defaultMediaType = media_type(defaultType);
            }
            else
            {
                m_defaultMediaType = nullopt;
            }
            
        }
    }

    const std::optional<media_type>& Printer::get_default_media_type() const noexcept
    {
        return m_defaultMediaType;
    }

    void Printer::populate_orientations()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_ORIENTATION, NULL))
        {
            ipp_attribute_t *orientations = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_ORIENTATION);
            int count = ippGetCount(orientations);
            for (int i = 0; i < count; ++i)
            {
                int orientation = ippGetInteger(orientations, i);
                m_orientations.push_back(page_orientation(orientation));
            }
        }
    }
    const page_orientations& Printer::get_orientations() const noexcept
    {
        return m_orientations;
    }

    void Printer::populate_default_orientation()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultOrientation =
            cupsGetOption(CUPS_ORIENTATION, m_dest->num_options, m_dest->options);
        if (defaultOrientation != nullptr)
        {
            int orientation = stoi(defaultOrientation);
            m_defaultOrientation = page_orientation(orientation);
        }
        else
        {
            ipp_attribute_t *defOrientation = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_ORIENTATION);
            int count = ippGetCount(defOrientation);
            if (count != 0)
            {
                int defaultOr = ippGetInteger(defOrientation, 0);
                if(defaultOr != 0)
                {
                    m_defaultOrientation = page_orientation(defaultOr);
                }
            }
            else
            {
                m_defaultOrientation = nullopt;
            }
            
        }
    }
    const optional<page_orientation>& Printer::get_default_orientation() const noexcept
    {
        return m_defaultOrientation;
    }

    void Printer::populate_color_modes()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_PRINT_COLOR_MODE, NULL))
        {
            ipp_attribute_t *colorModes = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_PRINT_COLOR_MODE);
            int count = ippGetCount(colorModes);
            for (int i = 0; i < count; ++i)
            {
                const char *colorMode = ippGetString(colorModes, i, NULL);
                m_colorModes.push_back(color_mode(colorMode));
            }
        }
    }
    const color_modes& Printer::get_color_modes() const noexcept
    {
        return m_colorModes;
    }

    void Printer::populate_default_color_mode()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultColorMode =
            cupsGetOption(CUPS_PRINT_COLOR_MODE, m_dest->num_options, m_dest->options);
        if (defaultColorMode != nullptr)
        {
            m_defaultColorMode = color_mode(defaultColorMode);
        }
        else
        {
            ipp_attribute_t *defColorMode = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_PRINT_COLOR_MODE);
            int count = ippGetCount(defColorMode);
            if (count != 0)
            {
                const char *defaultColorMode = ippGetString(defColorMode, 0, NULL);
                m_defaultColorMode = color_mode(defaultColorMode);
            }
            else
            {
                m_defaultColorMode = nullopt;
            }
        }
    }

    const std::optional<color_mode>& Printer::get_default_color_mode() const noexcept
    {
        return m_defaultColorMode;
    }

    void Printer::populate_print_qualities()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_PRINT_QUALITY, NULL))
        {
            ipp_attribute_t *qualities = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_PRINT_QUALITY);
            int count = ippGetCount(qualities);
            for (int i = 0; i < count; ++i)
            {
                int quality = ippGetInteger(qualities, i);
                m_printQualities.push_back(print_quality(quality));
            }
        }
    }
    const print_qualities& Printer::get_print_qualities() const noexcept
    {
        return m_printQualities;
    }

    void Printer::populate_default_print_quality()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultQuality =
            cupsGetOption(CUPS_PRINT_QUALITY, m_dest->num_options, m_dest->options);
        if (defaultQuality != nullptr)
        {
            int quality = stoi(defaultQuality);
            m_defaultPrintQuality = print_quality(quality);
        }
        else
        {
            ipp_attribute_t *defQuality = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_PRINT_QUALITY);
            int count = ippGetCount(defQuality);
            if (count != 0)
            {
                int defaultQuality = ippGetInteger(defQuality, 0);
                m_defaultPrintQuality = print_quality(defaultQuality);
            }
            else
            {
                m_defaultPrintQuality = nullopt;
            }
        }   
    }
    const std::optional<print_quality>& Printer::get_default_print_quality() const noexcept
    {
        return m_defaultPrintQuality;
    }

    void Printer::populate_sides()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, info, CUPS_SIDES, NULL))
        {
            ipp_attribute_t *sides = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_SIDES);
            int count = ippGetCount(sides);
            for (int i = 0; i < count; ++i)
            {
                const char *sid = ippGetString(sides, i, NULL);
                m_sides.push_back(side(sid));
            }
        }
    }
    
    const sides& Printer::get_sides() const noexcept
    {
        return m_sides;
    }

    void Printer::populate_default_side()
    {
        cups_dinfo_t *info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
        const char *defaultSide =
            cupsGetOption(CUPS_SIDES, m_dest->num_options, m_dest->options);
        if (defaultSide != nullptr)
        {
            m_defaultSide = side(defaultSide);
        }
        else
        {
            ipp_attribute_t *defSide = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                info, CUPS_SIDES);
            int count = ippGetCount(defSide);
            if (count != 0)
            {
                const char *defaultSide = ippGetString(defSide, 0, NULL);
                    m_defaultSide = side(defaultSide);
            }
            else
            {
                m_defaultSide = nullopt;
            }
        }   
    }

    const std::optional<side>& Printer::get_default_side() const noexcept
    {
        return m_defaultSide;
    }

    const std::string Printer::get_printer_state() const
    {
        string printerState;
        const char* printerUri = cupsGetOption("device-uri", m_dest->num_options, m_dest->options);
        regex hostRegex("^[a-zA-Z]+://([0-9a-zA-Z]+(\\.[0-9a-zA-Z]+)*)");
        string uri(printerUri);
        smatch match;
        if (regex_search(uri, match, hostRegex) && match.size() > 1)
        {
            string host = match.str(1);
            ipp_t *request, *response;
            static const char * const requested_attributes[] =
            {
                "printer-state",
                "printer-state-reasons",
                "printer-is-accepting-jobs",
                "printer-is-shared"
            };

            http_t *http = httpConnect2(host.c_str(), 631, NULL, AF_UNSPEC, HTTP_ENCRYPTION_IF_REQUESTED, 1, 30000, NULL);

            request = ippNewRequest(IPP_OP_GET_PRINTER_ATTRIBUTES);
            ippAddString(request, IPP_TAG_OPERATION, IPP_TAG_URI, "printer-uri", NULL, uri.c_str());
            ippAddStrings(request, IPP_TAG_OPERATION, IPP_TAG_KEYWORD, "requested-attributes", (int)(sizeof(requested_attributes) / sizeof(requested_attributes[0])), NULL, requested_attributes);

            response = cupsDoRequest(http, request, "/ipp/print");

            ipp_attribute_t *attr;
            const char *name;
            char val[2048];
            map<string, string> optMap;

            for (attr = ippFirstAttribute(response); attr; attr = ippNextAttribute(response))
            {
                string name = ippGetName(attr);

                if (!name.empty())
                {
                    ippAttributeString(attr, val, sizeof(val));
                    optMap[name] = string(val);
                }
            }
            printerState = optMap["printer-state"];
            if (printerState.empty())
            {
                printerState = u8"offline";
            }
            string reasons = optMap["printer-state-reasons"];
            if (!reasons.empty() && reasons != "none")
            {
                printerState += ", " + reasons;
            }
            string accepting = optMap["printer-is-accepting-jobs"];
            if (!accepting.empty() && accepting == "true")
            {
                printerState += ", accepting jobs";
            }
            else
            {
                printerState += ", not accepting jobs";
            }
            string shared = optMap["printer-is-shared"];
            if (!shared.empty() && shared == "true")
            {
                printerState += ", shared";
            }
            else
            {
                printerState += ", not shared";
            }
        }
        return printerState;
    }

    const std::string Printer::get_printer_make_and_model() const
    {
        return get_options()["printer-make-and-model"];
    }

    const std::string Printer::get_printer_location() const
    {
        return get_options()["printer-location"];
    }

    const std::string Printer::get_printer_info() const
    {
        return get_options()["printer-type"];
    }
}       