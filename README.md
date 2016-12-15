# thsensor
Temperature and humidity sensor based on Adafruit Huzzah (esp8266) sending data to ThingSpeak cloud.

(Do not look at this project just yet! It is nothing but a bunch of files -- at this stage of development, it is unlikely to be useful for anyone.

Overview:
The intent of this project is to create a battery-powered, cloud-connected temperature and humidity sensor that is easy to assemble
and is reasonably cheap.

What does the sensor do is very simple: it wakes up every 10 minutes, connects to WiFi, reads temperature,
humidity and input voltage and sends the data to your ThingSpeak channel. Rest of the time it spends in deep sleep.


The main board used is Adafruit Huzzah -- a esp8266 breakout board. Buy it on adafruit.com for $10.
Temperature/humidity sensor is DHT22, you can buy it on ebay or aliexpress for $2 or less.
There are two resistors, 1MOhm and 220KOhm that allow the chip to monitor input battery voltage -- you can 
change the coefficients in the sketch if you want to use different resistors.


Files and folders:
* sketch_schematic.fzz -- Fritzig diagram of the sensor shematic
* sketch_code -- Arduino IDE project containig the sketch source code

Planned:
* andoid_setup_app -- Android app that can be used to initialize a sensor