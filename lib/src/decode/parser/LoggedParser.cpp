#include "LoggedParser.h"
#include <plog/Log.h> // Step1: include the headers

LoggedParser::LoggedParser(Parser* parser, plog::Severity logLevel) : parser(parser), logLevel(logLevel) {
}
bool LoggedParser::isUsed() const {
    LOG(logLevel) << "Parser usage request";
    return parser->isUsed();
}
void LoggedParser::requireNotUsed() const {
    LOG(logLevel) << "Unused parser required";
    return parser->requireNotUsed();
}
Visitor* LoggedParser::parse() {
    LOG(plog::fatal) << "Parsing START";
    auto visitor = parser->parse();
    LOG(logLevel) << "Parsing FINISH";
    return visitor;
}
