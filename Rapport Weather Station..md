# Report Weather Station.
# Index:

  - Technological choice
      - Technological choice explanation
      - Schematic solution
      - Electronic schematic
- How to install and launch our application
- Potential uses

### Technological choice explanation

 For this project we have chosen Wi-Fi technolgy insted of Sigfox because we tought that it requires less parts so it would be cheaper and it would also be less likely to fail simply because there are less components. Sigfox is a wireless network for internet-connected objects it would also be a good solution but as few parts are used the better.


### Schematic solution
![N|Solid](https://raw.githubusercontent.com/Essim28/Internet-des-Objects/master/conexions.PNG)
 We have an html file that comunicates with the arduino to show the charts and share data, we load the arduino program to the board that gives us an IP (the board has to be congifured to a Wi-Fi network), later we input the IP that was given to us previously in a computer conected to the same network and that will show us the data

### Electronic Schematic
![N|Solid](https://raw.githubusercontent.com/Essim28/Internet-des-Objects/master/captura.PNG)
 Instead of only using the DHT11 sensor for both humidity and temperature we tought it would be better to use a NTC because is far more accurate than the DHT11 sensor.
 How we measure the temperature is by making a voltage divider with the NTC (temperature variable resistor), so in funcion of how the volage changes with the fixed resistor and the NTC we can use a function to estimate the temprature. The DHT11 sensor already gives us the value of the temperature and humidity because it uses its own library, so the conexions for the DHT11 are as simple as the first pin used to transfer data, the second one is the VCC, the third one has no use to we keep it disconnected and the fourth one is the GND



### How to install and launch our application
 First of all, we have to upload the skecth to the data folder (command in Arduino) in order to have our Arduino code and our HTML (web server) communicating between each other. Then, we load our Arduino code on the ESP8266 board. We have to have our NodeMCU connected to Wi-Fi at every moment to have our application on. Once we have our code loaded in the board, we just look at the monitor serie of Arduino, it will display the IP adress of our web server and we can copy it into our URL web browser. 
 If we have our application working in the same network always, the IP adress won't change, it will change only if we change the network.
 We should see in the monitor serie something similiar to this:
 
 ```sh
 Connecting to Wi-Fi
 Connecting to Wi-Fi
 Connecting to Wi-Fi
 192.168.0.102
 ```
 Then just copy that IP adress and we will have our weather station web displayed.
 
 ### Potential Uses
 WiFi is a well-known and standardised technology; building an IoT network over such is therefore less challenging than with some other wireless options as it ensures a consistent approach.
 
 Using WiFi in IoT has distinct advantages in our application, with its ability to connect directly with a recognised secure key exchange, and without the need for additional physical layer protocol bridges and gateway hardware – reducing cost and network architecture complexity.
 A potential use of our application is that as it is via Wi-Fi we can use it indoors in order to control the actual temperature of our house, for example to control the heating inside it.
  
    
  
  Just as the Internet of Things will continue to grow and evolve, WiFi is set to do the same and become a primary connectivity option and driver for IoT applications – dominating over other wireless standards as it becomes more expansive in its capabilities.





*Weather Station project for "Internet of Things". Done by:*

  *- Adrián Dominguez Molina*
  *- Luis García Gámez*
  *- Eros Ortega Cobos* 

>[![N|Isen](https://www.isen-lille.fr/wp-content/themes/isenwp/images/logo.png)](https://www.isen-lille.fr/)











 
