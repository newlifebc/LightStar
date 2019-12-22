/*
 * LightStar Firmware
 * Written by Matthew Swarts, 2019
 * 
 * Designed for use with Light of the World https://www.youtube.com/watch?v=eI302Av7vSI
 * 
 * Functionality:
 * Flashes briefly when turned on
 * Enters QuietMode for 30s unless there is an Infrared Signal
 * If there is an Infrared Signal, it Flashes again, and resets QuietMode
 * After 30s, it enters TwinkleMode, where it twinkles as an ornament
 * Because it is very low power, during QuietMode, it can run off the 10uF capacitor,
 *  so turning the off switch during QuietMode may not reset the device
 * 
 * Hardware: 
 * ATtiny85V: 0-4MHz@1.8V, 1-10MHz@2.7V
 * 
 * Bootloader:
 * 8MHz clock - //allows operation at down to 1.8V and saves some uA
 * BOD Disabled - allows operation down to 1.8V and saves some uA
 * 
 * External (to AVR) Libraries:
 * IRLib2
 * 
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/power.h>
#include <avr/sleep.h>
#include <avr/wdt.h>

#ifndef cbi
#define cbi(sfr, bit) (_SFR_BYTE(sfr) &= ~_BV(bit))
#endif
#ifndef sbi
#define sbi(sfr, bit) (_SFR_BYTE(sfr) |= _BV(bit))
#endif

// add this to the top of your sketch
#define NOP __asm__ __volatile__ ("nop\n\t")

//#include "IRLibAll.h"

#include <IRLibDecodeBase.h> // First include the decode base
#include <IRLib_P01_NEC.h>   // Now include only the protocols you wish
#include <IRLib_P02_Sony.h>  // to actually use. The lowest numbered
//#include <IRLib_P07_NECx.h>  // must be first but others can be any order.
//#include <IRLib_P09_GICable.h>
//#include <IRLib_P11_RCMM.h>
#include <IRLibCombo.h>     // After all protocols, include this

//#include <IRLibRecvPCI.h> 

/*
PB0 MOSI 0
PB1 MISO 1
PB2 SCK  2 INT0 - IR INPUT
PB3      3 
PB4      4 -none

        PB0   PB1   PB3
LED101  HIGH  LOW   FLOAT
LED102  FLOAT HIGH  LOW
LED103  LOW   HIGH  FLOAT
LED104  FLOAT LOW   HIGH
LED105  HIGH  FLOAT LOW
LED106  LOW   FLOAT HIGH

IF NO IR after 40 seconds, it will sparkle
LED Pattern is


mode: sparkling mode
wake on ir
 -reset last ir received timer to zero
 -change mode to listening mode
wake every 1 second
 -increment ir received timer
 -get random number 1-6 to flash 1 millisecond
 -go to sleep

mode: lighting mode
wake on ir
 -reset last ir received timer to zero
wake every 1 second
 -increment ir received timer
schedule leds
go to sleep if done with animation

mode: listening mode
wake on ir
 -reset last ir received timer to zero
wake every 1 second
 -increment ir received timer
schedule leds
go to sleep if done with animation

*/

#define PIN_LED_A 0
#define PIN_LED_B 1
#define PIN_LED_C 3
#define PIN_IR_RECV 2
#define INT_IR_RECV 0

//IRrecvPCI _ir_receiver(INT_IR_RECV); //pin 2 is INT0
//IRdecode _ir_decoder; // Create a decoder object


class IRdecodeNEO: public virtual IRdecodeBase
{
  public:
    virtual bool decode(void);
};



uint32_t _animTimer = 0;
uint32_t _animDelay = 1000;
uint32_t _currMillis = 0;

typedef void (*loopModeType)();
loopModeType _currMode;

void flash(uint8_t val, uint32_t dur_ms){
  uint32_t dur_us = dur_ms*1000;
  //for(uint32_t t=0;t<dur_us;t+=60){
  for(uint32_t t=0;t<dur_us;t+=400){
    light((1)*bitRead(val,0));
    light((2)*bitRead(val,1));
    light((3)*bitRead(val,2));
    light((4)*bitRead(val,3));
    light((5)*bitRead(val,4));
    light((6)*bitRead(val,5));
//    for(uint8_t i=0;i<=5;i++){
//      //get bit value from val byte
//      light((i+1)*bitRead(val,i));
//      //delay(1);
////      uint8_t multiplier = (val >> i) & 1;
////      light(multiplier*(i+1));
//     // delayMicroseconds(1); //may not really matter
////      delayMicroseconds(7);//derated from 10;
//      
//    }
  }
  light(0);
}

void flashOne(uint8_t val, uint16_t dur){
  light(val);
  //LowPower.deepSleep(dur);
  light(0);
}

void flashAll(uint16_t dur){
  _currMillis = millis();
  _animTimer = _currMillis;
  _animDelay = dur;
  while(_currMillis-_animTimer>_animDelay){
    light(1);
    light(2);
    light(3);
    light(4);
    light(5);
    light(6);
    light(0);
    //LowPower.deepSleep(1);
    _currMillis = millis();  
  }
}

void light(uint8_t val){
  switch(val){
    case 0:
      //OFF
      pinMode(PIN_LED_A,INPUT); //FLOAT
      pinMode(PIN_LED_B,INPUT); //FLOAT
      pinMode(PIN_LED_C,INPUT); //FLOAT
    break;
    case 1:
      pinMode(PIN_LED_C,INPUT); //FLOAT
      pinMode(PIN_LED_A,OUTPUT); //HIGH
      digitalWrite(PIN_LED_A,HIGH); //HIGH
      pinMode(PIN_LED_B,OUTPUT); //LOW
      digitalWrite(PIN_LED_B,LOW); //LOW
    break;
    case 2:
      pinMode(PIN_LED_A,INPUT); //FLOAT
      pinMode(PIN_LED_B,OUTPUT); //HIGH
      digitalWrite(PIN_LED_B,HIGH); //HIGH
      pinMode(PIN_LED_C,OUTPUT); //LOW
      digitalWrite(PIN_LED_C,LOW); //LOW
    break;
    case 3:
      pinMode(PIN_LED_C,INPUT); //FLOAT
      pinMode(PIN_LED_B,OUTPUT); //HIGH
      digitalWrite(PIN_LED_B,HIGH); //HIGH
      pinMode(PIN_LED_A,OUTPUT); //LOW
      digitalWrite(PIN_LED_A,LOW); //LOW
    break;
    case 4:
      pinMode(PIN_LED_A,INPUT); //FLOAT
      pinMode(PIN_LED_C,OUTPUT); //HIGH
      digitalWrite(PIN_LED_C,HIGH); //HIGH
      pinMode(PIN_LED_B,OUTPUT); //LOW
      digitalWrite(PIN_LED_B,LOW); //LOW
    break;
    case 5:
      pinMode(PIN_LED_B,INPUT); //FLOAT
      pinMode(PIN_LED_A,OUTPUT); //HIGH
      digitalWrite(PIN_LED_A,HIGH); //HIGH
      pinMode(PIN_LED_C,OUTPUT); //LOW
      digitalWrite(PIN_LED_C,LOW); //LOW
    break;
    case 6:
      pinMode(PIN_LED_B,INPUT); //FLOAT
      pinMode(PIN_LED_C,OUTPUT); //HIGH
      digitalWrite(PIN_LED_C,HIGH); //HIGH
      pinMode(PIN_LED_A,OUTPUT); //LOW
      digitalWrite(PIN_LED_A,LOW); //LOW
    break;
  }
}


#define COUNT_DOWN_WDT_CYCLES_TO_FLASH_OFF 3
volatile uint16_t _wdtCyclesToFlashOff = 0;

// This variable is made volatile because it is changed inside
// an interrupt function 468 x 64ms ~= 30s
#define COUNT_DOWN_SLEEP_CYCLES_TWINKLE 468
volatile uint16_t _wdtCyclesToNextTwinkle=0;

#define COUNT_DOWN_WDT_CYCLES_INFRARED 20
volatile uint8_t _wdtCyclesToInfrared=COUNT_DOWN_WDT_CYCLES_INFRARED;

// Watchdog Interrupt Service. This is executed when watchdog timed out.
ISR(WDT_vect) {
  if(_wdtCyclesToNextTwinkle>0){
    _wdtCyclesToNextTwinkle-=1; //countdown by 1 sleep cycle
  }
  if(_currMode == LightMode){
    if(_wdtCyclesToFlashOff>0){
      _wdtCyclesToFlashOff--;
    }else{
      _currMode = QuietMode; //switch to quietMode
    }
    
  }
}



//https://gist.github.com/dwhacks/8055287
// set system into the sleep state 
// system wakes up when wtchdog is timed out
void system_sleep() {
  //cbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter OFF

  set_sleep_mode(SLEEP_MODE_PWR_DOWN); // sleep mode is set here
  sleep_enable();
  sei(); //enable interrupts
  sleep_mode();                        // System sleeps here

  sleep_disable();                     // System continues execution here when watchdog timed out 
  //sbi(ADCSRA,ADEN);                    // switch Analog to Digitalconverter ON
}



//https://gist.github.com/dwhacks/8055287
void setup_watchdog(int ii) {

  /*
   * 0 -   16ms
   * 1 -   32ms
   * 2 -   64ms
   * 3 -  125ms : 30/.125 = 240:<255 byte
   * 4 -  250ms : 60/.250 = 240:<255 byte
   * 5 -  500ms
   * 6 - 1000ms
   * 7 - 2000ms
   * 8 - 4000ms
   * 9 - 8000ms
   */

  byte bb;
  int ww;
  if (ii > 9 ) ii=9;
  bb=ii & 7;
  if (ii > 7) bb|= (1<<5);
  bb|= (1<<WDCE);
  ww=bb;

  MCUSR &= ~(1<<WDRF);
  // start timed sequence
  WDTCR |= (1<<WDCE) | (1<<WDE);
  // set new watchdog timeout value
  WDTCR = bb;
  WDTCR |= _BV(WDIE);
}


//void sleep(uint32_t dur_ms){
//  //https://gist.github.com/stojg/aec2c8c54c29c0fab407
//  MCUSR &= ~(1<<WDRF); // Clear the reset flag on the MCUSR, the WDRF bit (bit 3).
//  WDTCSR |= (1<<WDCE) | (1<<WDE); // Set the WDCE bit (bit 4) and the WDE bit (bit 3) of the WDTCSR. The WDCE
//  WDTCSR  = (0<<WDP3) | (1<<WDP2) | (1<<WDP1) | (0<<WDP0); //1 second
//  WDTCSR |= _BV(WDIE); // Enable the WD interrupt (note: no reset).
//  set_sleep_mode(SLEEP_MODE_PWR_DOWN);
//  sleep_enable();
//  sleep_mode();
//  // The program will continue from here after the WDT timeout
//  sleep_disable();// First thing to do is disable sleep.
//  power_all_enable();// Re-enable the peripherals.
//  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
//}










void TwinkleMode(){
  if(_wdtCyclesToNextTwinkle==0){
    flash(random(64),10); //flash a random combination of LEDs for ~10ms
    _wdtCyclesToNextTwinkle=random(3,30); //should be random from 3 to 16 @64ms intervals
  }
}

void QuietMode(){
  //after 30 seconds (or 468 wdt sleep cycles at 64ms), switch to TwinkleMode
  //if(_wdtCyclesToNextTwinkle%16==0){
    _wdtCyclesToInfrared=COUNT_DOWN_WDT_CYCLES_INFRARED; //reset infrared countdown
  //}
  if(_wdtCyclesToNextTwinkle==0){
    _currMode = TwinkleMode;
    //_wdtCyclesToInfrared=COUNT_DOWN_WDT_CYCLES_INFRARED; //reset infrared countdown
  }
}

void FlashMode(){
  _currMode = QuietMode; //switch to quietMode
  flash(63,30); //flash all LEDs for 30ms
  _wdtCyclesToNextTwinkle=COUNT_DOWN_SLEEP_CYCLES_TWINKLE; //reset countdown to start twinkle
}

void LightMode(){
  //_currMode = QuietMode; //switch to quietMode
  _wdtCyclesToNextTwinkle=COUNT_DOWN_SLEEP_CYCLES_TWINKLE; //reset countdown to start twinkle

  uint16_t c = 4000; //timed for about 2.5 seconds
  uint8_t a = 100;
  uint8_t r = 0;
  while(_wdtCyclesToFlashOff>0){
    if(c>0){
      light(1+c%6);
      //light(1);light(2);light(3);light(4);light(5);light(6);
      
      
      c--;
    }else{
      if(a==0){
        r = random(7);
        a=100;
      }
      light(r);
      a--;
    }
  }
  light(0);
  _currMode = QuietMode; //switch to quietMode
}



void IrMode(){
/*
  if (_ir_receiver.getResults()) {
    //Decode the data
    _ir_decoder.decode();
    if(_ir_decoder.value!=0)
    {
      _ir_decoder.dumpResults(); //Show the results on serial monitor
      
      //currentHue = (uint16_t)_ir_decoder.value;
      //currentColor = Wheel(currentHue & 255);
      //refreshPixels(); //could put after resume
    }
    delay(100);
    _ir_receiver.enableIRIn(); //Restart the receiver
  }
  */  
}




ISR(INT0_vect) {
  if(_wdtCyclesToInfrared>0){
    _wdtCyclesToInfrared--;
    _wdtCyclesToFlashOff = COUNT_DOWN_WDT_CYCLES_TO_FLASH_OFF; //reset wdt counter for flash on cycles
  }else{
    _wdtCyclesToInfrared=COUNT_DOWN_WDT_CYCLES_INFRARED; //reset infrared countdown
    _currMode = LightMode;//FlashMode; //flash mode
  }
}



void setup() {
  ADCSRA &= ~(1<<ADEN); //Disable ADC, saves ~230uA
  pinMode(4,INPUT_PULLUP); //pull up unused pins to reduce power consumption
  GIMSK |= _BV(INT0); //enable INT0
  
  //_ir_receiver.enableIRIn(); // Start the infrared receiver
  light(0); //turn off leds
  
  _currMode = FlashMode; //flash once and then enter quiet mode for 40 seconds
  
  setup_watchdog(2);//Setup watchdog to go off after 64ms
}



void loop() {
  // Wait until the watchdog have triggered a wake up.
  _currMode();
  
  system_sleep();//Go to sleep! Wake up 64ms later and check watchdog timer counter
}
