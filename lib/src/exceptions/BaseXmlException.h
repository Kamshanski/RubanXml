#ifndef XML_RUBAN_BASEXMLEXCEPTION_H
#define XML_RUBAN_BASEXMLEXCEPTION_H

#include "../_utils/ExceptionsExtensions.h"
#include "../_utils/StringUtils.h"

class XmlException : BaseException {
    public:
    XmlException(int index, const std::string& msg) : XmlException("XmlException", index, msg) {}

    protected:
    XmlException(const std::string& exceptionName, int index, const std::string& msg) :
        BaseException(exceptionName, to_string("At ") + std::to_string(index) + ": " + msg) {}
};

#endif //XML_RUBAN_BASEXMLEXCEPTION_H
