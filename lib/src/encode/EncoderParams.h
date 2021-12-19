#ifndef XML_RUBAN_ENCODERPARAMS_H
#define XML_RUBAN_ENCODERPARAMS_H

class EncoderParams {
protected:
    bool beautify = true;
    bool shortenEmptyTags = true;
    bool spacesAroundAttributeEqualSign = false;
public:
    bool isBeautify() const;
    bool isShortenEmptyTags() const;
    bool isSpacesAroundAttributeEqualSign() const;
};

#endif //XML_RUBAN_ENCODERPARAMS_H
