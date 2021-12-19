#ifndef RUBANXML_LOGGEDSINK_H
#define RUBANXML_LOGGEDSINK_H

#include <plog/Severity.h>
#include "Sink.h"

class LoggedSink : public Sink {
private:
    plog::Severity logLevel;
    Sink& sink;
protected:
public:
    LoggedSink(Sink& sink, plog::Severity logLevel);
protected:
    void _write(const std::string& str) override;
    void _write(char ch) override;
    void _close() override;
};


#endif //RUBANXML_LOGGEDSINK_H
