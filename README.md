#BeagleBone Black Driver Library (BBDL)


## Syslog message of BBDL

```bash
    tail -f /var/log/syslog | grep "BBDL"
```

## UART Pin Configuration

### Method 1
Create configure-pins.sh file in autorun folder if using cloud9:
```bash
#!/bin/bash

config-pin p9.26 uart
config-pin p9.24 uart
```
### Method 2
Debian image ~16.04 switched from capemgr to u-boot overlays. To enable Uart 1, in /boot/uEnv.txt set:
```bash
uboot_overlay_addr0=/lib/firmware/BB-UART1-00A0.dtbo 
```
And then reboot.
This method is explained here [here](https://groups.google.com/forum/#!topic/beagleboard/OG1_tts4OcU).
###Method 3
#### Create file `/usr/bin/enable-i2c-pins.sh`
This method is explained [here](https://gist.github.com/pdp7/d4770a6ba17e666848796bf5cfd0caee).
* **sudo vi /usr/bin/enable-i2c-pins.sh**
```
#!/bin/bash

config-pin p9.17 i2c
config-pin p9.18 i2c
```
* **sudo chmod 755 /usr/bin/enable-i2c-pins.sh**

#### Create file `/lib/systemd/system/enable-i2c-pins.service`
* **sudo vi /lib/systemd/system/enable-i2c-pins.service**
```
[Unit]
Description=Enable I2C pins
After=generic-board-startup.service

[Service]
Type=simple
ExecStart=/usr/bin/enable-i2c-pins.sh

[Install]
WantedBy=multi-user.target
```
#### Enable the new systemd service
* **sudo systemctl daemon-reload**
* **sudo systemctl enable enable-i2c-pins.service**
```
Created symlink /etc/systemd/system/multi-user.target.wants/enable-i2c-pins.service → /lib/systemd/system/enable-i2c-pins.service.
```

#### Reboot and test
* **sudo systemctl status enable-i2c-pins.service**
```
debian@beaglebone:~$ sudo systemctl status enable-i2c-pins.service
● enable-i2c-pins.service - Enable I2C pins
   Loaded: loaded (/lib/systemd/system/enable-i2c-pins.service; enabled)
   Active: inactive (dead) since Wed 2017-04-19 06:35:06 UTC; 48s ago
  Process: 649 ExecStart=/usr/bin/enable-i2c-pins.sh (code=exited, status=0/SUCCESS)
 Main PID: 649 (code=exited, status=0/SUCCESS)

Apr 19 06:35:05 beaglebone sudo[664]: root : TTY=unknown ; PWD=/ ; USER=root ; COMMAND=/bin/bash -c echo i2c > /sys/devices/platform/ocp/ocp:P9_17_pinmux/state
Apr 19 06:35:05 beaglebone sudo[664]: pam_unix(sudo:session): session opened for user root by (uid=0)
Apr 19 06:35:05 beaglebone sudo[664]: pam_unix(sudo:session): session closed for user root
Apr 19 06:35:06 beaglebone sudo[677]: root : TTY=unknown ; PWD=/ ; USER=root ; COMMAND=/bin/bash -c echo i2c > /sys/devices/platform/ocp/ocp:P9_18_pinmux/state
Apr 19 06:35:06 beaglebone sudo[677]: pam_unix(sudo:session): session opened for user root by (uid=0)
Apr 19 06:35:06 beaglebone sudo[677]: pam_unix(sudo:session): session closed for user root
```
* **config-pin -q p9.17 && config-pin -q p9.18**
```
debian@beaglebone:~$ config-pin -q p9.17 && config-pin -q p9.18
P9_17 Mode: i2c
P9_18 Mode: i2c
```