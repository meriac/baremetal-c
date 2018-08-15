/**************************************************************************//**
 * @file     cmsis_compiler.h
 * @brief    CMSIS compiler common header file
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
#ifndef __CMSIS_COMPILER_H__
#define __CMSIS_COMPILER_H__

#if defined ( __GNUC__ )
#  include "CMSIS5/cmsis_gcc.h"
#else
#  error Unsupported compiler, currently only GCC is supported.
#endif

#endif/*__CMSIS_COMPLILER_H__*/
