/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of BeagleBone Black Drivers Library (BBDL).            *
 *                                                                          *
 *   BBBDL is free software: you can redistribute it and/or modify it       *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   BBDL is distributed in the hope that it will be useful,                *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/
 
/*!
 *  @file       uart.h
 *	@author 	Maximiliano Valencia
 *	@date		4/10/2018
 *  @brief      UART driver interface
 *
 *  To use the UART driver, include this header file as follows:
 *  @code
 *  #include "drivers/uart.h"
 *  @endcode
 *
 *  # Overview #
 *  A UART is used to translate data between the chip and a serial port.
 *  The UART driver simplifies reading and writing to any of the UART
 *  peripherals on the board, with multiple modes of operation and performance.
 *
 *  # Usage #
 *
 *  The UART driver interface provides device independent APIs, data types,
 *  and macros.  The following code example opens a UART instance, reads
 *  a byte from the UART, and then writes the byte back to the UART.
 *
 *  @code
 *	// Set UART properties.
 *	init_bbc_lib();
 *	uart_properties *uart = malloc(sizeof(uart_properties));
 *	uart->uart_id = uart1;
 *	uart->baudrate = B4800;
 *
 *  uint8_t isOpen = uart_open(uart);
 *  @endcode
 *
 *  Details for the example code above are described in the following
 *  subsections.
 *
 *  ### Opening the UART Driver #
 *
 *  Opening a SPI requires four steps:
 *  1.  Create and initialize a uart_properties structure.
 *  2.  Fill in the desired parameters.
 *  3.  Call uart_open(), passing the uart_properties structure.
 *  4.  Check that the uint8_t returned by uart_open() is zero.
 *
 *  ### Reading and Writing data #
 *
 *  The example code reads one byte frome the UART instance, and then writes
 *  one byte back to the same instance:
 *
 *  @code
 *	char tx[] = "Hello!\n";
 *  unsigned char rx[100];
 *  uart_write(uart, tx, strlen(tx) + 1);
 *  uart_read(uart, rx, 100);
 *  @endcode
 *
 */


#ifndef __UART_H_
#define __UART_H_

#include <stdio.h>
#include <termios.h>

/*!
 *  @brief      Available UART peripherals
 */
typedef enum {
	uart0 = 0, 
	uart1 = 1, 
	uart2 = 2, 
	uart3 = 4
} uart;

/*!
 *  @brief      UART properties structure type definition
 */
typedef struct {
	int fd;
	uart uart_id;
	int baudrate;
} uart_properties;

/*!
 *  @brief  Function to initialize a given UART peripheral
 *
 *  Function to initialize a given UART peripheral specified by the
 *  particular index value.
 *
 *  @warning None.
 *
 *  @param  uart		A uart_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern int uart_open(uart_properties *uart);

/*!
 *  @brief  Function that writes data to a UART.
 *
 *  %uart_send() writes data from a memory buffer to the SPI interface.
 *  The source is specified by \a tx and the number of bytes to write
 *  is given by \a length.
 *
 *  @warning None.
 *
 *  @pre	uart_open() has been called
 *
 *  @param  uart		A uart_properties structure 
 *
 *  @param  tx      	A buffer containing data to be written to the UART
 *
 *  @param  length      The number of bytes in the buffer that should be written
 *                      to the UART
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern int uart_write(uart_properties *uart, char *tx, int length);

/*!
 *  @brief  Function that reads data from a UART.
 *
 *  %uart_read() reads data from a UART interface to a memory buffer.
 *  The sink is specified by \a rx and the number of bytes to write
 *  is given by \a length.
 *
 *  @warning None.
 *
 *  @pre	uart_open() has been called
 *
 *  @param  uart		A uart_properties structure 
 *
 *  @param  rx      	A buffer that will contain data to be read from the UART
 *
 *  @param  length      The number of bytes in the buffer that should be read
 *                      from the UART
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern int uart_read(uart_properties *uart,unsigned char *rx, int length);

/*!
 *  @brief  Function to close a UART peripheral specified by the UART handle
 *
 *  @warning None.
 *
 *  @pre	uart_open() has been called
 *	@pre	No data transfer is ongoing
 *
 *  @param  uart		A spi_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern int uart_close(uart_properties *uart);

#endif /* __UART_H_ */