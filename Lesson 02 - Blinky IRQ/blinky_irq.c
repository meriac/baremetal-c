/**************************************************************************//**
 * @file     blinky_irq.c
 * @brief    Demonstrate IRQ-driven program, blinking LED2
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

/* Lesson 02 gets LED2 */
#define LED_PIN 18

static void OnIrqUnused(void)
{
    /* Spin and do nothing, useful for detecting
     * spurious interrupts while debugging */
    while(true);
}

static void OnSysTick(void)
{
    /* Alternate on every SysTick between LED 'on' or LED 'off'
     * in an interrupt-safe way. Please explain what this code does
     * and why this is an improvement over Lesson 01 */
    if(NRF_P0->OUT & (1UL << LED_PIN))
        NRF_P0->OUTCLR = 1UL << LED_PIN;
    else
        NRF_P0->OUTSET = 1UL << LED_PIN;
}

/* reset function called by CPU upon start */
void OnReset(void)
{
    /* Initialize LED pin as output */
    NRF_P0->PIN_CNF[LED_PIN] =
          (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_PULL_Pos);

    /* Configure periodic SysTick timer interrupt next.
     * Fire every 2^24 CPU cyles, at the maximum counter value */
    SysTick->LOAD = SysTick_LOAD_RELOAD_Msk;
    /* Start counting at zero */
    SysTick->VAL  = 0;
    /* Configure Systick behaviour */
    SysTick->CTRL = SysTick_CTRL_CLKSOURCE_Msk | /* Use CPU clock */
                    SysTick_CTRL_TICKINT_Msk |   /* Trigger Interrupt */
                    SysTick_CTRL_ENABLE_Msk;     /* Run SysTick timer */
    /* Infinitely wait for interrupts to happen,
     * explaining in Lesson 03 for why this is a bad idea */
    while(true);
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
    OnIrqUnused, /* -14: NonMaskableInt_IRQn     */
    OnIrqUnused, /* -13: HardFault_IRQn          */
    OnIrqUnused, /* -12: MemoryManagement_IRQn   */
    OnIrqUnused, /* -11: BusFault_IRQn           */
    OnIrqUnused, /* -10: UsageFault_IRQn         */
    OnIrqUnused, /*  -9:                         */
    OnIrqUnused, /*  -8:                         */
    OnIrqUnused, /*  -7:                         */
    OnIrqUnused, /*  -6:                         */
    OnIrqUnused, /*  -5: SVCall_IRQn             */
    OnIrqUnused, /*  -4: DebugMonitor_IRQn       */
    OnIrqUnused, /*  -3:                         */
    OnIrqUnused, /*  -2: PendSV_IRQn             */
    OnSysTick,   /*  -1: SysTick_IRQn            */
};
