/**
 *  \brief A Printer finishings class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/finishings.cpp
 */

#include <iostream>
#include <cups/cups.h>
#include "finishings.h"

using namespace std;

namespace nanaprint
{
    finishings::finishings() : m_none(true), m_bind(false), m_printCover(false),
        m_fold(false), m_punch(false), m_staple(false), m_trim(false)
    {

    }

    void finishings::set_finishing(const string& finish)
    {
        if (finish == CUPS_FINISHINGS_NONE) set_none();
        else if (finish == CUPS_FINISHINGS_BIND) set_bind();
        else if (finish == CUPS_FINISHINGS_COVER) set_print_cover();
        else if (finish == CUPS_FINISHINGS_FOLD) set_fold();
        else if (finish == CUPS_FINISHINGS_PUNCH) set_punch();
        else if (finish == CUPS_FINISHINGS_STAPLE) set_staple();
        else if (finish == CUPS_FINISHINGS_TRIM) setTrim();
    }

    void finishings::set_none()
    {
        m_none = true;
        m_bind = false;
        m_printCover = false;
        m_fold = false;
        m_punch = false;
        m_staple = false;
        m_trim = false;
    }

    void finishings::set_bind()
    {
        m_bind = true;
        m_none = false;
    }

    void finishings::set_print_cover()
    {
        m_printCover = true;
        m_none = false;
    }

    void finishings::set_fold()
    {
        m_fold = true;
        m_none = false;
    }

    void finishings::set_punch()
    {
        m_punch = true;
        m_none = false;
    }

    void finishings::set_staple()
    {
        m_staple = true;
        m_none = false;
    }

    void finishings::setTrim()
    {
        m_trim = true;
        m_none = false;
    }

    std::ostream& operator<<(std::ostream& os, const finishings& finishing)
    {
        os << u8"Finishings:\n";
        os << (finishing.get_none() ? u8"    None\n" : "");
        os << (finishing.get_bind() ? u8"    Bind\n" : "");
        os << (finishing.get_print_cover() ? u8"    Cover\n" : "");
        os << (finishing.get_fold() ? u8"    Fold\n" : "");
        os << (finishing.get_punch() ? u8"    Punch\n" : "");
        os << (finishing.get_staple() ? u8"    Staple\n" : "");
        os << (finishing.get_trim() ? u8"    Trim\n" : "");

        return os;
    }
}
