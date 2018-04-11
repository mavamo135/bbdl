/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of Box.                                                *
 *                                                                          *
 *   Box is free software: you can redistribute it and/or modify it         *
 *   under the terms of the GNU Lesser General Public License as published  *
 *   by the Free Software Foundation, either version 3 of the License, or   *
 *   (at your option) any later version.                                    *
 *                                                                          *
 *   Box is distributed in the hope that it will be useful,                 *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of         *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the          *
 *   GNU Lesser General Public License for more details.                    *
 *                                                                          *
 *   You should have received a copy of the GNU Lesser General Public       *
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/** 
 *	@file   spi.c 
 *	@brief  SPI driver interface
 *	@author Maximiliano Valencia
 *	@date 4/10/2018
 */

#include <sys/ioctl.h>
#include <linux/spi/spidev.h>
/* SPI Driver Header File */
#include "driver.h"
#include "spi.h"



/*
 *  ======== spi_open ========
 */
uint8_t spi_open(spi_properties *spi) {
    /* syslog (LOG_INFO, "spi open - spi:%d bits_per_word:%d speed:%d mode:%f", spi, bits_per_word, speed, mode); */
    char filename[20];
    sprintf(filename, "/dev/spidev1.%d", spi->spi_id);
    spi->fd = open(filename, spi->flags); 
    if (spi->fd < 0) {
		perror("SPI: Could not open spi.");
		return -1;
    }
    printf("[INF] SPI FD: %i", spi->fd);
    if (ioctl(spi->fd, SPI_IOC_WR_MODE, &spi->mode)==-1){
       perror("SPI: Can't set SPI mode.");
       return -1;
    }
    if (ioctl(spi->fd, SPI_IOC_WR_BITS_PER_WORD, &spi->bits_per_word)==-1){
       perror("SPI: Can't set bits per word.");
       return -1;
    }
    if (ioctl(spi->fd, SPI_IOC_WR_MAX_SPEED_HZ, &spi->speed)==-1){
       perror("SPI: Can't set max speed HZ");
       return -1;
    }
    /* Check that the properties have been set */
    syslog(LOG_INFO,"SPI fd is: %d\n", spi->fd);
    syslog(LOG_INFO,"SPI Mode is: %d\n", spi->mode);
    syslog(LOG_INFO,"SPI Bits is: %d\n", spi->bits_per_word);
    syslog(LOG_INFO,"SPI Speed is: %d\n", spi->speed);
    return 0;
}

/*
 *  ======== spi_close ========
 */
uint8_t spi_close(spi_properties *spi) {
	syslog(LOG_INFO, "SPI close - SPI:%d", spi->fd);
    close(spi->fd);
    return 0;
}

/*
 *  ======== spi_write ========
 */
uint8_t spi_write(spi_properties *spi, unsigned char tx[], int length) {
	unsigned char rx[length];
	return spi_transfer(spi, tx, rx, length);
}

/*
 *  ======== spi_transfer ========
 */
uint8_t spi_transfer(spi_properties *spi, unsigned char tx[], unsigned char rx[], int length) {
	struct spi_ioc_transfer transfer = {
		   .tx_buf = (unsigned long)tx,
		   .rx_buf = (unsigned long)rx,
		   .len = length,
		   .delay_usecs = 0,
		   .speed_hz = spi->speed,
		   .bits_per_word = spi->bits_per_word,
   };
   /* send the SPI message (all of the above fields, inc. buffers) */
   int status = ioctl(spi->fd, SPI_IOC_MESSAGE(1), &transfer);
   if (status < 0) {
      perror("SPI: SPI_IOC_MESSAGE Failed");
      return -1;
   }
   return 0; /* status */;
}