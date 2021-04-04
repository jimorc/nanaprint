#ifndef NANAPRINT_FINISHINGS_H
#define NANAPRINT_FINISHINGS_H

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
    class finishings
    {
        public:
            finishings();
            ~finishings() {}
            void set_finishing(const std::string& finish);
            bool get_none() const { return m_none; }
            bool get_bind() const { return m_bind; }
            bool get_print_cover() const { return m_printCover; }
            bool get_fold() const { return m_fold; }
            bool get_punch() const { return m_punch; }
            bool get_staple() const { return m_staple; }
            bool get_trim() const { return m_trim; }

            void set_none();
            void set_bind();
            void set_print_cover();
            void set_fold();
            void set_punch();
            void set_staple();
            void set_trim();
        private:
            bool m_none;
            bool m_bind;
            bool m_printCover;
            bool m_fold;
            bool m_punch;
            bool m_staple;
            bool m_trim;
    };

    std::ostream& operator<<(std::ostream& os, const finishings& finishing);

}

#endif      // NANAPRINT_FINISHINGS_H