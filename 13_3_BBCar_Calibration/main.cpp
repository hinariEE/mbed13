#include "mbed.h"
#include "bbcar.h"

Ticker servo_ticker;
PwmOut pin5(D12), pin6(D13);

BBCar car(pin5, pin6, servo_ticker);

int main() {
   // please contruct you own calibration table with each servo
   double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   double speed_table0[] = {-16.742, -16.104, -14.589, -10.523, -4.006, 0.558, 6.936, 12.436, 15.227, 16.343, 16.742};
   double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   double speed_table1[] = {-16.423, -16.024, -15.067, -11.560, -5.262, 0.000, 6.856, 12.516, 15.227, 16.263, 16.662};

   // first and fourth argument : length of table
   car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

   while (1) {
      car.goStraightCalib(5);
      ThisThread::sleep_for(5s);
      car.stop();
      ThisThread::sleep_for(5s);
   }
}
