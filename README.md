# Patient Monitoring System built on top of POSIX SJ2-c (https://gitlab.com/sjtwo-c-dev/sjtwo-c)
We have simulated a patient monitoring system using FreeRTOS. It includes task functions for monitoring patient data such as heart rate, blood pressure, and SpO2, distributing tasks among caretakers, nurses, and doctors based on predefined thresholds and random decision-making. Queues are utilized for inter-task communication. The main function initializes queues and tasks, specifying their parameters and priorities, before starting the FreeRTOS scheduler. The system reads patient data from files, sends messages to task queues based on thresholds, and simulates task distribution among healthcare professionals namely: Caretaker unit, Nursing unit (with 4 nurses), doctor unit (with 2 on-call doctors) and one on-demand doctor. 

Task Priority used:
Priority of HeartRate: 1
Priority of SPO2 concentration: 2
Priority of Blood Pressure: 3
Priority of Caretaker : 4
Priority of Nurse: 5
Priority of Doctor: 6
Priority of on demand doctor: 7

Delay for each Healthcare unit:
Delay of Caretaker queue(taskqueue): 1000ms
Delay of Nurses queue: 2000ms
Delay of Doctor queue: 3000ms
Delay of on call doctor: 3000ms
# Code
Find the code under projects/x86_freertos/main.c
Run the project on a linux system.
Replace the files for SPO2,BP,heartrate with own files and change path in main.c 
# Demo
https://github.com/user-attachments/assets/b38df903-b33f-4730-acbc-53563af4ad7b

# Flowchart
![sys_PMS](https://github.com/user-attachments/assets/f25ffa98-162f-48e7-9701-2dd4fe4d6336)

# System Overview

![PMS_SYS_OVER](https://github.com/user-attachments/assets/e4cf0b8b-4447-4134-9dda-932640373779)


----From the sjtwo-c repo -----
# SJ2-C Development Environment

An `SJ2` board is used at San Jose State University (SJSU) to teach Embedded Systems' courses. Part of this Git repository also includes development environment for not just an ARM controller, but also support to compile and test software on your host machine such as Windows, Mac etc.

The sample project of the SJ2 board contains code written in C that anyone can understand easily. It was designed to **learn the low level workings of a microcontroller platform with an RTOS**:

Project highlights:

- Fully implemented in C
- Minimalistic design with little to no abstractions
- Follows good coding principles (such as YAGNI and DRY)

Infrastructure highlights:

- Supports Mac, Linux, Windows out of the box
- Version controlled toolchains and other supplementary tools
- No VMs
- No WSL dependency on Windows

----

## Next Steps

- [Build and Flash Project](README-GETTING-STARTED.md) 
- [Read more about SCons](README-SCons.md) to figure out how to build projects

## Videos

We have made some videos that you may find useful

- [Comprehensive Development Environment](https://www.youtube.com/watch?v=EbiCummaIM0)
- [Compile ARM project](https://www.youtube.com/watch?v=--AL0VKzvU8)

----

## Build System

We use [SCons](https://scons.org/) as our build platform. The developers of SJ2-C applied experience of diverse set of build systems acquired over many years, and resorted to this one. The candidates were:

- SCons (used at Tesla, and many other companies)
- Bazel (used at Google, Zoox and many other companies)
- Make

SCons discusses the advantages and disadvantages of other existing build systems: [Build System Comparison](https://github.com/SCons/scons/wiki/sconsvsotherbuildtools)

From experience, we can state that `bazel` is really cool, but hard to extend and problematic in Windows. SCons dependencies are tricky, but it is based on python and easy to understand and extend. SCons takes advantage of a Python interpreter making it portable across multiple platforms (Mac, Linux, Windows).

----

## History

We wanted to build a strong foundational sample project for SJ-2 development board that is used at SJSU.

Originally, Preet created "SJ1" development board, which meant that there was one development board across multiple classes at SJSU. I was an enthusiast and created a hybrid project composed of C and C++ sources. I love C++ a little more than C because I can express artistic designs in the language, but a language is really a tool, and you need to select the right tool for the job. Presently I work on Embedded *Firmware* code for automotive industry which is in C, and *Software* code in C++, because C is the right tool for firmware, and C++ is the right tool for software. "SJ2" [original](https://github.com/kammce/SJSU-Dev2) software was also designed by an enthusiast (Khalil), who is a very talented person, but expressing a starter project in C++ increased the complexity so much that many developers had a difficult time adopting it.

This is where the *SJ2-C* was born, which was completely re-designed to write simple code that everyone could understand. Many students are new to programming and it was not expected that C++ would come naturally. The code may appear less fancy, but it is simple to understand and traceable with minimal abstractions. The goal is to avoid designing yet another Arduino platform. There is no such thing as magic in the field of firmware engineering.

----
