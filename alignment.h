#ifndef ALIGNMENT_H
#define ALIGNMENT_H

#include <QString>
#include <QVector>
#include <QMap>
#include <QStringList>

class Alignment
{
public:
    Alignment(QStringList l0, QStringList l1,
              QMap<int, QVector<int> > m01, QMap<int, QVector<int> > m10);
    QStringList &getL0();
    QStringList &getL1();
    QMap<int, QVector<int> > &getM01();
    QMap<int, QVector<int> > &getM10();
private:
    QStringList l0, l1;
    QMap<int, QVector<int> > m01, m10;
};

#endif // ALIGNMENT_H
