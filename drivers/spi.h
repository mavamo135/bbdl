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
 *  @file       spi.h
 *	@author 	Maximiliano Valencia
 *	@date		4/10/2018
 *  @brief      SPI driver interface
 *
 *  To use the SPI driver, include this header file as follows:
 *  @code
 *  #include "drivers/spi.h"
 *  @endcode
 *
 *  # Overview #
 *  A SPI is used to translate data between the chip and a serial port.
 *  The SPI driver simplifies reading and writing to any of the SPI
 *  peripherals on the board, with multiple modes of operation and performance.
 *
 *  # Usage #
 *
 *  The SPI driver interface provides device independent APIs, data types,
 *  and macros.  The following code example opens a SPI instance.
 *
 *  @code
 *	// Set SPI properties.
 *	spi_properties *spi = malloc(sizeof(spi_properties));
 *	spi->spi_id = spi0;
 *	spi->bits_per_word = 8;
 *	spi->mode = 0;
 *	spi->speed = 10000000;
 *	spi->flags = O_RDWR;
 *
 *	uint8_t isOpen = spi_open(spi);
 *  @endcode
 *
 *  Details for the example code above are described in the following
 *  subsections.
 *
 *  ### Opening the SPI Driver #
 *
 *  Opening a SPI requires four steps:
 *  1.  Create and initialize a spi_properties structure.
 *  2.  Fill in the desired parameters.
 *  3.  Call spi_open(), passing the spi_properties structure.
 *  4.  Check that the uint8_t returned by spi_open() is zero.
 *
 *  ### Reading and Writing data #
 *
 *  The example code reads one byte frome the SPI instance, and then writes
 *  one byte back to the same instance:
 *
 *  @code
 *	unsigned char tx = 0x04;
 *  unsigned char rx;
 *  spi_send(spi, tx, 1);
 *  spi_transfer(spi, tx, rx, 1);
 *  @endcode
 *
 */


#ifndef __SPI_H_
#define __SPI_H_

#include <linux/spi/spidev.h>

/*!
 *  @brief      Available SPI peripherals
 */
typedef enum {
	spi0 = 0, 
	spi1 = 1
} spi;

/*!
 *  @brief      SPI properties structure type definition
 */
typedef struct {
	int fd;
	spi spi_id;
	uint8_t bits_per_word;	/*!< @brief is used to hold the bits per word size of SPI */
	uint8_t mode;			/*!< @brief is used to hold the mode of SPI */
	uint32_t speed; 		/*!< @brief is used to hold the speed of SPI */
	uint8_t flags;
} spi_properties;

/*!
 *  @brief  Function to initialize a given SPI peripheral
 *
 *  Function to initialize a given SPI peripheral specified by the
 *  particular index value.
 *
 *  @warning None.
 *
 *  @param  spi			A spi_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t spi_open(spi_properties* spi);

/*!
 *  @brief  Function that writes data to a SPI.
 *
 *  %spi_send() writes data from a memory buffer to the SPI interface.
 *  The source is specified by \a tx and the number of bytes to write
 *  is given by \a length.
 *
 *  @warning None.
 *
 *  @pre	spi_open() has been called
 *
 *  @param  spi			A spi_properties structure 
 *
 *  @param  tx      	A buffer containing data to be written to the SPI
 *
 *  @param  length      The number of bytes in the buffer that should be written
 *                      to the SPI
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t spi_write(spi_properties *spi, unsigned char tx[], int length);

/*!
 *  @brief  Function that writes and reads data to a SPI.
 *
 *  %spi_transfer() writes data from a memory buffer to the SPI interface.
 *	%spi_transfer() reads data from the SPI interface to a memory buffer.
 *  The source and sink are specified by \a tx and \a rx 
 *  and the number of bytes to write is given by \a length.
 *
 *  @warning None.
 *
 *  @pre	spi_open() has been called
 *
 *  @param  spi			A spi_properties structure 
 *
 *  @param  tx      	A buffer containing data to be written to the SPI
 *
 *  @param  rx      	A buffer that will contain data to be read from the SPI
 *
 *  @param  length      The number of bytes in the buffer that should be written
 *                      to the SPI
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t spi_transfer(spi_properties *spi, unsigned char tx[], unsigned char rx[], int length);

/*!
 *  @brief  Function to close a SPI peripheral specified by the SPI handle
 *
 *  @warning None.
 *
 *  @pre	spi_open() has been called
 *	@pre	No data transfer is ongoing
 *
 *  @param  spi			A spi_properties structure 
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t spi_close(spi_properties *spi);

#endif /* __SPI_H_ */