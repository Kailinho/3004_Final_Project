#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    ui->batteryLabel->setText("Battery Level: Initializing"); //Initial Battery Status

    aed.createPatient(true, 2); // First scenario so we can start coding

    connect(&aed, SIGNAL(batteryLevelChanged(int)), this, SLOT(updateBatteryLevel(int)));
    connect(ui->powerButton, SIGNAL(released()), this, SLOT(pressPowerButton()));
    connect(ui->adultPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->adultPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad1CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
    connect(ui->childPad2CheckBox, SIGNAL(stateChanged(int)), this, SLOT(applyPads()));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::pressPowerButton()
{
    if(aed.getDeviceStatus() == false)
    {
        aed.setDeviceOn();
        ui->powerButton->setStyleSheet("QPushButton { image: url(:/images/power-button.png); border-radius: 30px; background-color: #30D5C8; }");  //UI Change
        ui->adultPad1CheckBox->setEnabled(true);
        ui->adultPad2CheckBox->setEnabled(true);
        ui->childPad1CheckBox->setEnabled(true);
        ui->childPad2CheckBox->setEnabled(true);
    }
    else
    {
        ui->powerButton->setStyleSheet("QPushButton { image: url(:/images/power-button.png); border-radius: 30px; background-color: #D5303D; }");  //UI Change
        aed.setDeviceOff();
        ui->adultPad1CheckBox->setChecked(false);
        ui->adultPad2CheckBox->setChecked(false);
        ui->childPad1CheckBox->setChecked(false);
        ui->childPad2CheckBox->setChecked(false);
        ui->adultPad1CheckBox->setEnabled(false);
        ui->adultPad2CheckBox->setEnabled(false);
        ui->childPad1CheckBox->setEnabled(false);
        ui->childPad2CheckBox->setEnabled(false);
    }
}

void MainWindow::applyPads() {
    aed.setPadsStatus(ui->adultPad1CheckBox->isChecked(), ui->adultPad2CheckBox->isChecked(), ui->childPad1CheckBox->isChecked(), ui->childPad2CheckBox->isChecked());
}


//Battery Slot
void MainWindow::updateBatteryLevel(int level) {
    ui->batteryLabel->setText("Battery Level: " + QString::number(level) + "%");
    QApplication::processEvents(); //Force UI updates
}
