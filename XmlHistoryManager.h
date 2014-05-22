#ifndef XMLHISTORYMANAGER_H
#define XMLHISTORYMANAGER_H

#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include "IHistoryManager.h"
#include "FileOpenException.h"
#include "XmlReadException.h"

class XmlHistoryManager : public IHistoryManager
{
    QString itsFileName;
    QList< QMap<QString, QString> >* itsHistory;
    QXmlStreamWriter* xmlWriter;
    QXmlStreamReader* xmlReader;

    QMap<QString, QString> parseRecord(QXmlStreamReader* xmlReader);
    void addElementDataToMap(QXmlStreamReader* xmlReader, QMap<QString, QString> &map) const;
public:
    XmlHistoryManager(QString fileName, QList<QMap<QString, QString> >& history);
    virtual ~XmlHistoryManager();
    virtual void writeHistory() throw(FileOpenException);
    virtual QList< QMap<QString, QString> >& readHistory() throw(FileOpenException, XmlReadException);
};

#endif // XMLHISTORYMANAGER_H
