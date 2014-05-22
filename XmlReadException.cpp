#include "XmlReadException.h"

XmlReadException::XmlReadException(QString message)
    : itsMessage(message)
{
}

QString XmlReadException::message() const
{
    return itsMessage;
}
