#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aed.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    AED aed;
    QLabel *imageLabel;

private slots:
    void pressPowerButton();
    void applyPads();
    void updateBatteryLevel(int level);
    void updateShockCount(int count);
    void displayHR(int status);
};
#endif // MAINWINDOW_H
