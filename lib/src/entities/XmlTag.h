#ifndef XML_RUBAN_XMLTAG_H
#define XML_RUBAN_XMLTAG_H


#include <ostream>
#include "XmlElement.h"
#include "XmlValues.h"
#include "XmlAttributes.h"

class XmlTag : public XmlElement {
private:
    std::string name;
    XmlValues* values = new XmlValues();
    XmlAttributes* attributes = new XmlAttributes();

    void addElementToValues(XmlElement* xmlElement);

public:
    XmlTag(std::string  name, XmlValues* values, XmlAttributes* attributes);
    XmlTag(std::string  name, XmlAttributes* attributes);
    XmlTag(std::string  name, XmlValues* values);
    explicit XmlTag(std::string  name);

    void addValue(std::string text);
    void addValue(XmlTag* tag);
    void addAttribute(std::string name, std::string value);

    std::string getName() const;
    XmlValues* getValues() const;
    XmlAttributes* getAttributes() const;
    void setName(const std::string& name);
    void setValues(XmlValues* values);
    void setAttributes(XmlAttributes* attributes);

    std::string asString() override;

    bool isEmpty() const override;
    int size() const override;
    std::string getClassName() override;

    void printTo(std::ostream& os, int indentation) const override;
    friend std::ostream& operator<<(std::ostream& os, const XmlTag& tag);

    XmlTag* firstOrNullTag(const std::string& tagName);

    void forEachTag(const std::function<void(int, XmlTag*)>& consumer);
    void forEachPrimitive(const std::function<void(int, XmlPrimitive*)>& consumer);
    void forEachAttribute(const std::function<void(int, const std::string&, const std::string&)>& consumer);

    virtual ~XmlTag();
};


#endif //XML_RUBAN_XMLTAG_H
