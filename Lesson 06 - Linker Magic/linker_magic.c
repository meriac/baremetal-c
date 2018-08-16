/**************************************************************************//**
 * @file     linker_magic.c
 * @brief    Demonstrate linker initializing SRAM upon boot
 * @date     16. August 2018
 ******************************************************************************/
/*
 * Copyright (c) 2018 Milosch Meriac <milosch@meriac.com>. All rights reserved.
 *
 * SPDX-License-Identifier: Apache-2.0
 *
 * Licensed under the Apache License, Version 2.0 (the License); you may
 * not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an AS IS BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */
#include <common.h>
#include <helper.h>

/* Lesson 06 gets LED1 */
#define LED_PIN 17

/* This variable is in SRAM, but
 * initialized by linker-magic during boot */
volatile int g_blink_count = 3;

static void Wait()
{
    volatile int i;

    /* wait ~0.5s */
    for(i=0; i<0x100000; i++);
}

static void Blink(int count)
{
    int i;

    for(i=0; i<count; i++)
    {
        NRF_P0->OUTCLR = 1UL << LED_PIN;
        Wait();
        NRF_P0->OUTSET = 1UL << LED_PIN;
        Wait();
    }
    Wait();
    Wait();
}

/* Main application entry - called by OnReset handler,
 * performing memory initalizations in helper_init.c */
void main_entry(void)
{
    /* Initialize LED pin as output */
    NRF_P0->PIN_CNF[LED_PIN] =
          (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_PULL_Pos);

    /* Sleep forever */
    while(1)
        Blink(g_blink_count++);
}
