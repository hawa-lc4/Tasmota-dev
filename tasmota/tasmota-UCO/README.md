This folder shall keep a collection of User Config Override files (user_config_override.h) showing projects and solutions created by me (hawa-lc4).
For all modifications here please refer to tasmota online documentation on https://tasmota.github.io/docs/
Builds are based on a modified platformio_override.ini file; please be aware of this being includes in the package.
Do not accidentally overwrite your local platformio_override.ini file!

Most solutions are based on tasmota scripting language (https://tasmota.github.io/docs/Scripting-Language/) for I found this more powerful than using Rules.
The file user_private_data.h not included in this package keeps private settings as this is:
 - STA_SSID1
 - STA_PASS1
 - STA_SSID2
 - STA_PASS2
 - NTP_SERVER1
 - NTP_SERVER2
 - NTP_SERVER3
 - MQTT_HOST
 - WEB_USERNAME
 - WEB_PASSWORD

If you need settings on any of these parameters at compilation time please create this file using the usual C++ rules and provide the information there.
Alternatively comment on the #include line if not already done and provide in user_config_override.h file directly.
 

A short description (UCO = User Config Override):
- UCO_BadFbHz:          A SmartHome switch to control an electric floor heater with PV overpower. Based on ESP8266 and basically the same as onIoff.
- UCO_onIoff:           A modification of a onIoff MS-101 smart switch. The processor chip inside has to be replaced by an ESP8266.
                        Build:  env:tasmota4M-script  only

- UCO_phase13:          A simple, selfmade smart switch controlled by wbec (https://github.com/steff393/wbec) to provide a phase control function to wbec and 
                        optimize solar charge effectivity for EV by this. Based on ESP8266 board.
                        Build:  env:tasmota4M-rule  oder env:tasmota4M-script (script untested!)

- UCO_tasmotix-sml:     A simple smart meter reader and data logger to SD-card for dedicated smart meters I have access to. Based on ESP8266 board.
                        Build:  env:tasmota4M-script  only
                        Work in progress .....

- UCO_mbtcp-gate:       A modbusTCP gateway for a PV-Inverter together with a fan control for this inverter based on temperature detected by a DS18B20 sensor
                        Also a smartmeter reader to provide data to a MQTT broker
                        Work in progress .....

- 



## License

This program is licensed under GPL-3.0-only
