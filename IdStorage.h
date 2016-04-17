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

#ifndef _SEARCHATHING_ARDUINO_UTILS_ID_STORAGE_H
#define _SEARCHATHING_ARDUINO_UTILS_ID_STORAGE_H

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

		// Id Storage using bits:
		// - stores 8 ids foreach byte
		// - use a reference id to make Allocate/Release
		//   relatives to a starting number
		// - recycle released ids
		//
		// Example:
		// IdStorage ids(100);
		// ids.Allocate() -> 100
		// ids.Allocate() -> 101
		// ids.Allocate() -> 102
		// ids.Release(101)
		// ids.Allocate() -> 101 ( recycle )
		// ids.Allocate() -> 103
		//
		// Notes:
		// - it will not resize back the memory expanded.
		class IdStorage
		{
			byte *storage = NULL;
			uint16_t storageSize = 0;
			uint16_t ref = 0;
			static const byte minChunkSize = 4;

			void Cleanup();

		public:
			// Default constructor ( ref will be 0 ).
			IdStorage();
			
			// Copy Constructor.
			IdStorage(const IdStorage& other);

			// Assign operator.
			IdStorage& operator=(const IdStorage& other);

			// Construct an idstorage with given reference.
			IdStorage(uint16_t _ref);

			// Destructor ( release used resources ).
			~IdStorage();

			// ID base reference used.
			uint16_t Ref() const;

			// Retrieve a next free id.
			uint16_t Allocate(bool *failed = NULL);

			// Release a previously allocated id. If the given id is out of
			// any previously allocated id a safety check disallow
			// segmentation fault and will be reported if DEBUG and
			// DEBUG_ASSERT macros are defined.
			void Release(uint16_t id);

		};

	}

}

#endif
