#ifndef XML_RUBAN_DECODERPARAMS_H
#define XML_RUBAN_DECODERPARAMS_H

class DecoderParams {
protected:
    bool keepBlankStringValues = false;
    bool trim = true;
public:
    bool isKeepBlankStringValues() const;
    bool isTrim() const;
};

#endif //XML_RUBAN_DECODERPARAMS_H
