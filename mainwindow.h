#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QDropEvent>
#include <QUrl>
#include <QDebug>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();


protected:
    void dropEvent(QDropEvent *ev);
    void dragEnterEvent(QDragEnterEvent *ev);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
