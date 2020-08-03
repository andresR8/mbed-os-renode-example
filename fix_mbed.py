#!/usr/bin/env python
import io, os, sys, json

mbed_lib_path='mbed-os/platform/mbed_lib.json'
mbed_overrides_path='mbed-os/targets/TARGET_STM/mbed_overrides.c'

files=[mbed_lib_path,mbed_overrides_path]

for f in files:
    if not os.path.exists(os.path.join(os.getcwd(),f)):
        sys.exit('File not found' + f + '\nFirst run: mbed deploy')


mbed_lib={}
with open(mbed_lib_path, 'r') as json_file:
    mbed_lib = json.load(json_file)

mbed_lib["config"]["use-mpu"]["value"] = False #Disable the use of MPU missing on Renode

with open(mbed_lib_path, "w") as json_file:
    json.dump(mbed_lib, json_file,indent=4)


with open(mbed_overrides_path, 'r') as file:
    mbed_overrides= file.read()

#rupdate the mbed_overrides to solve the UART initialization
mbed_overrides = mbed_overrides.replace('#include \"objects.h\"\n\nint', '#include \"objects.h\"\n#include \"mbed_debug.h\"\n\nint')
mbed_overrides = mbed_overrides.replace('void mbed_sdk_init()\n{\n#', 'void mbed_sdk_init()\n{\n    debug("\\n");\n#') 

with open(mbed_overrides_path, 'w') as file:
    file.write(mbed_overrides)