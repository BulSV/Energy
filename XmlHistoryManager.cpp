#include <QFile>
#include "XmlHistoryManager.h"


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

QList<QMap<QString, QString> > XmlHistoryManager::readHistory() throw(FileOpenException)
{
    QFile file(itsFileName);

    if (!file.open(QIODevice::ReadOnly))
    {
        throw FileOpenException("The file does not exist");
    }

    file.close();

    return itsHistory;
}
