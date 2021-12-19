#ifndef XML_RUBAN_FILESINK_H
#define XML_RUBAN_FILESINK_H


#include <fstream>
#include "Sink.h"

class FileSink : public Sink {
private:
    std::ofstream file;

public:
    explicit FileSink(std::string& path);
protected:
    void _write(const std::string& str) override;
    void _write(char ch) override;
    void _close() override;
};


#endif //XML_RUBAN_FILESINK_H
