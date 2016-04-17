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

#ifndef _SEARCHATHING_ARDUINO_UTILS_DYNAMIC_TIMEOUT_H
#define _SEARCHATHING_ARDUINO_UTILS_DYNAMIC_TIMEOUT_H

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

		// Dynamic timeout manager.		
		// See: Expired() function documentation.
		//
		// Typical loop application:
		//-------------------------------------------------------------------
		// while (!answered)
		// {
		//    "send"
		//    while (!dynamicTimeout.Expired())
		//    {	
		//       if ( "received" ) { answered = true; break; }
		//    }		
		// }	
		class DynamicTimeout
		{			
			unsigned long begin;
			unsigned int timeoutBase;
			unsigned int timeout;
			unsigned int timeoutMax;

		public:
			// Constructor.			
			// This will call the Reset() initially.
			DynamicTimeout(unsigned int _timeoutBase, unsigned int _timeoutMax);

			// Sets the begin time to the current millis() and the timeout
			// to the timeoutBase.
			void Reset();

			// Checks if the current time expired the current timeout.
			// In that case:
			// - the timeout value will be increased of a timeoutBase unit
			//   and if exceeded the timeoutMax then it will be reset to the
			//   timeoutBase value.
			// - the begin time will be reset to the current time.
			// - returns true
			// If current time not yet timedout returns false.
			bool Expired();

		};

	}

}

#endif
