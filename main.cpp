#include <QtGui/QApplication>
#include "mainwindow.h"
#include "alignmentreader.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //QVector<Alignment*> *alignment = AlignmentReader::read("C:/Users/vee/Develop/wa01.txt", "C:/Users/vee/Develop/wa10.txt");
    MainWindow w(0);
    w.show();
    return a.exec();
}
