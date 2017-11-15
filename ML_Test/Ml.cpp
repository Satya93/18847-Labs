#include "Ml.h"
#include <Arduino.h>

int *buff = 0;

void Ml::clear_all()
{
  _cnt = 0;
  _sum = 0;
  _min = 0.0;
  _max = 0.0;
  _stddev = 0.0;
  _pin = 4;
  _old = 0;
  randomSeed(48);
}

void Ml::append(float f)
{
  int dev;
  if(_cnt==0)
  {
    _min = f;
    _max = f;
  }
  else{
    if (f < _min){
      _min = f;
    }
    if (f > _max){
      _max = f;
    }
  }
  _sum += f;
  _cnt++;
  _mean = _sum/_cnt;
  dev = f-_mean;
  _stddev = (_stddev+dev)/_cnt;
  //-------------------------------------------------
  //Slope Calculations
  //-------------------------------------------------
  _del = f-_old;
  _old = f;
  /*SerialUSB.print("Count : ");
  SerialUSB.println(_cnt);
  SerialUSB.print("Minimum Value : ");
  SerialUSB.println(_min);
  SerialUSB.print("Maximum Value : ");
  SerialUSB.println(_max);
  SerialUSB.print("Sum : ");
  SerialUSB.println(_sum);
  SerialUSB.print("Standard Deviation : ");
  SerialUSB.println(_stddev);
  //SerialUSB.print("Change in readings : ");
  //SerialUSB.println(_del);
  //SerialUSB.print("Target Value : ");
  //SerialUSB.println(calc_val);
  //SerialUSB.print("Err : ");
  //SerialUSB.println(_err/_cnt);
  //SerialUSB.println(" ");*/
}

void Ml::sample(int s)
{
  buff = (int*) malloc(s * sizeof(int));
  int curr_val;
  int mx_cnt = s;
  _mx_cnt = s;
  int count = 0;
  int sample_data[100] = {7, 7, 8, 12, 9, 7, 12, 17, 11, 13, 12, 17, 18, 20, 16, 23, 25, 20, 25, 22, 27, 25, 26, 25, 31, 29, 33, 28, 36, 32, 32, 37, 35, 43, 44, 43, 41, 39, 41, 46, 48, 46, 51, 48, 52, 46, 50, 53, 52, 54, 60, 53, 56, 56, 60, 61, 59, 58, 61, 69, 62, 62, 65, 64, 67, 74, 74, 69, 74, 75, 72, 79, 82, 81, 81, 79, 82, 87, 83, 80, 88, 86, 90, 90, 87, 91, 88, 91, 96, 98, 100, 93, 101, 99, 100, 98, 99, 99, 105, 105};
  while(count<s){
    curr_val = sample_data[count];
    //get_data();
    append(curr_val);
    buff[count] = curr_val;
    count++;
  }
}

int Ml::get_data()
{
  //Insert logic to get data
  //return analogRead(4);
  //append(5);
  int randi;
  randi = random(10,100);
  //SerialUSB.println(randi);
  return randi;
}

void Ml::regression(int numiter)
{
 
  float err = 1000; 
  float m = 2;
  float c = _mean;
  float calc_val;
  float alpha = 0.005;
  float err_1;
  float err_0;
  float toterr_0;
  float toterr_1;
  double cost = 1000; // Power and accuracy comparison using double and float
  int i = 0;
  float olderr;
  float tot_cost = 10000;
  int itno = 0;
  int boost = 1;
  int maxcnt = numiter;
  //SerialUSB.println("Regression");
  //while(tot_cost>4){
  
  while(itno<maxcnt){
    // Reset Aggregation variables
    olderr = tot_cost;
    cost = 0;
    i = 0;
    toterr_1 = 0;
    toterr_0 = 0;
    // Begin iteration
    while(i<_mx_cnt){
      // Get Initial Estimate
      calc_val = m*(i+1) + c;
      // Calculate Cost and First Derivatives of Slope and Error
      cost = ((calc_val-buff[i])*(calc_val-buff[i]));
      err_0 = (calc_val-buff[i]);
      err_1 = (calc_val-buff[i])*(i - _min)/(_max-_min);
      // Aggregate Errors
      toterr_0 += err_0;
      toterr_1 += err_1;
      tot_cost += cost;
      i++;
    }
    // Calculate Iteration Cost
    tot_cost = tot_cost/(2*i);
    // Update Slope and Intercept
    m = m - (alpha*toterr_1/_mx_cnt);
    c = c - (alpha*toterr_0/_mx_cnt);
    itno++;
  }

}
