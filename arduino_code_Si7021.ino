#include <Wire.h>

const int SI7021_ADDR = 0x40; // I2C address of the SI7021
int ledred = 3; //Error LED
int ledgreen = 4; //Aproved Temperature LED

void setup() {
  pinMode(ledgreen, OUTPUT);
  pinMode(ledred, OUTPUT);
  Wire.begin(); // Initialize I2C communication
  Serial.begin(115200); // Initialize serial communication
  Serial.println("I2C communication started");
}

void loop() {
  float temperature = readTemperature();
  Serial.print("Temperature: ");
  Serial.print(temperature);
  Serial.println(" C");  
  delay(500); // Wait for 1 second
	
	//led for teste without a PC
	
  if (temperature > 10){   
    digitalWrite(ledgreen,HIGH);
    delay(300);
   }
 	
   else if (temperature == -999.0){
    digitalWrite(ledred,HIGH);
    delay(100);
    digitalWrite(ledred,LOW);
    delay(50);    
   }  
}

float readTemperature(  ) {
  Wire.beginTransmission(SI7021_ADDR);
  Wire.write(0xF3); // Send temperature measurement command
  Wire.endTransmission();
  
  delay(50); // Wait for the measurement to complete
  
  Wire.requestFrom(SI7021_ADDR, 2); // Request 2 bytes from the SI7021
  
  if (Wire.available() == 2) {
    // Read the two bytes and combine them
    uint16_t rawData = (Wire.read() << 8) | Wire.read();
    // Convert to temperature (SI7021 datasheet formula)
    float temperature = ((175.72 * rawData) / 65536.0) - 46.85;
    return temperature;
  } else {
    Serial.println("Error: Unable to read temperature data");
    return -999.0; // Return an error value
  }
}
