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
#include "cups/cups.h"
#include "cups/ppd.h"
#include "printer.h"
#include "values.h"

using namespace std;
using namespace nanaprint;

constexpr size_t RESOURCE_SIZE = 200;          // sets size of resources returned by cupsConnectDest
constexpr int MAX_CONNECT_ATTEMPT_TIME = 5000; // max allowed time for printer connect in ms

namespace nanaprint
{
    class printer::ppd
    {
        private:
            ppd_file_t* m_ppd;
        public:
            ppd(const char* fileName) : m_ppd(nullptr)
            {
                #pragma GCC diagnostic push
                #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
                const char *fname = cupsGetPPD(fileName);
                if (fname)
                {
                    m_ppd = ppdOpenFile(fname);
                }
                #pragma GCC diagnostic pop
            }

            ~ppd() noexcept
            {
                if (m_ppd)
                {
                    #pragma GCC diagnostic push
                    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
                    ppdClose(m_ppd);
                    m_ppd = nullptr;
                    #pragma GCC diagnostic pop
                }
            }

            ppd(ppd&& other)
            {
                m_ppd = other.m_ppd;
                other.m_ppd = nullptr;
            }

            ppd(const ppd&) = delete;
            ppd& operator=(const ppd&) = delete;
            printer::ppd& operator=(ppd&&) = delete;

            std::vector<std::string> get_option(const char* optionName)
            {
                vector<string> optionValues;
                if (m_ppd)
                {
                    #pragma GCC diagnostic push
                    #pragma GCC diagnostic ignored "-Wdeprecated-declarations"
                    ppd_option_t *option = ppdFindOption(m_ppd, "cupsPrintQuality");
                    if (option)
                    {
                        int num_choices = option->num_choices;
                        ppd_choice_t *choices = option->choices;
                        for (int i = 0; i < num_choices; ++i)
                        {
                            optionValues.push_back(string(choices[i].text));
                        }
                    }
                    #pragma GCC diagnostic pop
                }
                return optionValues;
            }
    };

    printer::printer(cups_dest_t *dest)
        : m_dest(dest)
    {
        m_pPpd = make_unique<ppd>(ppd(dest->name));
        m_info = cupsCopyDestInfo(CUPS_HTTP_DEFAULT, m_dest);
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

    printer::~printer() {}

    std::shared_ptr<printer> printer::create(cups_dest_t *dest)
    {
        return std::make_shared<printer>(printer(dest));
    }

    std::vector<std::string> printer::get_cups_string_values(const std::string &cupsValues)
    {
        vector<string> values;
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, m_info, cupsValues.c_str(), NULL))
        {
            ipp_attribute_t *source = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                                                            m_info, cupsValues.c_str());
            int count = ippGetCount(source);
            for (int i = 0; i < count; ++i)
            {
                const char *src = ippGetString(source, i, NULL);
                values.push_back(src);
            }
        }
        return values;
    }

    std::vector<int> printer::get_cups_integer_values(const std::string& cupsValues)
    {
        vector<int> intValues;
        if (cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest, m_info, cupsValues.c_str(), NULL))
        {
            ipp_attribute_t *source = cupsFindDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                                                                m_info, cupsValues.c_str());
            int count = ippGetCount(source);
            for (int i = 0; i < count; ++i)
            {
                int value = ippGetInteger(source, i);
                intValues.push_back(value);
            }
        }
        return intValues;
    }

    optional<string> printer::get_cups_default_string_value(const std::string& cupsValue)
    {
        optional<string> value(nullopt);
        const char *optionValue =
            cupsGetOption(cupsValue.c_str(), m_dest->num_options, m_dest->options);
        if (optionValue != nullptr)
        {
            value = string(optionValue);
        }
        else
        {
            ipp_attribute_t *defaultAttr = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                                                           m_info, cupsValue.c_str());
            int count = ippGetCount(defaultAttr);
            if (count != 0)
            {
                const char *defaultValue = ippGetString(defaultAttr, 0, NULL);
                // found one case where count=1, but defaultValue=nullptr
                value = (defaultValue) ? optional<string>(string(defaultValue)) : nullopt;
            }
            else
            {
                value = nullopt;
            }
        }
        return value;
    }

    optional<int> printer::get_cups_default_integer_value(const std::string& cupsValue)
    {
        optional<int> value;
        int optionValue =
            cupsGetIntegerOption(CUPS_ORIENTATION, m_dest->num_options, m_dest->options);
        if (optionValue != INT32_MIN)
        {
           value = optionValue;
        }
        else
        {
            ipp_attribute_t *defaultAttr = cupsFindDestDefault(CUPS_HTTP_DEFAULT, m_dest,
                m_info, cupsValue.c_str());
            int count = ippGetCount(defaultAttr);
            if (count != 0)
            {
                int defaultValue = ippGetInteger(defaultAttr, 0);
                if (defaultValue != 0)
                {
                    value = defaultValue;
                }
            }
        }
        return value;
    }

    std::map<std::string, std::string> printer::get_options() const
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

    const string printer::get_printer_state_string(string value) const
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

    const string printer::get_printer_type_string(const string &value) const
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
            if (type.size() != 0)
            {
                type += ", ";
            }
            type += printerType;
        }
        return type;
    }

    void printer::populate_media_sizes()
    {
        if (m_mediaSizes.size() == 0)
        {
            int mSizeCount = cupsGetDestMediaCount(CUPS_HTTP_DEFAULT, m_dest, m_info, 0);
            cups_size_t size;
            for (int i = 0; i < mSizeCount; ++i)
            {
                int result = cupsGetDestMediaByIndex(CUPS_HTTP_DEFAULT, m_dest, m_info, i, 0, &size);
                m_mediaSizes.push_back((media_size(
                    size.media, size.width, size.length, size.bottom, size.left,
                    size.right, size.top)));
            }
        }
    }

    const media_sizes &printer::get_media_sizes() const noexcept
    {
        return m_mediaSizes;
    }

    void printer::populate_default_media_size()
    {
        cups_size_t size;
        int result = cupsGetDestMediaDefault(CUPS_HTTP_DEFAULT, m_dest, m_info, 0, &size);
        if (result)
        {
            m_defaultMediaSize = media_size(size.media, size.width, size.length,
                                            size.bottom, size.left, size.right, size.top);
        }
        else
        {
            m_defaultMediaSize = nullopt;
        }
    }

    const std::optional<media_size> &printer::get_default_media_size() const noexcept
    {
        return m_defaultMediaSize;
    }

    const finishings &printer::get_finishings() const noexcept
    {
        return m_finishings;
    }

    const finishings &printer::get_default_finishings() const noexcept
    {
        return m_defaultFinishings;
    }

    bool printer::can_print_multiple_copies() const
    {
        return cupsCheckDestSupported(CUPS_HTTP_DEFAULT, m_dest,
                                      m_info, CUPS_COPIES, NULL);
    }

    void printer::populate_finishings()
    {
        vector<int> finishings = get_cups_integer_values(CUPS_FINISHINGS);
        for (const auto finishing : finishings)
        {
            set_finishing(finishing);
        }
    }

    void printer::set_finishing(int finish)
    {
        char fin[10]; // should only need to be 2 or 3 characters long
        sprintf(fin, "%d", finish);
        m_finishings.set_finishing(fin);
    }

    void printer::populate_media_sources()
    {
        vector<string> sources = get_cups_string_values(CUPS_MEDIA_SOURCE);
        for (const auto &source : sources)
            m_mediaSources.push_back(media_source(source));
    }

    const media_sources printer::get_media_sources() const noexcept
    {
        return m_mediaSources;
    }

    void printer::populate_default_finishings()
    {
        optional<string> defFinishings = get_cups_default_string_value(CUPS_FINISHINGS);
        if (defFinishings)
        {
            m_defaultFinishings.set_none();
            regex rgx("[0-9]*");
            smatch match;
            if (regex_search(*defFinishings, match, rgx))
            {
                for (auto m : match)
                {
                    m_defaultFinishings.set_finishing(m);
                }
            }
        }
    }

    void printer::populate_default_media_source()
    {
        m_defaultMediaSource = get_cups_default_string_value(CUPS_MEDIA_SOURCE);
    }

    const std::optional<media_source> &printer::get_default_media_source() const noexcept
    {
        return m_defaultMediaSource;
    }

    void printer::populate_media_types()
    {
        vector<string> types = get_cups_string_values(CUPS_MEDIA_TYPE);
        for (const auto& mediaType : types)
        {
            m_mediaTypes.push_back(media_type(mediaType));
        }
    }

    const media_types &printer::get_media_types() const noexcept
    {
        return m_mediaTypes;
    }

    void printer::populate_default_media_type()
    {
        m_defaultMediaType = get_cups_default_string_value(CUPS_MEDIA_TYPE);
    }

    const std::optional<media_type> &printer::get_default_media_type() const noexcept
    {
        return m_defaultMediaType;
    }

    void printer::populate_orientations()
    {
        vector<int> orientations = get_cups_integer_values(CUPS_ORIENTATION);
        for (const auto orientation : orientations)
        {
            m_orientations.push_back(page_orientation(orientation));
        }
    }
    const page_orientations &printer::get_orientations() const noexcept
    {
        return m_orientations;
    }

    void printer::populate_default_orientation()
    {
        m_defaultOrientation = get_cups_default_integer_value(CUPS_ORIENTATION);
    }

    const optional<page_orientation> &printer::get_default_orientation() const noexcept
    {
        return m_defaultOrientation;
    }

    void printer::populate_color_modes()
    {
        vector<string> colorModes = get_cups_string_values(CUPS_PRINT_COLOR_MODE);
        for (const auto& colorMode : colorModes)
        {
            m_colorModes.push_back(color_mode(colorMode));
        }
    }
    const color_modes &printer::get_color_modes() const noexcept
    {
        return m_colorModes;
    }

    void printer::populate_default_color_mode()
    {
        m_defaultColorMode = get_cups_default_string_value(CUPS_PRINT_COLOR_MODE);
    }

    const std::optional<color_mode> &printer::get_default_color_mode() const noexcept
    {
        return m_defaultColorMode;
    }

    void printer::populate_print_qualities()
    {
        // use ppd functions to get print qualities. This is necessary because the ipp_attributes
        // always return either Normal or None.
        m_printQualities.clear();
        if (m_pPpd)
        {
            vector<string> qualities = m_pPpd->get_option("cupsPrintQuality");
            // this can probably be done using transform algorithm, but would require a number
            // of constructors and operator= methods for print_quality.
            for(auto& quality: qualities)
            {
                m_printQualities.push_back(print_quality(quality));
            }
        }
    }

    const print_qualities &printer::get_print_qualities() const noexcept
    {
        return m_printQualities;
    }

    void printer::populate_default_print_quality()
    {
        // use ppd functions to get print qualities. This is necessary because the ipp_attributes
        // always return either Normal or None.
        m_defaultPrintQuality = nullopt;
        if (m_pPpd)
        {
            vector<string> defaultQuality = m_pPpd->get_option("DefaultcupsPrintQuality");
            if (defaultQuality.size() > 0)
            {
                m_defaultPrintQuality = defaultQuality[0];
            }
        }
    }

    const std::optional<print_quality> &printer::get_default_print_quality() const noexcept
    {
        return m_defaultPrintQuality;
    }

    void printer::populate_sides()
    {
        vector<string> cupsSides = get_cups_string_values(CUPS_SIDES);
        for(const auto& cupsSide : cupsSides)
        {
            m_sides.push_back(side(cupsSide));
        }
    }

    const sides &printer::get_sides() const noexcept
    {
        return m_sides;
    }

    void printer::populate_default_side()
    {
        m_defaultSide = get_cups_default_string_value(CUPS_SIDES);
    }

    const std::optional<side> &printer::get_default_side() const noexcept
    {
        return m_defaultSide;
    }

    const std::string printer::get_printer_state() const
    {
        string printerState;
        const char *printerUri = cupsGetOption("device-uri", m_dest->num_options, m_dest->options);
        regex hostRegex("^[a-zA-Z]+://([0-9a-zA-Z]+(\\.[0-9a-zA-Z]+)*)");
        string uri(printerUri);
        smatch match;
        if (regex_search(uri, match, hostRegex) && match.size() > 1)
        {
            string host = match.str(1);
            ipp_t *request, *response;
            static const char *const requested_attributes[] =
                {
                    "printer-state",
                    "printer-state-reasons",
                    "printer-is-accepting-jobs",
                    "printer-is-shared"};

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

    const std::string printer::get_printer_make_and_model() const
    {
        return get_options()["printer-make-and-model"];
    }

    const std::string printer::get_printer_location() const
    {
        return get_options()["printer-location"];
    }

    const std::string printer::get_printer_info() const
    {
        return get_options()["printer-type"];
    }

    std::ostream &operator<<(std::ostream &os, const printer &prtr)
    {
        string s = prtr.get_printer_state();
        os << "Printer: " << prtr.get_name() << '\n';
        os << "    Name = " << prtr.get_name() << '\n';
        os << "    Is default: " << (prtr.is_default() ? "true" : "false") << '\n';
        if (prtr.can_print_multiple_copies())
        {
            os << "    Can print multiple copies\n";
        }

        os << "Supported ";
        const finishings &finishes = prtr.get_finishings();
        os << finishes;

        os << "Default ";
        finishings defaultFinishings = prtr.get_default_finishings();
        os << defaultFinishings;

        os << "Supported ";
        auto mediaSources = prtr.get_media_sources();
        os << mediaSources;

        os << "Default Media Source:\n";
        auto defaultMediaSource = prtr.get_default_media_source();
        os << "    ";
        os << ((defaultMediaSource) ? defaultMediaSource.value().get_value() : "None") << "\n";

        os << "Supported ";
        auto mediaTypes = prtr.get_media_types();
        os << mediaTypes;

        os << "Default Media Type:\n";
        auto defaultMediaType = prtr.get_default_media_type();
        os << "    ";
        os << ((defaultMediaType) ? defaultMediaType.value().get_value() : "None") << "\n";

        auto orientations = prtr.get_orientations();
        os << orientations;

        os << "Default Orientation:\n";
        auto defOrientation = prtr.get_default_orientation();
        if (defOrientation)
        {
            os << defOrientation.value();
        }
        else
        {
            os << "    None\n";
        }

        os << "Supported ";
        auto colorModes = prtr.get_color_modes();
        os << colorModes;

        os << "Default Color Mode:\n";
        auto defaultColorMode = prtr.get_default_color_mode();
        if (defaultColorMode)
        {
            os << defaultColorMode.value();
        }
        else
        {
            os << "    None/n";
        }

        auto printQualities = prtr.get_print_qualities();
        os << printQualities;

        os << "Default Print Quality:\n";
        auto printQuality = prtr.get_default_print_quality();
        os << "    ";
        os << ((printQuality) ? printQuality.value().get_value() : "None") << '\n';

        os << "Supported ";
        auto sides = prtr.get_sides();
        os << sides;

        os << "Default Side\n";
        auto side = prtr.get_default_side();
        os << "    ";
        os << ((side) ? side.value().get_value() : "None") << '\n';

        os << "    Options: " << '\n';
        for (auto option : prtr.get_options())
        {
            os << "        " << option.first << ":  " << option.second << '\n';
        }

        os << prtr.get_media_sizes();

        os << "Default Media Size:\n";
        auto defaultSize = prtr.get_default_media_size();
        os << ((defaultSize) ? defaultSize.value().get_translated_name() : "None") << "\n";

        os << endl;
        return os;
    }
}