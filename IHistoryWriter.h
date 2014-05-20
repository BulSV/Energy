#ifndef IHISTORYWRITERR_H
#define IHISTORYWRITERR_H

class IHistoryWriter
{
public:
    virtual ~IHistoryWriter();
    virtual void writeHistory() = 0;
};

#endif // IHISTORYWRITER_H
