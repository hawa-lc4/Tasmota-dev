var dNo = 6
var pwr1 = int(tasmota.get_power()[0])
var pwr2 = int(tasmota.get_power()[1])
var cnt1 = gpio.counter_read(0)
var briA = 128
var topM = "openWB/config/get/SmartHome/Devices/"
var manMode = false
var pwr2enable = 0
var maxpwr = 1200.0
import mqtt
import webserver

myLeds1 = Leds(2,gpio.pin(gpio.WS2812, 0))
myLeds2 = Leds(2,gpio.pin(gpio.WS2812, 1))


def led_power2(value, trigger)
  pwr2 = value
  if pwr2 == 1 
    myLeds1.set_pixel_color(0,0xCC0000,briA)
  else
    myLeds1.set_pixel_color(0,0x00CC00,briA)
    myLeds1.set_pixel_color(1,0x000000,briA)
  end
  myLeds1.show()
end


def led_energy(value, trigger)
  var ledcol = 0
  if pwr2 == 1
    var currpwr = maxpwr
    if value < maxpwr
      currpwr = value
    end
    var red = int(currpwr * 255.0 / maxpwr)
    var green = int(255 - red)
    ledcol = (red << 16) + (green << 8)
  end
  myLeds1.set_pixel_color(1,ledcol,briA)
  myLeds1.show()
end


def led_remote(value, trigger)
  pwr1 = value
  if pwr1 == 1 
    myLeds2.set_pixel_color(0,0x0000FF,briA)
  else
    myLeds2.set_pixel_color(0,0,0)
  end
  myLeds2.show()
end


def chk_cntr(value, trigger)
  if value >= 50
    myLeds2.set_pixel_color(1,0x00CC66,briA)
    pwr2enable = 1
  else
    myLeds2.set_pixel_color(1,0xCC0066,briA)
    pwr2enable = 0
  end
  myLeds2.show()
  gpio.counter_set(0,0)
  if pwr1 == 1 && pwr2enable == 1
    tasmota.set_power(1, true)
  else
    tasmota.set_power(1, false)
  end
end


def devMode(topic, idx, payload_s, payload_b)
  print(topic, payload_s)
  if payload_s == "1"
    manMode = true
  else
    manMode = false
  end
  return true
end


def leds_boot(value, trigger)
  pwr1 = int(tasmota.get_power()[0])
  pwr2 = int(tasmota.get_power()[1])
  led_remote(pwr1, trigger)
  led_power2(pwr2, trigger)
  mqtt.subscribe(topM +str(dNo) +str("/mode"), devMode)
end


class WebUI
  def web_sensor()
    webserver.content_send(format("{s}<span>Manuelle Steuerung: {m}%d</span>{e}", int(manMode)))
    webserver.content_send(format("{s}<span>openWB Geräte-Nr.: {m}%d</span>{e}", int(dNo)))
    webserver.content_send("<table style='width:100%; border-top:2px solid grey; font-size:24px; font-weight:bold;'>")
    webserver.content_send("<tbody><tr>")
    webserver.content_send("<td style='width:50%; text-align:center;'>openWB</td>")
    webserver.content_send("<td style='width:50%; text-align:center;'>Relais</td>")
    webserver.content_send("</tr></tbody></table>")
  end
end
web_text = WebUI()
tasmota.remove_driver(web_text)
tasmota.add_driver(web_text)


tasmota.add_rule("System#Boot", leds_boot)
tasmota.add_rule("Power1#State", led_remote)
tasmota.add_rule("Power2#State", led_power2)
tasmota.add_rule("Energy#Power", led_energy)
tasmota.add_rule("COUNTER#C1", chk_cntr)
