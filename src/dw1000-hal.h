/*
 * dw1000, driver for decawave dw1000 UVB chip
 *  Copyright (C) 2014  Kim Albertsson
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU Lesser Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *  GNU Lesser Public License for more details.
 *  
 *  You should have received a copy of the GNU Lesser Public License
 *  along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef DW1000_HAL_H
#define DW1000_HAL_H

/**
 * \file dw1000-hal.h
 * \author Kim Albertsson
 * \date 2014-Oct-16
 */

/**
 * \addtogroup hal HAL interface
 * @{
 *
 * \brief Hardware abstraction layer for the Decawave dw1000 driver. Each 
 * platform has its own implementation of this interface where implementation 
 * details can be found.
 * 
 * \details Areas handled:
 *  - Interrupts (currently used to implement asyncronous communication).
 *  Interrupts are generated by the dw1000 when a masked event occurs, this 
 *  can be caught by the host processor if interrupts are enabled. The HAL 
 *  module interrupt part handles the host side of the dw1000 interrupt chain.
 *
 * \todo Refactor the SPI module to the HAL module. The SPI part was developed 
 * before the HAL module, it does however logically belong to the HAL module
 * and should thus be refactored in under it. It would require renaming quite
 * a lot of function calls in dw1000-base, but this should be all.
 *
 */

/**
 * \brief Run by the driver at initialisation. Set everything up so that the 
 * HAL can be used.
 */
void dw_hal_init();

/**
 * \ingroup hal
 * \addtogroup interrupt Interrupt system
 *
 * \brief Defines the hardware abstraction for interrupts.
 *
 * \details 
 *
 * \note Requires that the hal as been initialised by \ref dw_hal_init. (This
 * function is run automatically by \ref dw_init).
 * @{
 */

/**
 * \brief Enables interrupts on the host device.
 */
void dw_hal_enable_interrupt();

/**
 * \brief Disables interrupts on the host device.
 */
void dw_hal_disable_interrupt();

/**
 * \brief Disables interrupts on the host device.
 * 
 * \todo Currently there is only one interrupt pin. To future-proof, this 
 * function should be expanded to include an enum argument with a single 
 * value: DW_MAIN_INTERRUPT.
 */
void dw_hal_clear_pending_interrupt();

/**
 * \brief Generalisation for interrupt vector.
 * \todo Should be private to platform-hal?
 */
void (* dw_hal_interrupt_handler)();
/**
 * \brief Host callback when interrupt detected.
 * \todo Should be private to platform-hal?
 */
void (* dw_hal_interrupt_callback)();

/** @}*/
/** @}*/

#endif