#ifndef XML_RUBAN_SINK_H
#define XML_RUBAN_SINK_H

#include "string"

class Sink {
private:
    bool _isClosed = false;
protected:
    virtual void _write(const std::string& str) = 0;
    virtual void _write(char ch) = 0;
    virtual void _close() = 0;
public:
    Sink* write(const std::string& str);
    Sink* write(char ch);
    void close();
    bool isClosed();
    void checkNotClosed();
};

#endif //XML_RUBAN_SINK_H
