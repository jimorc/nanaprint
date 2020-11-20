/**
 *  \brief A PageSetup class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/pagesetup.cpp
 */

#include "pagesetup.h"

using namespace std;
using namespace nana;

namespace nanaprint
{
    PageSetup::PageSetup(nana::form& parent) : form(parent, {500, 250})
    {
        caption(u8"Page Setup");
    }
}