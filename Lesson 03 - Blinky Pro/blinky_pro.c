/**************************************************************************//**
 * @file     blinky_pro.c
 * @brief    Demonstrate low power blinking LED
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
#include <helper.h>

/* Lesson 03 gets LED3 */
#define LED_PIN 19

void OnIrq_RTC0(void)
{
    if(NRF_RTC0->EVENTS_TICK)
    {
        /* Acknowledge clock tick interrupt */
        NRF_RTC0->EVENTS_TICK = 0;

        /* Alternate on every SysTick between LED 'on' or LED 'off'
         * in an interrupt-safe way. Please explain what this code does
         * and why this is an improvement over Lesson 01 */
        if(NRF_P0->OUT & (1UL << LED_PIN))
            NRF_P0->OUTCLR = 1UL << LED_PIN;
        else
            NRF_P0->OUTSET = 1UL << LED_PIN;
    }
}

/* reset function called by CPU upon start */
void OnReset(void)
{
    /* Initialize LED pin as output */
    NRF_P0->PIN_CNF[LED_PIN] =
          (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_PULL_Pos);


    /* Select 32kHz crystal oscillator as clock source for RTC */
    NRF_CLOCK->LFCLKSRC =
        (CLOCK_LFCLKSRCCOPY_SRC_Xtal << CLOCK_LFCLKSRCCOPY_SRC_Pos);
    /* Reset 'Started' event just in case */
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;
    /* Spin up the low frequency clock */ 
    NRF_CLOCK->TASKS_LFCLKSTART = 1;
    /* Wait till the clock sis started, can easily take 100's of ms */
    while(!NRF_CLOCK->EVENTS_LFCLKSTARTED);
    /* Acknowledge clock start event */
    NRF_CLOCK->EVENTS_LFCLKSTARTED = 0;


    /* Setup RTC0 timer to trigger twice per second */
    NRF_RTC0->PRESCALER = 32768/2-1;
    /* Enable interrupt on every increment of the RTC timer */ 
    NRF_RTC0->INTENSET =
        (RTC_INTENSET_TICK_Enabled << RTC_INTENSET_TICK_Pos);
    /* Tell CPU NVIC to actually listen to that interrupt */
    NVIC_EnableIRQ(RTC0_IRQn);
    /* And start RTC0 counting */
    NRF_RTC0->TASKS_START = 1;


    /* Actually put the CPU sleeping while waiting for the timer */
    while(true)
        __WFE();
}
