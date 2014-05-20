#ifndef IHISTORYCREATOR_H
#define IHISTORYCREATOR_H

class IHistoryCreator
{
public:
    virtual ~IHistoryCreator();
    virtual void createHistory() = 0;
};

#endif // IHISTORYCREATOR_H
