#ifndef IHISTORYREADER_H
#define IHISTORYREADER_H

#include <QList>
#include <QMap>
#include <QString>

class IHistoryReader
{
public:
    virtual ~IHistoryReader();
    virtual QList< QMap<QString, QString> >& readHistory() = 0;
};

#endif // IHISTORYREADER_H
