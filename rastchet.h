#ifndef RASTCHET_H
#define RASTCHET_H

#include <QObject>

class Rastchet
{
    int itsPotochni;
    int itsPoperedni;
    float itsTaryfDo150;
    float itsTaryfPonad150;

public:
    Rastchet();
    Rastchet(int potochni, int poperedni, float taryfDo150, float taryfPonad150);

    int spozhyto() const;
    int spozhytoDo150() const;
    int spozhytoPonad150() const;
    float taryfDo150() const;
    float taryfPonad150() const;
    float summaDo150() const;
    float summaPonad150() const;
    float summaZagalna() const;
    void setTaryfDo150(float taryfDo150);
    void setTaryfPonad150(float taryfPonad150);
    void setPotochni(int potochni);
    void setPoperedni(int poperedni);
};

#endif // RASTCHET_H
