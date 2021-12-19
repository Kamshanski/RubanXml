#ifndef XML_RUBAN_XMLVALUES_H
#define XML_RUBAN_XMLVALUES_H

#include <vector>
#include <functional>
#include "XmlElement.h"

class XmlValues : public XmlElement {
private:
    std::vector<XmlElement*> elements;

public:

    void put(XmlElement* element);

    XmlElement* get(int index);

    bool isEmpty() const override;

    int size() const override;

    bool isSingle();
    XmlElement* single();

    bool isLastPrimitive() const;
    bool isFirstTag() const;

public:
    void printTo(std::ostream& oss, int indentation) const override;
    XmlTag* firstOrNullTag(const std::string& tagName);

    void forEachTag(const std::function<void(int, XmlTag*)>& consumer);
    void forEachPrimitive(const std::function<void(int, XmlPrimitive*)>& consumer);

    std::string getClassName() override;
    virtual ~XmlValues();
    std::string asString() override;
};


#endif //XML_RUBAN_XMLVALUES_H
