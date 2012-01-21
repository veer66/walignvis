#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QtGui>
#include "visualizer.h"
#include "alignment.h"

class MainWindow : public QWidget
        //public QMainWindow
{
    Q_OBJECT
    
public:
    MainWindow(QVector<Alignment*> *alignments, QWidget *parent = 0);
    ~MainWindow();

public slots:
    void viewAlignment(QModelIndex index);
    void get01FileName();
    void get10FileName();
    void about();
    void load();
private:
    //Visualizer *visualizer;
    QVector<Alignment*> *alignments;
    QTreeView *sentPairTreeView;
    QStringListModel *sentPairModel;
    QLineEdit *lineEdit01;
    QLineEdit *lineEdit10;
    QPushButton *browseFileButton01;
    QPushButton *browseFileButton10;
    QStringListModel *buildSentPairModel();
    QFileDialog *fileDialog01;
    QFileDialog *fileDialog10;
};

#endif // MAINWINDOW_H
