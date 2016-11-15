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

#ifndef DW_FRAME_TYPE_H
#define DW_FRAME_TYPE_H

#include "stdint.h"

#define DW_FRAME_SEC  (1<<3)
#define DW_FRAME_PEND (1<<4)
#define DW_FRAME_ACK  (1<<5)

#define DW_FRAME_RANGE_LEN 21
#define DW_FRAME_BLINK_LEN 10
#define DW_FRAME_FCS_LEN   2

#define DW_MSG_POLL_LEN       1
#define DW_MSG_RESPONSE_LEN   4
#define DW_MSG_FINAL_LEN      16
#define DW_MSG_RANGE_INIT_LEN 5

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Header
	uint16_t  frame_control; // Constant 0xCC41 for DecaRange
	uint8_t   seq_no;
	uint16_t  pan_id;        // Constant 0xDECA for DecaRange
	uint64_t  dest_addr;
	uint64_t  src_addr;

	// Data
	uint8_t * pPayload;

	// Checksum
	uint16_t  fcs;           // Generated by chip at transmit
} dw_frame_range_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Frame control should always be 0xC5 for blink frame
	uint8_t  frame_control;
	uint8_t  seq_no;
	uint64_t tag_id;
	uint16_t fcs;
} dw_frame_blink_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Function code should always be 0x21 for poll message
	uint8_t  function_code;
} dw_message_poll_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Function code should always be 0x10 for response message
	uint8_t  function_code;
	uint8_t  activity;
	uint16_t activity_param;
} dw_message_response_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Function code should always be 0x29 for final message
	uint8_t function_code;
	uint8_t poll_msg_tx_timestamp[5];
	uint8_t resp_msg_rx_timestamp[5];
	uint8_t final_msg_tx_timestamp[5];
} dw_message_final_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Function code should always be 0x2A for report message
	uint8_t function_code;
	uint8_t tof[6];
} dw_message_report_t;

/* Warning: Packed struct. Never use pointers to fields.
 * http://stackoverflow.com/questions/8568432/is-gccs-attribute-packed-pragma-pack-unsafe
 */
typedef struct __attribute__((packed))
{
	// Function code should always be 0x20 for range init message
	uint8_t  function_code;
	uint16_t tag_addr;
	uint16_t response_delay_ms;
} dw_message_range_init_t;

void dw_init_frame_blink( dw_frame_blink_t * blinkFrame );
void dw_init_frame_range( dw_frame_range_t * rangeFrame, uint64_t destAddr );

void dw_init_message_poll(     dw_message_poll_t * msg     );
void dw_init_message_response( dw_message_response_t * msg );
void dw_init_message_final( 	 dw_message_final_t * msg,
							     uint64_t poll_tx,
							     uint64_t resp_rx,
							     uint64_t final_tx
							);
void dw_init_message_report(     dw_message_report_t     * msg, uint64_t tof );
void dw_init_message_range_init( dw_message_range_init_t * msg, uint16_t tagAddr, uint16_t respDelay );
#endif