#include "mainwindow.h"
#include "aboutdialog.h"
#include "alignmentreader.h"

MainWindow::MainWindow(QVector<Alignment*> *alignments, QWidget *parent)
    : QWidget(parent), alignments(alignments)
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

    fileDialog01 = new QFileDialog;
    fileDialog10 = new QFileDialog;

    QVBoxLayout *layout = new QVBoxLayout;

    QHBoxLayout *file01Layout = new QHBoxLayout;
    QLabel *file01Label = new QLabel("L0->L1 File");
    file01Layout->addWidget(file01Label);
    lineEdit01 = new QLineEdit;
    file01Layout->addWidget(lineEdit01);
    browseFileButton01 = new QPushButton("Browse");
    connect(browseFileButton01, SIGNAL(clicked()), this, SLOT(get01FileName()));
    file01Layout->addWidget(browseFileButton01);


    QHBoxLayout *file10Layout = new QHBoxLayout;
    QLabel *file10Label = new QLabel("L1->L0 File");
    file10Layout->addWidget(file10Label);
    lineEdit10 = new QLineEdit;
    file10Layout->addWidget(lineEdit10);
    browseFileButton10 = new QPushButton("Browse");
    connect(browseFileButton10, SIGNAL(clicked()), this, SLOT(get10FileName()));
    file10Layout->addWidget(browseFileButton10);

    QHBoxLayout *controlPanelLayout = new QHBoxLayout;
    QPushButton *aboutButton = new QPushButton("About");
    controlPanelLayout->addWidget(aboutButton);
    connect(aboutButton, SIGNAL(clicked()), this, SLOT(about()));
    controlPanelLayout->addStretch();
    QPushButton *loadAlignmentButton = new QPushButton("Load alignments");
    controlPanelLayout->addWidget(loadAlignmentButton);
    connect(loadAlignmentButton, SIGNAL(clicked()), this, SLOT(load()));

    layout->addLayout(file01Layout);
    layout->addLayout(file10Layout);
    layout->addLayout(controlPanelLayout);
    layout->addWidget(sentPairTreeView);
    //setCentralWidget(layout);
    setLayout(layout);
}

void MainWindow::load() {
    alignments = AlignmentReader::read(lineEdit01->text(), lineEdit10->text());
    if(sentPairModel != 0)
        delete sentPairModel;
    sentPairModel = buildSentPairModel();
    sentPairTreeView->setModel(sentPairModel);
}

void MainWindow::about() {
    AboutDialog dialog(this);
    dialog.exec();
}

void MainWindow::get01FileName() {
    lineEdit01->setText(fileDialog01->getOpenFileName());
}

void MainWindow::get10FileName() {
    lineEdit10->setText(fileDialog10->getOpenFileName());
}

QStringListModel *MainWindow::buildSentPairModel()
{
    QStringList strList;
    if(alignments != 0) {
        QVectorIterator<Alignment*> i(*alignments);
        while(i.hasNext()) {
            Alignment *alignment = i.next();
            strList.push_back(alignment->getL0().join(" ") + "\n" + alignment->getL1().join(" "));
        }
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
