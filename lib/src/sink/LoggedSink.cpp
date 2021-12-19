#include <plog/Log.h>
#include "LoggedSink.h"

void LoggedSink::_write(const std::string& str) {
    std::ostringstream os;
    os << "Write string: " << str;
    LOG(logLevel) << os.str();
    sink.write(str);
}
void LoggedSink::_write(char ch) {
    std::ostringstream os;
    os << "Write string: " << ch;
    LOG(logLevel) << os.str();
    sink.write(ch);
}
void LoggedSink::_close() {
    LOG(logLevel) << "Close sink";
    sink.close();
}
LoggedSink::LoggedSink(Sink& sink, plog::Severity logLevel) : sink(sink), logLevel(logLevel) {}
