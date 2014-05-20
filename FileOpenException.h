#ifndef FILEOPENEXCEPTION_H
#define FILEOPENEXCEPTION_H

#include <QString>

class FileOpenException
{
    QString itsMessage;
public:
    FileOpenException();
    FileOpenException(QString message);
    QString message() const;
};

#endif // FILEOPENEXCEPTION_H