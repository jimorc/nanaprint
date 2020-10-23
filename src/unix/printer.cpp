/**
 *  \brief A Printer class
 *
  *	nanaprint C++ Library(http://www.github.com/jimorc/nanaprint)
 *	Copyright(C) 2020 Jim Orcheson (jimorcheson@gmail.com)
 *
 *	Distributed under the Boost Software License, Version 1.0.
 *	(See accompanying file LICENSE or copy at
 *	http://www.boost.org/LICENSE_1_0.txt)
 *
 *  @file unix/printer.cpp
 */

#include "printer.h"

using namespace nanaprint;

constexpr size_t RESOURCE_SIZE = 200;      // sets size of resources returned by cupsConnectDest
constexpr int MAX_CONNECT_ATTEMPT_TIME = 5000;     // max allowed time for printer connect in ms

Printer::Printer(cups_dest_t* dest)
    : m_dest(dest)
{

}

std::shared_ptr<Printer> Printer::create(cups_dest_t* dest)
{
    char resource[RESOURCE_SIZE];
    http_t* http = cupsConnectDest(dest, CUPS_DEST_FLAGS_DEVICE, MAX_CONNECT_ATTEMPT_TIME,
        NULL, resource, RESOURCE_SIZE, NULL, NULL);
    return std::make_shared<Printer>(Printer(dest));
}


