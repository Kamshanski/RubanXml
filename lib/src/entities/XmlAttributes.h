#ifndef XML_RUBAN_XMLATTRIBUTES_H
#define XML_RUBAN_XMLATTRIBUTES_H

#include <utility>
#include "../rules/CharExcapeRules.h"
#include "../exceptions/IllegalCharacterExceptions.h"
#include "XmlElement.h"
#include "../_utils/LinkedMap.h"

class XmlAttributes : public XmlElement {
    LinkedMap<std::string, std::string> attributes;

public:
    bool isEmpty() const override;
    int size() const override;
    void printTo(std::ostream& oss, int indentation) const override;
    std::string getClassName() override;

    std::string get(const std::string& name);

    void put(std::string name, std::string value);

    void putAll(LinkedMap<std::string, std::string>& attributes);

    std::pair<std::string, std::string> indexed(int index);
    void forEachAttribute(const std::function<void(int, const std::string&, const std::string&)>& consumer);

};


#endif //XML_RUBAN_XMLATTRIBUTES_H
