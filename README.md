# Smart Medicine Dispenser

## Abstract
Prescription required keeping us healthy, however old age people require caretaker who can deal with their medicines plans. Because of busy schedules and less time, it's really hard to take proper medicines at a specific time. Many patients have to take multiple medicines daily but often forget which medicine to take at what time. Taking wrong medicines or missing doses can cause serious health issues or even death. This smart medicine dispenser solves this problem by informing patients to take medicine at the accurate time.

📺 **Watch Project Video:** [YouTube Link](https://youtu.be/2iEwzeNC6vI?si=L5tpUQl3PAM0V7xV)

## Keywords
Microcontrollers, Servomotor, LCD, RTC, IR sensor

## Introduction
Many medicinal errors occur due to elderly patients having to manage many medicines daily. Keeping track of the right medicine at the right time is challenging for elders. Nowadays, doctors prescribe many medicines, and people tend to forget their medication schedules, leading to serious consequences like illness or death. The Automatic Medication Dispenser helps patients take medicines efficiently and on time, minimizing human errors.

## Literature Survey
Studies show a high percentage of elderly patients take multiple medicines daily and often experience inappropriate medication or adverse outcomes. Surveys indicate many hospital deaths occur due to overdose or underdose of medicines, highlighting the need for such a device.

## Proposed Idea
The system aims to provide an easy, simple, and errorless solution for patients and elders by designing a self-medicine dispensing device requiring no human interference. The device uses compartments to store medicine and servomotors to dispense it. It includes an alarm system with a speaker to alert the patient.

## Methodology and Implementation
- **Microcontroller**: Arduino Uno is used for controlling the device, interfacing sensors, servomotors, and display.
- **RTC Module**: Provides real-time clock functionality for accurate timing.
- **Servo Motor**: Controls the dispensing mechanism precisely.
- **Pill Containers**: Store medicines safely, with 3 compartments each holding 15 days' supply.
- **Power Supply**: 12V DC power supply for microcontroller and speaker.
- **Keypad and Display**: 4x3 keypad for user input and 20x4 LCD to display status and alarms.
- **IR Sensor**: Detects the patient's hand to confirm medicine collection and avoid loss.

## Features
- Multiple alarms for different pills.
- Password protection for alarm setup.
- Real-time clock synchronization.
- Audible buzzer alerts.
- Servo-controlled medicine dispensing.
- Hand detection to confirm medicine taken.

## Future Scope
- Adding wireless connectivity for remote monitoring.
- Integration with mobile apps for notifications.
- Support for more compartments and complex schedules.

---

This project helps elderly and busy patients manage their medication schedules effectively and safely.
