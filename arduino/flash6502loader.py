import serial
import argparse
import sys

LOADER_CMD =    0x1B
LOADER_UPLOAD = 0xFF
LOADER_STDIN =  0x00
LOADER_STDOUT = 0x01
LOADER_STDERR = 0x02


parser = argparse.ArgumentParser(prog = 'flash6502loader')
parser.add_argument('PORT')           # Serial port
parser.add_argument('PROG')           # 64k program file
args = parser.parse_args()

# Configure the serial connection
port = serial.Serial(port=args.PORT, baudrate=115200)
port.write(b'\x65\x02')

# Read in binary file
with open(args.PROG, "rb") as f:
    prog = f.read()
    
while True:
    data = port.read(1)
    if data == LOADER_CMD:
        cmd = port.read(1)
        if cmd == LOADER_UPLOAD:
            # Send program to Arduino
            for b in prog:
                port.write(b)
        # Do stuff with byte.
        elif cmd == LOADER_STDIN:
            # Read byte from sdtin
            pass
        elif cmd == LOADER_STDOUT:    
            sys.stdout.write(port.read(1))
        elif cmd == LOADER_STDERR:    
            sys.stderr.write(port.read(1))
    else:
        sys.stdout.write(data.decode("utf-8"))
        sys.stdout.flush()

