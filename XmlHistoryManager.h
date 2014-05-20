#ifndef XMLHISTORYMANAGER_H
#define XMLHISTORYMANAGER_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "IHistoryManager.h"

class XmlHistoryManager : public IHistoryManager
{
    QString itsFileName;
public:
    XmlHistoryManager(QString fileName);
    virtual ~XmlHistoryManager();
    virtual void createHistory();
    virtual QMultiMap<QString, QString> getHistory();
};

#endif // XMLHISTORYMANAGER_H
