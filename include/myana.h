#ifndef MYANA_H
#define MYANA_H

#include "simpleStatistics.hpp"
#include "linearRegression.hpp"
#include <fstream>
#include <iomanip>

class MyAna
{
public:
 MyAna();

 lineareRegression<double> fillingReg, flattopReg;
 ulong pid;
 std::string name;
 double time;
 std::string indicator;
 enum class stateNum: char {
  normal='n',
  trip='t',
  off='o',
  disturbances='d',
  fluctuations='f',
  compensations='c'
 };

 struct report {
  std::string cavityName;
  ulong pid;
  //    long pid;
  double time;
  stateNum state;
  std::string comment;
  float mean;
  float sigma;

  std::string header() {
   std::stringstream sSTmp;
   sSTmp
     << "cavityName "
     << "PID "
     << "Time "
     << "State "
     << "Comment "
     << "FlatTopMean "
     << "FlatTopSigma "
     << "\n";
   return sSTmp.str();
  }
  std::string data() {
   std::stringstream sSTmp;
   sSTmp
     << cavityName << " "
     << std::setprecision(12)
     << pid << " "
     << time << " "
     << static_cast<char>( state ) << " "
     << comment << " "
     << std::setprecision(6)
     << mean << " "
     << std::setprecision(4)
     << sigma << "\n";
   return sSTmp.str();
  }
 };
 report rep;
 std::vector<report> reportHisto;

 double delay;
 double filling;
 double flattop;
 double fs;
 std::vector<double> pulse;

 void setData(ulong _pid, std::string _name, double _time, double _delay, double _filling, double _flattop, double _fs, std::vector<double> _pulse);

 void write(std::string filename);

 void mach();
};

#endif // MYANA_H
