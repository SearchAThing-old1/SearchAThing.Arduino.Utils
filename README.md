# SearchAThing.Arduino.Utils

Just to modularize some aspect of the software built with Arduino I developed this simple library that contains in summary the following:

| topic | description |
|---|---|
| DPrint | Function to print through the serial or other devices without to use Serial.print ( to save some bytes on the flash ) |
| TimeDiff | A function that help to compute the time difference managing uint32 overflow |
| FreeMemory | Functions to retrieve free memory ( fragmented and contiguos ) |
| BufferInfo | Just a container for a dynamic pointer with its size ( without memory management ) |
| IdStorage | Compact set of ids |
| SList | A templated simple linked list |
| RamData | A container of bytes, but can be used for strings too, that allocate and deallocate memory dynamically with some useful functions such as string comparision, word splitting, etc |
| BufWrite/Read | Read/Write uint16 and uint32 from and to a bytes buffer using MSB order |

> For a technical documentation of the API please refer to the documentation contained inside the source code header files accessible through the IDE intellisense.

## Source code

To instal the library just clone [this git repository](https://github.com/devel0/SearchAThing.Arduino.Utils) into your Documents/Arduino/libraries folder.

## DPrint

### Introduction

The need for a dprint routine come to me todo some hex formatting of 16bit and 32bit values with arbitrary byte order and to reduce the size of the flash used by removing the usage of the Serial and vsnprintf references. Here some comparision of the flash / ram program size ( bytes )

In short using DPrint about 1K flash and 200 bytes of RAM can be saved that for an atmega328 are ~3% of the Flash and ~10% RAM.

### Test conditions

- print without newlines ( Serial.print, DPrint )
- print string with sample "HI"
- cast over argument types ( eg. DPrint((uint16_t)1); )

### Example

```cplusplus
// Copyright(c) 2016 Lorenzo Delana, https://searchathing.com, License under MIT

//===========================================================================
// EXAMPLE	: ex01-dprint.ino
//===========================================================================
// Setup()
//   - Print some data using the speed as defined by the SERIAL_SPEED macro
// Loop()
//---------------------------------------------------------------------------
// Suggested defines for this example
//---------------------------------------------------------------------------
// SEARCHATHING_DISABLE;DPRINT_SERIAL;SERIAL_SPEED=9600
//

// SearchAThing.Arduino debug macro definitions
#include <SearchAThing.Arduino.Utils\DebugMacros.h>

//---------------------------------------------------------------------------
// Libraries
//---------------------------------------------------------------------------
#include <SearchAThing.Arduino.Utils\Util.h>
using namespace SearchAThing::Arduino;

//---------------------------------------------------------------------------
// Setup
//---------------------------------------------------------------------------
void setup()
{
  // Note : DPrint serial begin automatic using speed from the macro
  //        SERIAL_SPEED

  auto r = 5.60;

  DPrint(F("Circle r=")); DPrint((float)r);
  DPrint(F(" C=")); DPrint((float)(2 * r * PI));
  DPrint(F(" A=")); DPrint((float)(r * r * PI));
}

//---------------------------------------------------------------------------
// Loop
//---------------------------------------------------------------------------
void loop()
{
}
```
