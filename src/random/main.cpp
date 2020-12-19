
#include <iostream>
#include <string>
#include <random>
#include <chrono>
//using namespace std;


//uniform_int_distribution(0,N-1)

void uniform_dist(std::string name, int n, std::default_random_engine &generator) {
 //


  std::cout << std::endl << "-----------------------------------" << std::endl;

  std::uniform_int_distribution<> dist(0,n-1);
  std::cout << name << "(0," << (n-1) << ") :" << std::endl << "  ";


//      std::random_device rd;  //Will be used to obtain a seed for the random number engine
   //   std::mt19937 gen(rd()); //Standard mersenne_twister_engine seeded with rd()
     // std::uniform_int_distribution<> dis(1, 6);

  for (int n=0; n<10; ++n) {
    std::cout << dist(generator) << ' ';
  }
  std::cout << std::endl;
}

void normal_dist(std::string name, float mean, float stddev, std::default_random_engine &generator) {
  const int nrolls=10000;  // number of experiments
  const int nstars=100;    // maximum number of stars to distribute

  std::cout << std::endl << "-----------------------------------" << std::endl;

  std::normal_distribution<double> distribution(mean, stddev);

  int p[10]={};

  for (int i=0; i<nrolls; ++i) {
    double number = distribution(generator);
    if ((number>=0.0)&&(number<10.0)) ++p[int(number)];
  }

  std::cout << name << " (" << mean << ", " << stddev << ") :" << std::endl;

  for (int i=0; i<10; ++i) {
    std::cout << i << "-" << (i+1) << ": ";
    std::cout << std::string(p[i]*nstars/nrolls,'*') << std::endl;
  }
}

int main() {
  std::default_random_engine generator;
  generator.seed(std::chrono::system_clock::now().time_since_epoch().count());

  normal_dist("normal", 7.0, 3.0, generator);
  uniform_dist("uniform",6,generator);

  return 0;
}
