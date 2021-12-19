#include "../include/xml_ruban/RubanXml.h"
#include <iostream>
#include "sink/FileSink.h"
#include "decode/parser/TagBuilder.h"
#include <source/LoggedSource.h>
#include <sink/LoggedSink.h>
#include <decode/parser/LoggedVisitor.h>
#include <decode/parser/LoggedParser.h>
#include <plog/Init.h>


RubanXml::RubanXml(XmlWriterFactory* xmlWriterFactory, XmlParserFactory* xmlParserFactory, plog::Severity logLevel, std::string logFileName)
        :  xmlWriterFactory(xmlWriterFactory), xmlParserFactory(xmlParserFactory), logLevel(logLevel),
           logFileName(logFileName)
{
    if (logLevel != plog::none && !logFileName.empty()) {
        plog::init(logLevel, logFileName.c_str());
    }
}

RubanXml::RubanXml() :
        RubanXml(
                new XmlWriterFactory(new EncoderParams()),
                new XmlParserFactory(new DecoderParams()),
                plog::none,
                ""
        ) {
}


std::string RubanXml::xmlTagToString(XmlTag* tag) {
    StringSink sink = StringSink();

    xmlTagToSink(tag, &sink);
    sink.close();
    return sink.toString();
}

void RubanXml::xmlTagToFile(XmlTag* tag, std::string path) {
    FileSink sink = FileSink(path);
    xmlTagToSink(tag, &sink);
    sink.close();
}

Sink* RubanXml::xmlTagToSink(XmlTag* tag, Sink* sink) {
    try {
        Sink* loggedSink = applyLogging(sink);
        Writer* writer = xmlWriterFactory->get(loggedSink);
        writer->write(tag);
        delete writer;
        return sink;
    } catch (std::exception& ex) {
        sink->close();
        throw ex;
    }
}

XmlTag* RubanXml::xmlTreeFromString(std::string xml) {
    auto source = StringSource(std::move(xml));
    return xmlTreeFromSource(&source);
}

XmlTag* RubanXml::xmlTreeFromFile(const std::string& path) {
    auto source = FileSource(path);
    return xmlTreeFromSource(&source);
}

XmlTag* RubanXml::xmlTreeFromSource(Source* source) {
    TagBuilder builder = TagBuilder();
    parseFromSource(source, &builder);
    return builder.getRoot();
}
void RubanXml::parseFromSource(Source* source, Visitor* visitor) {
    try {
        Source* loggedSource = applyLogging(source);

        Parser* parser = xmlParserFactory->get(loggedSource, visitor);
        parser = applyLogging(parser);

        parser->parse();

        delete parser;
    } catch (std::exception& ex) {
        source->close();
        throw ex;
    }
}


RubanXml::~RubanXml() {
    delete xmlWriterFactory;
    delete xmlParserFactory;
}
Sink* RubanXml::applyLogging(Sink* sink) {
    if (logLevel != plog::none) {
        return new LoggedSink(*sink, logLevel);
    }
    return sink;
}
Source* RubanXml::applyLogging(Source* source) {
    if (logLevel != plog::none) {
        return new LoggedSource(*source, logLevel);
    }
    return source;
}
Visitor* RubanXml::applyLogging(Visitor* visitor) {
    if (logLevel != plog::none) {
        return new LoggedVisitor(*visitor, logLevel);
    }
    return visitor;
}
Parser* RubanXml::applyLogging(Parser* parser) {
    if (logLevel != plog::none) {
        return new LoggedParser(parser, logLevel);
    }
    return parser;
}


