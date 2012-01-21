#include "aboutdialog.h"

AboutDialog::AboutDialog(QWidget *parent) :
    QDialog(parent)
{
    mainLabel = new QLabel("wAlignVis is a visualizer for displaying word alignment generated from GIZA++\n\nCopyright (2) 2012 Vee Satayamas", this);
//    mainLabel->show();
}
