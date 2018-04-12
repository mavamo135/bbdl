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
 *   License along with Box.  If not, see <http://www.gnu.org/licenses/>.   *
 ****************************************************************************/

/** 
 *  @file       driver.c 
 *	@brief      UART driver interface
 *	@author     Maximiliano Valencia
 *	@date       4/10/2018
 */


/* UART Driver Header File */
#include "driver.h"

void (*callbackFxn)(void);

/*
 *  ======== sigintHandler ========
 */
/* Signal Handler for SIGINT */
void sigintHandler(int sig_num) {
    /* Reset handler to catch SIGINT next time.
       Refer http://en.cppreference.com/w/c/program/signal */
    signal(SIGINT, sigintHandler);
    (*callbackFxn)();
}

/*
 *  ======== drivers_init ========
 */
uint8_t drivers_init(void (*fxn)(void)) {
	openlog("BBDL", LOG_PID | LOG_CONS | LOG_NDELAY | LOG_NOWAIT, LOG_LOCAL0);
	syslog(LOG_INFO, "%s", "Starting BBDL");
	
	callbackFxn = fxn;
	
	signal(SIGINT, sigintHandler);
	
	return 0;
}