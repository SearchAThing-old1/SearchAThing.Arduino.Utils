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
#include "RamData.h"
#include "Util.h"
#include "DPrint.h"

#include <stdarg.h>

namespace SearchAThing
{

	namespace Arduino
	{

		void RamData::InitWithBytes(const byte *bytes, uint16_t _size)
		{
			size = _size;
			if (size > 0)
			{
				buf = (byte *)malloc(size);
				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
				else
					memcpy(buf, bytes, size);
			}
		}

		void RamData::InitWithFlash(const __FlashStringHelper *str)
		{
			size = FlashLen(str);
			if (size > 0)
			{
				buf = (byte *)malloc(size);
				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
				else
				{
					auto p = (const char PROGMEM *)str;
					auto i = 0;
					char c;
					while (c = pgm_read_byte(p + i))
					{
						buf[i] = c;
						++i;
					}
				}
			}
		}

		int RamData::FlashLen(const __FlashStringHelper *str) const
		{
			auto p = (const char PROGMEM *)str;
			auto i = 0;
			while (pgm_read_byte(p + i)) ++i;

			return i;
		}

		RamData::RamData(const RamData& other)
		{
			*this = other;
		}

		RamData& RamData::operator = (const RamData& other)
		{
			Clear();

			if (other.size > 0)
			{
				size = other.size;

				buf = (byte *)malloc(size);

				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT	
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
				else
					memcpy(buf, other.buf, size);
			}
			return *this;
		}

		RamData::RamData(uint16_t _size)
		{
			size = _size;
			if (size > 0)
			{
				buf = (byte *)malloc(size);
				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
			}
		}

		RamData::RamData(const char *str, bool appendNullChar)
		{
			size = strlen(str);

			if (appendNullChar)
			{
				++size;

				buf = (byte *)malloc(size);
				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
				else
				{
					memcpy(buf, str, size - 1);
					buf[size] = 0;
				}
			}
			else
			{
				buf = (byte *)malloc(size);
				if (buf == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT			
					DPrint(F("* RamData alloc of ")); DPrint(size); DPrintln(F(" out of memory"));
#endif
					size = 0;
				}
				else
					memcpy(buf, str, size);
			}
		}

		RamData::RamData(const __FlashStringHelper *str)
		{
			InitWithFlash(str);
		}

		RamData::RamData(const byte *srcbuf, uint16_t _size)
		{
			InitWithBytes(srcbuf, _size);
		}

		RamData::~RamData()
		{
			Clear();
		}

		RamData RamData::FromArray(uint16_t len, ...)
		{
			byte buf[len];

			{
				va_list ap;
				va_start(ap, len);
				for (int i = 0; i < len; ++i)
				{
					buf[i] = va_arg(ap, int);
				}
				va_end(ap);
			}

			return RamData(buf, len);
		}

		RamData RamData::FromUInt16(uint16_t value)
		{
			char tmp[6 + 1];

			utoa(value, tmp, DEC);

			return RamData(tmp);
		}

		void RamData::Clear()
		{
			if (buf != NULL) free(buf);
			buf = NULL;
			size = 0;
		}

		uint16_t RamData::Size() const
		{
			return size;
		}
		byte *RamData::Buf() { return buf; }
		const byte *RamData::ConstBuf() const { return (const byte *)buf; }

		RamData RamData::And(const RamData& other) const
		{
#if defined DEBUG && defined DEBUG_ASSERT
			if (size != other.size)
			{
				DPrintln(F("ramdata size mismatch"));
				return RamData();
			}
#endif
			RamData res(size);
			auto bufRes = res.Buf();
			auto bufOther = other.ConstBuf();

			for (int i = 0; i < size; ++i)  bufRes[i] = buf[i] & bufOther[i];

			return res;
		}

		// print bytes in their correspondent character representation
		void RamData::PrintAsChars() const
		{
			auto b = (const char *)buf;
			auto s = size;

			while (s && *b)
			{
				DPrint(*b);
				--s; ++b;
			}
		}

		bool RamData::Equals(const byte *_buf, uint16_t bufSize) const
		{
			return size == bufSize && memcmp(buf, _buf, size) == 0;
		}

		bool RamData::Equals(const RamData& other) const
		{
			return size == other.size && memcmp(buf, other.buf, size) == 0;
		}

		bool RamData::Equals(const __FlashStringHelper *str) const
		{
			return StartsWith(str, true);
		}

		bool RamData::StartsWith(const __FlashStringHelper *str, bool equals) const
		{
			auto p = (const char PROGMEM *)str;
			auto i = 0;
			char c;
			while (c = pgm_read_byte(p + i))
			{
				if (buf[i] != c) return false;
				++i;
			}

			if (equals)
				return i == size;
			else
				return true;
		}

		RamData RamData::Trim(bool begin, bool end) const
		{
			if (size > 0)
			{
				int i = 0, j = size - 1;
				if (begin) while (buf[i] == ' ') ++i;
				if (end) while (buf[j] == ' ') --j;
				return RamData(ConstBuf() + i, j - i + 1);
			}
			else
				return RamData();
		}

		RamData RamData::StripBegin(const __FlashStringHelper *str) const
		{
			if (StartsWith(str))
			{
				auto l = FlashLen(str);
				return RamData(ConstBuf() + l, size - l);
			}
			else
				return RamData(ConstBuf(), size);
		}

		uint16_t RamData::ToUInt16_t() const
		{
			char tmp[size + 1];

			strncpy(tmp, (const char *)buf, size);
			tmp[size] = 0;

			return atoi(tmp);
		}

		RamData RamData::Append(RamData other) const
		{
			RamData res(size + other.size);

			if (size > 0) memcpy(res.buf, buf, size);
			if (other.size > 0) memcpy(res.buf + size, other.buf, other.size);

			return res;
		}

	}

}
