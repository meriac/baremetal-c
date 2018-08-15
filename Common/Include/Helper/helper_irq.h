/**************************************************************************//**
 * @file     helper_irq.h
 * @brief    Create centralied overridable IRQ & Fault handler table
 * @date     15. August 2018
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
#ifndef __HELPER_IRQ_H__
#define __HELPER_IRQ_H__

/*
 * Special case: reset never returns, allows compiler to optimize
 * */
void OnReset(void) __attribute__ ((noreturn));

/*
 * Generic Arm Architecture Fault Handlers
 */
extern void OnReset(void);
extern void OnNonMaskableInt(void);
extern void OnHardFault(void);
extern void OnMemoryManagement(void);
extern void OnBusFault(void);
extern void OnUsageFault(void);
extern void OnSVCall(void);
extern void OnDebugMonitor(void);
extern void OnPendSV(void);
extern void OnSysTick(void);

/*
 * Vendor-specific IRQ handlers
 */
extern void OnIrq_POWER_CLOCK(void);
extern void OnIrq_RADIO(void);
extern void OnIrq_UARTE0_UART0(void);
extern void OnIrq_SPI0(void);
extern void OnIrq_SPI1(void);
extern void OnIrq_NFCT(void);
extern void OnIrq_GPIOTE(void);
extern void OnIrq_SAADC(void);
extern void OnIrq_TIMER0(void);
extern void OnIrq_TIMER1(void);
extern void OnIrq_TIMER2(void);
extern void OnIrq_RTC0(void);
extern void OnIrq_TEMP(void);
extern void OnIrq_RNG(void);
extern void OnIrq_ECB(void);
extern void OnIrq_CCM_AAR(void);
extern void OnIrq_WDT(void);
extern void OnIrq_RTC1(void);
extern void OnIrq_QDEC(void);
extern void OnIrq_COMP_LPCOMP(void);
extern void OnIrq_SWI0_EGU0(void);
extern void OnIrq_SWI1_EGU1(void);
extern void OnIrq_SWI2_EGU2(void);
extern void OnIrq_SWI3_EGU3(void);
extern void OnIrq_SWI4_EGU4(void);
extern void OnIrq_SWI5_EGU5(void);
extern void OnIrq_TIMER3(void);
extern void OnIrq_TIMER4(void);
extern void OnIrq_PWM0(void);
extern void OnIrq_PDM(void);
extern void OnIrq_MWU(void);
extern void OnIrq_PWM1(void);
extern void OnIrq_PWM2(void);
extern void OnIrq_SPI2(void);
extern void OnIrq_RTC2(void);
extern void OnIrq_I2S(void);
extern void OnIrq_FPU(void);

#endif/*__HELPER_IRQ_H__*/
