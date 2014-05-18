#ifndef RASTCHET_H
#define RASTCHET_H

#include <QObject>

class Rastchet
{
    int itsPilga;
    int itsLimit;
    int itsPotochni;
    int itsPoperedni;
    float itsTaryfDo150;
    float itsTaryfPonad150;
    float itsTaryfPonad800;

public:
    Rastchet();
    Rastchet(int pilga,
             int limit,
             int potochni,
             int poperedni,
             float taryfDo150,
             float taryfPonad150,
             float taryfPonad800);

    int spozhyto() const;
    int spozhytoPilgovi() const;
    int spozhytoDo150() const;
    int spozhytoPonad150() const;
    int spozhytoPonad800() const;
    float taryfPilgovi() const;
    float taryfDo150() const;
    float taryfPonad150() const;
    float taryfPonad800() const;
    float summaPilgovi() const;
    float summaDo150() const;
    float summaPonad150() const;
    float summaPonad800() const;
    float summaZagalna() const;
    void setPilga(int pilga);
    void setLimit(int limit);
    void setTaryfDo150(float taryfDo150);
    void setTaryfPonad150(float taryfPonad150);
    void setTaryfPonad800(float taryfPonad800);
    void setPotochni(int potochni);
    void setPoperedni(int poperedni);
};

#endif // RASTCHET_H
