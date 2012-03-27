#include "alignment.h"

Alignment::Alignment(QStringList l0, QStringList l1,
                     QMap<int, QVector<int> > m01, QMap<int, QVector<int> > m10)
    : l0(l0), l1(l1), m01(m01), m10(m10)
{    
}

QStringList &Alignment::getL0()
{
    return l0;
}

QStringList &Alignment::getL1()
{
    return l1;
}

QMap<int, QVector<int> > &Alignment::getM01()
{
    return m01;
}

QMap<int, QVector<int> > &Alignment::getM10()
{
    return m10;
}
