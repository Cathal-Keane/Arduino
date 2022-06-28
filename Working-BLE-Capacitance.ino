#include <ArduinoBLE.h>

//----------------------------------------------------------------------------------------------------------------------
// BLE UUIDs
//----------------------------------------------------------------------------------------------------------------------

#define BLE_UUID_TEST_SERVICE               "9A48ECBA-2E92-082F-C079-9E75AAE428B1"
#define BLE_UUID_FLOAT_VALUE                "C8F88594-2217-0CA6-8F06-A4270B675D69"


//----------------------------------------------------------------------------------------------------------------------
// BLE
//----------------------------------------------------------------------------------------------------------------------

BLEService testService( BLE_UUID_TEST_SERVICE );
BLEFloatCharacteristic floatValueCharacteristic( BLE_UUID_FLOAT_VALUE, BLENotify );


const int OUT_PIN = A2;
const int IN_PIN = A0;

const float IN_STRAY_CAP_TO_GND = 1.80; //initially this was 30.00
const float IN_EXTRA_CAP_TO_GND = 0.0;
const float IN_CAP_TO_GND  = IN_STRAY_CAP_TO_GND + IN_EXTRA_CAP_TO_GND;
const int MAX_ADC_VALUE = 1023;


void setup()
{
  pinMode(OUT_PIN, OUTPUT);
  /*digitalWrite(OUT_PIN, LOW);  - This is the default state for outputs */
  pinMode(IN_PIN, OUTPUT);
  /*digitalWrite(IN_PIN, LOW); */

  BLE.begin();
  Serial.begin(115200);
  
  // set advertised local name and service
  BLE.setDeviceName( "Arduino Nano 33 BLE" );
  BLE.setLocalName( "Arduino Nano 33 BLE" );
  BLE.setAdvertisedService( testService );

  // BLE add characteristics
  testService.addCharacteristic( floatValueCharacteristic );
 

  // add service
  BLE.addService( testService );

  BLE.advertise();
}

void loop()
{
  /*Capacitor under test between OUT_PIN and IN_PIN */
  /*Rising high edge on OUT_PIN */
  
  
  pinMode(IN_PIN, INPUT);
  digitalWrite(OUT_PIN, HIGH);
  int val = analogRead(IN_PIN);

  float capacitance = (float)val * IN_CAP_TO_GND / (float)(MAX_ADC_VALUE - val);

  floatValueCharacteristic.writeValue( capacitance );
  

  Serial.print(F("Capacitance Value = "));  /*These two line can be commented out in favour of block below (lines 71-75) */
  Serial.println(capacitance, 3);           /*The two lines print only the capacitance hence are useful for copying data from the serial */
  
  /*Serial.print(F("Capacitance Value = "));
  Serial.print(capacitance, 3);
  Serial.print(F(" pF ("));
  Serial.print(val);
  Serial.println(F(") ")); */

  while (millis() % 50 != 0)

  BLEDevice central = BLE.central();

  delay(100);
} 
