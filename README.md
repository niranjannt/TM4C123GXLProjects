# ⚙️ TM4C123GXL Embedded Systems Projects  

This repository showcases multiple embedded systems projects developed on the **Texas Instruments TM4C123GXL (Tiva C Series LaunchPad)** using **C** and **Code Composer Studio**.  
Each project integrates **timers**, **GPIO**, **LCD display**, and **audio feedback** to create interactive real-time systems.

---

## 🧠 Projects Overview  

<details>
<summary><b>🎮 Simon Says Memory Game</b></summary>

A memory-based game inspired by *Simon Says*, where the player replicates increasingly long LED sequences. Audio tones and LCD feedback enhance interactivity.

### ✨ Features
- LED sequence generation using **SysTick** and **Timer1A**  
- Audio tones via **4-bit resistor DAC**  
- Correct/incorrect feedback with buzzer tones  
- LCD messages: *“Round X Passed”* or *“Game Over”*  
- Dynamic sequence-tracking logic using arrays and GPIO switch input  

### 🕹️ Example Workflow
1. System flashes a sequence (e.g., Red → Green → Yellow).  
2. Player repeats the sequence using switches.  
3. Correct → next round with extended sequence.  
4. Incorrect → buzzer + *“Game Over”* message.

</details>

---

<details>
<summary><b>⚡ LED Reaction Time Game</b></summary>

A game that measures how quickly the player reacts to a randomly lit LED. Reaction times are displayed on the LCD in milliseconds.

### ✨ Features
- Random LED activation with **SysTick**  
- Reaction time measurement via **Timer1A**  
- Switch-based user input detection  
- LCD display: *“Reaction Time: XXX ms”*

### 🕹️ Example Workflow
1. LED lights up after a random delay.  
2. Player presses the switch as quickly as possible.  
3. LCD displays the reaction time result.  

</details>

---

<details>
<summary><b>⏱️ Digital Stopwatch</b></summary>

A digital stopwatch with start, stop, and reset controls, displaying elapsed time on the LCD in real time.

### ✨ Features
- Controlled via **GPIO switches** (Start / Stop / Reset)  
- Time tracking with **Timer1A** (HH:MM:SS format)  
- Periodic tick sound via **SysTick + DAC**  
- Dynamic LCD updates  

### 🕹️ Example Workflow
1. Press **Start** to begin timing.  
2. Press **Stop** to pause.  
3. Press **Reset** to clear to 00:00:00.  

</details>

---

<details>
<summary><b>🕒 LCD Digital Clock</b></summary>

A real-time digital clock displayed on the ST7735 LCD, capable of showing time in **12-hour AM/PM** format with manual adjustment.

### ✨ Features
- Real-time tracking using **SysTick**  
- LCD display in **HH:MM:SS AM/PM** format  
- Manual **time setting controls** via GPIO switches  
- AM/PM toggle functionality  
- Periodic tick sound using **DAC output**

### 🕹️ Example Workflow
1. Clock updates continuously every second.  
2. Use buttons to adjust **hours**, **minutes**, or **toggle AM/PM**.  
3. LCD reflects all changes in real time.

</details>

---

## 🔩 Hardware Components  

| Component | Description |
|------------|-------------|
| **TM4C123GXL LaunchPad** | Main microcontroller board |
| **ST7735 LCD** | SPI interface for text and graphics |
| **4-bit Resistor DAC + Piezo Buzzer** | Generates audio tones |
| **Onboard LEDs** | Red, Green, Yellow indicators |
| **Push-button Switches** | Used for input and control |

---

## 🧰 Development Setup  

**🧑‍💻 Tools Used**
- **Language:** C  
- **IDE:** Code Composer Studio  
- **Debugger/Programmer:** Onboard ICDI  

**🚀 Getting Started**
1. Clone this repository.  
2. Open the desired project in Code Composer Studio.  
3. Connect the TM4C123GXL via USB.  
4. Build and flash the program.  
5. Interact using the switches and LCD display.

---

## 🌟 Future Improvements  

| Project | Planned Enhancements |
|----------|----------------------|
| **Simon Says** | Add difficulty scaling and high-score tracking |
| **Reaction Game** | Support multiple rounds with average time scoring |
| **Stopwatch** | Add lap-time tracking functionality |
| **LCD Clock** | Add alarm feature and 24-hour time option |

---

## 🧾 License  
This project is provided for educational and personal use.  

---

🛠 These were summer passion projects developed using **Code Composer Studio** and the **TM4C123GXL Tiva C LaunchPad**.
