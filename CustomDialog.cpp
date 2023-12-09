#include <QDialog>
#include <QVBoxLayout>
#include <QInputDialog>
#include <QComboBox>
#include <QPushButton>
#include "mainwindow.h"
#include <QApplication>

class CustomDialog : public QDialog {
public:
    CustomDialog(QWidget* parent = nullptr) : QDialog(parent) {
        setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint);

        QVBoxLayout* layout = new QVBoxLayout(this);

        QComboBox* comboBox = new QComboBox(this);
        comboBox->addItems(QStringList() << "Adult" << "Child");
        layout->addWidget(comboBox);

        QPushButton* okButton = new QPushButton("OK", this);
        layout->addWidget(okButton);

        connect(okButton, &QPushButton::clicked, this, &CustomDialog::accept);
        // Set a fixed size
        setFixedSize(200, 100);

        // Center the dialog on the main window
        centerOnMainWindow();
    }
private:
    void centerOnMainWindow() {
        QWidget* mainWindow = parentWidget();
        if (mainWindow) {
            QPoint center = mainWindow->geometry().center();
            move(center.x() - width() / 2, center.y() - height() / 2);
        }
    }
};

void MainWindow::initializePatient() {
    CustomDialog dialog(this);
    if (dialog.exec() == QDialog::Accepted) {
        QString choice = "Adult"; // Default choice
        // Retrieve the selected patient type from the custom dialog
        QList<QComboBox*> comboBoxes = dialog.findChildren<QComboBox*>();
        if (!comboBoxes.isEmpty()) {
            choice = comboBoxes.first()->currentText();
        }

        bool isAdult = (choice == "Adult");
        // Create the patient with the chosen type
        int randomScenario = QRandomGenerator::global()->bounded(3, 4);
        aed.createPatient(isAdult, randomScenario);

        qInfo("Patient created with type: %s", qPrintable(choice));
    } else {
        qInfo("User closed the dialog");
        qInfo("No Patient Type Selected. Please Restart the Device.");
        QApplication::quit();
    }

}


