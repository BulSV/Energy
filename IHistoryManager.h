#ifndef IHISTORYMANAGER_H
#define IHISTORYMANAGER_H

#include "IHistoryCreator.h"
#include "IHistoryGetter.h"

class IHistoryManager : public IHistoryCreator, public IHistoryGetter
{
public:
    virtual ~IHistoryManager();
    virtual void createHistory() = 0;
    virtual QMultiMap<QString, QString> getHistory() = 0;
};

#endif // IHISTORYMANAGER_H
