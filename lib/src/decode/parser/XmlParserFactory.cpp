
#include <decode/parser/XmlParserFactory.h>


XmlParserFactory::XmlParserFactory(DecoderParams* decoderParams) : decoderParams(decoderParams) {
    if (this->decoderParams == nullptr) {
        throw std::invalid_argument("Decoder Params cannot be null");
    }
}

Parser* XmlParserFactory::get(Source* source, Visitor* visitor) {
    if (source == nullptr) {
        throw std::invalid_argument("Source cannot be null");
    }

    Parser* parser = new XmlParser(source, decoderParams, visitor);

    return parser;
}
XmlParserFactory::~XmlParserFactory() {
    delete decoderParams;
}
