// Include the libraries we need
#include <OneWire.h>
#include <DallasTemperature.h>
float smoothedValue = 0;     // Поточне згладжене значення


// Setup a oneWire instance to communicate with any OneWire devices (not just Maxim/Dallas temperature ICs)
OneWire oneWire(ONE_WIRE_BUS);

// Pass our oneWire reference to Dallas Temperature.
DallasTemperature sensors(&oneWire);

/*
 * The setup function. We only start the sensors here
 */
void setup_in(void)
{
  // Start up the library
  sensors.begin();
}

/*
 * Main function, get and show the temperature
 */
float get_temp()
{
  // call sensors.requestTemperatures() to issue a global temperature
  // request to all devices on the bus
  // Serial.print("Requesting temperatures...");
  sensors.requestTemperatures(); // Send the command to get temperatures
  // Serial.println("DONE");
  // After we got the temperatures, we can print them here.
  // We use the function ByIndex, and as an example get the temperature from the first sensor only.
    
  float tempC = sensors.getTempCByIndex(0);
  smoothedValue = tempC;
  smoothedValue = 0.9 * smoothedValue + 0.1 * tempC;
  // Check if reading was successful
  if (tempC != DEVICE_DISCONNECTED_C)
  {
    // Serial.print("Temperature for the device 1 (index 0) is: ");
    // Serial.println(tempC);
  }
  else
  {
    Serial.println("Error: Could not read temperature data");
  }
  return smoothedValue;
}
