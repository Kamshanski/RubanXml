#ifndef XML_RUBAN_SOURCE_H
#define XML_RUBAN_SOURCE_H

class Source {
private:
    bool _isClosed = false;
    bool _isRead = false;
    char obtainedChar = 0;
protected:
    virtual char obtainNextCharOrEof() = 0; // return 0 if EOF
    virtual void _close() = 0;
public:
    virtual char nextChar();
    virtual bool hasNext();
    virtual bool close();
    virtual bool isClosed() const;
    virtual bool hasObtainedChar() const;
};

#endif //XML_RUBAN_SOURCE_H
