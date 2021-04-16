#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winspool.h>
#include <stdexcept>
#include <sstream>
#include "printer.h"

namespace nanaprint
{
    class printer::impl
    {
        public:
            impl(descriptor desc) : m_name(desc), m_printerHandle(nullptr)
            {
                if (!OpenPrinter(m_name.data(), &m_printerHandle, nullptr))
                {
                    auto error = GetLastError();
                    std::stringstream ss;
                    ss << "Could not open " << m_name << ": error code is " << error << '\n';
                    ss << "See https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes\n";
                    ss << "for the meaning of the error\n";
                    throw std::runtime_error(ss.str());
                    SetLastError(0);
                }
            }
            ~impl()
            {
                if (m_printerHandle)
                {
                    ClosePrinter(m_printerHandle);
                    m_printerHandle = nullptr;
                }
            }
            const std::string& get_name() const noexcept { return m_name; }
            bool is_default()
            {
                // max size of printer name is 64 chars.
                constexpr DWORD maxDefPrinterChars = 65;
                DWORD defPrinterSize = maxDefPrinterChars;
                char defPrinter[maxDefPrinterChars];
                GetDefaultPrinter(defPrinter, &defPrinterSize);
                auto isDefault = m_name.compare(defPrinter);
                return isDefault == 0;
            }
            const media_sizes& get_media_sizes() const noexcept { return m_mediaSizes; }
            const std::optional<media_size>& get_default_media_size() const noexcept
            {
                return m_defaultMediaSize;
            }
            const finishings& get_finishings() const noexcept { return m_finishings; }
            const finishings& get_default_finishings() const noexcept { return m_defaultFinishings; }
            const media_sources get_media_sources() const noexcept { return m_mediaSources; }
            const std::optional<media_source>& get_default_media_source() const noexcept
            {
                return m_defaultMediaSource;
            }
            const media_types& get_media_types() const noexcept { return m_mediaTypes; }
            const std::optional<media_type>& get_default_media_type() const noexcept { return m_defaultMediaType; }
            const page_orientations& get_orientations() const noexcept { return m_orientations; }
            const std::optional<page_orientation>& get_default_orientation() const noexcept
            {
                return m_defaultOrientation;
            }
            const color_modes& get_color_modes() const noexcept { return m_colorModes; }
            const std::optional<color_mode>& get_default_color_mode() const noexcept { return m_defaultColorMode; }
            const print_qualities& get_print_qualities() const noexcept { return m_printQualities; }
            const std::optional<print_quality>& get_default_print_quality() const noexcept
            {
                return m_defaultPrintQuality;
            }
            const sides& get_sides() const noexcept { return m_sides; }
            const std::optional<side>& get_default_side() const noexcept { return m_defaultSide; }
        private:
            std::string m_name;
            HANDLE m_printerHandle;
            media_sizes m_mediaSizes;
            media_sources m_mediaSources;
            media_types m_mediaTypes;
            page_orientations m_orientations;
            color_modes m_colorModes;
            print_qualities m_printQualities;
            sides m_sides;
            finishings m_finishings;

            std::optional<media_size> m_defaultMediaSize;
            std::optional<media_source> m_defaultMediaSource;
            std::optional<media_type> m_defaultMediaType;
            std::optional<page_orientation> m_defaultOrientation;
            std::optional<color_mode> m_defaultColorMode;
            std::optional<print_quality> m_defaultPrintQuality;
            std::optional<side> m_defaultSide;
            finishings m_defaultFinishings;
    };

    printer::printer(descriptor desc) : m_pImpl(std::make_unique<impl>(desc)) {}

    printer::~printer() {}

    std::shared_ptr<printer> printer::create(descriptor desc)
    {
        return std::make_shared<printer>(printer(desc));
    }
    
    const std::string printer::get_name() const
    {
        return m_pImpl->get_name();
    }
    
    bool printer::is_default() const noexcept
    {
        return m_pImpl->is_default();
    }

    std::map<std::string, std::string> printer::get_options() const
    {
        return std::map<std::string, std::string>();
    }

    const media_sizes& printer::get_media_sizes() const noexcept
    {
        return m_pImpl->get_media_sizes();
    }

    const std::optional<media_size>& printer::get_default_media_size() const noexcept
    {
        return m_pImpl->get_default_media_size();
    }

    bool printer::can_print_multiple_copies() const
    {
        return false;
    }

    const finishings& printer::get_finishings() const noexcept
    {
        return m_pImpl->get_finishings();
    }

    const finishings& printer::get_default_finishings() const noexcept
    {
        return m_pImpl->get_default_finishings();
    }

    const media_sources printer::get_media_sources() const noexcept
    {
        return m_pImpl->get_media_sources();
    }

    const std::optional<media_source>& printer::get_default_media_source() const noexcept
    {
        return m_pImpl->get_default_media_source();
    }

    const media_types& printer::get_media_types() const noexcept
    {
        return m_pImpl->get_media_types();
    }

    const std::optional<media_type>& printer::get_default_media_type() const noexcept
    {
        return m_pImpl->get_default_media_type();
    }

    const page_orientations& printer::get_orientations() const noexcept
    {
        return m_pImpl->get_orientations();
    }

    const std::optional<page_orientation>& printer::get_default_orientation() const noexcept
    {
        return m_pImpl->get_default_orientation();
    }

    const color_modes& printer::get_color_modes() const noexcept
    {
        return m_pImpl->get_color_modes();
    }

    const std::optional<color_mode>& printer::get_default_color_mode() const noexcept
    {
        return m_pImpl->get_default_color_mode();
    }

    const print_qualities& printer::get_print_qualities() const noexcept
    {
        return m_pImpl->get_print_qualities();
    }

    const std::optional<print_quality>& printer::get_default_print_quality() const noexcept
    {
        return m_pImpl->get_default_print_quality();
    }

    const sides& printer::get_sides() const noexcept
    {
        return m_pImpl->get_sides();
    }

    const std::optional<side>& printer::get_default_side() const noexcept
    {
        return m_pImpl->get_default_side();
    }

    const std::string printer::get_printer_state() const
    {
        return "";
    }

    const std::string printer::get_printer_make_and_model() const
    {
        return "";
    }

    const std::string printer::get_printer_location() const
    {
        return "";
    }

    const std::string printer::get_printer_info() const
    {
        return "";
    }

    std::ostream& operator<<(std::ostream& os, const printer& prtr)
    {
        os << prtr.get_name() << '\n';
        bool isDefault = prtr.is_default();
        os << "Is " << (prtr.is_default() ? "" : "not ") << "default printer\n";
        return os;
    }
}