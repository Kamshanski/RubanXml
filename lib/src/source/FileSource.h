#ifndef XML_RUBAN_FILESOURCE_H
#define XML_RUBAN_FILESOURCE_H


#include <iostream>
#include <fstream>
#include "Source.h"

class FileSource : public Source {
private:
    std::ifstream file;
    char obtainNextCharOrEof() override;
    void _close() override;
public:
    FileSource(const std::string& path);
};


#endif //XML_RUBAN_FILESOURCE_H
