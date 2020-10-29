#include "mediasizestranslator.h"

namespace nanaprint
{
    MediaSizesTranslator::MediaSizesTranslator()
    {

    }

    MediaSizesTranslator::~MediaSizesTranslator()
    {

    }

    const std::string MediaSizesTranslator::getTranslatedSize(const std::string& mediaName) const
    {
        std::string translatedSize("3.5x5in");
        return translatedSize;
    }
}