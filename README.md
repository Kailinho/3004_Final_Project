# 3004_Final_Project
AED Plus Simulation

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
