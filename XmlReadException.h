#ifndef XMLREADEXCEPTION_H
#define XMLREADEXCEPTION_H

#include <QString>

class XmlReadException
{
    QString itsMessage;
public:
    XmlReadException(QString message);
    QString message() const;
};

#endif // XMLREADEXCEPTION_H
