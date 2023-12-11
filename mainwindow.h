#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "aed.h"
#include <QRandomGenerator>

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
    QLabel *imageLabelCPR;

signals:
    void badCPR();
    void okCPR();
    void goodCPR();
    void Release();

private slots:
    void pressPowerButton();
    void applyPads();
    void updateBatteryLevel(int level);
    void updateShockCount(int count);
    void displayHR(int status);
    void initializePatient();
    void displayCompressions(int quality);
    void on_pushButton_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void buttonEnable(bool value);
    void on_pushButton_4_clicked();
};
#endif // MAINWINDOW_H
