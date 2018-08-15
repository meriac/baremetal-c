#  ##################################################################
#  # @file     Flashing & SWO Debug Helper Makefile
#  # @brief    Demonstrate JLink SWO debug printing and flashing
#  # @date     15. August 2018
#  ##################################################################
#
#  Copyright (c) 2018 Milosch Meriac <milosch@meriac.com>.
#  All rights reserved.
#
#  SPDX-License-Identifier: Apache-2.0
#
#  Licensed under the Apache License, Version 2.0 (the License);
#  You may not use this file except in compliance with the License.
#  You may obtain a copy of the License at
#
#  www.apache.org/licenses/LICENSE-2.0
#
#  Unless required by applicable law or agreed to in writing, software
#  distributed under the License is distributed on an AS IS BASIS,
#  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express
#  or implied. See the License for the specific language governing
#  permissions and limitations under the License.
#

# CPU target
CPU:=nRF52832_xxAA

# debug settings
JLINK:=$(SEGGER)JLinkExe
JLINK_FREQ:=4000000
JLINK_VIEWER_MASK:=0x7
JLINK_PARAM:=-Device $(CPU) -if SWD -speed auto

.PHONY: flash reset swo

flash: $(PROJECT).bin
	@echo running "$(JLINK) $(JLINK_PARAM)"
	@echo "$$__SCRIPT_FLASH" | $(JLINK) $(JLINK_PARAM)

reset:
	@echo "$$__SCRIPT_RESET" | $(JLINK) $(JLINK_PARAM)

swo: flash
	@echo "$$__SCRIPT_SWO" | $(JLINK) $(JLINK_PARAM)

#
# helper script for viewing SWO debug output
#
define __SCRIPT_SWO
	connect
	swoview $(JLINK_FREQ)
endef
export __SCRIPT_SWO

#
# helper script for flashing the firmware image
#
define __SCRIPT_FLASH
	connect
	h
	loadbin $(PROJECT).bin 0
	r
	g
	q
endef
export __SCRIPT_FLASH

#
# helper script for resetting CPU remotely
#
define __SCRIPT_RESET
	connect
	h
	r
	g
	q
endef
export __SCRIPT_RESET

