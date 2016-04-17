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

#ifndef _SEARCHATHING_ARDUINO_UTILS_DEBUG_MACROS_H
#define _SEARCHATHING_ARDUINO_UTILS_DEBUG_MACROS_H

#if defined(ARDUINO) && ARDUINO >= 100
#include "arduino.h"
#else
#include "WProgram.h"
#endif

#define SERIAL_SPEED	9600

//===========================================================================
// USER OVERRIDABLE MACROS
//---------------------------------------------------------------------------
// Change macro by:
// - comment out functionalities not needed, or
// - by compiler flags ( -DSEARCHATHING_DISABLE [defines to enable] )
//   eg. -DSEARCHATHING_DISABLE -DDEBUG -DDEBUG_ASSERT
//===========================================================================

#ifndef SEARCHATHING_DISABLE	// !(disable everything)

//===========================================================================
// GENERAL
//---------------------------------------------------------------------------

#define DEBUG			// general debugging
#define DEBUG_ASSERT	// assert failed
#define DPRINT_SERIAL	// dprint output to serial

//---------------------------------------------------------------------------
// SearchAThing.Arduino.Utils
//---------------------------------------------------------------------------

//#define DEBUG_FREE_MEMORY_MAX	// FreeMemoryMaxBlock function debug

//---------------------------------------------------------------------------
// SearchAThing.Arduino.Net
//---------------------------------------------------------------------------

#define DEBUG_DHCP		// DHCP protocol
#define DEBUG_ETH2		// EthernetII protocol
#define DEBUG_ARP		// ARP protocol
#define DEBUG_UDP		// UDP protocol
#define DEBUG_DNS		// DNS protocol
#define DEBUG_IPV4		// IPV4 protocol
#define DEBUG_ICMP		// ICMP protocol
#define DEBUG_SRUDP		// SRUDP protocol

//---------------------------------------------------------------------------
// SearchAThing.Arduino.Enc28j60
//---------------------------------------------------------------------------

#define DEBUG_ETH_REGS			// registers
#define DEBUG_ETH_DRIVER		// driver status
#define DEBUG_ETH_RX			// rx data
#define DEBUG_ETH_RX_VERBOSE	// rx data ( verbose )
#define DEBUG_ETH_TX			// tx data
#define DEBUG_ETH_TX_VERBOSE	// tx data ( verbose )
#define DEBUG_ETH_PROC			// EthProcess management

//===========================================================================

#endif // SEARCHATHING_DISABLE

#include "DPrint.h"

#endif