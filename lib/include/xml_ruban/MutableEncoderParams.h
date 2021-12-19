#ifndef XML_RUBAN_MUTABLEENCODERPARAMS_H
#define XML_RUBAN_MUTABLEENCODERPARAMS_H

#include "../../src/encode/EncoderParams.h"

class MutableEncoderParams : public EncoderParams {
public:
    void setBeautify(bool beautify);
    void setShortenEmptyTags(bool shortenEmptyTags);
    void setSpacesAroundAttributeEqualSign(bool spacesAroundAttributeEqualSign);
};


#endif //XML_RUBAN_MUTABLEENCODERPARAMS_H
