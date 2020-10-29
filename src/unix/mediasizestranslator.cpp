#include "mediasizestranslator.h"

namespace nanaprint
{
    MediaSizesTranslator::MediaSizesTranslator()
        : m_mediaMap {
            { "oe_photo-l_3.5x5in", "3.5x5in" },
            { "na_index_4x6in", "4x6in" }
        }
    {

    }

    MediaSizesTranslator::~MediaSizesTranslator()
    {

    }

    const std::string MediaSizesTranslator::getTranslatedSize(const std::string& mediaName)
    {
        auto translatedSize = m_mediaMap[mediaName];
        return translatedSize;
    }
}