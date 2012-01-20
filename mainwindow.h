#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "visualizer.h"
#include "alignment.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QVector<Alignment*> *alignments, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void viewAlignment(QModelIndex index);

private:
    //Visualizer *visualizer;
    QVector<Alignment*> *alignments;
    QTreeView *sentPairTreeView;
    QStringListModel *sentPairModel;

    QStringListModel *buildSentPairModel();
};

#endif // MAINWINDOW_H
