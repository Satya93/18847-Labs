#ifndef Ml_h
#define Ml_h

#include <math.h>;

class Ml
{
  public:
    void clear_all();
    void append(float);
    int count();
    float sum();
    float average();
    float minimum();
    float maximum();
    float std_dev();
    void regression(int);
    void sample(int);
    int get_data();

  protected:
    int _old;
    long _cnt;
    float _store;
    float _sum;
    float _min;
    float _max;
    float _mean;
    float _del;
    float _stddev;
    float _variance;
    float _err;
    int _mx_cnt;
    int _pin = 4;
};
#endif
