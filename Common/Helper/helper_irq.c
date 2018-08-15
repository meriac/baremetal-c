/**************************************************************************//**
 * @file     helper_irq.c
 * @brief    Create centralied overridable IRQ & Fault handler table
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
#include <stdint.h>
#include <Helper/helper_irq.h>

/* Have a centrally maintenable function for aliasing IRQs */
#define ALIAS(f) __attribute__ ((weak, alias (#f)))

/*
 * Point all fault handlers by default to OnUnknownFault
 */

void OnUnknownFault(void)
{
    /* Spin and do nothing, useful for detecting
     * spurious interrupts while debugging */
    for(;;);
}

void OnNonMaskableInt(void) ALIAS(OnUnknownFault);
void OnHardFault(void) ALIAS(OnUnknownFault);
void OnMemoryManagement(void) ALIAS(OnUnknownFault);
void OnBusFault(void) ALIAS(OnUnknownFault);
void OnUsageFault(void) ALIAS(OnUnknownFault);
void OnSVCall(void) ALIAS(OnUnknownFault);
void OnDebugMonitor(void) ALIAS(OnUnknownFault);
void OnPendSV(void) ALIAS(OnUnknownFault);
void OnSysTick(void) ALIAS(OnUnknownFault);

/*
 * Point all interrupt handler by default to OnUnknownIrq
 */

static void OnUnknownIrq(void)
{
    /* Spin and do nothing, useful for detecting
     * spurious interrupts while debugging */
    for(;;);
}

void OnIrq_POWER_CLOCK(void) ALIAS(OnUnknownIrq);
void OnIrq_RADIO(void) ALIAS(OnUnknownIrq);
void OnIrq_UARTE0_UART0(void) ALIAS(OnUnknownIrq);
void OnIrq_SPI0(void) ALIAS(OnUnknownIrq);
void OnIrq_SPI1(void) ALIAS(OnUnknownIrq);
void OnIrq_NFCT(void) ALIAS(OnUnknownIrq);
void OnIrq_GPIOTE(void) ALIAS(OnUnknownIrq);
void OnIrq_SAADC(void) ALIAS(OnUnknownIrq);
void OnIrq_TIMER0(void) ALIAS(OnUnknownIrq);
void OnIrq_TIMER1(void) ALIAS(OnUnknownIrq);
void OnIrq_TIMER2(void) ALIAS(OnUnknownIrq);
void OnIrq_RTC0(void) ALIAS(OnUnknownIrq);
void OnIrq_TEMP(void) ALIAS(OnUnknownIrq);
void OnIrq_RNG(void) ALIAS(OnUnknownIrq);
void OnIrq_ECB(void) ALIAS(OnUnknownIrq);
void OnIrq_CCM_AAR(void) ALIAS(OnUnknownIrq);
void OnIrq_WDT(void) ALIAS(OnUnknownIrq);
void OnIrq_RTC1(void) ALIAS(OnUnknownIrq);
void OnIrq_QDEC(void) ALIAS(OnUnknownIrq);
void OnIrq_COMP_LPCOMP(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI0_EGU0(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI1_EGU1(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI2_EGU2(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI3_EGU3(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI4_EGU4(void) ALIAS(OnUnknownIrq);
void OnIrq_SWI5_EGU5(void) ALIAS(OnUnknownIrq);
void OnIrq_TIMER3(void) ALIAS(OnUnknownIrq);
void OnIrq_TIMER4(void) ALIAS(OnUnknownIrq);
void OnIrq_PWM0(void) ALIAS(OnUnknownIrq);
void OnIrq_PDM(void) ALIAS(OnUnknownIrq);
void OnIrq_MWU(void) ALIAS(OnUnknownIrq);
void OnIrq_PWM1(void) ALIAS(OnUnknownIrq);
void OnIrq_PWM2(void) ALIAS(OnUnknownIrq);
void OnIrq_SPI2(void) ALIAS(OnUnknownIrq);
void OnIrq_RTC2(void) ALIAS(OnUnknownIrq);
void OnIrq_I2S(void) ALIAS(OnUnknownIrq);
void OnIrq_FPU(void) ALIAS(OnUnknownIrq);

/* stack end address declared in linker script (minimal.ld etc.) */
extern const uint32_t StackTop;

/* declare vector table */
__attribute__ ((section(".vtor")))
const void* VectorTable[] = {
    &StackTop,          /* CPU will automatically       *
                         * set stack its pointer        *
                         * to this value                */

    OnReset,            /* -15: Reset_IRQn              */
    OnNonMaskableInt,   /* -14: NonMaskableInt_IRQn     */
    OnHardFault,        /* -13: HardFault_IRQn          */
    OnMemoryManagement, /* -12: MemoryManagement_IRQn   */
    OnBusFault,         /* -11: BusFault_IRQn           */
    OnUsageFault,       /* -10: UsageFault_IRQn         */
    OnUnknownFault,     /*  -9:                         */
    OnUnknownFault,     /*  -8:                         */
    OnUnknownFault,     /*  -7:                         */
    OnUnknownFault,     /*  -6:                         */
    OnSVCall,           /*  -5: SVCall_IRQn             */
    OnDebugMonitor,     /*  -4: DebugMonitor_IRQn       */
    OnUnknownFault,     /*  -3:                         */
    OnPendSV,           /*  -2: PendSV_IRQn             */
    OnSysTick,          /*  -1: SysTick_IRQn            */

    OnIrq_POWER_CLOCK,  /*   0: POWER_CLOCK_IRQn        */
    OnIrq_RADIO,        /*   1: RADIO_IRQn              */
    OnIrq_UARTE0_UART0, /*   2: UARTE0_UART0_IRQn       */
    OnIrq_SPI0,         /*   3: SPIM0_SPIS0_TWIM0_TWIS0_SPI0_TWI0_IRQn */
    OnIrq_SPI1,         /*   4: SPIM1_SPIS1_TWIM1_TWIS1_SPI1_TWI1_IRQn */
    OnIrq_NFCT,         /*   5: NFCT_IRQn               */
    OnIrq_GPIOTE,       /*   6: GPIOTE_IRQn             */
    OnIrq_SAADC,        /*   7: SAADC_IRQn              */
    OnIrq_TIMER0,       /*   8: TIMER0_IRQn             */
    OnIrq_TIMER1,       /*   9: TIMER1_IRQn             */
    OnIrq_TIMER2,       /*  10: TIMER2_IRQn             */
    OnIrq_RTC0,         /*  11: RTC0_IRQn               */
    OnIrq_TEMP,         /*  12: TEMP_IRQn               */
    OnIrq_RNG,          /*  13: RNG_IRQn                */
    OnIrq_ECB,          /*  14: ECB_IRQn                */
    OnIrq_CCM_AAR,      /*  15: CCM_AAR_IRQn            */
    OnIrq_WDT,          /*  16: WDT_IRQn                */
    OnIrq_RTC1,         /*  17: RTC1_IRQn               */
    OnIrq_QDEC,         /*  18: QDEC_IRQn               */
    OnIrq_COMP_LPCOMP,  /*  19: COMP_LPCOMP_IRQn        */
    OnIrq_SWI0_EGU0,    /*  20: SWI0_EGU0_IRQn          */
    OnIrq_SWI1_EGU1,    /*  21: SWI1_EGU1_IRQn          */
    OnIrq_SWI2_EGU2,    /*  22: SWI2_EGU2_IRQn          */
    OnIrq_SWI3_EGU3,    /*  23: SWI3_EGU3_IRQn          */
    OnIrq_SWI4_EGU4,    /*  24: SWI4_EGU4_IRQn          */
    OnIrq_SWI5_EGU5,    /*  25: SWI5_EGU5_IRQn          */
    OnIrq_TIMER3,       /*  26: TIMER3_IRQn             */
    OnIrq_TIMER4,       /*  27: TIMER4_IRQn             */
    OnIrq_PWM0,         /*  28: PWM0_IRQn               */
    OnIrq_PDM,          /*  29: PDM_IRQn                */
    OnUnknownIrq,       /*  30:                         */
    OnUnknownIrq,       /*  31:                         */
    OnIrq_MWU,          /*  32: MWU_IRQn                */
    OnIrq_PWM1,         /*  33: PWM1_IRQn               */
    OnIrq_PWM2,         /*  34: PWM2_IRQn               */
    OnIrq_SPI2,         /*  35: SPIM2_SPIS2_SPI2_IRQn   */
    OnIrq_RTC2,         /*  36: RTC2_IRQn               */
    OnIrq_I2S,          /*  37: I2S_IRQn                */
    OnIrq_FPU           /*  38: FPU_IRQn                */
};
