#include "mainwindow.h"

MainWindow::MainWindow(QVector<Alignment*> *alignments, QWidget *parent)
    : QMainWindow(parent), alignments(alignments)
{
    //Alignment *alignment = (*alignments)[0];
    //visualizer = new Visualizer(alignment);
    sentPairTreeView = new QTreeView();
    sentPairModel = buildSentPairModel();
    sentPairTreeView->setWordWrap(true);
    sentPairTreeView->setHeaderHidden(true);
    sentPairTreeView->setEditTriggers(QTreeView::NoEditTriggers);
    sentPairTreeView->setModel(sentPairModel);
    connect(sentPairTreeView, SIGNAL(clicked(QModelIndex)), this, SLOT(viewAlignment(QModelIndex)));
    setCentralWidget(sentPairTreeView);
}

QStringListModel *MainWindow::buildSentPairModel()
{
    QVectorIterator<Alignment*> i(*alignments);
    QStringList strList;
    while(i.hasNext()) {
        Alignment *alignment = i.next();
        strList.push_back(alignment->getL0().join(" ") + "\n" + alignment->getL1().join(" "));
    }
    return new QStringListModel(strList);
}

void MainWindow::viewAlignment(QModelIndex index)
{
    Alignment *alignment = (*alignments)[index.row()];
    Visualizer *visualizer = new Visualizer(alignment);
    visualizer->show();
}

MainWindow::~MainWindow()
{
    
}
