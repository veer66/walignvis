#ifndef ALIGNMENTREADER_H
#define ALIGNMENTREADER_H
#include "alignment.h"
#include <QStringList>

struct TemporaryAlignment {
    QStringList l0, l1;
    QMap<int, QVector<int> > map;
};

class AlignmentReader
{
public:
    AlignmentReader();
    static QVector<Alignment*> *read(QString a01filePath, QString a10filePath);
private:
    static QVector<TemporaryAlignment> *readEachSide(QString filePath);
    static TemporaryAlignment decode(QString chunks[]);
};

#endif // ALIGNMENTREADER_H
