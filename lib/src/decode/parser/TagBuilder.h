#ifndef XML_RUBAN_TAGBUILDER_H
#define XML_RUBAN_TAGBUILDER_H


#include "entities/XmlTag.h"
#include "Visitor.h"

class TagBuilder : public Visitor {
private:
    XmlTag* root = nullptr;
    std::vector<XmlTag*> branch {};
    XmlTag* getCurrent() const;
    XmlTag* getCurrentsParent() const;

public:
    void onAttribute(std::string attrName, std::string attrValue) override;
    void onTagOpen(std::string tagName) override;
    void onTagClosed(std::string tagName) override;
    void onTagTextValue(std::string tagTextValue) override;

    XmlTag* getRoot() const;
};


#endif //XML_RUBAN_TAGBUILDER_H
