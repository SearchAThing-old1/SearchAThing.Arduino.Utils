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

#ifndef _SEARCHATHING_ARDUINO_UTILS_UTIL_H
#define _SEARCHATHING_ARDUINO_UTILS_UTIL_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DebugMacros.h"

#define BOARD_MAX_MEMORY	(RAMEND-RAMSTART)

namespace SearchAThing
{

	namespace Arduino
	{

		// Returns available fragmented free memory available.
		int FreeMemorySum();

		// Returns max contiguous block of ram free by testing through a
		// bisection algorithm that starts from the `upperLimit' given
		// checking using the `malloc' exitcode.
		int FreeMemoryMaxBlock(int upperLimit = BOARD_MAX_MEMORY);

		// Prints total fragmented memory available and the max contiguos
		// block of free ram allocatable.
		void PrintFreeMemory();

		// Prints the ram layout (data,bss,heap,stack).
		void PrintRAMLayout();

		// Compute time delta (ms) between given `now' and reference `start'.
		// Pre: `start' must be a value of time taken from millis()
		// effectively before the `now.
		unsigned long TimeDiff(unsigned long start, unsigned long now);

		// Write the given unsigned 16bit integer into the given bytes buffer
		// (msb mode).
		void BufWrite16(byte *buf, uint16_t v);

		// Write the given unsigned 32bit integer into the given bytes buffer
		// (msb mode).
		void BufWrite32(byte *buf, uint32_t v);

		// Read 2 bytes from the given buffer pointer composing an unsigned
		// 16bit integer (msb mode).
		uint16_t BufReadUInt16_t(byte *buf);

		// Read 4 bytes from the given buffer pointer composing an unsigned
		// 32bit integer (msb mode).
		uint32_t BufReadUInt32_t(byte *buf);

		// Converts the given float into a string.
		void FloatToString(char *buf, float f, int prec);	

	}

}

#endif
