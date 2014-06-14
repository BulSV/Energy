#ifndef IPAYMENT_H
#define IPAYMENT_H

class IPayment
{
public:
    virtual ~IPayment();
    virtual int consumed() const = 0;
};

#endif // IPAYMENT_H
