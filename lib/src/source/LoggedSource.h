#ifndef RUBANXML_LOGGEDSOURCE_H
#define RUBANXML_LOGGEDSOURCE_H

#include <plog/Severity.h>
#include "Source.h"

class LoggedSource : public Source {
    Source& source;
    plog::Severity logLevel;
public:
    LoggedSource(Source& source, plog::Severity logLevel);

    char nextChar() override;
    bool hasNext() override;
    bool close() override;
    bool isClosed() const override;
    bool hasObtainedChar() const override;
protected:
    char obtainNextCharOrEof() override;
    void _close() override;
};


#endif //RUBANXML_LOGGEDSOURCE_H
