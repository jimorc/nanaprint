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
    Finishings::Finishings() : m_none(true), m_bind(false)
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
    }

    void Finishings::setNone()
    {
        m_none = true;
        m_bind = false;
    }

    void Finishings::setBind()
    {
        m_bind = true;
        m_none = false;
    }
}
