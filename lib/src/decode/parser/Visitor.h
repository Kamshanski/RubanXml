#ifndef XML_RUBAN_VISITOR_H
#define XML_RUBAN_VISITOR_H

#include "string"

class Visitor {
public:
    virtual void onAttribute(std::string attrName, std::string attrValue) = 0;
    virtual void onTagOpen(std::string tagName) = 0;
    virtual void onTagClosed(std::string tagName) = 0;
    virtual void onTagTextValue(std::string tagTextValue) = 0;
};

#endif //XML_RUBAN_VISITOR_H
