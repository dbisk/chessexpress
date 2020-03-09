"""Functions here are a part of the Internet Connectivity Unit (ICU)

The Internet Connectivity Unit handles all the WiFi and internet talking for
Chess Express.
"""
import time
import board
import busio
from digitalio import DigitalInOut
import neopixel
from adafruit_esp32spi import adafruit_esp32spi
from adafruit_esp32spi import adafruit_esp32spi_wifimanager

class ICU:
  def __init__(self):
    self.esp_connect()

  def esp_connect(self):
    try:
      from secrets import secrets
    except ImportError:
      print("WiFi secrets are kept in secrets.py. Check secrets_template.py for an example.")
      raise

    # might need to change these pins depending on the connection
    self.esp32_cs = DigitalInOut(board.ESP_CS)
    self.esp32_ready = DigitalInOut(board.ESP_BUSY)
    self.esp32_reset = DigitalInOut(board.ESP_RESET)

    self.spi = busio.SPI(board.SCK, board.MOSI, board.MISO)
    self.esp = adafruit_esp32spi.ESP_SPIcontrol(self.spi, self.esp32_cs, self.esp32_ready, self.esp32_reset)

    # might not be necessary, depending on if we want status LED
    self.status_light = neopixel.NeoPixel(board.NEOPIXEL, 1, brightness=0.2)

    self.wifi = adafruit_esp32spi_wifimanager.ESPSPI_WiFiManager(self.esp, secrets, self.status_light)
