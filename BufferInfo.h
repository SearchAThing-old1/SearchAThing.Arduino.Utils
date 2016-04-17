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

#ifndef _SEARCHATHING_ARDUINO_UTILS_BUFFER_INFO_H
#define _SEARCHATHING_ARDUINO_UTILS_BUFFER_INFO_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DebugMacros.h"

namespace SearchAThing
{

	namespace Arduino
	{

		// Container object for informations about a buffer its maximum
		// length ( capacity ) and its actual length.
		// There aren't provided functions for allocation/deallocation,
		// so any memory management has to be provided out of the box.
		class BufferInfo
		{
			byte *buf = NULL;
			uint16_t len = 0;
			uint16_t capacity = 0;

		public:
			// Default constructor ( note: buf is NULL )
			BufferInfo();

			// Constructor : initialize the container with given buffer
			// pointer and the capacity it has been already allocated
			// out of the box.
			BufferInfo(byte *_buf, uint16_t _capacity);

			// Buffer pointer.
			byte *Buf();

			// Buffer pointer ( const ).
			const byte *ConstBuf() const;

			// Sets the length object variable.
			// Note this not change anything in the allocation storage.
			// If DEBUG;DEBUG_ASSERT defined a warning results if capacity
			// will exceeded.
			void SetLength(uint16_t _newLength);

			// Actual length of the buffer.
			uint16_t Length() const;

			// Capacity of the buffer.
			uint16_t Capacity() const;

		};

	}

}

#endif
