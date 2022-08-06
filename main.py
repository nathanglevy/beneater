import os.path
import subprocess
import sys


def vasm(asm_file: str):
    filename = os.path.basename(asm_file)
    name = filename.rsplit('.', 1)[0]
    target = "images/" + name + ".bin"
    subprocess.call(["./vbcc/bin/vasm6502_oldstyle.exe", asm_file, "-dotdir", "-Fbin", "-o", target])
    return target


def minipro(bin_file: str):
    subprocess.call(["./minipro/minipro/minipro.exe", "-p", "AT28C256", "-w", bin_file])

# Press the green button in the gutter to run the script.
if __name__ == '__main__':
    asm_file = sys.argv[1]
    print("########################################################################")
    print("reading asm file: " + asm_file)
    print("########################################################################")
    bin_file = vasm(asm_file)
    print("########################################################################")
    print("writing bin file: " + bin_file + " to ROM")
    print("########################################################################")
    minipro(bin_file)
    print("########################################################################")
    print("done writing to ROM")
    print("########################################################################")

# See PyCharm help at https://www.jetbrains.com/help/pycharm/
