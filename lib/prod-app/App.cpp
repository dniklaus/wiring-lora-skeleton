/*
 * App.cpp
 *
 *  Created on: 18.05.2023
 *      Author: didi
 */
#include <Arduino.h>
#include <SerialCommand.h>
#include <SpinTimer.h>
#include <Indicator.h>
#include <IndicatorFactory.h>
#include <MyBuiltinLedIndicatorAdapter.h>
#include <Button.h>
#include <ButtonEdgeDetector.h>
#include <MyButtonAdapter.h>
#include <ArduinoDigitalInPinSupervisor.h>
#include <ProductDebug.h>

#include <Assets.h>
#include <MyDeviceSerialNrAdapter.h>
#include <DetectorFakePersDataMemory.h>
#include <Battery.h>
#include <MyBatteryAdapter.h>
#include <LoraWanAbp.h>
#include <LoRaWanDriver.h>
#include <MyLoRaWanConfigAdapter.h>

#include "App.h"


LoRaWanDriver* m_LoraWanInterface = 0;
// Pin mapping
//#if defined(ARDUINO_SAMD_FEATHER_M0)
const lmic_pinmap lmic_pins = LmicPinMap_AdafruitFeatherM0();
//#elif defined (__arm__) && defined (__SAM3X8E__)              // Arduino Due => Dragino Shield
//const lmic_pinmap lmic_pins = LmicPinMap_DraginoShield();
//#elif defined (__avr__)                                       // Arduino Uno or Mega 2560 => Dragino Shield
//const lmic_pinmap lmic_pins = LmicPinMap_DraginoShield();
//#endif

Assets* assets = 0;
Battery* battery = 0;

const char App::s_termChar = '\n';

App::App()
: m_sCmd(new SerialCommand(s_termChar))
, m_led(0)
{ }

App::~App()
{ 
  // delete m_led->adapter();  // TODO: this needs the Indicator dtor to provice public CCSS
  // m_led->assignAdapter(0);

  // delete m_led;
  // m_led = 0;

  // delete m_sCmd;
  // m_sCmd = 0;
}

void App::setup()
{

  // setup basic debug environment (heap usage printer, trace ports & dbg cli)
  ProductDebug::setupProdDebugEnv(m_sCmd);

  // indicator LED
  m_led = IndicatorFactory::createIndicator("led", "Built in LED.");
  m_led->assignAdapter(new MyBuiltinLedIndicatorAdapter());

  #ifdef USER_BTN
    new Button(new ArduinoDigitalInPinSupervisor(USER_BTN), new ButtonEdgeDetector(), new MyButtonAdapter(m_led));
  #endif
  
  //-----------------------------------------------------------------------------
  // Assets (inventory and persistent data)
  //-----------------------------------------------------------------------------
  assets = new Assets(new MyDeviceSerialNrAdapter(), new DetectorFakePersDataMemory());

  //-----------------------------------------------------------------------------
  // Battery Voltage Surveillance
  //-----------------------------------------------------------------------------
  BatteryThresholdConfig battCfg = { 3.6, // BATT_WARN_THRSHD [V]
                                     3.4, // BATT_STOP_THRSHD [V]
                                     3.2, // BATT_SHUT_THRSHD [V]
                                     0.1  // BATT_HYST        [V]
                                   };
  battery = new Battery(new MyBatteryAdapter(), battCfg);

  //-----------------------------------------------------------------------------
  // LoRaWan
  //-----------------------------------------------------------------------------
  m_LoraWanInterface = new LoraWanAbp(new MyLoRaWanConfigAdapter(assets));


  const char txString[] = "0123456789";
  unsigned char txBuffer[strlen(txString)+1];
  memcpy(txBuffer, txString, strlen(txString));
  m_LoraWanInterface->setPeriodicMessageData(txBuffer, strlen(txString));

}

void App::loop()
{
  if (0 != m_sCmd)
  {
    m_sCmd->readSerial();     // process serial commands
  }
  scheduleTimers();
  m_LoraWanInterface->loopOnce();   // process LoRaWan driver

}
