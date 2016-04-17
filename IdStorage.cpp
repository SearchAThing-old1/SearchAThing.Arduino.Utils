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
#include "IdStorage.h"
#include "Util.h"

namespace SearchAThing
{

	namespace Arduino
	{

		void IdStorage::Cleanup()
		{
			if (storage != NULL) free(storage);
			ref = 0;
			storage = NULL;
			storageSize = 0;
		}

		IdStorage::IdStorage()
		{
		}

		IdStorage::IdStorage(const IdStorage& other)
		{
			*this = other;
		}

		IdStorage& IdStorage::operator=(const IdStorage& other)
		{
			Cleanup();

			if (other.storageSize > 0)
			{
				storage = (byte *)malloc(other.storageSize);
				if (storage == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT	
					DPrint(F("* IdStorage alloc of ")); DPrint(other.storageSize); DPrintln(F(" out of memory"));
#endif				
				}
				else
				{
					storageSize = other.storageSize;
					memcpy(storage, other.storage, storageSize);
				}
			}
			ref = other.ref;

			return *this;
		}

		IdStorage::IdStorage(uint16_t _ref)
		{
			ref = _ref;
		}

		IdStorage::~IdStorage()
		{
			Cleanup();
		}

		uint16_t IdStorage::Ref() const { return ref; }

		uint16_t IdStorage::Allocate(bool *failed)
		{
			if (storage == NULL)
			{
				storage = (byte *)malloc(minChunkSize);

				if (storage == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT	
					DPrint(F("* IdStorage alloc of ")); DPrint(minChunkSize); DPrintln(F(" out of memory"));
#endif								
					if (failed != NULL) *failed = true;

					return 0;
				}
				else
				{
					storageSize = minChunkSize;
					memset(storage, 0, storageSize);
				}
			}

			uint16_t id = 0;

			// search for avail
			for (int i = 0; id == 0 && i < storageSize; ++i)
			{
				if (storage[i] == 0xff) continue; // octect full

				int bitpos = 0;
				while (storage[i] & (1 << bitpos)) ++bitpos;
				storage[i] |= (1 << bitpos);

				id = ref + i * 8 + bitpos;
			}

			if (id == 0) // need to allocate more
			{
				auto *newEph = (byte *)malloc(storageSize + minChunkSize);

				if (newEph == NULL)
				{
#if defined DEBUG && defined DEBUG_ASSERT	
					DPrint(F("* IdStorage alloc of ")); DPrint(storageSize + minChunkSize); DPrintln(F(" out of memory"));
#endif								
					if (failed != NULL) *failed = true;
					return 0;
				}
				else
				{
					memcpy(newEph, storage, storageSize);
					free(storage);
					storage = newEph;
					storageSize += minChunkSize;
					memset(storage + storageSize - minChunkSize, 0, minChunkSize);
				}

				return Allocate(failed);
			}

			if (failed != NULL) *failed = false;

			return id;
		}

		void IdStorage::Release(uint16_t id)
		{
			auto storageIdx = (id - ref) / 8;
			if (storageIdx < storageSize)
			{
				byte bitpos = ((id - ref) % 8);
				storage[storageIdx] -= (1 << (bitpos));
			}
#if defined DEBUG && defined DEBUG_ASSERT
			else
			{
				DPrint("Invalid storageIdx:"); DPrint(storageIdx); DPrint(" >= "); DPrintln(storageSize);
			}
#endif
		}

	}

}
