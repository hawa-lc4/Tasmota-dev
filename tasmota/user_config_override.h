/*
  user_config_override.h - user configuration overrides my_user_config.h for Tasmota

  Copyright (C) 2021  Theo Arends

  This program is free software: you can redistribute it and/or modify
  it under the terms of the GNU General Public License as published by
  the Free Software Foundation, either version 3 of the License, or
  (at your option) any later version.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

#ifndef _USER_CONFIG_OVERRIDE_H_
#define _USER_CONFIG_OVERRIDE_H_

/*****************************************************************************************************\
 * USAGE:
 *   To modify the stock configuration without changing the my_user_config.h file:
 *   (1) copy this file to "user_config_override.h" (It will be ignored by Git)
 *   (2) define your own settings below
 *
 ******************************************************************************************************
 * ATTENTION:
 *   - Changes to SECTION1 PARAMETER defines will only override flash settings if you change define CFG_HOLDER.
 *   - Expect compiler warnings when no ifdef/undef/endif sequence is used.
 *   - You still need to update my_user_config.h for major define USE_MQTT_TLS.
 *   - All parameters can be persistent changed online using commands via MQTT, WebConsole or Serial.
\*****************************************************************************************************/

#include "user_private_data.h"               // not sharing sensible data with the global community; hawa-lc4
// don't forget to check and modify the file above!

// #ifdef %identifier%
// #undef %identifier%
// #endif
// #define %identifier%   %the_new_value%

#ifdef PROJECT
#undef PROJECT
#endif
#define PROJECT               "tasmotix"   // der Spielw�rfel

#ifdef T4M_RULE
  #warning **** Build: RULES ****
  #undef CODE_IMAGE_STR
  #define CODE_IMAGE_STR "T4M_RULE"
  #ifdef USE_SCRIPT
  #undef USE_SCRIPT
  #endif

  #ifndef USE_RULES
  #define USE_RULES
  #endif

  #ifndef USE_EXPRESSION
  #define USE_EXPRESSION
  #endif

  #ifndef SUPPORT_IF_STATEMENT
  #define SUPPORT_IF_STATEMENT
  #endif

  #define USER_RULE1            "ON Power1#Boot DO Backlog0 Hostname tasmotix;FriendlyName2 programm;AdcParam 7,0,515,0.23,0;Mem2 openWB/config/set/SmartHome/Devices/3/mode;Mem3 openWB/config/set/SmartHome/Devices/3/device_manual_control;Rule1 0;Rule1 \" ENDON"
  #define USER_RULE2            "ON System#Init DO Backlog Ruletimer1 2;LedPower3 1 ENDON ON Power1#State DO Backlog RuleTimer1 2;LedPower3 1 ENDON ON Rules#Timer=1 DO LedPower3 0 ENDON ON Power1#State=1 DO backlog Mem1=1; adcparam 7,0,612,0.23,0 ENDON ON Power1#State=0 DO backlog Mem1=0;adcparam 7,0,0,0.23,0 ENDON ON Power2#State DO LedPower3 %value% ENDON ON Button1#State DO IF (Mem1==0) publish %Mem2% 1;Power1 1;publish %Mem3% 1 ELSE publish %Mem3% 0;Power1 0;ruletimer3 60 ENDIF ENDON ON rules#timer=3 DO publish %Mem2% 0 ENDON"
  #define USER_RULE3            ""
  #define USER_BACKLOG          "Rule1 1;Rule2 1;Rule3 1;PulseTime2 7"
#endif // T4M_RULE

#ifdef T4M_SCRIPT
  #warning **** Build: SCRIPT ****
  #undef CODE_IMAGE_STR
  #define CODE_IMAGE_STR "T4M_SCRIPT"

  #undef USE_RULES
  #undef USE_TIMERS
  #undef USE_TIMERS_WEB
  #undef USE_SUNRISE

  #define USE_SCRIPT

  #define USE_SCRIPT_SERIAL
  #define USE_SCRIPT_TIMERS
  // #define USE_SCRIPT_SUB_COMMAND
  #define USE_SCRIPT_GLOBVARS
  // #define USE_SCRIPT_JSON_EXPORT
  #define USE_SCRIPT_WEB_DISPLAY
  #define USE_BUTTON_EVENT
  #define SCRIPT_POWER_SECTION
  #define START_SCRIPT_FROM_BOOT      // https://tasmota.github.io/docs/Scripting-Language/
  #define USER_BACKLOG "Script 1"     // hier nur script aktivieren, sonst nichts!

  #define PRECONFIGURED_SCRIPT \
  ">D\n\n"
  
/*   5 Zeichen Skript; 8187 Zeichen �brig von 8192   */

#endif // T4M_SCRIPT

#ifdef USER_TEMPLATE
#undef USER_TEMPLATE
#endif
#define USER_TEMPLATE "{\"NAME\":\"tasmotix\",\"GPIO\":[32,0,544,0,0,0,0,0,0,0,0,0,0,0],\"FLAG\":0,\"BASE\":18,\"CMND\":\"Module 0\"}"  // [Template] Set JSON template
// https://tasmota.github.io/docs/Components/  &  https://randomnerdtutorials.com/esp8266-pinout-reference-gpios
// D:\Users\G�nter\Documents\Elektronik\ESP32\__Dokumentation\ESP8266_D1-mini-pinout.pdf
// GPIO0  Taster gegen GND (kann damit auch zum FlashBoot benutzt werden) -- 32     // Taster 
// GPIO1  TX UART0                                                        -- 0      // 
// GPIO2  hat die interne LED gegen VCC; Funktion LedLink (544; _i: 576)  -- 544    // LedLink
// GPIO3  RX UART0                                                        -- 0      // 
// GPIO4  I2C SDA (640)                                                   -- 0      // 
// GPIO5  I2C SCL (608)                                                   -- 0      // 
// GPIO9  DO NOT USE!!                                                    -- 0      // DO NOT USE!!
// GPIO10 DO NOT USE!!                                                    -- 0      // DO NOT USE!!
// GPIO12 SPI MISO (672)                                                  -- 0      // 
// GPIO13 SPI MOSI (704)                                                  -- 0      // 
// GPIO14 SPI CLK  (736)                                                  -- 0      // 
// GPIO15 SPI SS (768) - SDCard CS (6240)                                 -- 0      // 
// GPIO16 (wake-up aus dem deep-sleep Modus: 4096)                        -- 0      // 
// GPIO17 ist der AD0 (CT Power: 4896)                                    -- 0      // 
/*  ACHTUNG:  der D1-mini hat am Eingang AD0 einen Spannungsteiler und damit eine max. Eingangsspannung von 3,3V
              der ESP8266 hat keinen Spannungsteiler und damit eine max. Eingangsspannung von 1,0V
*/
//
// AdcParam:  7
//  1. Param:   Nullpunkt f�r DC Messung; bei AC immer 0!
//  2. Param:   Multiplikator; param = (100.000 * Irms / ADC_value); ADC_value = Upp_sensor / 5,0244 * 1023; 1 / 820 * (3300 + 820) = 5,0244   // f�r ACS712 Stromsensoren
//              (https://github.com/arendst/Tasmota/discussions/19409#discussioncomment-6857837)
//  3. Param:   Spannung; Wert * 1000
//  4. Param:   NULL-Offset; Strom kleiner als der hier eingetragene wird als 0 behandelt
// hawa-lc4: xsns_02_analog.ino Zeile 482 (12.5.0.2) bzw. 504 (13.2.0.2) aktivieren des logging der ADC Werte
#define hawa_LOG               false


#define USE_UFILESYS
#define UFSYS_SIZE 8192
#define GUI_EDIT_FILE
#define GUI_TRASH_FILE

#ifdef TELE_PERIOD
#undef TELE_PERIOD
#endif
#define TELE_PERIOD             300              // [TelePeriod] Telemetry (0 = disable, 10 - 3600 seconds)

#ifdef MODULE
#undef MODULE
#endif
#define MODULE                 USER_MODULE

#ifdef MQTT_USE
#undef MQTT_USE
#endif
#define MQTT_USE               false

#ifdef MQTT_TOPIC
#undef MQTT_TOPIC
#endif
#define MQTT_TOPIC             PROJECT

//  #define SUPPORT_MQTT_EVENT                     // Support trigger event with MQTT subscriptions (+3k5 code)

#ifdef FRIENDLY_NAME
#undef FRIENDLY_NAME
#endif
#define FRIENDLY_NAME          PROJECT

#ifdef GUI_SHOW_HOSTNAME
#undef GUI_SHOW_HOSTNAME
#endif
#define GUI_SHOW_HOSTNAME      true

#ifdef APP_TIMEZONE
#undef APP_TIMEZONE
#endif
#define APP_TIMEZONE           99

#ifdef MY_LANGUAGE
#undef MY_LANGUAGE
#endif
#define MY_LANGUAGE            de_DE

#ifdef USE_DOMOTICZ
#undef USE_DOMOTICZ                              
#endif 

#ifdef USE_EMULATION_HUE
#undef USE_EMULATION_HUE
#endif

#ifdef USE_EMULATION_WEMO
#undef USE_EMULATION_WEMO
#endif

#ifdef USE_TELEGRAM
#undef USE_TELEGRAM
#endif

#ifdef USE_KNX
#undef USE_KNX
#endif

#ifdef USE_SONOFF_RF
#undef USE_SONOFF_RF
#endif

#ifdef ROTARY_V1
#undef ROTARY_V1
#endif

#ifdef USE_SONOFF_SC
#undef USE_SONOFF_SC
#endif

#ifdef USE_TUYA_MCU
#undef USE_TUYA_MCU
#endif

#ifdef USE_ARMTRONIX_DIMMERS
#undef USE_ARMTRONIX_DIMMERS
#endif

#ifdef USE_PS_16_DZ
#undef USE_PS_16_DZ
#endif

#ifdef USE_SONOFF_IFAN
#undef USE_SONOFF_IFAN
#endif

#ifdef USE_BUZZER
#undef USE_BUZZER
#endif

#ifdef USE_ARILUX_RF
#undef USE_ARILUX_RF
#endif

#ifdef USE_SHUTTER
#undef USE_SHUTTER
#endif

#ifdef USE_DEEPSLEEP
#undef USE_DEEPSLEEP
#endif

#ifdef USE_EXS_DIMMER
#undef USE_EXS_DIMMER
#endif

#ifdef USE_DEVICE_GROUPS
#undef USE_DEVICE_GROUPS
#endif

#ifdef USE_PWM_DIMMER
#undef USE_PWM_DIMMER
#endif

#ifdef USE_SONOFF_D1
#undef USE_SONOFF_D1
#endif

#ifdef USE_SHELLY_DIMMER
#undef USE_SHELLY_DIMMER
#endif

#ifdef USE_LIGHT
#undef USE_LIGHT
#endif

#ifdef USE_WS2812
#undef USE_WS2812
#endif

#ifdef USE_MY92X1
#undef USE_MY92X1
#endif

#ifdef USE_SM16716
#undef USE_SM16716
#endif

#ifdef USE_SM2135
#undef USE_SM2135
#endif

#ifdef USE_SM2335
#undef USE_SM2335
#endif

#ifdef USE_BP1658CJ
#undef USE_BP1658CJ
#endif

#ifdef USE_BP5758D
#undef USE_BP5758D
#endif

#ifdef USE_SONOFF_L1
#undef USE_SONOFF_L1
#endif

#ifdef USE_ELECTRIQ_MOODL
#undef USE_ELECTRIQ_MOODL
#endif

#ifdef USE_LIGHT_PALETTE
#undef USE_LIGHT_PALETTE
#endif

#ifdef USE_LIGHT_VIRTUAL_CT
#undef USE_LIGHT_VIRTUAL_CT
#endif

#ifdef USE_DGR_LIGHT_SEQUENCE
#undef USE_DGR_LIGHT_SEQUENCE
#endif

#ifdef USE_DS18x20
#undef USE_DS18x20
#endif

#ifdef USE_I2C
#undef USE_I2C
#endif

#ifdef USE_SPI
#undef USE_SPI
#endif

#ifdef USE_SERIAL_BRIDGE
#undef USE_SERIAL_BRIDGE
#endif

#ifdef USE_HLW8012
#undef USE_HLW8012
#endif

#ifdef USE_CSE7766
#undef USE_CSE7766
#endif

#ifdef USE_PZEM004T
#undef USE_PZEM004T
#endif

#ifdef USE_PZEM_AC
#undef USE_PZEM_AC
#endif

#ifdef USE_PZEM_DC
#undef USE_PZEM_DC
#endif

#ifdef USE_MCP39F501
#undef USE_MCP39F501
#endif

#ifdef USE_BL09XX
#undef USE_BL09XX
#endif

#ifdef USE_DHT
#undef USE_DHT
#endif

#ifdef USE_IR_REMOTE
#undef USE_IR_REMOTE
#endif

#endif  // _USER_CONFIG_OVERRIDE_H_

