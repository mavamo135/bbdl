/****************************************************************************
 * Copyright (C) 2018 by Maximiliano Valencia                               *
 *                                                                          *
 * This file is part of BeagleBone Black Drivers Library (BBDL).            *
 *                                                                          *
 *   BBDL is free software: you can redistribute it and/or modify it        *
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
 *   License along with BBDL.  If not, see <http://www.gnu.org/licenses/>.  *
 ****************************************************************************/

/** 
 *  @file       uart.c 
 *	@brief      UART driver interface
 *	@author     Maximiliano Valencia
 *	@date       4/10/2018
 */


/* UART Driver Header File */
#include "driver.h"
#include "uart.h"

/*
 *  ======== uart_open ========
 */
int uart_open(uart_properties *uart) {
	char buf[30] = "/dev/ttyO";
	char port_nr[2];
	struct termios options;
	
	/* Set UART peripheral number */
	sprintf(port_nr, "%d", uart->uart_id);
	strcat(buf,port_nr);
    /* OPEN THE UART
     * The flags (defined in fcntl.h):
     *	Access modes (use 1 of these):
     *		O_RDONLY - Open for reading only.
     *		O_RDWR - Open for reading and writing.
     *		O_WRONLY - Open for writing only.
     *
     *	O_NDELAY / O_NONBLOCK (same function) - Enables nonblocking mode. When set read requests on the file can return immediately with a failure status
     *											if there is no input immediately available (instead of blocking). Likewise, write requests can also return
     *											immediately with a failure status if the output can't be written immediately.
     *
     *	O_NOCTTY - When set and path identifies a terminal device, open() shall not cause the terminal device to become the controlling terminal for the process.
     */
    uart->fd = open(buf, O_RDWR | O_NOCTTY | O_NDELAY);	/* Open in non blocking read/write mode */
    if (uart->fd < 0) { /* ERROR - CAN'T OPEN SERIAL PORT */
    	syslog(LOG_ERR, "Unable to open UART %i (%s)", uart->uart_id, buf);
    	exit(1);
    }
    syslog(LOG_ERR, "UART %i (%s) opened", uart->uart_id, buf);
	/* CONFIGURE THE UART
     * The flags (defined in /usr/include/termios.h - see http://pubs.opengroup.org/onlinepubs/007908799/xsh/termios.h.html):
     *	Baud rate:- B1200, B2400, B4800, B9600, B19200, B38400, B57600, B115200, B230400, B460800, B500000, B576000, B921600, B1000000, B1152000, B1500000, B2000000, B2500000, B3000000, B3500000, B4000000
     *	CSIZE:- CS5, CS6, CS7, CS8
     *	CLOCAL - Ignore modem status lines
     *	CREAD - Enable receiver
     *	IGNPAR = Ignore characters with parity errors
     *	ICRNL - Map CR to NL on input (Use for ASCII comms where you want to auto correct end of line characters - don't use for binary comms!)
     *	PARENB - Parity enable
     *	PARODD - Odd parity (else even)
     */
    tcgetattr(uart->fd, &options);
    options.c_cflag = uart->baudrate | CS8 | CLOCAL | CREAD;
    options.c_iflag = IGNPAR | ICRNL;
    options.c_oflag = 0;
    options.c_lflag = 0;
    /* clean the line and set the attributes */
    tcflush(uart->fd, TCIFLUSH);
    tcsetattr(uart->fd, TCSANOW, &options);

	return 0;
}

/*
 *  ======== uart_write ========
 */
int uart_write(uart_properties *uart, char *tx, int length) {
	if (write(uart->fd, tx, length) == -1) {
		syslog(LOG_ERR, "Could not write %s to UART %i", tx, uart->uart_id);
		return -1;
	}
	syslog(LOG_INFO, "Wrote %s to UART %i", tx, uart->uart_id);
	return 0;
}

/*
 *  ======== uart_read ========
 */
int uart_read(uart_properties *uart,unsigned char *rx, int length) {
	int count;
	if( (count = read(uart->fd,(void*)rx,length)) > 0) {
		syslog(LOG_ERR, "Could not read from UART %i", uart->uart_id);
		return count;
	}
	syslog(LOG_INFO, "Read %s from UART %i", rx, uart->uart_id);
	return 0;
}

/*
 *  ======== uart_close ========
 */
int uart_close(uart_properties *uart) {
	close(uart->fd);
	return 0;
}