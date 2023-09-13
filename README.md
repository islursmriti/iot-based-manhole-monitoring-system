# iot-based-manhole-monitoring-system
The project design consists of three sensors which are used to detect water level, gas  level and tilt in the manhole cover. If the sensor values reach the threshold level, then  that data is sent to the administrator via IFTTT platform. We also collected our IoT data and Analyzed it on  ThingSpeak.
Steps:
1.  Video link of the complete code explanation and demo

https://drive.google.com/file/d/14oTjIhXtLYBbh2UbChmtEb98Nl2fIbe4/view?usp=sharing

2.	Connect the sensors to the nodemcu 
3.	Connect hardware to the pc through usb cord 

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/b533cd66-8b7b-4da9-8917-24ae8e048ac3)

4.	Write the code("newcode_withifttt.ino" -> there in this repo) in arduino ide and burn the code in nodemcu

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/7623b812-80a6-4e15-992c-e9bd5d680302)
![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/d4e82dfd-9925-4982-ac56-3a48049f3660)

5.	Create channel on thingspeak 

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/30788d7e-bb34-42b4-a196-98919871bb29)

6.	Put the thingspeak channel id and api key in the code

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/198c5ed7-f015-45c3-b5ba-2ad1b6acd029)
![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/dc270c74-a78d-497e-9c9e-1a0dfd04e5d1)

7.	Create applet on ifttt platform 

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/c4c4f3ac-dd73-4426-bdfb-825d3deb176b)

8.	Put the website link obtained from ifttt platform in the code(u can find the link by clicking the webhook icon ->and click documentation-> u will find the site)

![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/bfac677c-0623-4584-b1e3-f5264b3088bd)
![image](https://github.com/islursmriti/iot-based-manhole-monitoring-system/assets/104566739/7f30bef4-36b2-4302-905e-96a6f62306e6)

9.	Insert the wifi name and password in the code
10.	Run the final code in Arduino ide 





