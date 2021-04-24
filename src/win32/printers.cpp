#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winspool.h>
#include <vector>
#include <memory>
#include <stdexcept>
#include <sstream>
#include "printers.h"

namespace nanaprint
{
    class printers::impl
    {           
            // printer_info_1s class contains PRINTER_INFO_1 objects retrieved from
            // calls to EnumPrinters. Because the number of PRINTER_INFO_1 structs
            // needed is not known until the first call to EnumPrinters, the buffer to
            // receive the structs can only be created after that first call. The buffer
            // is created on the heap by calling new. The printer_info_1s struct
            // destructor calls delete[] on the buffer to ensure that the buffer
            // is deleted even if an exception is thrown.
            class printer_info_1s
        {
            public:
                printer_info_1s(size_t numBytes) : m_pInfo(nullptr)
                {
                    m_pInfo = new BYTE[numBytes];
                }
                ~printer_info_1s()
                {
                    if (m_pInfo)
                    {
                        delete[] m_pInfo;
                        m_pInfo = nullptr;
                    }
                }
                operator LPBYTE()
                {
                    return m_pInfo;
                }
                PRINTER_INFO_1& operator[](size_t index)
                {
                    PRINTER_INFO_1* pi1 = reinterpret_cast<PRINTER_INFO_1*>(m_pInfo);
                    return pi1[index];
                }
            private:
                BYTE* m_pInfo;
        };
        public:
            impl()
            {
                DWORD sizeNeeded = 0;
                DWORD numStructs = 0;
                auto result = EnumPrinters(
                    PRINTER_ENUM_LOCAL,
                    nullptr,
                    1,          // retrieve PRINTER_INFO_1 structs
                    nullptr,
                    0,
                    &sizeNeeded,
                    &numStructs
                );

                printer_info_1s pi1s(sizeNeeded);


                SetLastError(0);

                result = EnumPrinters(
                    PRINTER_ENUM_LOCAL,
                    nullptr,
                    1,          // retrieve PRINTER_INFO_1 structs
                    pi1s,
                    sizeNeeded,
                    &sizeNeeded,
                    &numStructs
                );
                if (result)
                {
                    for (DWORD i = 0; i < numStructs; ++i)
                    {
                        auto pPrinter = printer::create(pi1s[i].pName);
                        m_printers.push_back(pPrinter);
                    }
                }
                else
                {
                    auto error = GetLastError();
                    std::stringstream ss;
                    ss << "Error in second call to EnumPrinters in printers constructor\n";
                    ss << "Error code returned is: " << error << '\b';
                    ss << "See https://docs.microsoft.com/en-us/windows/win32/debug/system-error-codes\n";
                    ss << "for the meaning of the error\n";
                    throw std::runtime_error(ss.str());
                }
            }

            std::vector<std::shared_ptr<printer>> get_printers() const
            {
                return m_printers; 
            }
            
            size_t get_default_printer_number() const
            {
                size_t printerNum = 0;
                for(size_t i = 0; i < m_printers.size(); ++i)
                {
                    if (m_printers[i]->is_default())
                    {
                        printerNum = i;
                        break;
                    }
                }
                return printerNum;
            }

            size_t get_printer_number(const std::string& printerName) const
            {
                size_t printerNum = 0;
                for( size_t i = 0; i < m_printers.size(); ++i)
                {
                    if (m_printers[i]->get_name() == printerName)
                        printerNum = i;
                }
                return printerNum;
            }

        private:
            std::vector<std::shared_ptr<printer>> m_printers;
    };


    printers::printers() : m_pImpl(std::make_unique<impl>())
    {

    }

    printers::~printers() {}

    std::vector<std::shared_ptr<printer>> printers::get_printers() const
    {
        return m_pImpl->get_printers();
    }

    size_t printers::get_default_printer_number() const
    {
        return m_pImpl->get_default_printer_number();
    }

    size_t printers::get_printer_number(const std::string& printerName) const
    {
        return m_pImpl->get_printer_number(printerName);
    }

    std::ostream& operator<<(std::ostream& os, const printers& prtrs)
    {
        auto prntrs = prtrs.get_printers();
        if (prntrs.size() == 0)
        {
            os << "No printers found.\n";
        }
        else
        {
            for(auto prntr : prntrs)
            {
                os << *prntr << '\n';
            }
        }
        return os;
    }
}