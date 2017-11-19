/**
   A BLE client example that is rich in capabilities.
*/

#include "BLEDevice.h"
//#include "BLEScan.h"

//The remote device (peripheral) we wish to connect
#define peripheralAddr "24:71:89:bf:2a:04"
// The remote service we wish to connect to.
//static BLEUUID serviceUUID("91bad492-b950-4226-aa2b-4ede9fa42f59");
static BLEUUID serviceUUID("f000aa00-0451-4000-b000-000000000000");
// The characteristic of the remote service we are interested in.
static BLEUUID    charUUID("f000aa01-0451-4000-b000-000000000000");

static BLEAddress *pServerAddress;
static BLEAddress *pPeripheralAddr;
static boolean doConnect = false;
static boolean characteristicFound = false;
static boolean connected = false;
static BLERemoteCharacteristic* pRemoteCharacteristic;

static void notifyCallback(
  BLERemoteCharacteristic* pBLERemoteCharacteristic,
  uint8_t* pData,
  size_t length,
  bool isNotify) {
  Serial.print("Notify callback for characteristic ");
  Serial.print(pBLERemoteCharacteristic->getUUID().toString().c_str());
  Serial.print(" of data length ");
  Serial.println(length);
}

void connectToServer(BLEAddress pAddress)
{
  delay(50); /*--D- -(-6-293--)- -B-LE-U--t-i-l-s : coRennceecivtTeodS ae rvGeAPr  -e-ve--n-t-: --E-S-P-_-GA--P-_-B-LE--_-S-C-A-N-_S--TO--P-_C-O--M-P-L-E-T-E-_E--VT-<\r>-<\n>
  -D-- -(6--3-0-7<\r>)<\n>
*/
  //Serial.println("----------------- connectToServer ------------------------------");
  Serial.print("Forming a connection to:");
  Serial.println(pAddress.toString().c_str());

  BLEClient*  pClient  = BLEDevice::createClient();
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
    return;
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
    return;
  }
  else
  {
    Serial.println("----------------- Found your characteristic ------------------------");
    characteristicFound = true;
  }

  // Read the value of the characteristic.
  std::string value = pRemoteCharacteristic->readValue();
  Serial.print("The characteristic value was: ");
  Serial.println(value.c_str());

  pRemoteCharacteristic->registerForNotify(notifyCallback);
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
      Serial.print("]\nServiceUUID: [");
      Serial.print(advertisedDevice.getServiceUUID().toString().c_str());
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
        Serial.println("Found matching device!");
        advertisedDevice.getScan()->stop();
        doConnect = true;

      } // Found our server
    } // onResult
}; // MyAdvertisedDeviceCallbacks


void setup() {
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
} // End of setup.


// This is the Arduino main loop function.
void loop() {

  // If the flag "doConnect" is true then we have scanned for and found the desired
  // BLE Server with which we wish to connect.  Now we connect to it.  Once we are
  // connected we set the connected flag to be true.
  if (doConnect == true) {
    connectToServer(*pServerAddress); //this internal reads the GATT
    doConnect = false;
    connected = true;
  }

  // If we are connected to a peer BLE Server, update the characteristic each time we are reached
  // with the current time since boot.
  if (connected)
  {
    Serial.println("----------------- still connected ------------------------");
    String newValue = "Time since boot: " + String(millis() / 1000);

    if (characteristicFound == true)
    {
      Serial.println("Setting new characteristic value to \"" + newValue + "\"");
      // Set the characteristic's value to be the array of bytes that is actually a string.
      pRemoteCharacteristic->writeValue(newValue.c_str(), newValue.length());
    }
  }

  delay(1000); // Delay a second between loops.
} // End of loop
