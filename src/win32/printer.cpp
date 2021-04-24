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
            enum class string_capability_names
            {
                e_paperName = DC_PAPERNAMES
            };
            class string_device_capabilities
            {
                public:
                    string_device_capabilities(std::string& printerName, 
                        string_capability_names capability)
                        : m_pOutput(nullptr), m_result(0)
                    {
                        int result = DeviceCapabilities(
                            printerName.c_str(),
                            nullptr,
                            (WORD)capability,
                            nullptr,
                            nullptr
                        );
                        m_pOutput = new char[capabilitySize[capability]*result];
                        result = DeviceCapabilities(
                            printerName.c_str(),
                            nullptr,
                            (WORD)capability,
                            m_pOutput,
                            nullptr
                        );
                        m_result = result;
                        for (int i = 0; i < result; ++i)
                        {
                            std::string cap(&m_pOutput[i*capabilitySize[capability]]);
                            cap = cap.substr(0, capabilitySize[capability]);
                            m_capabilities.push_back(cap);
                        }
                    }
                    ~string_device_capabilities() noexcept
                    {
                        if (m_pOutput)
                        {
                            delete[] m_pOutput;
                            m_pOutput = nullptr;
                        }
                    }
                    std::vector<std::string>& get_capabilities()
                    {
                        return m_capabilities;
                    }
                private:
                    std::map<string_capability_names, int> capabilitySize
                    {
                        {string_capability_names::e_paperName, 64}
                    };
                    char* m_pOutput;
                    std::vector<std::string> m_capabilities;
                    int m_result;
            };
            class print_form
            {
                public:
                    print_form(HANDLE printerHandle, std::string& paperName)
                        : m_info(nullptr)
                    {
                        DWORD needed = 0;
                        GetForm(printerHandle,
                            paperName.data(),
                            1,
                            nullptr,
                            0,
                            &needed);
                        m_info = new char[needed];
                        
                        if (needed >= sizeof(FORM_INFO_1))
                        {
                            if (GetForm(printerHandle,
                                paperName.data(),
                                1,
                                (LPBYTE)m_info,
                                needed,
                                &needed ))
                            {
                                FORM_INFO_1* form1 = reinterpret_cast<FORM_INFO_1*>(m_info);
                                m_mediaSize = media_size(paperName,
                                    form1->Size.cx / 10, form1->Size.cy / 10,
                                    form1->ImageableArea.bottom / 10, form1->ImageableArea.left / 10,
                                    form1->ImageableArea.right / 10, form1->ImageableArea.top / 10);
                            }
                        }
                    }
                    ~print_form() noexcept{
                        if (m_info)
                        {
                            delete[] m_info;
                            m_info = nullptr;
                        }
                    }
                    const std::optional<media_size>& get_media_size()
                    {
                        return m_mediaSize;
                    }
                private:
                    char* m_info;
                    std::optional<media_size> m_mediaSize;
            };
            impl(descriptor desc) : m_name(desc), m_printerHandle(nullptr)
            {
                if (OpenPrinter(m_name.data(), &m_printerHandle, nullptr))
                {
                    populate_media_sizes();
                }
                else
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
            void populate_media_sizes()
            {
                string_device_capabilities capabilities(m_name, 
                    string_capability_names::e_paperName);
                auto paperNames = capabilities.get_capabilities();
                for (auto paperName: paperNames)
                {
                    print_form form(m_printerHandle, paperName);
                    auto mediaSize = form.get_media_size();
                    if(mediaSize.has_value())
                    {
                        m_mediaSizes.push_back(mediaSize.value());
                    }
                }
            }
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
        os << "Paper Sizes\n";
        media_sizes mSizes = prtr.get_media_sizes();
        for (auto mSize : mSizes)
        {
            os << mSize;
        }
        return os;
    }
}