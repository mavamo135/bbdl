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
 *  @file       gpio.c 
 *	@brief      GPIO driver interface
 *	@author     Maximiliano Valencia
 *	@date       4/11/2018
 */

#include <stdio.h>
/* GPIO Driver Header File */
#include "driver.h"
#include "gpio.h"

/*
 *  ======== gpio_open ========
 */
uint8_t gpio_open(gpio_properties *gpio) {
    syslog (LOG_INFO, "gpio_open(): export GPIO %d", gpio->nr);
    FILE *export;
    
    export = fopen(SYSFS_GPIO_DIR "/export", "w");
    if (export < 0) {
    	perror("gpio_open(): export");
    	return -1;
    }
    char str[15];
    sprintf(str, "%d", gpio->nr);
    fputs(str, export);
    fclose(export);
    
    syslog (LOG_INFO, "gpio_open(): set direction %d, %d", gpio->nr, gpio->direction);
    FILE *fd;
    char buf[MAX_BUF];
    snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/direction", gpio->nr);
    fd = fopen(buf, "w");
    if (fd < 0) {
    	perror("gpio_open(): direction");
    	return -1;
    }
    if (gpio->direction == OUTPUT_PIN) {
    	fputs("out", fd);
    } else {
    	fputs("in", fd);
    }
    fclose(fd);
    return 0;
}

/*
 *  ======== gpio_write ========
 */
uint8_t gpio_write(gpio_properties *gpio, int value) {
	syslog (LOG_INFO, "gpio_write(): GPIO %d set value %d", gpio->nr, value);
	FILE *fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio->nr);

	fd = fopen(buf, "w");
	if (fd < 0) {
		perror("gpio_write(): set value");
		return -1;
	}

	char str[2];
	sprintf(str, "%d", value);
	fputs(str, fd);

	fclose(fd);
	return 0;
}

/*
 *  ======== gpio_read ========
 */
uint8_t gpio_read(gpio_properties *gpio) {
	syslog (LOG_INFO, "gpio_read(): GPIO %d get value", gpio->nr);
	uint8_t value;
	FILE *fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/value", gpio->nr);
	fd = fopen(buf, "r");
	if (fd < 0) {
		perror("gpio_read(): get value");
		return -1;
	}

	char str[2];
	fgets(str, 2, fd);

	if (strcmp(str, "1") == 0) {
		value = 1;
	} else {
		value = 0;
	}

	fclose(fd);
	return value;
}

/*
 *  ======== gpio_edge ========
 */
uint8_t gpio_edge(gpio_properties *gpio, char *edge) {
	syslog (LOG_INFO, "gpio_edge(): GPIO %d set edge %s", gpio->nr, edge);
	FILE *fd;
	char buf[MAX_BUF];

	snprintf(buf, sizeof(buf), SYSFS_GPIO_DIR "/gpio%d/edge", gpio->nr);

	fd = fopen(buf, "w");
	if (fd < 0) {
		perror("gpio_edge(): set edge");
		return 1;
	}

	fputs(edge, fd);
	fclose(fd);
	return 0;
}

/*
 *  ======== gpio_close ========
 */
uint8_t gpio_close(gpio_properties *gpio) {
	syslog (LOG_INFO, "gpio_close(): unexport GPIO %d", gpio->nr);
	FILE *fd;
	fd = fopen(SYSFS_GPIO_DIR "/unexport", "w");
	if (fd < 0) {
		perror("gpio_close(): unexport");
		return -1;
	}
	char str[15];
	sprintf(str, "%d", gpio->nr);
	fputs(str, fd);
	fclose(fd);

	return 0;
}