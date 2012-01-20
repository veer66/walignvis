#include "visualizer.h"
#include <stdio.h>

const int space = 10;

Visualizer::Visualizer(Alignment *alignment, QWidget * parent) :
    QGraphicsView(parent), alignment(alignment), pen01(QColor(00,0xB0,00)), pen10(QColor(00,00,0xB0)),
    font("Sans", 12.0)
{
    scene = new QGraphicsScene;
    QVector<QPointF> *l0Points = putText(alignment->getL0(), 0, 0, true);
    QVector<QPointF> *l1Points = putText(alignment->getL1(), 0, 150, false);
    putLinks(alignment->getM01(), l0Points, l1Points, pen01);
    putLinks(alignment->getM10(), l1Points, l0Points, pen10);
    setScene(scene);
    delete l0Points;
    delete l1Points;
}

void Visualizer::closeEvent(QCloseEvent *event)
{

}

void Visualizer::putLinks(QMap<int, QVector<int> > map,
                           QVector<QPointF> *l0Points, QVector<QPointF> *l1Points, QPen &pen)
{
    QMapIterator<int, QVector<int> > i(map);
    while(i.hasNext()) {
        i.next();

        int source = i.key() + 1;
        QVector<int> targets = i.value();
        QVectorIterator<int> j(targets);
        while(j.hasNext()) {
            int target = j.next();
            qreal x0 = (*l0Points)[source].x();
            qreal y0 = (*l0Points)[source].y();
            qreal x1 = (*l1Points)[target].x();
            qreal y1 = (*l1Points)[target].y();

            scene->addLine(x0, y0, x1, y1, pen);
            QString buf;
            qDebug(buf.sprintf("%d %d %f %f %f %f", source, target, x0, y0, x1, y1).toLocal8Bit());
        }
    }
}

QRectF Visualizer::putWord(QString word, float x, float y) {
    QGraphicsTextItem *wordItem = new QGraphicsTextItem(QString(word));
    wordItem->setFont(font);
    wordItem->setPos(x, y);
    QRectF rect = wordItem->boundingRect();
    scene->addItem(wordItem);
    return rect;
}

QPointF Visualizer::findPointForConnection(QRectF &rect, float x, float y, bool isOnTop)
{
    QString buf;
    //qDebug(buf.sprintf("FindPoint: %f %f", x, y).toLocal8Bit());
    return QPoint(x + (rect.width() / 2), y + (isOnTop ? rect.height() : 0));
}

QVector<QPointF> *Visualizer::putText(QStringList wordList, float x, float y, bool isOnTop)
{
    QVector<QPointF> *points = new QVector<QPointF>;
    QRectF rect = putWord("___", x, y);
    points->push_back(findPointForConnection(rect, x, y, isOnTop));
    x += rect.width() + space;   
    QStringListIterator i(wordList);
    while(i.hasNext()) {
        QString word = i.next();
        QRectF rect = putWord(word, x, y);
        points->push_back(findPointForConnection(rect, x, y, isOnTop));
        x += rect.width() + space;        
    }
    return points;
}
