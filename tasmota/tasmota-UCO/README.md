This folder shall keep a collection of User Config Override files (user_config_override.h) showing projects and solutions created by me (hawa-lc4).
For all modifications here please refer to tasmota online documentation on https://tasmota.github.io/docs/
Builds are based on a modified platformio_override.ini file; please be aware of this and make sure it is included in the build procedure.
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
 - WIFI_AP_PASSPHRASE

If you need settings on any of these parameters at compilation time please create this file using the usual C++ rules and provide the information there.
Alternatively comment on the #include line, if not already done, and provide the information needed in user_config_override.h file directly.
 
A very brief description (UCO = User Config Override):
- UCO_BadFbHz:          A SmartHome switch to control an electric floor heater with PV overpower. Temperature control is done outside this module.
                        Based on ESP8266 and basically the same as onIoff.
- UCO_BadHkHz?:         Basically the same funktion as UCO_BadFbHz expanded with a display and a rotary switch to change the target temperature.

- UCO_onIoff:           A modification of a onIoff MS-101 smart switch. The processor chip inside has to be replaced by an ESP8266.
                        Build:  env:tasmota4M-script  only

- UCO_Kuehlfix:         Also a smart switch to activate a air conditioner if PV overpower is available. Module based on ESP8266 and scritping language.
                        Temperature is taken by a DS18B20 1wire sensor and displayed on the device ba a small 0.96" OLED display.
                        The reference temperature can be adjusted ba a slider in Web UI. Once the compressor motor here is turned off it cannot be turned on
                        at once again, it strictly needs a few minutes delay. The main control is not intended to be done by Web UI but done by MQTT or http
                        commands from a HEMS.

- UCO_phase13:          A simple, selfmade smart switch controlled by wbec (https://github.com/steff393/wbec) to provide a phase control function to wbec and 
                        to optimize solar charge effectivity for EV. Based on ESP8266 board.
                        Build:  env:tasmota4M-rule  oder env:tasmota4M-script (script untested!)

- UCO_SML-logger:       A simple smart meter reader and data logger to SD-card for dedicated smart meters I have access to. Based on ESP8266 board.
                        Work In Progress! The logging rate is too high; has to be changed.
                        Build:  env:tasmota4M-script  only
                        Work in progress .....
- UCO_SML-reader&NTP:   Basically the same as UCO_SML-logger; a special version to permanently in AP mode and expanded by a RTC module to work fully
                        without internet access. A special version for Volker.

- UCO_mbtcp-gate:       A modbusTCP gateway for a PV-Inverter together with a PWM fan control for this inverter based on temperature given by a DS18B20 sensor
                        Also including a smartmeter reader to provide grid data to a MQTT broker.

- UCO_mbtcp-gate32:     The same as UCO_mbtcp-gate but redesigned to use a WT32-ETH01 module working via Ethernet only instead of using WiFi.

- UCO_BMX-LightControl: A module to control lightswitches for a BMX trail secured by RFID chips. There is no network/WiFi available there so this module
                        (based on ESP8266) works in AP-mode all time but can also connect to a WiFi hotspot hosted by a smartphone temporarily.
                        The time base is provided by an RTC module. Control program is based on scripting language.
                        It has a modified library xdrv_01_9_webserver.ino; please read this: https://github.com/arendst/Tasmota/discussions/19009

- UCO_Heizstab_berry:   A modified Shelly Plus Plug-S to control a heater element added to the central heating in my house.
                        The heating function is supervised ba a flow sensor detecting the central heater pump is active or not. It also hosts a 1-wire
                        temperature sensor to show the temparature of the outgoing water; currently not used to control the heater function.
                        The four WS2812 RGB-Leds can be controlled by Berry-script separately and are used to indicate the state of activation via HEMS,
                        state of the flow sensor, state of the power relay and the actual power consumption.
                        Based on the env:tasmota32-berry and operated by Berry-script only.

- UCO_Shelly+_PlugS_berry: A Shelly Plus Plug-S moved to Tasmota firmware and fully controlled by Berry-script similar to UCO_Heizstab_berry.
                        Similar configuration used for other smart plugs of same type, only project name changed.
                        (This single device Silvercrest was flashed succeffully by OTA; unfortunately no documentation of the steps performed.
                        Further attempts to convert absolutely similar devices by OTA failed, the devices had to be opened and flashed by serial interface.
                        Affected configurations/devices: Heizstab, Honeywell and Tasmota-Plug)


The subfolder "temp" only keeps projects started but not finished and probaly they never will be.
Keep caution! They may work or not!

## License

This program is licensed under GPL-3.0-only
