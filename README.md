# ESP32-based-AQI-monitor
#Overview
  This project is an IoT-based prototype that monitors environmental parameters using an ESP32 and sensors. It reads gas levels, temperature, and humidity, then sends the data to a Bluetooth serial monitor and the ThingSpeak cloud for real-time observation.  
  This is Version 1 of the system and focuses on building a stable sensing + transmission pipeline.  

#Features  
  Reads gas concentration using MQ135 sensor  
	Measures temperature and humidity using DHT11  
  Sends live data to Bluetooth Serial Monitor  
  Uploads data to ThingSpeak using Wi-Fi API  
  Designed for continuous monitoring (tested up to ~12 hours)  

#Components Used  
ESP32 Development Board  
MQ135 Gas Sensor  
DHT11 Temperature & Humidity Sensor  
OLED Display (optional/expandable)  
Breadboard & Jumper Wires  

#How It Works  
MQ135 and DHT11 sensors collect environmental data.  
ESP32 processes the sensor readings.  
Data can be accesed by:  
Bluetooth Serial Monitor  
ThinkSpeak stores and visualizes data in form of graph and various illustration  

#Project Structure  
code/ – ESP32 source code (.ino)  
circuit/ – circuit diagram / setup image  
images/ – hardware setup photos   

#Setup Instructions  
Connect MQ135 and DHT11 to ESP32 as per the circuit diagram.  
Install required libraries:  
Adafruit_GFX.h  
Adafruit_SSD1306.h  
DHT.h  
#include "ThingSpeak.h"  
Add your Wi-Fi credentials and ThingSpeak API key in the code.  
Upload the code to ESP32 using Arduino IDE.  
Open Serial/Bluetooth monitor to view live readings.  

#Output  
Real-time gas level, temperature, and humidity readings  
Data transmitted to ThingSpeak for cloud visualization  
Stable continuous operation tested for up to 12 hours  

#Output  
Real-time gas level, temperature, and humidity readings  
Data transmitted to ThingSpeak for cloud visualization  
Stable continuous operation tested for up to 12 hours  

#Future Improvements  
Integrate PMS7003 sensor for accurate PM2.5/PM10 measurement  
Improve AQI calculation accuracy  
Add mobile dashboard / web interface  
Add enclosure for portability  

Developed As Part of  
Multidisciplinary Project( 1st semester project)  



