/*
###########################################################################################
// cNVMe - An Open Source NVMe Device Simulation - MIT License
// Copyright 2017 - Intel Corporation

// Permission is hereby granted, free of charge, to any person obtaining a
// copy of this software and associated documentation files (the "Software"),
// to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
// sell copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be
// included in all copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
// INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR
// PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE
// LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT
// OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
// OTHER DEALINGS IN THE SOFTWARE.
############################################################################################
ControllerRegisters.cpp - An implementation file for the ControllerRegisters
*/

#include "Controller.h"
#include "ControllerRegisters.h"
#include "Strings.h"

#include <math.h>

#define CHANGE_CHECK_SLEEP_MS 1 // Used as a way of seeing when interrupts happen

namespace cnvme
{
	namespace controller
	{
		namespace registers
		{

			std::string CONTROLLER_CAPABILITIES::toString() const
			{
				std::string retStr;
				retStr += "Controller Capabilities (CAP / Offset 0x00):\n";
				retStr += strings::toString(ToStringParams(MQES, "Maximum Queue Entries Supported"));
				retStr += strings::toString(ToStringParams(CQR, "Contiguous Queues Required"));
				retStr += strings::toString(ToStringParams(AMS, "Arbitration Mechanism Supported"));
				retStr += strings::toString(ToStringParams(RSVD2, "Reserved"));
				retStr += strings::toString(ToStringParams(TO, "Timeout"));
				retStr += strings::toString(ToStringParams(DSTRD, "Doorbell Stride"));
				retStr += strings::toString(ToStringParams(NSSRS, "NVM Subsystem Reset Supported"));
				retStr += strings::toString(ToStringParams(CSS, "Command Sets Supported"));
				retStr += strings::toString(ToStringParams(RSVD1, "Reserved"));
				retStr += strings::toString(ToStringParams(MPSMIN, "Memory Page Size Minimum"));
				retStr += strings::toString(ToStringParams(MPSMAX, "Memory Page Size Maximum"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string VERSION::toString() const
			{
				std::string retStr;
				retStr += "Version (VS / Offset 0x08):\n";
				retStr += strings::toString(ToStringParams(TER, "Tertiary Version Number"));
				retStr += strings::toString(ToStringParams(MNR, "Minor Version Number"));
				retStr += strings::toString(ToStringParams(MJR, "Major Version Number"));
				return retStr;
			}

			std::string INTERRUPT_MASK_SET::toString() const
			{
				std::string retStr;
				retStr += "Interrupt Mask Set (INTMS / Offset 0x0C):\n";
				retStr += strings::toString(ToStringParams(IVMS, "Interrupt Vector Mask Set"));
				return retStr;
			}

			std::string INTERRUPT_MASK_CLEAR::toString() const
			{
				std::string retStr;
				retStr += "Interrupt Mask Clear (INTMC / Offset 0x10):\n";
				retStr += strings::toString(ToStringParams(IVMC, "Interrupt Vector Mask Clear"));
				return retStr;
			}

			std::string CONTROLLER_CONFIGURATION::toString() const
			{
				std::string retStr;
				retStr += "Controller Configuration (CC / Offset 0x14):\n";
				retStr += strings::toString(ToStringParams(EN, "Enable"));
				retStr += strings::toString(ToStringParams(RSVD1, "Reserved"));
				retStr += strings::toString(ToStringParams(CSS, "I/O Command Set Selected"));
				retStr += strings::toString(ToStringParams(MPS, "Memory Page Size"));
				retStr += strings::toString(ToStringParams(AMS, "Arbitration Mechanism Selected"));
				retStr += strings::toString(ToStringParams(SHN, "Shutdown Notification"));
				retStr += strings::toString(ToStringParams(IOSQES, "I/O Submission Queue Entry Size"));
				retStr += strings::toString(ToStringParams(IOCQES, "I/O Completion Queue Entry Size"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string CONTROLLER_STATUS::toString() const
			{
				std::string retStr;
				retStr += "Controller Status (CSTS / Offset 0x1C):\n";
				retStr += strings::toString(ToStringParams(RDY, "Ready"));
				retStr += strings::toString(ToStringParams(CFS, "Controller Fatal Status"));
				retStr += strings::toString(ToStringParams(SHST, "Shutdown Status"));
				retStr += strings::toString(ToStringParams(NSSRO, "NVM Subsystem Reset Occurred"));
				retStr += strings::toString(ToStringParams(PP, "Processing Paused"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string NVM_SUBSYSTEM_RESET::toString() const
			{
				std::string retStr;
				retStr += "NVM Subsystem Reset (NSSR / Offset 0x20):\n";
				retStr += strings::toString(ToStringParams(NSSRC, "NVM Subsystem Reset Control"));
				return retStr;
			}

			std::string ADMIN_QUEUE_ATTRIBUTES::toString() const
			{
				std::string retStr;
				retStr += "Admin Queue Attributes (AQA / Offset 0x24):\n";
				retStr += strings::toString(ToStringParams(ASQS, "Admin Submission Queue Size"));
				retStr += strings::toString(ToStringParams(RSVD1, "Reserved"));
				retStr += strings::toString(ToStringParams(ACQS, "Admin Completion Queue Size"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string ADMIN_SUBMISSION_QUEUE_BASE_ADDRESS::toString() const
			{
				std::string retStr;
				retStr += "Admin Submission Queue Base Address (ASQ / Offset 0x28):\n";
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				retStr += strings::toString(ToStringParams(ASQB, "Admin Submission Queue Base"));
				return retStr;
			}

			std::string ADMIN_COMPLETION_QUEUE_BASE_ADDRESS::toString() const
			{
				std::string retStr;
				retStr += "Admin Completion Queue Base Address (ACQ / Offset 0x30):\n";
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				retStr += strings::toString(ToStringParams(ACQB, "Admin Completion Queue Base"));
				return retStr;
			}

			std::string CONTROLLER_MEMORY_BUFFER_LOCATION::toString() const
			{
				std::string retStr;
				retStr += "Controller Memory Buffer Location (CMBLOC / Offset 0x38):\n";
				retStr += strings::toString(ToStringParams(BIR, "Base Indicator Register"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				retStr += strings::toString(ToStringParams(OFST, "Offset"));
				return retStr;
			}

			std::string CONTROLLER_MEMORY_BUFFER_SIZE::toString() const
			{
				std::string retStr;
				retStr += "Controller Memory Buffer Size (CMBSZ / Offset 0x3C):\n";
				retStr += strings::toString(ToStringParams(SQS, "Submission Queue Support"));
				retStr += strings::toString(ToStringParams(CQS, "Completion Queue Support"));
				retStr += strings::toString(ToStringParams(LISTS, "PRP SGL List Support"));
				retStr += strings::toString(ToStringParams(RDS, "Read Data Support"));
				retStr += strings::toString(ToStringParams(WDS, "Write Data Support"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				retStr += strings::toString(ToStringParams(SZU, "Size Units"));
				retStr += strings::toString(ToStringParams(SZ, "Size"));
				return retStr;
			}

			std::string SUBMISSION_QUEUE_Y_TAIL_DOORBELL::toString() const
			{
				std::string retStr;
				retStr += "Submission Queue Y Tail Doorbell (SQyTDBL / Offset (0x1000 + ((2y) * (4 << CAP.DSTRD)))):\n";
				retStr += strings::toString(ToStringParams(SQT, "Submission Queue Tail"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string COMPLETION_QUEUE_Y_HEAD_DOORBELL::toString() const
			{
				std::string retStr;
				retStr += "Completion Queue Y Head Doorbell (CQyHDBL / Offset (0x1000 + ((2y + 1) * (4 << CAP.DSTRD)))):\n";
				retStr += strings::toString(ToStringParams(CQH, "Completion Queue Head"));
				retStr += strings::toString(ToStringParams(RSVD0, "Reserved"));
				return retStr;
			}

			std::string CONTROLLER_REGISTERS::toString() const
			{
				std::string retStr;
				retStr += "Controller Registers:\n";
				retStr += strings::indentLines(CAP.toString());
				retStr += strings::indentLines(VS.toString());
				retStr += strings::indentLines(INTMS.toString());
				retStr += strings::indentLines(INTMC.toString());
				retStr += strings::indentLines(CC.toString());
				retStr += strings::indentLines(CSTS.toString());
				retStr += strings::indentLines(NSSR.toString());
				retStr += strings::indentLines(AQA.toString());
				retStr += strings::indentLines(ASQ.toString());
				retStr += strings::indentLines(ACQ.toString());
				retStr += strings::indentLines(CMBLOC.toString());
				retStr += strings::indentLines(CMBSZ.toString());
				return retStr;
			}

			std::string QUEUE_DOORBELLS::toString() const
			{
				std::string retStr;
				retStr += "Queue Doorbells:\n";
				retStr += strings::indentLines(SQTDBL.toString());
				retStr += strings::indentLines(CQHDBL.toString());
				return retStr;
			}

			ControllerRegisters::ControllerRegisters()
			{
				ControllerRegistersPointer = nullptr;
				Controller = nullptr;
			}

			ControllerRegisters::ControllerRegisters(UINT_64 memoryLocation) : ControllerRegisters::ControllerRegisters()
			{
				ControllerRegistersPointer = (CONTROLLER_REGISTERS*)memoryLocation;
				controllerReset();

#ifndef SINGLE_THREADED
				RegisterWatcher = LoopingThread([&] {ControllerRegisters::checkForChanges(); }, CHANGE_CHECK_SLEEP_MS);
				RegisterWatcher.start();
#endif
			}

			ControllerRegisters::ControllerRegisters(UINT_64 memoryLocation, cnvme::controller::Controller* controller) : ControllerRegisters(memoryLocation)
			{
				Controller = controller;
			}

			ControllerRegisters::~ControllerRegisters()
			{
				RegisterWatcher.end(); // Make sure the registers aren't watched at this point.
			}

			CONTROLLER_REGISTERS* ControllerRegisters::getControllerRegisters()
			{
				return ControllerRegistersPointer;
			}

			void ControllerRegisters::checkForChanges()
			{
				if (ControllerRegistersPointer)
				{
					if (ControllerRegistersPointer->CC.EN == 0 && !controllerResetInitiated)
					{
						LOG_INFO("CC.EN was flipped to 0. Initiating controller reset.");
						controllerReset();
						// CSTS.RDY should now be 0
					}

					if (controllerResetInitiated && ControllerRegistersPointer->CC.EN == 1)
					{
						LOG_INFO("CC.EN was set back to 1. Setting CSTS.RDY to 1.");
						controllerResetInitiated = false; // the reset is complete
						ControllerRegistersPointer->CSTS.RDY = 1; // Controller has been re-enabled. We are now ready.
					}
				}
			}

			QUEUE_DOORBELLS* ControllerRegisters::getQueueDoorbells()
			{
				return (controller::registers::QUEUE_DOORBELLS*)((UINT_8*)this->getControllerRegisters() \
					+ sizeof(registers::CONTROLLER_REGISTERS));
			}

			void ControllerRegisters::waitForChangeLoop()
			{
#ifndef SINGLE_THREADED
				RegisterWatcher.waitForFlip();
#else
				checkForChanges();
#endif
			}

			UINT_32 ControllerRegisters::getMemoryPageSize()
			{
				CONTROLLER_REGISTERS* controllerRegisters = getControllerRegisters();
				if (controllerRegisters)
				{
					return (UINT_32)std::pow(2, 12 + controllerRegisters->CC.MPS);
				}
				ASSERT("Unable to get memory page size due to the controller registers being NULL");
				return 0;
			}

			void ControllerRegisters::controllerReset()
			{
				if (ControllerRegistersPointer)
				{
					LOG_INFO("Doing the controller level reset.");
					controllerResetInitiated = true;

					// Save this as it persists
					ADMIN_QUEUE_ATTRIBUTES AQA = ControllerRegistersPointer->AQA;
					ADMIN_SUBMISSION_QUEUE_BASE_ADDRESS ASQ = ControllerRegistersPointer->ASQ;
					ADMIN_COMPLETION_QUEUE_BASE_ADDRESS ACQ = ControllerRegistersPointer->ACQ;

					memset(ControllerRegistersPointer, 0, sizeof(CONTROLLER_REGISTERS));

					ControllerRegistersPointer->CAP.MPSMAX = 0; // 4096 max
					ControllerRegistersPointer->CAP.MPSMIN = 0; // 4096 min
					ControllerRegistersPointer->CAP.CSS = 1;    // NVM Command set
					ControllerRegistersPointer->CAP.NSSRS = 1;  // NVM Subsystem Reset Supported
					ControllerRegistersPointer->CAP.TO = 32;    // Worst case of 16 seconds
					ControllerRegistersPointer->CAP.MQES = 0xFFFF; // At most 0xFFFF + 1 (zero based) queue entries
					ControllerRegistersPointer->CAP.CQR = 1;    // Must use contiguous queues

					// NVMe 1.3
					ControllerRegistersPointer->VS.MJR = 1;
					ControllerRegistersPointer->VS.MNR = 3;
					ControllerRegistersPointer->VS.TER = 0;

					// Todo: Interrupts

					// Admin Queue persists
					ControllerRegistersPointer->AQA = AQA;
					ControllerRegistersPointer->ASQ = ASQ;
					ControllerRegistersPointer->ACQ = ACQ;

					if (Controller)
					{
						LOG_INFO("Notifying the controller of the controller reset");
						Controller->controllerResetCallback();
					}
				}
				else
				{
					LOG_ERROR("controllerReset() was called without a valid ControllerRegistersPointer");
				}
			}
		}
	}
}
