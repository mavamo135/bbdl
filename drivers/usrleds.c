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
 *  @file       usrleds.c 
 *	@brief      User LEDs driver interface
 *	@author     Maximiliano Valencia
 *	@date       4/10/2018
 */

/* User LEDs Driver Header File */
#include "driver.h"
#include "usrleds.h"


/*
 *  ======== writeToFile ========
 */
static void writeToFile(char* filename, char* text) {
    FILE* file = fopen(filename, "w");
    fprintf(file, "%s", text);
    fclose(file);
}

/*
 *  ======== usrleds_init ========
 */
void usrleds_init() {
    usrleds_write(LED1, 0);
    usrleds_write(LED2, 0);
    usrleds_write(LED3, 0);
    usrleds_write(LED4, 0);
}

/*
 *  ======== usrleds_write ========
 */
void usrleds_write(char* led, int value) {
    char filename[255];
    char valueStr[10];

    sprintf(filename, "%s/trigger", led);
    writeToFile(filename, "none");

    sprintf(filename, "%s/brightness", led);
    sprintf(valueStr, "%i", value);

    writeToFile(filename, valueStr);
}

/*
 *  ======== usrleds_flash ========
 */
void usrleds_flash(char* led) {
    char filename[255];

    sprintf(filename, "%s/trigger", led);
    writeToFile(filename, "timer");

    sprintf(filename, "%s/delay_on", led);
    writeToFile(filename, "200");

    sprintf(filename, "%s/delay_off", led);
    writeToFile(filename, "200");
}