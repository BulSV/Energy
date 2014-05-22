#ifndef IHISTORYMANAGER_H
#define IHISTORYMANAGER_H

#include "IHistoryWriter.h"
#include "IHistoryReader.h"

class IHistoryManager : public IHistoryWriter, public IHistoryReader
{
public:
    virtual ~IHistoryManager();
    virtual void writeHistory() = 0;
    virtual QList< QMap<QString, QString> >& readHistory() = 0;
};

#endif // IHISTORYMANAGER_H
