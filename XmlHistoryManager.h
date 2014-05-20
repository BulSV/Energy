#ifndef XMLHISTORYMANAGER_H
#define XMLHISTORYMANAGER_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "IHistoryManager.h"
#include "FileOpenException.h"

class XmlHistoryManager : public IHistoryManager
{
    QString itsFileName;
    QList< QMap<QString, QString> > itsHistory;
    QXmlStreamWriter* xmlWriter;
    QXmlStreamReader* xmlReader;
public:
    XmlHistoryManager(QString fileName, QList<QMap<QString, QString> > history);
    virtual ~XmlHistoryManager();
    virtual void writeHistory() throw(FileOpenException);
    virtual QList< QMap<QString, QString> > readHistory() throw(FileOpenException);
};

#endif // XMLHISTORYMANAGER_H
