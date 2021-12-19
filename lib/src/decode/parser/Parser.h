#ifndef RUBANXML_PARSER_H
#define RUBANXML_PARSER_H

#include "Visitor.h"

class Parser {
public:
    virtual bool isUsed() const = 0;
    virtual void requireNotUsed() const = 0;
    virtual Visitor* parse() = 0;
};
#endif //RUBANXML_PARSER_H
