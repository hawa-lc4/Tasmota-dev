var dNo = 4
var pwr1 = false
var pwr1S = false
var maxpwr = 2400.0
var briA = 240
var blinky = false
var btn1 = 0
var manMode = true
var devStat = 0
var mqttC = false
var topM = "openWB/config/get/SmartHome/Devices/"
var topS = "openWB/SmartHome/Devices/"
var topic = "openWB/config/set/SmartHome/Devices/"
import mqtt
import webserver

myLeds2 = Leds(2,gpio.pin(gpio.WS2812, 0))
myLeds1 = Leds(2,gpio.pin(gpio.WS2812, 1))


def led_manM(value, trigger)
  if value == true
    myLeds1.set_pixel_color(1,0xCC0000,briA)
  else
    myLeds1.set_pixel_color(1,0,0)
  end
  myLeds1.show()
end


def led_power(value, trigger)
  pwr1 = bool(value)
  if pwr1 == true
    myLeds1.set_pixel_color(0,0xCC,255)
  else
    myLeds1.set_pixel_color(0,0,0)
    myLeds2.set_pixel_color(0,0,0)
    myLeds2.set_pixel_color(1,0,0)
    myLeds2.show()
  end
  myLeds1.show()
end


def led_energy(value, trigger)
  var ledcol = 0
  if pwr1 == true
    var currpwr = maxpwr
    if value < maxpwr
      currpwr = value
    end
    var red = int(currpwr * 255.0 / maxpwr)
    var green = int(255 - red)
    ledcol = (red << 16) + (green << 8)
    myLeds2.set_pixel_color(0,ledcol,briA)
    myLeds2.set_pixel_color(1,ledcol,briA)
  else
    myLeds2.set_pixel_color(0,0,0)
    myLeds2.set_pixel_color(1,0,0)
  end
  myLeds2.show()
end


def btn_action(value, trigger)
  btn1 = value
  if btn1 == 3   # HOLD
    manMode = !manMode
    mqtt.publish(topic +str(dNo) +str("/mode"), str(int(manMode)))
    led_manM(manMode)
  end
  if btn1 == 10 && manMode == true   # SINGLE
    mqtt.publish(topic +str(dNo) +str("/mode"), str(int(manMode)))
    pwr1S = !pwr1
    if mqtt.connected() == true
      mqtt.publish(topic +str(dNo) +str("/device_manual_control"), str(int(!pwr1)))
    else
      tasmota.set_power(0, !pwr1)
    end
  end
end


def devStat(topic, idx, payload_s, payload_b)
  print(topic, payload_s)
  if payload_s == "1"
    pwr1S = true
  else
    pwr1S = false
  end
  tasmota.set_power(0, pwr1S)
  return true
end


def devMode(topic, idx, payload_s, payload_b)
  print(topic, payload_s)
  if payload_s == "1"
    manMode = true
    myLeds1.set_pixel_color(1,0xCC0000,briA)
  else
    manMode = false
    myLeds1.set_pixel_color(1,0)
  end
  myLeds1.show()
  return true
end


def boot_action1(value, trigger)
  print("BOOT1", value, trigger)
  led_manM(manMode)
  pwr1 = tasmota.get_power()[0]
  pwr1S = pwr1
  led_power(pwr1)
  led_energy(0)
end

def boot_action2(value, trigger)
  print("BOOT2", value, trigger)
  mqtt.subscribe(topS +str(dNo) +str("/RelayStatus"), devStat)
  mqtt.subscribe(topM +str(dNo) +str("/mode"), devMode)
end


class BlinkLed
  def web_sensor()
    webserver.content_send(format("{s}<span>Manuelle Steuerung: {m}%d</span>{e}", int(manMode)))
    webserver.content_send(format("{s}<span>openWB Geräte-Nr.: {m}%d</span>{e}", int(dNo)))
  end
  def every_second()
    if manMode == true && pwr1S != pwr1
      if blinky == false
        myLeds1.set_pixel_color(1,0)
      else
        myLeds1.set_pixel_color(1,0xCC0000,briA)
      end
      myLeds1.show()
      blinky = !blinky
    end
    if manMode == true && pwr1S == bool(pwr1)
      myLeds1.set_pixel_color(1,0xCC0000,briA)
      myLeds1.show()
    end
  end
end
d1 = BlinkLed()
tasmota.add_driver(d1)

tasmota.when_network_up(boot_action1)
tasmota.add_rule("System#Boot", boot_action2)
tasmota.add_rule("Button1#State", btn_action)
tasmota.add_rule("Power1#State", led_power)
tasmota.add_rule("Energy#Power", led_energy)
