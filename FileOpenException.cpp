#include "FileOpenException.h"

FileOpenException::FileOpenException(QString message)
    : itsMessage(message)
{
}

QString FileOpenException::message() const
{
   return itsMessage;
}
