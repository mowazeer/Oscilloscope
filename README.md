# Oscilloscope 
The project has two main parts:  
1- Six Channel Oscilloscope that allows the user to select Time per Division and the used channel, to draws the input signal and calculates: 
  • Frequency 
  • Periodic Time 
  • (Minimum, Maximum and Average) Volt  
2- Signal generator that can generate “32 software PWM signal” with different Frequency and different Duty cycle at the same time.  
-Although I can generate the signal using: 
  • "TMU" that refers to Time management unit 
  • "SOS" that refer to a small OS or non-preemptive scheduler

## Watch The video to know more about my Oscilloscopee.
[![Oscilloscope](https://drive.google.com/open?id=1pM88eYPzky2qfbIlj5tIme_ANgS9Gsia)

## Hardware Components:
Oscilloscope:
     • ATMEGA32
     • LCD_TFT_ili9486
     • Two Potentiometer “10k ohm”
Signal Generator :
     • ATMEGA32
     • LED

## Target:
   * MCAL Layer for atmega32.
   * Just change the MCAL Folder with your own target.
