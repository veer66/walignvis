#ifndef VISUALIZER_H
#define VISUALIZER_H

#include <QtGui>
#include <QGraphicsView>
#include "alignment.h"
#include <QPointF>
#include <QFont>
#include "wordref.h"

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
    QVector<QPointF> *putText(QStringList wordList, float x, float y, bool isOnTop, QMap<int, QVector<int> > map);
    QRectF putWord(QString word, float x, float y, bool isOnTop, int pos, QMap<int, QVector<int> > map);
    void putLinks(QMap<int, QVector<int> > map, QVector<QPointF> *l0Points, QVector<QPointF> *l1Points, QPen &pen);
    QPointF findPointForConnection(QRectF &rect, float x, float y, bool isOnTop);
    void draw();
    QPen pen01, pen10;
    QFont font;
    WordRef selWordRef;
protected:
    virtual void mousePressEvent (QMouseEvent *event);
};

#endif // VISUALIZER_H
