#include "mbed.h"
#include "bbcar.h"
#include "bbcar_rpc.h"

Ticker servo_ticker;
PwmOut pin5(D12), pin6(D13);
BufferedSerial xbee(D1, D0);

BBCar car(pin5, pin6, servo_ticker);

void RPC_goStraightCalib (Arguments *in, Reply *out)   {
    int speed = in->getArg<double>();
    car.goStraightCalib(speed);
    return;
}

RPCFunction rpcCtrl2(&RPC_goStraightCalib, "goStraightCalib");

int main() {
   double pwm_table0[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   double speed_table0[] = {-16.742, -16.104, -14.589, -10.523, -4.006, 0.558, 6.936, 12.436, 15.227, 16.343, 16.742};
   double pwm_table1[] = {-150, -120, -90, -60, -30, 0, 30, 60, 90, 120, 150};
   double speed_table1[] = {-16.423, -16.024, -15.067, -11.560, -5.262, 0.000, 6.856, 12.516, 15.227, 16.263, 16.662};

   car.setCalibTable(11, pwm_table0, speed_table0, 11, pwm_table1, speed_table1);

   char buf[256], outbuf[256];
   FILE *devin = fdopen(&xbee, "r");
   FILE *devout = fdopen(&xbee, "w");
   while (1) {
      memset(buf, 0, 256);
      for( int i = 0; ; i++ ) {
         char recv = fgetc(devin);
         if(recv == '\n') {
            printf("\r\n");
            break;
         }
         buf[i] = fputc(recv, devout);
      }
   RPC::call(buf, outbuf);
   }
}
