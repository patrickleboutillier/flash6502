
# flash6502
Trying to build a 6502-compatible CPU on breadboards, using as few chips as possible.

## Introduction
For a while I've been working on small projects that implement various "toy/fictitious" CPUs (namely the [Scott CPU](https://github.com/patrickleboutillier/jcscpu-hmc)) using discrete components, but I grew frustrated for 2 reasons:

1. Memory space is usually to small to create useful/fun programs.
2. You have to write your own assembler and tool chain.

After viewing Ben Eater's great video series on the 6502, I wondered if it might be possible to implement a 6502 CPU (not *a computer using a 6502 CPU chip*...) on breadboards using discrete components. Also, since breadboard projects tend to take up a lot of space very quickly (in squares inches I mean), I decided to try and use the least amount of chips possible, ideally under 40.

## Architecture

### Architecture Decisions
In order to achieve these goals, I made the following architecture decisions:

- It's ok if it's slower (perhaps even some orders of magnitude slower) than a real 6502.
- It's ok for the design to be assisted by a microcontroller (i.e. Arduino) for power, clocking and for some complicated parts like the reset sequence.
- It's ok if it doesn't run actual existing 6502 ROMs, but it has to run programs that I write myself using a standard 6502 assembler.
- It's ok if the actual 6502 timing is not respected.
- It's ok to use chips that did not exist at the time the 6502 was designed, namely large ROMs (which are used extensively), in order to keep the chips count low and simplify the design.

### High-Level Architecture
The system is made up of 8 sections, which I will refer to using the following names:

- **Registers**: contains the Arduino controller, as well as the X, Y and ACC registers.
- **ALU**: contains the 8-bit ALU with 16 operations, as well as the A and B registers that are connected to it.
- **Status**: contains the status (P) register, as well as the status logic implementd in a ROM chip. There is also a multiplexer to select the source for the status bits (ALU or data bus) and a buffer to control sending the status byte to the data bus.
- **Data Bus**: the 8 bit data bus.
- **Address Low**: contains the low bytes of the stack pointer (SP), the program counter (PC) and the effective address (EA) register, all connected to the "address low" bus, as well as a buffer to allow sourcing any of these from the data bus.
- **Address High**: contains the high bytes of the stack pointer (SP), the program counter (PC) and the effective address (EA) register, all connected to the "address low" bus, as well as a buffer to allow sourcing any of these (except the high byte of SP which is a constant) from the data bus.
- **RAM**: contains the instruction register (INST), the 64k RAM chip (connected to the "address low" and "address high" busses, as well as the data bus) and the memory mapping logic, as well as 2 buffers allowing to send the contents of the "address low/high" buses to the data bus.
- **Control Unit**: contains the stepping logic and 5 ROM chips that handle the 40 control signals. Each ROM chip receives the output of the step counting (6 bits), the output of the INST register (8 bits), as well as 4 other input signals that vary depending on the chip.

### Breadboard Block Diagram
![Block Diagram](https://github.com/patrickleboutillier/flash6502/raw/feature/docs/images/block_architecture.jpeg)

## Sections
### Registers
![Registers](https://github.com/patrickleboutillier/flash6502/raw/feature/docs/images/reg.jpg)

The Registers section contains 3 registers, ACC, X and Y, implemented using SN74HC373 chips. These registers are connected to the Data Bus. There are 6 control signals used to set or enable each of these 3 registers: *ACC_e*, *ACC_s*, *X_e*, *X_s*, *Y_e*, *Y_s*.

### ALU
![ALU](https://github.com/patrickleboutillier/flash6502/raw/feature/docs/images/alu.jpg)

The ALU section contains 2 registers, A and B, implemented using SN74HC373 chips. These registers can be set from the Data Bus, and their outputs are fed directly into the ALU. The ALU is made up of 2 SST39SF020A Flash chips. It has 16 operations that can be selected using 4 controls bits.
The operations are defined as such:

Here are the details of each of the pins for the 2 Flash chips, ALU Low and ALU High:
#### ALU Low
- A16, A15, A12, A7: The lower nibble of the A register.
- A3, A2, A1, A0: The lower nibble of the B register.
- A13, A8, A9, A11: The ALU operation (see above).
- A10: The "ALU carry" output of the Status section.
- A17: Bit 4 of the B register. Used, for example, during the "shift right" operations.
- A14: Bit 7 of the B register. Used during the "sign extend" operation. 
- DQ3, DQ2, DQ1, DQ0: The result of the operation (these pins are connected to the Data Bus).
- DQ6: The "zero" output of the operation.
- DQ5: The "carry" output of the operation.
- DQ4: The "shift" output of the operation.
- OE#: Connected to the *ALU_e* control signal used to enable the result onto the Data Bus.

#### ALU High

#### Control signals
The control signals for the sections are *ALU[3-0]*, *ALU_e*, *A_s* and *B_s*.

### Status
### Data Bus
### Address Low
### Address High
### RAM
### Control Unit
### Arduino Controller
