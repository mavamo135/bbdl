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
 *  @file       driver.h
 *	@author 	Maximiliano Valencia
 *	@date		4/10/2018
 *  @brief      Drivers Header File
 */

#ifndef __DRIVER_H_
#define __DRIVER_H_


#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stddef.h>
#include <unistd.h>	
#include <string.h>
#include <strings.h>
#include <fcntl.h>		
#include <termios.h>	
#include <dirent.h>
#include <syslog.h>
#include <signal.h>

/*!
 *  @brief  Function to initialize drivers library
 *
 *  @return Returns if an error ocurred, 0 means no error ocurred
 */
extern uint8_t drivers_init();

#endif /* __DRIVER_H */