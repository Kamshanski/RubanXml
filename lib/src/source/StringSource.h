#ifndef XML_RUBAN_STRINGSOURCE_H
#define XML_RUBAN_STRINGSOURCE_H

#include <string>
#include "Source.h"

class StringSource : public Source {
private:
    std::string source;
    int index = 0;
    int limit;

public:
    explicit StringSource(std::string source);

private:
    char obtainNextCharOrEof() override;
    void _close() override;
};


#endif //XML_RUBAN_STRINGSOURCE_H
