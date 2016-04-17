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

#ifndef _SEARCHATHING_ARDUINO_UTILS_RAMDATA_H
#define _SEARCHATHING_ARDUINO_UTILS_RAMDATA_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#include "DebugMacros.h"

#include "SList.h"

namespace SearchAThing
{

	namespace Arduino
	{

		// Dynamic ram data container.
		// Can be constructed with an initial size, or with a given input
		// buffer of specified length. Each byte of given input buffer will
		// be copied into a inside allocated memory that will be freed
		// automatically at destruct-time.
		class RamData
		{

		protected:
			uint16_t size = 0;
			byte *buf = NULL;

			void InitWithBytes(const byte *bytes, uint16_t _size);
			void InitWithFlash(const __FlashStringHelper *str);

			int FlashLen(const __FlashStringHelper *str) const;

		public:
			// Copy constructor.
			RamData(const RamData& other);

			// Assign operator.
			RamData& operator = (const RamData& other);

			// Allocate given `_size' ram bytes. If failed .Size()==0
			RamData(uint16_t _size = 0);

			// Constructor with a string of characters ending with leading 0.
			// It stores the characters of the string into inside ram
			// without leading 0 if `appendNullChar' == false (as default).
			RamData(const char *str, bool appendNullChar = false);

			// Constructor with a string of flash characters ending with
			// leading 0.
			// It stores the characters of the string into inside ram
			// without leading 0 if `appendNullChar' == false (as default).
			RamData(const __FlashStringHelper *str);

			// Constructor with a buffer of given size. A memory of the given
			// `_size' will be allocated and the content of the buffer copied
			// into it. Memory will be released at destruct-time.
			RamData(const byte *srcbuf, uint16_t _size);

			// Destructor. Releases allocated memory.
			~RamData();

			// Creates a RamData that store `len' bytes passed inline
			// with the variable arguments after the first len argument.
			// note: data arguments are considered as bytes
			static RamData FromArray(uint16_t len, ...);

			// Creates a RamData that contains the string equivalent the
			// given unsigned 16-bit integer.
			static RamData FromUInt16(uint16_t value); // TODO unit test

			// Release allocated memory and sets size to 0.
			void Clear();

			// Retrieve allocated buffer size.
			uint16_t Size() const;

			// Direct read-write pointer to the buffer of Size() bytes len.
			byte *Buf();

			// Direct read-only pointer to the buffer of Size() bytes length.
			const byte *ConstBuf() const;

			// Bitwise AND operator between this and given `other' RamData
			// bytes. If DEBUG and DEBUG_ASSERT enabled a check about
			// mismatch in two ramdata sizes will be reported if any.
			// Return a ramdata with same size of input argument where
			// each byte is the bitwise and this & other.
			RamData And(const RamData& other) const;

			// Print byte buffer as characters for the len equal to the
			// Size() of ramdata, so there is no need for leading 0 byte.
			void PrintAsChars() const;

			// Returns true if first `bufSize' ramdata bytes are equals
			// to the first given `_buf' bytes. If sizes mismatch returns
			// false.
			bool Equals(const byte *_buf, uint16_t bufSize) const;

			// Returns true if two ramdata are equals in size and byte
			// comparision.
			bool Equals(const RamData& other) const;

			// Returns true if this ramdata equals the given flash string.
			bool Equals(const __FlashStringHelper *str) const;

			// Check if this ramdata start with the specified string token.
			bool StartsWith(const __FlashStringHelper *str, bool equals = false) const; // TODO unit test

			// trim out whitespaces from begin and end as specified.
			RamData Trim(bool begin = true, bool end = true) const;

			// Return this ramdata without beginning string prefix if any.
			RamData StripBegin(const __FlashStringHelper *str) const; // TODO unit test

			// Converts this ramdata to unsigned int 16-bit.
			uint16_t ToUInt16_t() const; // TODO unit test

			// Return composition of this and other bytes.
			RamData Append(RamData other) const; // TODO unit test			

			// Split the ramdata into strings based on the given split char.
			SList<RamData> Split(char c) const
			{
				SList<RamData> res;

				auto i = 0;
				while (i < size)
				{
					while (i < size && buf[i] == c) ++i;
					if (i == size) break;

					auto start = i;
					while (i < size && buf[i] != c) ++i;

					res.Add(RamData(buf + start, i - start));// + ((i == size) ? 0 : 1)));
				}

				return res;
			}

		};

	}

}

#endif
