#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtGui>
#include <QGraphicsView>
#include "alignment.h"
#include <QPointF>
#include <QFont>

class Visualizer : public QGraphicsView
{
    Q_OBJECT
public:
    explicit Visualizer(Alignment *alignment, QWidget * parent = 0);
    
signals:
    
public slots:
    void closeEvent(QCloseEvent *event);

private:
    QGraphicsScene *scene;
    Alignment *alignment;
    QVector<QPointF> *putText(QStringList wordList, float x, float y, bool isOnTop);
    QRectF putWord(QString word, float x, float y);
    void putLinks(QMap<int, QVector<int> > map, QVector<QPointF> *l0Points, QVector<QPointF> *l1Points, QPen &pen);
    QPointF findPointForConnection(QRectF &rect, float x, float y, bool isOnTop);
    QPen pen01, pen10;
    QFont font;
};

#endif // VISUALIZER_H
