#pragma(once)

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

#include <memory>
#include <iostream>

namespace nanaprint
{
    constexpr int PLAIN_NORMAL = 2;
    constexpr int FAST = 3;
    constexpr int NORMAL = 4;
    constexpr int HIGH = 5;
    constexpr int PHOTO = 6;

    class PrintQuality
    {
        public:
            ~PrintQuality() {}
            static std::shared_ptr<PrintQuality> create(const int quality);
            virtual std::string getPrintQuality() const = 0;
            
//            friend std::ostream& operator<<(std::ostream& os, const PrintQuality& quality);
        protected:
            PrintQuality() {}
    };

    std::ostream& operator<<(std::ostream& os, const PrintQuality& quality);

    class PlainNormalQuality : public PrintQuality
    {
        public:
            virtual ~PlainNormalQuality() {}
            static std::shared_ptr<PlainNormalQuality> create();
            virtual std::string getPrintQuality() const override;

        protected:
            PlainNormalQuality() {}
    };

    class FastQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<FastQuality> create();
            std::string getPrintQuality() const;
            virtual ~FastQuality() {}

        protected:
            FastQuality() {}
    };

    class NormalQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<NormalQuality> create();
            std::string getPrintQuality() const;
            virtual ~NormalQuality() {}

        protected:
            NormalQuality() {}
    };

    class HighQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<HighQuality> create();
            std::string getPrintQuality() const;
            virtual ~HighQuality() {}

        protected:
            HighQuality() {}
    };

    class PhotoQuality : public PrintQuality
    {
        public:
            static std::shared_ptr<PhotoQuality> create();
            std::string getPrintQuality() const;
            virtual ~PhotoQuality() {}

        protected:
            PhotoQuality() {}
    };
}