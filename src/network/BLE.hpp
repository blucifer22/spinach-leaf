#include "NimBLEDevice.h"

#define SERVICE_UUID      "eaa636ce-ffc0-4444-923e-cb0622a6772f"
#define CONFIG_UUID       "7815d597-62b4-4d3a-a58f-c4b2d9ae13e3"
#define LEFT_LIDAR_UUID   "bcbc0b7d-c813-48c4-ac04-5289cff3ebf6"
#define CENTER_LIDAR_UUID "51283344-4a85-472f-aef5-8023253bc0a5"
#define RIGHT_LIDAR_UUID  "8799087d-e65a-4ea3-9331-7222cc242da2"


class BLEProvider {
private:
    NimBLEServer* pServer;
    NimBLEService* pService;
    NimBLECharacteristic* pConfig;
    NimBLECharacteristic* pLeft;
    uint8_t* pLeftVal;
    NimBLECharacteristic* pCenter;
    uint8_t* pCenterVal;
    NimBLECharacteristic* pRight;
    uint8_t* pRightVal;
    NimBLEAdvertising* pAdvertising;

public:
    BLEProvider();

    bool sensorsEnabled();

    void updateLeftLidar(unsigned int newVal);

    void updateCenterLidar(unsigned int newVal);

    void updateRightLidar(unsigned int newVal);
};
