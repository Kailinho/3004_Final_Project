# 3004_Final_Project
AED Plus Simulation

Team Members
- Mathew Gravel-Whalen
- Kailash Balakrishnan
- Annie Zhang
- Thara Radha Palaniswamy

Task Distributions (Design)
- Use Cases: Annie
- UML Class Diagram: Mathew
- Sequence Diagrams: Thara + Annie
- State Diagrams: Thara
- Design Decisions:
- Traceability Matrix: Mathew?

Task Distributions (Code)
There was a lot of collaboration on the code, especially towards the end. But the following is a rough breakdown of what each person was (broadly) responsible for.
- UI Design and Implementation: Kailash
- Basic Code Framework (Setting up header files, etc): Mathew
- CPR Functionality: Thara
- Patient Functionality: Annie + Kailash
- Heart Rate Display: Thara
- AED Functionality: Mathew + Annie
- Final Touches: Thara + Kailash



File Organization
The submission folder consists of two sub-directories.
 - Design Documents: Contains all design documents for this project. File names reflect the contents.
 - 3004_Final_Project: Project Source Code.
    Images folder containing visual assets for the application.
	Source & Header Files: aed.ccp/h, CPR.cpp/h, mainwindow.cpp/h/ui,main.cpp, patient.cpp/h, resources.qrc and QT .pro file.



Installation, Setup and Instructions for Use.
- Open the 3004_Final_Project folder or the .pro file in QT.
- Build and Run the app in QT.
- Turn the device On/Off
    Press the power button.


Class Diagram
```mermaid
classDiagram
class MainWindow {
    -QLabel *imageLabel

    -pressPowerButton()
    -applyPads()
    -updateBatteryLevel()
    -updateShockCount()
    -displayHR(int)
    -initializePatient()
}

class AED {
    -bool isOn
    -QPair&lt;bool, bool&gt;adultPads
    -QPair&lt;bool, bool&gt;childPads
    -int batteryLevel
    -int shockCount

    +getPower() bool
    +getBatteryLevel() bool
    +togglePower()
    +setPadsStatus(bool, bool, bool, bool)
    +checkPads()
    +monitorHeart()
    +deliverShock()
    +cprFeedback(int)
    +createPatient()

    +batteryLevelChanged(int)
    +shockCountChanged(int)
    +displayHRSignal(int)
}

class Patient {
    -int num
    -bool isAdult
    -int status

    +getIsAdult() bool
    +getstatus() int
    +setStatus(int)
}

MainWindow "1" --> "1" AED
AED "0..1" --> "0..1" Patient
```
