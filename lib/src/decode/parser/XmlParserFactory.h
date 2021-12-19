#ifndef XML_RUBAN_XMLPARSERFACTORY_H
#define XML_RUBAN_XMLPARSERFACTORY_H

#include "../../source/Source.h"
#include "Visitor.h"
#include "../DecoderParams.h"
#include "XmlParser.h"

class XmlParserFactory {
private:
    DecoderParams* decoderParams;

public:
    explicit XmlParserFactory(DecoderParams* decoderParams);

    virtual Parser* get(Source* source, Visitor* visitor);
    virtual ~XmlParserFactory();
};


#endif //XML_RUBAN_XMLPARSERFACTORY_H
