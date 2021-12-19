#include "../include/xml_ruban/RubanXmlBuilder.h"
#include <plog/Init.h>

#include <utility>

RubanXmlBuilder* RubanXmlBuilder::setPrettyPrinting(bool beautify) {
    encoderParams->setBeautify(beautify);
    return this;
}
RubanXmlBuilder* RubanXmlBuilder::keepBlankStringValues(bool keepBlankStringValues) {
    decoderParams->setKeepBlankStringValues(keepBlankStringValues);
    return this;
}
RubanXmlBuilder* RubanXmlBuilder::shortenEmptyTags(bool shortenEmptyTags) {
    encoderParams->setShortenEmptyTags(shortenEmptyTags);
    return this;
}
RubanXmlBuilder* RubanXmlBuilder::setSpacesAroundAttributeEqualSign(bool setSpaces) {
    encoderParams->setSpacesAroundAttributeEqualSign(setSpaces);
    return this;
}
RubanXmlBuilder* RubanXmlBuilder::setTrim(bool trim) {
    decoderParams->setTrim(trim);
    return this;
}
RubanXmlBuilder* RubanXmlBuilder::setLoggingLevel(plog::Severity level, std::string logFileName) {
    this->logFileName = std::move(logFileName);
    this->logLevel = level;
    return this;
}
RubanXml RubanXmlBuilder::create() {
    return {new XmlWriterFactory(encoderParams), new XmlParserFactory(decoderParams), logLevel, logFileName};
}
