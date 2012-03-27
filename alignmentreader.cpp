#include "alignmentreader.h"
#include <QFile>
#include <QTextStream>
#include <QtGlobal>
#include <iostream>

const unsigned int chunkSize = 3;

using namespace std;

AlignmentReader::AlignmentReader()
{
}

QVector<Alignment*> *AlignmentReader::read(QString a01filePath, QString a10filePath)
{
    QVector<TemporaryAlignment> *a01Vec = readEachSide(a01filePath);
    QVector<TemporaryAlignment> *a10Vec = readEachSide(a10filePath);
    QVector<Alignment*> *alignments = new QVector<Alignment*>;
    cout << a01Vec->count() << " " << a10Vec->count() << endl;
    for(int i = 0; i < a01Vec->count(); i++) {
        TemporaryAlignment a01 = (*a01Vec)[i];
        TemporaryAlignment a10 = (*a10Vec)[i];
        (*alignments) << new Alignment(a01.l0, a01.l1, a01.map, a10.map);
    }

    delete a01Vec;
    delete a10Vec;
    return alignments;
}

TemporaryAlignment AlignmentReader::decode(QString *chunks)
{
    TemporaryAlignment alignment;
    QString &l0Raw = chunks[2];
    QString &l1Raw = chunks[1];

    alignment.l1 = l1Raw.split(QRegExp("\\s+"));
    QStringList l0ImmList = l0Raw.split(" ");

    const int WORD_STATE = 0;
    const int INDEX_STATE = 1;

    int state = WORD_STATE;

    QStringListIterator l0ImmI(l0ImmList);
    int wordIndex = 0;
    while(l0ImmI.hasNext()) {
        QString tok = l0ImmI.next();
        if(state == WORD_STATE) {
            if(tok.compare("({") == 0) {
                state = INDEX_STATE;
            } else {
                if(wordIndex > 0) {
                    alignment.l0 << tok;
                }
                wordIndex++;
            }
        } else {
            if(tok.compare("})") == 0) {
                state = WORD_STATE;
            } else {
                int targetIdx = tok.toInt();
                int sourceIdx = wordIndex - 2;
                alignment.map[sourceIdx] << targetIdx;
            }
        }
    }
    return alignment;
}

QVector<TemporaryAlignment> *AlignmentReader::readEachSide(QString filePath)
{
    qDebug("!!!");
    QFile file(filePath);
    file.open(QFile::ReadOnly);
    QTextStream textStream(&file);
    textStream.setCodec("UTF-8");
    QString line;

    QString chunks[chunkSize];
    unsigned int chunkIndex = 0;

    QVector<TemporaryAlignment> *alignments = new QVector<TemporaryAlignment>;
    do {
        line = textStream.readLine();
        chunks[chunkIndex++] = line;

        if(chunkIndex == chunkSize) {
            cout << "@@@ " << chunkIndex << endl;
            TemporaryAlignment alignment = decode(chunks);

            (*alignments) << alignment;
            chunkIndex = 0;
        }        
    } while(!line.isNull());
    file.close();
    return alignments;
}
