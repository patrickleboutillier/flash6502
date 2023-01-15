import serial
import argparse
import sys

LOADER_CMD =    0x1B
LOADER_UPLOAD = 0xFF
LOADER_STDIN  = 0x00
LOADER_STDOUT = 0x01
LOADER_STDERR = 0x02
LOADER_HALT   = 0x09


parser = argparse.ArgumentParser(prog = 'flash6502loader')
parser.add_argument('PORT')           # Serial port
parser.add_argument('PROG')           # 64k program file
args = parser.parse_args()

# Configure the serial connection
port = serial.Serial(port=args.PORT, baudrate=9600)
# Wait for Arduino to send null byte after reboot 
port.read(1)
# Send our magic number
port.write(b'\x65\x02')

# Read in binary file
with open(args.PROG, "rb") as f:
    prog = f.read()
    
while True:
    data = port.read(1)
    # print("data:{:02X}".format(data[0]))
    if data[0] == LOADER_CMD:
        cmd = port.read(1)
        # print("cmd:{:02X}".format(cmd[0]))
        if cmd[0] == LOADER_UPLOAD:
            # Send program to Arduino
            port.write(prog)
        elif cmd[0] == LOADER_STDIN:
            # Read byte from sdtin
            port.write(sys.stdin.read(1).encode('utf-8'))
        elif cmd[0] == LOADER_STDOUT:    
            sys.stdout.write(port.read(1).decode("utf-8"))
            sys.stdout.flush()
        elif cmd[0] == LOADER_STDERR:    
            sys.stderr.write(port.read(1).decode("utf-8"))
            sys.stdout.flush()
        elif cmd[0] == LOADER_HALT: 
            sys.exit(0)   
    else:
        sys.stdout.write(data.decode("utf-8"))
        sys.stdout.flush()

