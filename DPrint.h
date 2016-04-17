/*
* The MIT License(MIT)
* Copyright(c) 2016 Lorenzo Delana, https://searchathing.com
*
* Permission is hereby granted, free of charge, to any person obtaining a
* copy of this software and associated documentation files (the "Software"),
* to deal in the Software without restriction, including without limitation
* the rights to use, copy, modify, merge, publish, distribute, sublicense,
* and/or sell copies of the Software, and to permit persons to whom the
* Software is furnished to do so, subject to the following conditions:
*
* The above copyright notice and this permission notice shall be included in
* all copies or substantial portions of the Software.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
* FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
* DEALINGS IN THE SOFTWARE.
*/

#ifndef _SEARCHATHING_ARDUINO_UTILS_DPRINT_H
#define _SEARCHATHING_ARDUINO_UTILS_DPRINT_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DebugMacros.h"

#ifdef DPRINT_SERIAL
#define BAUD SERIAL_SPEED
#include <util/setbaud.h>
#endif

namespace SearchAThing
{

	namespace Arduino
	{

		class RamData;

		extern bool _DPrintInitialized;
		// Initializes the debug output line.
		// If DSERIAL_PRINT is defined then the serial with the SERIAL_SPEED
		// will be used as output line. Its an internal function that is
		// called automatically when DPrint functions are used.
		void _DPrintInit();

		// Prints a newline.
		void DNewline();

		// Prints a newline.
		void DPrintln();

		// Prints a single char.
		void DPrint(char c);

		// Prints a single char.
		// followed by a newline.
		void DPrintln(char c);

		// Prints given char for `cnt' times.
		void DPrintX(char c, uint16_t cnt);

		// Prints given char for `cnt' times.
		// Follows a newline.
		void DPrintXln(char c, uint16_t cnt);

		// Prints numeric value of the given byte.
		void DPrint(byte b);

		// Prints numeric value of the given byte.
		// Follows a newline.
		void DPrintln(byte b);

		// Prints numeric value (0,1) of the given boolean.
		void DPrint(bool b);

		// Prints numeric value (0,1) of the given boolean.
		// Follows a newline.
		void DPrintln(bool b);

		// Prints numeric value of the given unsigned 16bit integer.
		void DPrint(uint16_t x);

		// Prints numeric value of the given unsigned 16bit integer.
		// Follows a newline.
		void DPrintln(uint16_t x);

		// Prints numeric value of the given signed 16bit integer.
		void DPrint(int16_t v);

		// Prints numeric value of the given signed 16bit integer.
		// Follows a newline.
		void DPrintln(int16_t v);

		// Prints numeric value of the given unsigned 32bit integer.		
		void DPrint(unsigned long v);

		// Prints numeric value of the given unsigned 32bit integer.		
		// Follows a newline.
		void DPrintln(unsigned long v);

		// Prints numeric value of the given signed 32bit integer.		
		void DPrint(signed long v);

		// Prints numeric value of the given signed 32bit integer.		
		// Follows a newline.
		void DPrintln(signed long v);

		// Prints numeric value of the given float with specified precision.
		void DPrint(float v, int prec = 2);

		// Prints numeric value of the given float with specified precision.
		// Follows a newline.
		void DPrintln(float v, int prec = 2);

		// Prints given flash string. Note: Use F("str") to pass argument.
		void DPrint(const __FlashStringHelper *str);

		// Prints given flash string. Follows a newline.
		// Note: Use F("str") to pass argument.		
		void DPrintln(const __FlashStringHelper *str);

		// Prints given string of chars until leading null char excluded.
		void DPrint(const char *str);

		// Prints given string of chars until leading null char excluded.
		// Follows a newline.
		void DPrintln(const char *str);

		// Prints given array of char for the given size.
		// Useful when a leading null char isn't available.
		void DPrint(const char *str, int size);

		// Prints given array of char for the given size.		
		// Useful when a leading null char isn't available.
		// Follows a newline.
		void DPrintln(const char *str, int size);

		// Prints `size' chars from the given flash string.
		// Note: Use F("str") to pass the argument.
		void DPrint(const __FlashStringHelper *str, int size);

		// Prints `size' chars from the given flash string.		
		// Note: Use F("str") to pass the argument.
		// Follows a newline.
		void DPrintln(const __FlashStringHelper *str, int size);

		// Prints '0' if the given numeric value is 0 and `1' otherwise.
		void DPrintBool(int v);

		// Prints '0' if the given numeric value is 0 and `1' otherwise.
		// Follows a newline.
		void DPrintBoolln(int v);

		// Prints numerical value of first `len' bytes of the given buffer
		// `buf' separating each number with the given separator `sep' char.
		void DPrintBytes(const byte *buf, uint16_t len, char sep = '.');

		// Prints numerical value of first `len' bytes of the given buffer
		// `buf' separating each number with the given separator `sep' char.
		// Follows a newline.
		void DPrintBytesln(const byte *buf, uint16_t len, char sep = '.');

		// Prints numerical value of all bytes in the `data' if `len'==-1 or
		// given `len'>=0 bytes separating each number with the given
		// separator `sep' char.
		void DPrintBytes(const RamData& data, int16_t len = -1, char sep = '.');

		// Prints numerical value of all bytes in the `data' if `len'==-1 or
		// given `len'>=0 bytes separating each number with the given
		// separator `sep' char.
		// Follows a newline.
		void DPrintBytesln(const RamData& data, int16_t len = -1, char sep = '.');

		// Prints lowercase hexadecimal value of the given byte.
		void DPrintHex(byte b);

		// Prints lowercase hexadecimal value of the given byte.
		// Follows a newline.
		void DPrintHexln(byte b);

		// Prints lowercase hexadecimal value of the given unsigned 16bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		void DPrintHex(uint16_t v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 16bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		// Follows a newline.
		void DPrintHexln(uint16_t v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 32bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		void DPrintHex(unsigned long v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given unsigned 32bit
		// integer prefixed with "0x" string when `prefix' option is set
		// to true.
		// Follows a newline.
		void DPrintHexln(unsigned long v, bool prefix = false);

		// Prints lowercase hexadecimal value of the given `len' bytes buffer
		// separating each with `sep' char.
		void DPrintHexBytes(const byte *buf, uint16_t len, char sep = '-');

		// Prints lowercase hexadecimal value of the given `len' bytes buffer
		// separating each with `sep' char.
		// Follows a newline.
		void DPrintHexBytesln(const byte *buf, uint16_t len, char sep = '-');

		// Prints lowercase hexadecimal value of all bytes in the `data' if
		// `len'==-1 or given `len'>=0 bytes separating each number with the
		// given separator `sep' char.
		void DPrintHexBytes(const RamData& data, int16_t len = -1, char sep = '-');

		// Prints lowercase hexadecimal value of all bytes in the `data' if
		// `len'==-1 or given `len'>=0 bytes separating each number with the
		// given separator `sep' char.
		// Follows a newline.
		void DPrintHexBytesln(const RamData& data, int16_t len = -1, char sep = '-');

		// Prints lowercase hexdecimal value of `len' bytes of the given
		// buffer in sequence (if `prettyPrint'==false) or in two column 8+8
		// space separated and addressed (when `prettyPrint'==true).
		void DPrintHex(const byte *buf, uint16_t len, bool prettyPrint = false);

		// Prints lowercase hexdecimal value of `len' bytes of the given
		// buffer in sequence (if `prettyPrint'==false) or in two column 8+8
		// space separated and addressed (when `prettyPrint'==true).
		// Follows a newline.
		void DPrintHexln(const byte *buf, uint16_t len, bool prettyPrint = false);

		// Print ramdata bytes content as chars.
		void DPrint(const RamData& rd);

		// Print ramdata bytes content as chars.
		// Follows a newline.
		void DPrintln(const RamData& rd);

	}

}

#endif
