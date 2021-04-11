#include "printers.h"

namespace nanaprint
{
    class printers::impl
    {
        public:
            impl() {}
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
                os << *prntr;
            }
        }
        return os;
    }
}