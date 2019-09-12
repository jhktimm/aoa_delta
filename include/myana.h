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

  void setData(ulong _pid, std::string _name, double _time, double _delay, double _filling, double _flattop, double _fs, std::vector<double> _pulse){
    time = _time;
    pid = _pid;
    name = _name;
    delay = _delay;
    filling = _filling;
    flattop = _flattop;
    fs = _fs;
    pulse = _pulse;
    auto sampleNumberFillingBegin = static_cast<ulong>( (delay) * fs );
    auto sampleNumberFlattopBegin = static_cast<ulong>( (delay + filling  ) * fs );
    auto sampleNumberFlattopRange = static_cast<ulong>( (flattop  ) * fs );
    fillingReg.clean();
//    std::cout << "pulse.size(): " << pulse.size() << std::endl;
//    std::cout << "sampleNumberFillingBegin: " << sampleNumberFillingBegin << std::endl;
//    std::cout << "sampleNumberFlattopBegin: " << sampleNumberFlattopBegin << std::endl;
//    std::cout << "sampleNumberFlattopRange: " << sampleNumberFlattopRange << std::endl;
    for (ulong i = sampleNumberFillingBegin; i < sampleNumberFlattopBegin; i++) {
      std::pair<float,float> value(i, static_cast<float>(  pulse.at(i) ));
      fillingReg.add(value);
    }
    flattopReg.clean();
    for (ulong i = sampleNumberFlattopBegin; i < sampleNumberFlattopRange + sampleNumberFlattopBegin; i++) {
      std::pair<float,float> value(i, static_cast<float>(  pulse.at(i) ));
      flattopReg.add(value);
    }

    if (fillingReg.size() < 2) {
        std::pair<float,float> value(0, 0);
        fillingReg.add(value);
        fillingReg.add(value);
    }
    if (flattopReg.size() < 2) {
        std::pair<float,float> value(0, 0);
        flattopReg.add(value);
        flattopReg.add(value);
    }

  }

  void write(std::string filename){
    std::fstream checkfileStream;
    checkfileStream.open(filename);
    bool is_first_time_open = checkfileStream.fail();
    checkfileStream.close();
    std::fstream file_out(filename, std::fstream::in | std::fstream::out | std::ofstream::app );
    if (is_first_time_open) {
     file_out
     << "PID"  << " "
     << "NAME"  << " "
     << "TIME"  << " "
     << "INDICATOR"  << " "

     << "fillingReg.m"  << " "
     << "fillingReg.sigmaM"  << " "
     << "fillingReg.R"  << " "
     << "flattopReg.m"  << " "
     << "flattopReg.sigmaM"  << " "
     << "flattopReg.R"  << " "
//     << rep.header()  << " "

     << std::endl;
    }

    file_out << std::setprecision(16)
     << pid                       << " "
     << name                       << " "
     << time                       << " "
     << indicator                       << " "
     << fillingReg.m()                       << " "
     << fillingReg.sigmaM()                       << " "
     << fillingReg.R()                       << " "
     << flattopReg.m()                       << " "
     << flattopReg.sigmaM()                       << " "
     << flattopReg.R()                       << " "
//     << rep.data()                       << " "

       ;
      file_out << std::endl;

    file_out.close();

  }

  void mach() {
    int maxHistorySize = 5;
    uint32_t deadEdgeSamples = 2000/9;
//    uint32_t deadEdgeSamples = 2000;
    float maxFlatTopSigma = 3;
    float maxTripDownSpeed = 0.2;
    float minFlatTopMean = 2;//below cavity is presumed to be off
    auto samplingFrequency = fs;
    auto pulseDelay = delay;
    auto pulseFilling = filling;
    auto pulseFlatTop = flattop;
    auto start = std::ceil( samplingFrequency * (pulseDelay + pulseFilling)) + deadEdgeSamples;
    auto stopp = std::ceil( samplingFrequency * (pulseDelay + pulseFilling + pulseFlatTop)) - deadEdgeSamples;
    simpleStatistics<float> amplFlatTopSD;
    std::string tripeventWarning;
    std::string tripeventState;
    std::string tripeventReport;
    if ( start <= stopp  ) {
      amplFlatTopSD.assign( std::vector<float>( pulse.begin() + (uint32_t) start, pulse.begin() + (uint32_t) stopp) );
//      amplFlatTopSD.assign( std::vector<float>( cav.signalInput.begin() + (uint32_t) start, cav.signalInput.begin() + (uint32_t) stopp) );
    } else {
  //    std::cout << << "\n" << cav.cavityName "deadEdgeSamples is too big, or pulseFlatTop too small for that.";
  //    std::cout << " deadEdgeSamples: " << deadEdgeSamples << " pulseFlatTop: " << samplingFrequency * pulseFlatTop << "\n";
      std::cout << '*' << std::flush;
    }
    rep.cavityName = name;
    rep.pid = pid;
    rep.time = time;
//    rep.time = timeSec + (  (double) timeUsec / 1000000);
    rep.mean = amplFlatTopSD.mean();
    rep.sigma = amplFlatTopSD.sigma();

    if(reportHisto.size() > 1) {
      if ( ( reportHisto.back().mean - rep.mean ) > maxTripDownSpeed ) {
        rep.state = stateNum::trip;
//        std::cout << "\ntrip!!!! " << (char) rep.state << "\n";
//        std::cout << rep.header();
//        std::cout << rep.data();
      } else if ( ( rep.mean > reportHisto.back().mean + reportHisto.back().sigma * maxFlatTopSigma )
                  | (rep.mean < reportHisto.back().mean - reportHisto.back().sigma  * maxFlatTopSigma ) ) {
        //    } else if ( rep.sigma > maxFlatTopSigma ) {
        rep.state = stateNum::fluctuations;
  //      std::cout << "disturbances!!!! " << (char) rep.state << "\n";
  //      std::cout << rep.header();
  //      std::cout << rep.data();
      } else if (  rep.sigma > reportHisto.back().sigma * maxFlatTopSigma ) {
        rep.state = stateNum::disturbances;
      } else if ( rep.mean < minFlatTopMean ) {
        rep.state = stateNum::off;
      } else {
        rep.state = stateNum::normal;
      }
      std::string plausible;
      if (reportHisto.back().pid == rep.pid) {
        plausible = '=';
      } else if (reportHisto.back().pid + 1 != rep.pid) {
        plausible = '~';
      }
      if (rep.pid != pid) {
//          if (rep.pid != macroPulseNumber) {
        plausible = plausible + '!';
        tripeventWarning = rep.data() + " " + plausible + "\n";
        tripeventWarning = "pid: " + std::to_string(rep.pid) + " macroPulseNumber: " + std::to_string(pid) + "\n";
//        tripeventWarning = "pid: " + std::to_string(rep.pid) + " macroPulseNumber: " + std::to_string(macroPulseNumber) + "\n";
        tripeventWarning = tripeventWarning + reportHisto.back().header();
        for (auto s : reportHisto) tripeventWarning = tripeventWarning + s.data();
//        tripeventWarning.write();
      }
//      std::cout << plausible << std::flush;
      rep.comment = plausible;
      tripeventState = std::string(1, (char) rep.state) + plausible;
  //    tripeventState = std::string(1, (char) rep.state);
//      tripeventState.write();

      // tripeventWarning
      if (rep.state==stateNum::fluctuations)
      {
        tripeventWarning = rep.data() + " " + plausible + "\n";
        tripeventWarning = tripeventWarning + reportHisto.back().header();
        for (auto s : reportHisto) tripeventWarning = tripeventWarning + s.data();
//        tripeventWarning.write();
      }
      // entering the trip state should be reported
      if ( ( rep.state==stateNum::trip ) & ( reportHisto.back().state !=stateNum::trip ) )
      {
        tripeventReport = rep.data() + " " + plausible + "\n";
        tripeventReport = tripeventReport + reportHisto.back().header();
        for (auto s : reportHisto) tripeventReport = tripeventReport + s.data();
//        tripeventReport.write();
      }
    }

//    std::cout << (char) rep.state << std::flush;

    reportHisto.push_back(rep);
    if ( reportHisto.size() > maxHistorySize ) reportHisto.assign(reportHisto.begin() + 1,reportHisto.end());
  }

};

#endif // MYANA_H
