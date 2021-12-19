#ifndef XML_RUBAN_WRITER_H
#define XML_RUBAN_WRITER_H


#include "../../entities/XmlElement.h"
#include "../../entities/XmlTag.h"
#include "../../entities/XmlValues.h"
#include "../../entities/XmlPrimitive.h"
#include "../../entities/XmlAttributes.h"
#include "../../sink/Sink.h"
#include "../EncoderParams.h"

class Writer{
private:
    Sink* sink;
    EncoderParams* params;
    int indentation = 0;
    bool _isUsed = false;

public:
    Writer(Sink* sink, EncoderParams* params);
    bool isUsed() const;
    void requireNotUsed() const;
    Sink* write(XmlElement* element);

private:
    void writeElement(XmlElement* element);
    void writeTag(XmlTag* tag);
    void writeFilledTag(XmlTag* tag);
    void writeEmptyTag(XmlTag* tag);
    void writeAttributes(XmlAttributes* tag);
    void writeValue(XmlValues* tag);
    void writePrimitive(XmlPrimitive* tag);
    void appendIndentation();

};


#endif //XML_RUBAN_WRITER_H
