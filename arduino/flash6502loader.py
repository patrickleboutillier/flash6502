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
parser.add_argument('PORT')             # Serial port
parser.add_argument('PROG', nargs='?')  # 64k program file
args = parser.parse_args()

# Configure the serial connection
port = serial.Serial(port=args.PORT, baudrate=9600)
# Wait for Arduino to send null byte after reboot 
port.read(1)
# Send our magic number
port.write(b'\x65\x02')
if args.PROG is not None:
    port.write(b'\xFF')     # Program will be uploaded by loader
    # Read in binary file
    with open(args.PROG, "rb") as f:
        prog = f.read()
else:
    port.write(b'\x00')     # Use built-in test suite


    
while True:
    data = port.read(1)
    # print("data:{:02X}".format(data[0]))
    if data[0] == LOADER_CMD:
        cmd = port.read(1)
        # print("cmd:{:02X}".format(cmd[0]))
        if cmd[0] == LOADER_UPLOAD:
            # Send program to Arduino
            # TODO: See if we can write 64 1k blocks to be able to indicate progress...
            offset = 0 
            chunk = 2048
            print()
            while offset < 0x10000:
                port.write(prog[offset:offset+chunk])
                offset = offset + chunk
                print("\r  {:3.0f}% loaded... ".format((offset / 0x10000) * 100), end="", flush=True)
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

