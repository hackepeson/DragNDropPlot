#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);
}

void MainWindow::dragEnterEvent(QDragEnterEvent *e)
{
    if (e->mimeData()->hasUrls())
    {
        e->acceptProposedAction();
    }
}

void MainWindow::dropEvent(QDropEvent *e)
{

    /*
    foreach (const QUrl &url, e->mimeData()->urls())
    {
        QString fileName = url.toLocalFile();
        qDebug() << "Dropped file:" << fileName;
    }
    */
    qDebug() << e->mimeData()->urls().at(0).toLocalFile();
    ui->widgetPlot->clearGraphs();
    ui->widgetPlot->addGraph();

    QFile inFile(e->mimeData()->urls().at(0).toLocalFile());
    if (inFile.open(QIODevice::ReadOnly))
    {

        QString data = inFile.readAll();
        QStringList qsl = data.split("\n");

        QVector<double> dataVec;
        QVector<double> timeVec;

        for (int i = 0; i < qsl.count(); i++)
        {
            dataVec.append(qsl.at(i).toDouble());
            timeVec.append(i);
        }
        ui->widgetPlot->graph(0)->addData(timeVec, dataVec);
        ui->widgetPlot->rescaleAxes();
        ui->widgetPlot->replot();

    }
    else
    {
        qDebug() << "Failed to open file";
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}
