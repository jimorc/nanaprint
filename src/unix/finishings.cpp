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

#include <cups/cups.h>
#include "finishings.h"

using namespace std;

namespace nanaprint
{
    Finishings::Finishings() : m_none(true), m_bind(false), m_printCover(false),
        m_fold(false), m_punch(false), m_staple(false)
    {

    }

    void Finishings::setFinishing(const string& finish)
    {
        if (finish == CUPS_FINISHINGS_NONE)
        {
            setNone();
        }
        else if (finish == CUPS_FINISHINGS_BIND)
        {
            setBind();
        }
        else if (finish == CUPS_FINISHINGS_COVER)
        {
            setPrintCover();
        }
        else if (finish == CUPS_FINISHINGS_FOLD)
        {
            setFold();
        }
        else if (finish == CUPS_FINISHINGS_PUNCH)
        {
            setPunch();
        }
        else if (finish == CUPS_FINISHINGS_STAPLE)
        {
            setStaple();
        }
    }

    void Finishings::setNone()
    {
        m_none = true;
        m_bind = false;
        m_printCover = false;
        m_fold = false;
        m_punch = false;
        m_staple = false;
    }

    void Finishings::setBind()
    {
        m_bind = true;
        m_none = false;
    }

    void Finishings::setPrintCover()
    {
        m_printCover = true;
        m_none = false;
    }

    void Finishings::setFold()
    {
        m_fold = true;
        m_none = false;
    }

    void Finishings::setPunch()
    {
        m_punch = true;
        m_none = false;
    }

    void Finishings::setStaple()
    {
        m_staple = true;
        m_none = false;
    }
}
