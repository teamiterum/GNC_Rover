#include <Wire.h>
#include <FreeSixIMU.h>
#include <FIMU_ADXL345.h>
#include <FIMU_ITG3200.h>
#include <Adafruit_BMP085.h>
#include <Adafruit_Sensor.h>
#include <Adafruit_HMC5883_U.h>
 
#define SLAVE_ADDRESS 0x04
float number[12];
float  *fp;    // pointer to a float
int state = 0;
float angles[3]; // yaw pitch roll
float gyro[3]; // 0,1,2 - gyro, 
float heading;
float temp;
float pres;
float alt; 
float sea_lvl;
float real_alt;
int number_rec, i;
int iArray[12];





Adafruit_BMP085 bmp;

// Set the FreeSixIMU object
FreeSixIMU sixDOF = FreeSixIMU();
/* Assign a unique ID to this sensor at the same time */
Adafruit_HMC5883_Unified mag = Adafruit_HMC5883_Unified(12345);
 


void displaySensorDetails(void)
{
  sensor_t sensor;
  mag.getSensor(&sensor);
  Serial.println("------------------------------------");
  Serial.print  ("Sensor:       "); Serial.println(sensor.name);
  Serial.print  ("Driver Ver:   "); Serial.println(sensor.version);
  Serial.print  ("Unique ID:    "); Serial.println(sensor.sensor_id);
  Serial.print  ("Max Value:    "); Serial.print(sensor.max_value); Serial.println(" uT");
  Serial.print  ("Min Value:    "); Serial.print(sensor.min_value); Serial.println(" uT");
  Serial.print  ("Resolution:   "); Serial.print(sensor.resolution); Serial.println(" uT");  
  Serial.println("------------------------------------");
  Serial.println("");
  delay(500);
}

void setup() {
 pinMode(13, OUTPUT);
 
 // initialize i2c as slave
 Wire.begin(SLAVE_ADDRESS);
 sixDOF.init(); //init the Acc and Gyro
 delay(5);
//  Serial.println("HMC5883 Magnetometer Test"); Serial.println("");
//  Initialise the sensor
  if(!mag.begin())
  {
//  There was a problem detecting the HMC5883 ... check your connections
    Serial.println("Ooops, no HMC5883 detected ... Check your wiring!");
    while(1);
  }
  if (!bmp.begin()) {
  Serial.println("Could not find a valid BMP085 sensor, check wiring!");
  }
 // define callbacks for i2c communication
// Wire.onReceive(receiveData);   //These cmds act as interrupts 
 Wire.onRequest(sendData);
}
 

void loop() {
  delay(1000);
  //temp = toggle();
 fp = &number[0];
  sixDOF.getEuler(fp); // angles[0,1,2] 3 angles getEuler(number(1,2,3))
  fp = &number[3];            //Byte*elements of array
  sixDOF.getQ(fp);     // gyro[0,1,2] 3 gyro angles
  fp = &number[6]; 
  getHeading();
  fp = &number[7]; 
  *fp = bmp.readTemperature();
  fp = &number[8];
  *fp = bmp.readPressure();
  fp = &number[9];
  *fp = bmp.readAltitude();
  fp = &number[10];
  *fp = bmp.readSealevelPressure(); 
  fp = &number[11];
  *fp = bmp.readAltitude(101500); 
  for(int i = 0; i < 12; ++i) {
    fp[i] = (int)iArray[i];
    Serial.print(iArray[i]);
} 
    
}
 
void getHeading(){
  //Adafruit compass code
  /* Get a new sensor event */ 
  sensors_event_t event; 
  mag.getEvent(&event);
 
  /* Display the results (magnetic vector values are in micro-Tesla (uT)) 
  Serial.print("X: "); Serial.print(event.magnetic.x); Serial.print("  ");
  Serial.print("Y: "); Serial.print(event.magnetic.y); Serial.print("  ");
  Serial.print("Z: "); Serial.print(event.magnetic.z); Serial.print("  ");Serial.println("uT");*/

  // Hold the module so that Z is pointing 'up' and you can measure the heading with x&y
  // Calculate heading when the magnetometer is level, then correct for signs of axis.
  heading = atan2(event.magnetic.y, event.magnetic.x);
  
  // Once you have your heading, you must then add your 'Declination Angle', which is the 'Error' of the magnetic field in your location.
  // Find yours here: http://www.magnetic-declination.com/
  // Mine is: -13* 2' W, which is ~13 Degrees, or (which we need) 0.22 radians
  // If you cannot find your Declination, comment out these two lines, your compass will be slightly off. Glasgow - -0.0485783 rad
  float declinationAngle = -0.0485783;
  heading += declinationAngle;
  
  // Correct for when signs are reversed.
  if(heading < 0)
    heading += 2*PI;
    
  // Check for wrap due to addition of declination.
  if(heading > 2*PI)
    heading -= 2*PI;
   
  // Convert radians to degrees for readability.
  heading = heading * 180/M_PI; 
}

// callback for received data
/*void receiveData(int byteCount){
 
 while(Wire.available()) {
  number_rec = Wire.read();
  if (number_rec == 1){
   if (state == 0){ 
//    number = 666; 
   }
  } if(number_rec==2) {
   //number = (int)temp;
  }
 }
}*/
 
// callback for sending data
void sendData(){
for (i= 0; i < 11; i++){ 
  Wire.write(iArray[i]);
  }
}

double toggle(void){
  double i;
   if (state == 0){
    digitalWrite(13, HIGH); // set the LED on
    i = 42;
    state = 1;
   } else{
    digitalWrite(13, LOW); // set the LED off
    i = 50;
    state = 0;
   }
  return i;
}
 

