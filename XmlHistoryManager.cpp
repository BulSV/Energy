#include <QFile>
#include "XmlHistoryManager.h"

#include <QDebug>
QMap<QString, QString> XmlHistoryManager::parseRecord(QXmlStreamReader *xmlReader)
{
    QMap<QString, QString> record;
    qDebug() << "XmlHistoryManager::parseRecord(): in";

    if(xmlReader->tokenType() != QXmlStreamReader::StartElement && xmlReader->name() == "record")
    {
        qDebug() << "XmlHistoryManager::parseRecord(): return";
        return record;
    }

    QXmlStreamAttributes attributes = xmlReader->attributes();

    if(attributes.hasAttribute("id"))
    {
        qDebug() << "XmlHistoryManager::parseRecord(): id";
        record["id"] = attributes.value("id").toString();
    }

    xmlReader->readNext();
    qDebug() << "XmlHistoryManager::parseRecord(): next";

    while(!(xmlReader->tokenType() == QXmlStreamReader::EndElement
            && xmlReader->name() == "record"))
    {
        if(xmlReader->name() == "data")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "benefit")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "limit")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "current")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "previous")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "consumed")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "benefit_consumed")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "to_150_consumed")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_150_consumed")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_800_consumed")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "benefit_tariff")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "to_150_tariff")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_150_tariff")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_800_tariff")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "benefit_invoicing")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "to_150_invoicing")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_150_invoicing")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "over_800_invoicing")
        {
            addElementDataToMap(xmlReader, record);
        }
        if(xmlReader->name() == "invoicing")
        {
            addElementDataToMap(xmlReader, record);
        }
        qDebug() << "XmlHistoryManager::parseRecord(): next" << xmlReader->name();

        xmlReader->readNext();
    }

    qDebug() << "XmlHistoryManager::parseRecord(): return record";

    return record;
}

void XmlHistoryManager::addElementDataToMap(QXmlStreamReader *xmlReader, QMap<QString, QString> map) const
{
    if(xmlReader->tokenType() != QXmlStreamReader::StartElement)
    {
        return;
    }

    QString elementName = xmlReader->name().toString();
    qDebug() << "elementName" << elementName;

    xmlReader->readNext();

    if(xmlReader->tokenType() != QXmlStreamReader::Characters)
    {
        return;
    }

    qDebug() << "attribute" << xmlReader->text().toString();
    map.insert(elementName, xmlReader->text().toString());
}

XmlHistoryManager::XmlHistoryManager(QString fileName,
                                     QList<QMap<QString, QString> > history)
    : itsFileName(fileName)
    , itsHistory(history)
    , xmlWriter(new QXmlStreamWriter)
    , xmlReader(new QXmlStreamReader)
{
    xmlWriter->setAutoFormatting(true);
}

XmlHistoryManager::~XmlHistoryManager()
{
    delete xmlReader;
    delete xmlWriter;
}

void XmlHistoryManager::writeHistory() throw(FileOpenException)
{
    QFile file(itsFileName);

    if (!file.open(QIODevice::WriteOnly))
    {
        throw FileOpenException("The file is in read only mode");
    }

    xmlWriter->setDevice(&file);
    xmlWriter->writeStartDocument();
    xmlWriter->writeStartElement("history");

    for(int i = 0; i < itsHistory.size(); ++i)
    {
        xmlWriter->writeStartElement("record");
        xmlWriter->writeAttribute("id", QString::number(i));

        xmlWriter->writeStartElement("date");
        xmlWriter->writeCharacters(itsHistory.at(i).value("date"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("benefit");
        xmlWriter->writeCharacters(itsHistory.at(i).value("benefit"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("limit");
        xmlWriter->writeCharacters(itsHistory.at(i).value("limit"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("current");
        xmlWriter->writeCharacters(itsHistory.at(i).value("current"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("previous");
        xmlWriter->writeCharacters(itsHistory.at(i).value("previous"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("consumed");
        xmlWriter->writeCharacters(itsHistory.at(i).value("consumed"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("benefit_consumed");
        xmlWriter->writeCharacters(itsHistory.at(i).value("benefit_consumed"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("to_15_consumed");
        xmlWriter->writeCharacters(itsHistory.at(i).value("to_150_consumed"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_150_consumed");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_150_consumed"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_800_consumed");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_800_consumed"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("benefit_tariff");
        xmlWriter->writeCharacters(itsHistory.at(i).value("benefit_tariff"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("to_150_tariff");
        xmlWriter->writeCharacters(itsHistory.at(i).value("to_150_tariff"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_150_tariff");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_150_tariff"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_800_tariff");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_800_tariff"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("benefit_invoicing");
        xmlWriter->writeCharacters(itsHistory.at(i).value("benefit_invoicing"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("to_150_invoicing");
        xmlWriter->writeCharacters(itsHistory.at(i).value("to_150_invoicing"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_150_invoicing");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_150_invoicing"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("over_800_invoicing");
        xmlWriter->writeCharacters(itsHistory.at(i).value("over_800_invoicing"));
        xmlWriter->writeEndElement();

        xmlWriter->writeStartElement("invoicing");
        xmlWriter->writeCharacters(itsHistory.at(i).value("invoicing"));
        xmlWriter->writeEndElement();

        xmlWriter->writeEndElement();
    }

    xmlWriter->writeEndElement();
    xmlWriter->writeEndDocument();

    file.close();
}

QList<QMap<QString, QString> > XmlHistoryManager::readHistory() throw(FileOpenException, XmlReadException)
{
    QFile file(itsFileName);

    qDebug() << "XmlHistoryManager::readHistory()";
    if (!file.open(QIODevice::ReadOnly))
    {
        throw FileOpenException("The file does not exist");
    }

    qDebug() << "XmlHistoryManager::readHistory(): file exist";

    xmlReader->setDevice(&file);

    qDebug() << "XmlHistoryManager::readHistory(): setDevice";

    while (!xmlReader->atEnd() && !xmlReader->hasError())
    {
        QXmlStreamReader::TokenType token = xmlReader->readNext();

        if(token == QXmlStreamReader::StartDocument)
        {
            qDebug() << "XmlHistoryManager::readHistory(): StartDocument";
            continue;
        }

        if(token == QXmlStreamReader::StartElement)
        {
            qDebug() << "XmlHistoryManager::readHistory(): StartElement";
            if(xmlReader->name() == "history")
            {
                qDebug() << "XmlHistoryManager::readHistory(): name - history";
                continue;
            }
            if(xmlReader->name() == "record")
            {
                qDebug() << "XmlHistoryManager::readHistory(): name - record";
                itsHistory.append(parseRecord(xmlReader));
                qDebug() << "XmlHistoryManager::readHistory(): name - record - end";
            }
        }

        qDebug() << "XmlHistoryManager::readHistory(): before error";

        if(xmlReader->hasError())
        {
            qDebug() << "XmlHistoryManager::readHistory(): error";
            throw XmlReadException(xmlReader->errorString());
        }
    }

    file.close();

    qDebug() << "XmlHistoryManager::readHistory(): return itsHistory";
    return itsHistory;
}
