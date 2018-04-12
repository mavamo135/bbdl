# BeagleBone Black Driver Library (BBDL)


## Syslog messages of BBDL

```bash
    tail -f /var/log/syslog | grep "BBDL"
```

## Configuration

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
This method is explained [here](https://groups.google.com/forum/#!topic/beagleboard/OG1_tts4OcU).

### Method 3
#### Create file `/usr/bin/configure-pins.sh`
This method is explained [here](https://gist.github.com/pdp7/d4770a6ba17e666848796bf5cfd0caee).
* **sudo nano /usr/bin/configure-pins.sh**
```
#!/bin/bash

config-pin p9.24 uart
config-pin p9.26 uart
```
* **sudo chmod 755 /usr/bin/configure-pins.sh**

#### Create file `/lib/systemd/system/configure-pins.service`
* **sudo nano /lib/systemd/system/configure-pins.service**
```
[Unit]
Description=Enable BBDL pins
After=generic-board-startup.service

[Service]
Type=simple
ExecStart=/usr/bin/configure-pins.sh

[Install]
WantedBy=multi-user.target
```
#### Enable the new systemd service
* **sudo systemctl daemon-reload**
* **sudo systemctl enable configure-pins.service**
```
Created symlink /etc/systemd/system/multi-user.target.wants/configure-pins.service → /lib/systemd/system/configure-pins.service.
```

#### Reboot and test
* **sudo systemctl status configure-pins.service**
```
debian@beaglebone:~$ sudo systemctl status configure-pins.service
● configure-pins.service - Enable BBDL pins
   Loaded: loaded (/lib/systemd/system/configure-pins.service; enabled)
   Active: inactive (dead) since Wed 2017-04-19 06:35:06 UTC; 48s ago
  Process: 649 ExecStart=/usr/bin/configure-pins.sh (code=exited, status=0/SUCCESS)
 Main PID: 649 (code=exited, status=0/SUCCESS)
```
* **config-pin -q p9.24 && config-pin -q p9.26**
```
debian@beaglebone:~$ config-pin -q p9.24 && config-pin -q p9.26
P9_24 Mode: uart
P9_26 Mode: uart
```

# TODO

* Automatic dependency tracking in Makefile

## License

This project is licensed under the MIT License - see the [LICENSE.md](LICENSE.md) file for details

## Acknowledgments

* sijpesteijn/BBCLib
