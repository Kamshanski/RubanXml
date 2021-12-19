#ifndef XML_RUBAN_MUTABLEDECODERPARAMS_H
#define XML_RUBAN_MUTABLEDECODERPARAMS_H

#include "../../src/decode/DecoderParams.h"

class MutableDecoderParams : public DecoderParams {
public:
    void setKeepBlankStringValues(bool keepBlankStringValues);
    void setTrim(bool trim);

};


#endif //XML_RUBAN_MUTABLEDECODERPARAMS_H
