using namespace std;

#ifndef MONTECARLOAI_H
#define MONTECARLOAI_H

class MonteCarloAI {
  public:
    MonteCarloAI(int num_trials=1000);
  private:
    int num_trials;
};

#endif