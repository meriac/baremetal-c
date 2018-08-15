/**************************************************************************//**
 * @file     blinky.c
 * @brief    Demonstrate minimum program blinking LED1
 * @date     12. August 2018
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

/* Lesson 01 gets LED1 */
#define LED_PIN 17

static void DoWait(void)
{
    volatile int i;

    /* wait ~0.5s */
    for(i=0; i<0x100000; i++);
}

/* reset function called by CPU upon start */
void OnReset(void)
{
    /* Initialize LED pin as output */
    NRF_P0->PIN_CNF[LED_PIN] =
          (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_PULL_Pos);

    /* Perform endless blinking loop */
    while(1)
    {
        /* Alternate LED_PIN GPIO output, explaining why
         * this specifically is a bad idea in Lesson 02 */
        NRF_P0->OUT ^= 1UL << LED_PIN;

        /* Use this wait function to illustrate
         * different C-compiler optimizations */
        DoWait();
    };
}

/* stack declared in blinky.ld */
extern const uint32_t StackTop;

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
    &StackTop,   /* CPU will automatically       *
                  * set stack its pointer        *
                  * to this value                */

    OnReset,     /* -15: Reset_IRQn              */
};

