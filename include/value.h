#ifndef NANAPRINT_VALUE_H
#define NANAPRINT_VALUE_H

/**
 *  \file printquality.h
 *  \brief This file provides printquality class required by nanaprint
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

#include <vector>

template<typename T>
class nanaprint_value
{
    public:
        nanaprint_value(const T& value) : m_value(value) {}
        virtual ~nanaprint_value() {}
        const T& get_value() const noexcept { return m_value; }
    private:
        T m_value;
};

#endif      // NANAPRINT_VALUE_H