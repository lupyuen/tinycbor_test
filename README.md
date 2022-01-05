# TinyCBOR Test App for Apache NuttX OS

Read the articles...

-   ["Encode Sensor Data with CBOR on Apache NuttX OS"](https://lupyuen.github.io/articles/cbor2)

-   ["LoRaWAN on Apache NuttX OS"](https://lupyuen.github.io/articles/lorawan3)

To add this repo to your NuttX project...

```bash
cd nuttx/apps/examples
git submodule add https://github.com/lupyuen/tinycbor_test
```

Then update the NuttX Build Config...

```bash
## TODO: Change this to the path of our "incubator-nuttx" folder
cd nuttx/nuttx

## Preserve the Build Config
cp .config ../config

## Erase the Build Config
make distclean

## For BL602: Configure the build for BL602
./tools/configure.sh bl602evb:nsh

## For ESP32: Configure the build for ESP32.
## TODO: Change "esp32-devkitc" to our ESP32 board.
./tools/configure.sh esp32-devkitc:nsh

## Restore the Build Config
cp ../config .config

## Edit the Build Config
make menuconfig 
```

In menuconfig, enable the TinyCBOR Test App under "Application Configuration" → "Examples".

In NuttX Shell, enter this to run the app...

```bash
tinycbor_test
```

# Output Log

```bash
nsh> tinycbor_test
test_cbor: Encoding { "t": 1234 }
CBOR Output: 6 bytes
  0xa1
  0x61
  0x74
  0x19
  0x04
  0xd2
test_cbor2: Encoding { "t": 1234, "l": 2345 }
CBOR Output: 11 bytes
  0xa2
  0x61
  0x74
  0x19
  0x04
  0xd2
  0x61
  0x6c
  0x19
  0x09
  0x29
```
