#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin5(D12), pin6(D13);
BBCar car(pin5, pin6, servo_ticker);

int main() {
   while(1){
      car.goStraight(200);
      ThisThread::sleep_for(5s);
      car.stop();
      ThisThread::sleep_for(5s);
   }
}
