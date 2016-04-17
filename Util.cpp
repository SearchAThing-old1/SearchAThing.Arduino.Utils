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

//===========================================================================
// info about data,bss,heap,staack in
// #include <stdlib.h>
//---------------------------------------------------------------------------
struct __freelist
{
	size_t sz;
	struct __freelist *nx;
};

extern char *__brkval;
extern struct __freelist *__flp;
extern size_t __malloc_margin;
extern char *__malloc_heap_start;
extern char __heap_start;

extern char *__data_start;
extern char *__data_end;
extern char *__bss_start;
extern char *__bss_end;
//---------------------------------------------------------------------------

#include <limits.h> // ULONG_MAX
#include <MemoryFree\MemoryFree.h> // freeMemory()

#include "Util.h"
#include "SList.h"

namespace SearchAThing
{

	namespace Arduino
	{

		int FreeMemorySum()
		{
			return freeMemory();
		}

		int FreeMemoryMaxBlock(int upper)
		{
			int size = upper;
			int lower = 0;

#if defined DEBUG && defined DEBUG_FREE_MEMORY_MAX
			DPrintln();
#endif

			while ((upper - lower) > 1)
			{
#if defined DEBUG && defined DEBUG_FREE_MEMORY_MAX
				DPrint("try="); DPrint(size);
#endif

				void *buf = malloc(size);

				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_FREE_MEMORY_MAX
					DPrint(" fail\t");
#endif
					// exclude size as upper limit decreasing by 1
					upper = size - 1;
				}
				else // successful on size
				{
#if defined DEBUG && defined DEBUG_FREE_MEMORY_MAX
					DPrint(" ok\t");
#endif

					free(buf);
					// sets new lower limit
					lower = size;
				}

				// checks between half of upper-lower bounds
				size = lower + (upper - lower) / 2;

#if defined DEBUG && defined DEBUG_FREE_MEMORY_MAX
				DPrint("upper="); DPrint(upper); DPrint(" size="); DPrint(size); DPrint(" lower="); DPrint(lower);
				DPrint(" diff="); DPrintln(upper - lower);
#endif				
			}

			return size + 4 * sizeof(int) + sizeof(void *);
		}

		void PrintFreeMemory()
		{
			DPrint(F("free blk=")); DPrint(FreeMemoryMaxBlock());
			DPrint(F(" frg=")); DPrintln(FreeMemorySum());
		}

		// http://www.nongnu.org/avr-libc/user-manual/malloc.html
		void PrintRAMLayout()
		{
			byte stack = 0;

			void *myCurStack = &stack;

			DPrintln(F("RAM LAYOUT"));
			DPrintXln('-', 20);
			DPrint(F("__malloc_margin\t\t")); DPrintln(__malloc_margin);

			DNewline();
			DPrint(F("__data_start\t\t")); DPrintHexln((size_t)&__data_start, true);
			DPrint(F("__data_end\t\t")); DPrintHexln((size_t)&__data_end, true);

			DNewline();
			DPrint(F("__bss_start\t\t")); DPrintHexln((size_t)&__bss_start, true);
			DPrint(F("__bss_end\t\t")); DPrintHexln((size_t)&__bss_end, true);

			DNewline();
			DPrint(F("__malloc_heap_start\t")); DPrintHexln((size_t)__malloc_heap_start, true);
			DPrint(F("__heap_start\t\t")); DPrintHexln((size_t)&__heap_start, true);
			DPrint(F("__brkval\t\t")); DPrintHexln((size_t)__brkval, true);
			DPrint(F("SP - __malloc_margin\t")); DPrintHexln((SP - __malloc_margin), true);

			DNewline();
			DPrint(F("SP\t\t\t")); DPrintHexln(SP, true);
			DPrint(F("myCurStack\t\t")); DPrintHexln((uint16_t)&myCurStack, true);
			DPrint(F("RAMEND\t\t\t")); DPrintHexln((uint16_t)RAMEND, true);

			// Free List

			DNewline();
			DPrintln(F("FREE LIST"));
			DPrintXln('-', 20);
			struct __freelist *fp = __flp;

			DPrint(F("__flp\t\t\t")); DPrintHexln((size_t)__flp, true);
			DNewline();

			while (fp != NULL)
			{
				DPrint(F("fp=")); DPrintHex((size_t)fp, true);
				DPrint(F(" sz=")); DPrint(fp->sz);
				DPrint(F(" nx=")); DPrintHexln((size_t)fp->nx, true);

				fp = fp->nx;
			}

		}

		unsigned long TimeDiff(unsigned long start, unsigned long now)
		{
			if (start <= now)
				return now - start;
			else
				return (ULONG_MAX - start) + now + 1;
		}

		void BufWrite16(byte *buf, uint16_t v)
		{
			buf[0] = highByte(v);
			buf[1] = lowByte(v);
		}

		void BufWrite32(byte *buf, uint32_t v)
		{
			buf[0] = (byte)(v >> 24);
			buf[1] = (byte)(v >> 16);
			buf[2] = (byte)(v >> 8);
			buf[3] = (byte)(v & 0xff);
		}

		uint16_t BufReadUInt16_t(byte *buf)
		{
			return
				((uint16_t)buf[0]) << 8 |
				buf[1];
		}

		uint32_t BufReadUInt32_t(byte *buf)
		{
			return
				((uint32_t)buf[0]) << 24 |
				((uint32_t)buf[1]) << 16 |
				((uint32_t)buf[2]) << 8 |
				buf[3];
		}

		void FloatToString(char *buf, float f, int prec)
		{
			auto x = (int32_t)f;

			ltoa(x, buf, DEC);
			
			if (prec > 0)
			{
				char *p = buf + strlen(buf);
				*p = '.';
				++p;

				if (x < 0) { x *= -1L; f *= -1.0; }

				auto frac = f - (float)x;
				
				while (prec)
				{
					frac *= 10.0;
					auto y = (uint32_t)frac;
					*p = (byte)'0' + (byte)y;
					++p;

					frac -= y;
					--prec;
				}
				*p = 0;
			}
		}
	}

}
