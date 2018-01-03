#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMimeData>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setAcceptDrops(true);

    // QCustomPlot
     ui->widgetPlot->setInteractions(QCP::iRangeDrag | QCP::iRangeZoom | QCP::iSelectAxes |
                                        QCP::iSelectLegend | QCP::iSelectPlottables);



    connect(ui->pushButtonUpdateFromCurrentFile, SIGNAL(released()), SLOT(updatePlotFromCurrentFile()));
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
    m_currentFile = e->mimeData()->urls().at(0).toLocalFile();
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
        inFile.close();

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

void MainWindow::updatePlotFromCurrentFile()
{
    ui->widgetPlot->clearGraphs();
    ui->widgetPlot->addGraph();

    QFile inFile(m_currentFile);
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
        inFile.close();

    }
    else
    {
        qDebug() << "Failed to open file";
    }


}

void MainWindow::mousePress(QMouseEvent* mevent)
{
    // if an axis is selected, only allow the direction of that axis to be dragged
    // if no axis is selected, both directions may be dragged

    if ( ui->widgetPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
         ui->widgetPlot->axisRect()->setRangeDrag(ui->widgetPlot->xAxis->orientation());
    else if ( ui->widgetPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
         ui->widgetPlot->axisRect()->setRangeDrag(ui->widgetPlot->yAxis->orientation());
    else
         ui->widgetPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);

}

void MainWindow::mouseWheel(QWheelEvent* mevent)
{
    if (ui->widgetPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->widgetPlot->axisRect()->setRangeZoom(ui->widgetPlot->xAxis->orientation());
    else if (ui->widgetPlot->yAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->widgetPlot->axisRect()->setRangeZoom(ui->widgetPlot->yAxis->orientation());
    else
        ui->widgetPlot->axisRect()->setRangeZoom(Qt::Horizontal|Qt::Vertical);
}

void MainWindow::mouseRelease(QMouseEvent *mevent)
{

    if (ui->widgetPlot->xAxis->selectedParts().testFlag(QCPAxis::spAxis))
        ui->widgetPlot->axisRect()->setRangeDrag(ui->widgetPlot->xAxis->orientation());
    else
        ui->widgetPlot->axisRect()->setRangeDrag(Qt::Horizontal|Qt::Vertical);

    double xMin = ui->widgetPlot->xAxis->range().center() - ui->widgetPlot->xAxis->range().size()/2.0;
    double xMax = ui->widgetPlot->xAxis->range().center() + ui->widgetPlot->xAxis->range().size()/2.0;



}

void MainWindow::mouseMove(QMouseEvent *mevent)
{

}
