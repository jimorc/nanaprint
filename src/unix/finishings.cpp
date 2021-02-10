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
        if (finish == CUPS_FINISHINGS_NONE) setNone();
        else if (finish == CUPS_FINISHINGS_BIND) setBind();
        else if (finish == CUPS_FINISHINGS_COVER) setPrintCover();
        else if (finish == CUPS_FINISHINGS_FOLD) setFold();
        else if (finish == CUPS_FINISHINGS_PUNCH) setPunch();
        else if (finish == CUPS_FINISHINGS_STAPLE) setStaple();
        else if (finish == CUPS_FINISHINGS_TRIM) setTrim();
    }

    void finishings::setNone()
    {
        m_none = true;
        m_bind = false;
        m_printCover = false;
        m_fold = false;
        m_punch = false;
        m_staple = false;
        m_trim = false;
    }

    void finishings::setBind()
    {
        m_bind = true;
        m_none = false;
    }

    void finishings::setPrintCover()
    {
        m_printCover = true;
        m_none = false;
    }

    void finishings::setFold()
    {
        m_fold = true;
        m_none = false;
    }

    void finishings::setPunch()
    {
        m_punch = true;
        m_none = false;
    }

    void finishings::setStaple()
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
        os << (finishing.getFold() ? u8"    Fold\n" : "");
        os << (finishing.getPunch() ? u8"    Punch\n" : "");
        os << (finishing.getStaple() ? u8"    Staple\n" : "");
        os << (finishing.getTrim() ? u8"    Trim\n" : "");

        return os;
    }
}
