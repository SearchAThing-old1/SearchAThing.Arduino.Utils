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

#include "DebugMacros.h"
#include "BufferInfo.h"

namespace SearchAThing
{

	namespace Arduino
	{		
		
		BufferInfo::BufferInfo()
		{
		}

		BufferInfo::BufferInfo(byte *_buf, uint16_t _capacity)
		{
			buf = _buf;
			len = capacity = _capacity;
		}

		byte *BufferInfo::Buf() { return buf; }
		const byte *BufferInfo::ConstBuf() const { return buf; }
		
		void BufferInfo::SetLength(uint16_t newLength)
		{			
			if (newLength > capacity)
			{
#if defined DEBUG && defined DEBUG_ASSERT
				DPrintln(F("* Fatal : len>capacity"));
#endif
				newLength = capacity;
			}
			len = newLength;
		}
		uint16_t BufferInfo::Length() const { return len; }
		uint16_t BufferInfo::Capacity() const { return capacity; }

	}

}
