#include <plog/Log.h>
#include "LoggedVisitor.h"

void LoggedVisitor::onAttribute(std::string attrName, std::string attrValue) {
    std::ostringstream os;
    os << "Attribute: " << attrName << " = " << attrValue;
    PLOG(logLevel) << os.str();
    visitor.onAttribute(attrName, attrValue);
}
void LoggedVisitor::onTagOpen(std::string tagName) {
    std::ostringstream os;
    os << "Tag open: " << tagName;
    PLOG(logLevel) << os.str();
    visitor.onTagOpen(tagName);
}
void LoggedVisitor::onTagClosed(std::string tagName) {
    std::ostringstream os;
    os << "Tag close: " << tagName;
    PLOG(logLevel) << os.str();
    visitor.onTagClosed(tagName);
}
void LoggedVisitor::onTagTextValue(std::string tagTextValue) {
    std::ostringstream os;
    os << "Tag Text Value: " << tagTextValue;
    PLOG(logLevel) << os.str();
    visitor.onTagTextValue(tagTextValue);
}
LoggedVisitor::LoggedVisitor(Visitor& visitor, plog::Severity logLevel) : visitor(visitor), logLevel(logLevel) {}
