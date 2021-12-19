#include "EncoderParams.h"

bool EncoderParams::isBeautify() const {
    return beautify;
}
bool EncoderParams::isShortenEmptyTags() const {
    return shortenEmptyTags;
}
bool EncoderParams::isSpacesAroundAttributeEqualSign() const {
    return spacesAroundAttributeEqualSign;
}