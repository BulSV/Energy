#ifndef IHISTORYGETTER_H
#define IHISTORYGETTER_H

#include <QMultiMap>
#include <QString>

class IHistoryGetter
{
public:
    virtual ~IHistoryGetter();
    virtual QMultiMap<QString, QString> getHistory() = 0;
};

#endif // IHISTORYGETTER_H
