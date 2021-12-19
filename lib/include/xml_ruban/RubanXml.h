#ifndef XML_RUBAN_RUBANXML_H
#define XML_RUBAN_RUBANXML_H

#include "plog/Severity.h"
#include "../../src/encode/writer/XmlWriterFactory.h"
#include "../../src/decode/parser/XmlParserFactory.h"
#include "../../src/sink/StringSink.h"
#include "../../src/source/StringSource.h"
#include "../../src/source/FileSource.h"
#include "../../src/entities/XmlTag.h"
#include "../../src/entities/XmlPrimitive.h"
#include "../../src/entities/XmlValues.h"
#include "../../src/entities/XmlAttributes.h"
#include "../../src/entities/XmlElement.h"
#include "../../src/decode/parser/Visitor.h"

class RubanXml {
    plog::Severity logLevel = plog::none;
    std::string logFileName = "";
    XmlWriterFactory* xmlWriterFactory;
    XmlParserFactory* xmlParserFactory;

    Sink* applyLogging(Sink* sink);
    Source* applyLogging(Source* sink);
    Visitor* applyLogging(Visitor* sink);
    Parser* applyLogging(Parser* parser);
public:
    RubanXml(XmlWriterFactory* xmlWriterFactory, XmlParserFactory* xmlParserFactory, plog::Severity logLevel, std::string logFileName = "");
    RubanXml();

    std::string xmlTagToString(XmlTag* tag);
    void xmlTagToFile(XmlTag* tag, std::string path);
    Sink* xmlTagToSink(XmlTag* tag, Sink* sink);
    void parseFromSource(Source* tag, Visitor* visitor);
    XmlTag* xmlTreeFromSource(Source* tag);
    XmlTag* xmlTreeFromString(std::string xml);
    XmlTag* xmlTreeFromFile(const std::string& path);

    virtual ~RubanXml();
};

#endif //XML_RUBAN_RUBANXML_H
