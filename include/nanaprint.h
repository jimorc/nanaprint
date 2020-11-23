#ifndef NANAPRINT_NANAPRINT_H
#define NANAPRINT_NANAPRINT_H

/**
 *  \brief Common settings for nanaprint
 *
 *	This header file is used in both Unix and Win32 implementations
 *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file includes/nanaprint.h
 */

namespace nanaprint
{
    enum class DialogStatus
    {
        cancel = 1,
        apply,
    };
}
#endif      // NANAPRINT_NANAPRINT_H