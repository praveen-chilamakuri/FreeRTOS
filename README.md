This repo is for documenting the FreeRTOS + Logic Analyser learning using STM32F411RE Nucleo.



LINKEDIN: https://www.linkedin.com/in/praveen-chilamakuri/



1/9/2026



FreeRTOS preemptive scheduling:


Task 1 (Low Priority): Actively toggles a GPIO pin, every 5 ms. 



Task 2 (High Priority): Another GPIO pin, stays blocked until a user button press triggers an external interrupt (EXTI) and sends a task notification.



When the button is pressed, the FreeRTOS scheduler instantly pauses Task 1 mid-execution. Because Task 1 is frozen in time, its GPIO pin stays stuck HIGH/LOW.



Task 2 takes complete control of the CPU to execute a 100,000 iteration blocking loop. At a 16 MHz clock and with debug optimisation (-O0) generating multiple clock cycles per assembly instruction, this loop takes \~70 ms to complete.



The exact millisecond Task 2 finishes, Task 1 resumes right where it left off.

