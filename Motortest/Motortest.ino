//thr_max was 2037
#include <AP_Common.h>
#include <AP_Math.h>
#include <AP_Param.h>
#include <AP_Progmem.h>
#include <AP_ADC.h>
#include <AP_InertialSensor.h>

#include <AP_HAL.h>
#include <AP_HAL_AVR.h>

#define MOTOR_FL   2    // Front left    
#define MOTOR_FR   0    // Front right
#define MOTOR_BL   1    // back left
#define MOTOR_BR   3    // back right


const AP_HAL::HAL& hal = AP_HAL_AVR_APM2;  // Hardware abstraction layer
uint16_t v_thr=2000;
void setup() 
{
  hal.rcout->set_freq(0xF, 490);
  hal.rcout->enable_mask(0xFF);
  
  hal.rcout->write(MOTOR_FR, 0);
  hal.rcout->write(MOTOR_FL, 0);
  hal.rcout->write(MOTOR_BR, 0);
  hal.rcout->write(MOTOR_BL, 0);
  
  hal.scheduler->delay(2000);
}

void loop() 
{
  uint16_t thr;
  if(v_thr<2037)
  {
    v_thr+=1;
    thr=v_thr;
  }
  hal.rcout->write(MOTOR_FR, thr);
  hal.rcout->write(MOTOR_FL, thr);
  hal.rcout->write(MOTOR_BR, thr);
  hal.rcout->write(MOTOR_BL, thr);
  
  hal.console->printf_P(
            PSTR("Sending Data...%d\n"),thr
            );
  
  hal.scheduler->delay(100);  //Wait 50ms 
  
  hal.rcout->write(MOTOR_FR, 0);
  hal.rcout->write(MOTOR_FL, 0);
  hal.rcout->write(MOTOR_BR, 0);
  hal.rcout->write(MOTOR_BL, 0);
  
  hal.scheduler->delay(400);
}
AP_HAL_MAIN();
