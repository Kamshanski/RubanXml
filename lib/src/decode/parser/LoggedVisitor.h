#ifndef RUBANXML_LOGGEDVISITOR_H
#define RUBANXML_LOGGEDVISITOR_H

#include <plog/Severity.h>
#include "Visitor.h"

class LoggedVisitor : public Visitor {
private:
    Visitor& visitor;
    plog::Severity logLevel;
public:
    LoggedVisitor(Visitor& visitor, plog::Severity log);

    void onAttribute(std::string attrName, std::string attrValue) override;
    void onTagOpen(std::string tagName) override;
    void onTagClosed(std::string tagName) override;
    void onTagTextValue(std::string tagTextValue) override;
};


#endif //RUBANXML_LOGGEDVISITOR_H
