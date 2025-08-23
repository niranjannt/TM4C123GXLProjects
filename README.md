TM4C123GXL Embedded Systems Projects

This repository showcases multiple embedded systems projects developed on the Texas Instruments TM4C123GXL (Tiva C Series LaunchPad) microcontroller using C and Code Composer Studio. Each project integrates timers, GPIO, LCD display, and audio feedback to create interactive real-time systems.

 Simon Says Memory Game
 Overview

A memory-based game inspired by Simon Says, where the player must replicate increasingly long LED sequences. Audio tones and LCD feedback provide an interactive gaming experience.

 Features

LED sequence generation and playback using SysTick and Timer1A

Audio tones for each LED via a 4-bit resistor DAC

Correct/incorrect feedback using buzzer and “ding” tones

LCD messages: "Round X Passed" or "Game Over"

Dynamic sequence-tracking logic with arrays and GPIO switch validation

Example Workflow

System flashes an LED sequence (e.g., Red → Green → Yellow).

Player reproduces the sequence with the corresponding switches.

If correct, a new round begins with an extended sequence.

If incorrect, the game ends with a buzzer sound and "Game Over" on the LCD.

 LED Reaction Time Game
 Overview

The Reaction Time Game tests how fast a user responds to an LED turning on. Reaction times are measured in milliseconds and displayed on the LCD.

Features

Random LED activation with SysTick

Reaction time measurement using Timer1A

Switch-based user input detection

LCD result display: "Reaction Time: XXX ms"

 Example Workflow

After a random delay, an LED lights up.

User presses the switch as quickly as possible.

The system calculates and displays the reaction time.

 Digital Stopwatch
 Overview

A digital stopwatch with start, stop, and reset controls. Displays the elapsed time on the LCD in HH:MM:SS format.

 Features

Stopwatch controlled by GPIO switches (Start, Stop, Reset)

Time tracked by Timer1A with second-level granularity

Tick sound generated with SysTick + DAC

LCD updates dynamically with the current stopwatch value

 Example Workflow

Press Start to begin timing.

Press Stop to pause.

Press Reset to clear the stopwatch.

LCD continuously updates with elapsed time.

Hardware Components

TM4C123GXL Tiva C Series LaunchPad

ST7735 LCD (SPI interface)

4-bit Resistor DAC + Piezo Buzzer (for audio tones)

Onboard LEDs (red, green, yellow)

Push-button switches (GPIO inputs)
 Digital Stopwatch
 Overview

A stopwatch with manual control using GPIO switches, displayed in real-time on the LCD.

 Features

Start, stop, and reset buttons via GPIO switches

Time tracking with Timer1A (HH:MM:SS format)

Periodic tick sound from SysTick + DAC

Dynamic LCD updates

 Example Workflow

Press Start to begin.

Press Stop to pause.

Press Reset to clear to 00:00:00.

 Development Tools

Language: C

IDE: Code Composer Studio

Debugger/Programmer: Onboard ICDI

 Getting Started

Clone the repository.

Open the project in Code Composer Studio.

Connect the TM4C123GXL via USB.

Build and flash the program.

Interact with the game/stopwatch using the switches and LCD.

 Future Improvements

Simon Says: Add difficulty scaling and high-score tracking

Reaction Game: Support multiple rounds with average time scoring

Stopwatch: Add lap-time functionality

