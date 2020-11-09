#pragma(once)

/**
 *  \file finishing.h
 *  \brief This file provides finishing and finishings classes required by nanaprint
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

#include <string>

namespace nanaprint
{
    class Finishings
    {
        public:
            Finishings();
            ~Finishings() {}
            void setFinishing(const std::string& finish);
            bool getNone() const { return m_none; }
            bool getBind() const { return m_bind; }
            bool getPrintCover() const { return m_printCover; }
            void setNone();
            void setBind();
            void setPrintCover();
        private:
            bool m_none;
            bool m_bind;
            bool m_printCover;
    };
}
