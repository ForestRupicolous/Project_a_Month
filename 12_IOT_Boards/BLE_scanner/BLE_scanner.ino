/**
   A BLE client example that is rich in capabilities.
*/

#include "BLEDevice.h"
//#include "BLEScan.h"
#include "esp_log.h"
#include <gatt_api.h> // bluedroid include
#ifdef ARDUINO_ARCH_ESP32
#include "esp32-hal-log.h"
#endif

//The remote device (peripheral) we wish to connect
//#define peripheralAddr "24:71:89:bf:2a:04"
#define peripheralAddr "f3:da:9d:26:22:c2"
// The remote service we wish to connect to.
static BLEUUID serviceUUID("eb0fd000-2d0a-43cf-9521-747be0681d5a");  //muse data service
//static BLEUUID serviceUUID("0000180f-0000-1000-8000-00805f9b34fb");  //battery service
static BLEUUID serviceconifgUUID("eb0fd000-2d0a-43cf-9521-747be0681d5a");
//static BLEUUID serviceUUID("f000aa00-0451-4000-b000-000000000000");
// The characteristic of the remote service we are interested in.
static BLEUUID    charconfigUUID("eb0fd002-2d0a-43cf-9521-747be0681d5a");
//static BLEUUID    charUUID("f000aa01-0451-4000-b000-000000000000");
//static BLEUUID    charUUID("00002a19-0000-1000-8000-00805f9b34fb");  //Battery characteristic
static BLEUUID    charUUID("eb0fd001-2d0a-43cf-9521-747be0681d5a"); //Muse data

static BLEAddress *pServerAddress;
static BLEAddress *pPeripheralAddr;
static boolean doConnect = false;
static boolean characteristicFound = false;
static boolean configFound = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;
static BLERemoteCharacteristic* pRemoteConfig;
static BLEClient* pClient;

typedef struct {
    uint16_t    pressure;
    int16_t     temperature;
    uint8_t     humidity;
    uint16_t    gas;
    uint16_t    brightness;
    uint8_t     loudness;
    uint8_t     status[6];
    uint32_t    timestamp;
} Measurement_Results_t;




static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
  Serial.print("Data: ");
  Serial.print(pData[0]);
  Serial.print(pData[1]);
  Serial.print(pData[2]);
  Serial.print(pData[3]);
  Serial.print(pData[4]);
  Serial.print(pData[5]);
  Serial.print(pData[6]);
  Serial.print(pData[7]);
  Serial.print(pData[8]);
  Serial.print(pData[9]);
  Serial.println(pData[10]);
 // BLEtimeout = 0;
}

void triggerMeasurement()
{
  if(connected)
    {
   // Obtain a reference to the service we are after in the remote BLE server.
    BLERemoteService* pRemoteConfigService = pClient->getService(serviceconifgUUID);
    if (pRemoteConfigService == nullptr)
    {
      Serial.print("Failed to find our service UUID: ");
      Serial.println(serviceconifgUUID.toString().c_str());
      return;
    }
    else
    {
      Serial.println("----------------- Found your service ------------------------");
    }
  
      delay(1000); // Delay a second between loops.
    // Obtain a reference to the characteristic in the service of the remote BLE server.
    pRemoteConfig = pRemoteConfigService->getCharacteristic(charconfigUUID);
    if (pRemoteConfig == nullptr) {
      Serial.print("Failed to find our characteristic UUID: ");
      Serial.println(charconfigUUID.toString().c_str());
      return;
    }
    else
    {
      Serial.println("----------------- Found config characteristic ------------------------");
      configFound = true;
      delay(1000); // Delay a second between loops.
      pRemoteConfig->writeValue(1, 1);
    }
  }
  
}


bool connectToServer(BLEAddress pAddress)
{
  delay(50); 
  //Serial.println("----------------- connectToServer ------------------------------");
  Serial.print("Forming a connection to:");
  Serial.println(pAddress.toString().c_str());

  pClient  = BLEDevice::createClient();
  Serial.println(" - Created client");

  // Connect to the remove BLE Server.
  pClient->connect(pAddress);
  Serial.println(" - Connected to server");

  // Obtain a reference to the service we are after in the remote BLE server.
  BLERemoteService* pRemoteService = pClient->getService(serviceUUID);
  if (pRemoteService == nullptr)
  {
    Serial.print("Failed to find our service UUID: ");
    Serial.println(serviceUUID.toString().c_str());
    return false;
  }
  else
  {
    Serial.println("----------------- Found your service ------------------------");
  }

  
  // Obtain a reference to the characteristic in the service of the remote BLE server.
  pRemoteCharacteristic = pRemoteService->getCharacteristic(charUUID);
  if (pRemoteCharacteristic == nullptr) {
    Serial.print("Failed to find our characteristic UUID: ");
    Serial.println(charUUID.toString().c_str());
    return false;
  }
  else
  {
    Serial.println("----------------- Found your characteristic ------------------------");
    characteristicFound = true;
  }
  // Read the value of the characteristic.
 // std::string value = pRemoteCharacteristic->readValue();
 // Serial.print("The characteristic value was: ");
 // Serial.println(value.c_str());
  
 // delay(1000); // Delay a second between loops.

  pRemoteCharacteristic->registerForNotify(notifyCallback);
  Serial.print("Register for notify of: ");
  Serial.println(charUUID.toString().c_str());
  return true;
}

/**
   Scan for BLE servers and find the first one that advertises the service we are looking for.
*/
class MyAdvertisedDeviceCallbacks: public BLEAdvertisedDeviceCallbacks {
    /**
        Called for each advertising BLE server.
    */
    void onResult(BLEAdvertisedDevice advertisedDevice)
    {
      //some infos and use of methods
      Serial.println("----------------------------------------------------------------------");
      Serial.print("BLE Advertised Device found: [");
      Serial.println(advertisedDevice.toString().c_str());
      Serial.print("]\nAddress: [");
      Serial.print(advertisedDevice.getAddress().toString().c_str());
      Serial.print("]\nName: [");
      Serial.print(advertisedDevice.getName().c_str());
      Serial.print("]\nManufacturerData: [");
      Serial.print(advertisedDevice.getManufacturerData().c_str());
      if (advertisedDevice.haveServiceUUID())
      {
        Serial.print("]\nPrimary ServiceUUID: [");
        Serial.print(advertisedDevice.getServiceUUID().toString().c_str());
      }
      Serial.print("]\nRSSI: [");
      Serial.print(advertisedDevice.getRSSI());
      Serial.print("]\nTXPower: [");
      Serial.print(advertisedDevice.getTXPower());
      Serial.print("]\nAppearance: [");
      Serial.print(advertisedDevice.getAppearance()); //misspelled ? Appearance
      Serial.println("]");

      // We have found a device, let us now see if it contains the devieceAddress we are looking for.
      if (advertisedDevice.getAddress().equals(*pPeripheralAddr))
      {
        pServerAddress = new BLEAddress(advertisedDevice.getAddress());
        Serial.println("*******************************************************************");
        Serial.print("Found matching device!");
        advertisedDevice.getScan()->stop();
        doConnect = true;

      } // Found our server
    } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {
  esp_log_level_set("*", ESP_LOG_ERROR);  //ESP_LOG_VERBOSE
  //GATT_SetTraceLevel(6);
  
  Serial.begin(115200);
  Serial.println("Starting Arduino BLE Client application...");

  pPeripheralAddr = new BLEAddress(peripheralAddr);

  BLEDevice::init("");

  // Retrieve a Scanner and set the callback we want to use to be informed when we
  // have detected a new device.  Specify that we want active scanning and start the
  // scan to run for 30 seconds.
  BLEScan* pBLEScan = BLEDevice::getScan();
  pBLEScan->setAdvertisedDeviceCallbacks(new MyAdvertisedDeviceCallbacks());
  pBLEScan->setActiveScan(true);
  pBLEScan->start(30);

  //BLERemoteService::retrieveCharacteristics()
  //
  
} // End of setup.


// This is the Arduino main loop function.
void loop() {
  uint16_t AmbientTemp;
  uint16_t ObjectTemp;
  std::string tmp;
  Measurement_Results_t muse_data;
  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    if (connectToServer(*pServerAddress)){ //this internal reads the GATT
      Serial.println("We are now connected to the BLE Server.");
      connected = true;
    } 
    else {
      Serial.println("We have failed to connect to the server; there is nothin more we will do.");
      Serial.println("#########################################################################");
    }
    doConnect = false;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected)
  {
    Serial.println("----------------- still connected ------------------------");
    //String newValue = "1";//"Time since boot: " + String(millis() / 1000);

    if (characteristicFound == true)
    {
      
     // Serial.println("Setting new characteristic value to \"" + newValue + "\"");
      // Set the characteristic's value to be the array of bytes that is actually a string.
     //pRemoteConfig->writeValue(newValue.c_str(), newValue.length());
    // triggerMeasurement();
    // pRemoteConfig->writeValue(1, 1);
     delay(1000);
        // Read the value of the characteristic.
      std::string value= pRemoteCharacteristic->readValue();
      
      //uint32_t data = pRemoteCharacteristic->readUInt32();
      Serial.print("The characteristic value was: ");
      if(value.size() == 20)
      {
        muse_data.pressure = *(uint16_t*) value.substr(0,2).data();      
        Serial.print("Pressure: ");
        Serial.print(muse_data.pressure);
        Serial.print(" hPa");
        muse_data.temperature = *(uint16_t*) value.substr(3,6).data();      
        Serial.print(" Temperature: ");
        Serial.print(muse_data.temperature);
        Serial.print(" °C");
      }
      else
      {
        for(uint8_t i = 0; i < value.size(); i++)
        {
           Serial.print((uint8_t) value[i],HEX);
        }
      }
      Serial.print(" lenght:");
      Serial.println(value.size());

     // Serial.print(" ");
     // Serial.println(value.length());
//      AmbientTemp = data & 0x0000FFFF;
//      Serial.print(" IR:");
//      Serial.print((float) AmbientTemp/100,1);
//      ObjectTemp = (data & 0xFFFF0000)>>16;
//      Serial.print(" Sensor:");
//      Serial.println((float) ObjectTemp/100,1);      

    }
  }

  delay(5000); // Delay a second between loops.
} // End of loop
