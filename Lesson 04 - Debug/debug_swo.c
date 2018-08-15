/**************************************************************************//**
 * @file     debug_swo.c
 * @brief    Demonstrate SWO debug printing
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

/* Lesson 04 gets LED4 */
#define LED_PIN 20

#define CHANNEL_DEBUG 0

/* print single character over SWO debug interface */
static void PrintChar(char data)
{
    /* wait for TX ready */
    while (ITM->PORT[CHANNEL_DEBUG].u32 == 0);
    /* TX debug character */
    ITM->PORT[CHANNEL_DEBUG].u8 = (uint8_t)data;
}

/* Print number as decimal ASCII string */
void PrintNumber(uint32_t num)
{
    char digit;

    digit = '0' + (num % 10);

    num /= 10;
    if(num)
        PrintNumber(num);

    PrintChar(digit);
}

/* Print ASCII string */
void PrintStr(const char* str)
{
    char c;
    while((c = *str++)!=0)
        PrintChar(c);
}

/* Reset function called by CPU upon start */
void OnReset(void)
{
    uint32_t counter;

    /* Initialize LED pin as output */
    NRF_P0->PIN_CNF[LED_PIN] =
          (GPIO_PIN_CNF_DIR_Output << GPIO_PIN_CNF_DIR_Pos)
        | (GPIO_PIN_CNF_INPUT_Disconnect << GPIO_PIN_CNF_PULL_Pos);

    /* Enable SWO debug output pins - 4MHz serial mode */
    NRF_CLOCK->TRACECONFIG =
        (CLOCK_TRACECONFIG_TRACEMUX_Serial << CLOCK_TRACECONFIG_TRACEMUX_Pos)
      | (CLOCK_TRACECONFIG_TRACEPORTSPEED_4MHz << CLOCK_TRACECONFIG_TRACEPORTSPEED_Pos);

    /* Reset previous channel settings */
    ITM->LAR  = 0xC5ACCE55;
    ITM->TCR  = ITM->TER = 0x0;

    /* Wait for debugger to connect */
    while(!((ITM->TCR & ITM_TCR_ITMENA_Msk) && (ITM->TER & (1<<CHANNEL_DEBUG))));

    /* Print endless hello world */
    counter = 0;
    while(1)
    {
        PrintNumber(counter++);
        PrintStr(": Hello World!\n\r");
    }

}
