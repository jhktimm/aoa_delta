#ifndef LINEAREREGRESSION_H
#define LINEAREREGRESSION_H

#include <vector>
#include <utility>
#include <iostream>
#include <stdexcept>
#include "simpleStatistics.hpp"

/*! This class is doing an linear regression
 * It is inherited from std::vector<std::pair<T, T>>, so from the pairs
 * first is x value and second the y value.
 * \f[ y = m * x + b  \f]
 *
 * m()      : \f$ m = Sxy / Sxx  \f$ \n
 * b()      : \f$ b = \bar{y}  -  \bar{x} * m \f$ \n
 * sigmaM() : \f$ \sigma_m = g * \sqrt{ 1 / Sxx}  \f$ \n
 * sigmaB() : \f$ \sigma_b = g * \sqrt{ Sx / ( Sxx * ( N - 2 ))}  \f$ \n
 *
 * R()      : \f$ R =  Sxx / \sqrt{ Sx * Syy }  \f$ \n
 * F()      : \f$ F =  R^2 * (1 - R^2) / ( 2 * ( N - 2 ) )  \f$ \n
 * with:
 * \f$ g = \sqrt{ Sy / ( N - 2 ) }  \f$ \n
 * and: \n
 * \f$ Sxy = \sum_{i=1}^{N}{ ( x_{i} - \bar{x} )*( y_{i} - \bar{y} ) }  \f$ \n
 * \f$ Sxx = \sum_{i=1}^{N}{ ( x_{i} - \bar{x} )^2 }  \f$ \n
 * \f$ Sx = \sum_{i=1}^{N}{ ( x_{i} )^2 }  \f$ \n
 * \f$ Sy = \sum_{i=1}^{N}{ ( y_{i} - ( m * x_{i} + b  ) )^2 }  \f$ \n
 * \f$ Syy = \sum_{i=1}^{N}{ ( y_{i} - \bar{y} )^2 }  \f$ \n
 *
 * print() : prints all values
 * clean() : musst be called befor new calculations
 *
 * Note that the template could be only float or double.
 */
template <typename T>
class lineareRegression : public std::vector<std::pair<T, T> >
{
public:
  using std::vector<std::pair<T, T> >::vector;

  inline T b() {
    return y.mean() - m() * x.mean();
  }

  inline T m() {
    calcSumSxySxx();
    return m_tmp;
  }

  inline T meanOfSingleMeasurments() {
    calcSumSxSySyy();
    return meanOfSingleMeasurments_tmp;
  }

  inline T sigmaM(){
    return meanOfSingleMeasurments() * std::sqrt( 1 / Sxx );
  }

  inline T sigmaB(){
    return meanOfSingleMeasurments() * std::sqrt( Sx / ( this->size() * Sxx )  );
  }

  inline T R(){
    calcSumSxSySyy();
    return Sxy / std::sqrt(Sxx*Syy);
  }

  inline T F(){
    auto r = R();
    return r * r * ( 1 - r*r ) / ( 2 * ( this->size() - 2 )  );
  }

  inline T sumOfSquareYi(){
    calcSumSxSySyy();
    return Sy;
  }

  inline void print () {
    std::cout << "linear regression y = m*x + b:" << std::endl;
    std::cout << " m: " << m() << " +/- " << sigmaM() << std::endl;
    std::cout << " b: " << b() << " +/- " << sigmaB() << std::endl;
    std::cout << " mean of single measurments: " << meanOfSingleMeasurments() << std::endl;
    std::cout << "                          R: " << R() << std::endl;
    std::cout << "          degree of freedom: " << this->size() - 2 << std::endl;
    std::cout << "           Sum of square yi: " << sumOfSquareYi() << std::endl;
    std::cout << "                          F: " << F() << std::endl;
    std::cout << std::endl;
  }

  inline void clean() {
    this->clear();
    Sxy = 0., Sxx = 0., Syy = 0., Sx = 0., Sy = 0.;
    meanOfSingleMeasurments_tmp = 0.;
    m_tmp =0;
    x.reset(); y.reset();
    calcSumSxSySyyFlag = true;
    calcSumSxySxxFlag = true;
    getXYFlag = true;
  }

  inline void setDebug() {debug = true;}

  inline void setXY(std::vector<T> xi, std::vector<T> yi){
    x.assign(xi);
    y.assign(yi);
    this->resize(x.size());
    getXYFlag = false;
  }

  inline void add(std::pair<T,T> in){
    this->push_back(in);
    x.push_back(in.first);
    y.push_back(in.second);
    getXYFlag = false;
  }

private:

  T Sxy = 0., Sxx = 0., Syy = 0., Sx = 0., Sy = 0.;

  T meanOfSingleMeasurments_tmp = 0.;
  T m_tmp = 0.;

  simpleStatistics<T> x;

  simpleStatistics<T> y;

  inline void getXY() {
    test();
    if (getXYFlag) {
      x.clear(); y.clear();
      for (auto v : *this) {
        x.push_back(v.first);
        y.push_back(v.second);
      }
      getXYFlag = false;
    }
  }
  bool getXYFlag = true;

  inline void calcSumSxySxx(){
    getXY();
    if (calcSumSxySxxFlag) {
      auto m_x = x.mean();
      auto m_y = y.mean();
      for (uint i = 0; i < this->size(); i++) {
        Sxy += ( x.at(i) - m_x ) * ( y.at(i) - m_y);
        Sxx += ( x.at(i) - m_x ) * ( x.at(i) - m_x );
      }
      m_tmp = Sxy / Sxx;
      if (debug) {
        std::cout << std::endl;
        std::cout << "  --- calcSumSxySxx: " << std::endl;
        printDebug();
      }
      calcSumSxySxxFlag = false;
    }
  }
  bool calcSumSxySxxFlag = true;

  inline void calcSumSxSySyy(){
    getXY();
    if (calcSumSxSySyyFlag) {
      Sy = 0. , Sx = 0., Syy = 0.;
      auto m_y = y.mean();
      auto _m = m();
      auto _b = b();
      for (uint i = 0; i < this->size(); i++) {
        Sy  += ( y.at(i) - ( _m*x.at(i) + _b ) ) * ( y.at(i) - ( _m*x.at(i) + _b ) );
        Syy += ( y.at(i) - m_y ) * ( y.at(i) - m_y );
        Sx  += x.at(i) * x.at(i);
      }
      meanOfSingleMeasurments_tmp = std::sqrt( Sy / ( this->size() - 2 ) );
      if (debug) {
        std::cout << std::endl;
        std::cout << "  --- calcSumSxSySyy: " << std::endl;
        printDebug();

      }
      calcSumSxSySyyFlag = false;
    }
  }
  bool calcSumSxSySyyFlag = true;

  void test() {
    if (this->size() < 2) throw std::runtime_error("linear regression: you need at least two values.\n");
  }

  bool debug = false;
  inline void printDebug(){
    std::cout << std::endl;
    std::cout << "  Sxy: " << Sxy << std::endl;
    std::cout << "  Sxx: " << Sxx << std::endl;
    std::cout << std::endl;
    std::cout << "  Sx: " << Sx << std::endl;
    std::cout << "  Sy: " << Sy << std::endl;
    std::cout << "  Syy: " << Syy << std::endl;
    std::cout << std::endl;
    std::cout << "  m_tmp: " << m_tmp << std::endl;
    std::cout << "  meanOfSingleMeasurments_tmp: " << meanOfSingleMeasurments_tmp << std::endl;
    std::cout << std::endl;
  }
};

#endif // LINEAREREGRESSION_H
