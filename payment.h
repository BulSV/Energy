#ifndef PAYMENT_H
#define PAYMENT_H

#include <QObject>

class Payment
{
    int itsBenefit;
    int itsLimit;
    int itsCurrent;
    int itsPrevious;
    float itsTariffTo150;
    float itsTariffOver150;
    float itsTariffOver800;

public:
    Payment();
    Payment(int benefit,
            int limit,
            int current,
            int previous,
            float tariffTo150,
            float tariffOver150,
            float tariffOver800);

    int consumed() const;
    int consumedBenefit() const;
    int consumedTo150() const;
    int consumedOver150() const;
    int consumedOver800() const;
    float tariffBenefit() const;
    float tariffTo150() const;
    float tariffOver150() const;
    float tariffOver800() const;
    float amountBenefit() const;
    float amountTo150() const;
    float amountOver150() const;
    float amountOver800() const;
    float amountTotal() const;
    void setBenefit(int benefit);
    void setLimit(int limit);
    void setTariffTo150(float tariffTo150);
    void setTariffOver150(float tariffOver150);
    void setTariffOver800(float tariffOver800);
    void setCurrent(int current);
    void setPrevious(int previous);
};

#endif // PAYMENT_H
