/*
 * simpleStatisticsOfCircularQuantities.hpp
 *
 *  Created on: Jun, 2019
 *      Author: Jan Timm jhktimm@gmail.com
 */

#ifndef SIMPLE_STATISTICS_HPP
#define SIMPLE_STATISTICS_HPP

#include <cmath>
#include <vector>
#include <numeric>
#include <algorithm>
#include <stdexcept>

/*! This class is doing some simple statistic like
 * - mean value from the given data \f$ x_{1}, x_{2}, ..., x_{N} \f$: mean()
 *  \f[ \bar{x} = \frac{1}{N} \sum_{i=1}^{N}{ x_{i} }  \f]
 * - standard deviation of mean: sigma()
 *  \f[ \sigma_{\bar{x}} = \sqrt{ \frac{1}{N} \sum_{i=1}^{N}{(x_{i} - \bar{x} )^2} }  \f]
 * - sample standard deviation: sampleSigma()
 *  \f[ \sigma_{x_{i}} = \sqrt{ \frac{1}{N-1} \sum_{i=1}^{N}{(x_{i} - \bar{x} )^2} }  \f]
 * - root mean square: rms()
 *  \f[ \mbox{rms} = \sqrt{ \frac{1}{N} \sum_{i=1}^{N}{x_{i}^2} }  \f]
 * 
 * and some other things... 
 */
template <class T>
struct simpleStatistics : public std::vector<T>{
  using std::vector<T>::vector;
  using std::vector<T>::assign;
//  struct simpleStatistics {
//  simpleStatistics(){}
//  simpleStatistics(std::vector<T> vec){ assign(vec);}
//  simpleStatistics(std::vector<T> vec, ulong start, ulong range){ assign(vec, start, range);}
//  ~simpleStatistics(){}
  explicit operator std::vector<T>*() const {
    return this;
  }

//  std::vector<T> values;//!< This vector contains the N input values \f$ x_{1}, x_{2}, ..., x_{N} \f$.
                        //!<
  
  /*! Assign the data from the given vector within the range
   * specified with start and range.
   * \param vec input data \f$ x_{1}, x_{2}, ..., x_{start}, ..., x_{start + rang}, ..., x_{N} \f$.
   * \param start start point
   * \param range used rang starting at start
   * The data is only taken from the specified rang \f$ x_{start}, ..., x_{start + range} \f$.
   */
  inline void assign(std::vector<T> vec, ulong start, ulong range) {
    if (vec.size() < start + range) {
      throw std::runtime_error("calculate: standard deviation: start + rang is bigger than the vector.\n");
    }
    this->assign(vec.begin() + start , vec.begin() + start + range);
    flagMeanTmp = true;
  }
  
  /*! Assign the data from the given vector \param vec.
   */  
  inline void assign(std::vector<T> vec) {
    this->assign(vec.begin(), vec.end());
    flagMeanTmp = true;
  }
  
  /*! Adds a single value to the data. 
   */
  inline void add(T in) {
    this->push_back(in);
    flagMeanTmp = true;    
  }
  
  /*! Clear the vector holding the data. 
   */
  inline void reset() {
    this->clear();
    flagMeanTmp = true;
    meanTmp = 0;
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*! Calculates the mean.
   * \f[ \bar{x} = \frac{1}{N} \sum_{i=1}^{N}{ x_{i} }  \f]
   */
  inline T mean(){
    if (flagMeanTmp) {
      T sum = std::accumulate(this->begin(), this->end(), 0.0);
      meanTmp = sum/this->size();
      flagMeanTmp = false;
    }
    return meanTmp;
  }
  inline static T mean(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.mean();
  }
  inline static T mean(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.mean();
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*! Calculates the standard deviation from the mean.
   * \f[ \sigma_{\bar{x}} = \sqrt{ \frac{1}{N} \sum_{i=1}^{N}{(x_{i} - \bar{x} )^2} }  \f]
   */
  inline T sigma(){
    T r = 0;
    T r_sum = 0;
    if (flagMeanTmp) mean();
    for ( auto v : *this) {
      r_sum += ( v - meanTmp) * ( v - meanTmp );//faster
    }
    r = std::sqrt( r_sum / this->size() );
    return r;
  }
  inline static T sigma(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.sigma();
  }
  inline static T sigma(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.sigma();
  }
  
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

  /*! Calculates the sample standard deviation from the input vales.
   * \f[ \sigma_{x_{i}} = \sqrt{ \frac{1}{N-1} \sum_{i=1}^{N}{(x_{i} - \bar{x} )^2} }  \f]
   */
  inline T sampleSigma(){
    T r = 0;
    T r_sum = 0;
    if (flagMeanTmp) mean();
    for ( auto v : *this) {
      r_sum += ( v - meanTmp ) * ( v - meanTmp );  
    }
    r = std::sqrt( r_sum / ( this->size() - 1 ));
    return r;
  }
  inline static T sampleSigma(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.sampleSigma();
  }
  inline static T sampleSigma(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.sampleSigma();
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*! Calculates the root mean square.
   * \f[ \mbox{rms} = \sqrt{ \frac{1}{N} \sum_{i=1}^{N}{x_{i}^2} }  \f]
   */
  inline T rms(){
    T r = 0;
    T r_sum = 0;
    for ( auto v : *this) {
      r_sum += ( v ) * ( v );      
    }
    r = std::sqrt( r_sum / this->size() );
    return r;
  }  
  inline static T rms(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.rms();
  }
  inline static T rms(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.rms();
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*! Calculates a relative error.
   * \f[ \mbox{relError} = \frac{\sigma_{\bar{x}}}{\bar{x}}\f]
   */
  inline T relError(){
    if (flagMeanTmp) mean();
    return sigma()/meanTmp;
  }
  inline static T relError(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.relError();
  }
  inline static T relError(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.relError();
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
  
  /*! Calculates a relative rms.
   * \f[ \mbox{relRMS} = \frac{\mbox{rms}}{\bar{x}}\f]
   * In principle this does not make sens.
   */
  inline T relRMS(){
    if (flagMeanTmp) mean();
    return rms()/meanTmp;
  }
  inline static T relRMS(std::vector<T> vec) {
    auto tmp = simpleStatistics(vec);
    return tmp.relRMS();
  }
  inline static T relRMS(std::vector<T> vec, ulong start, ulong range) {
    auto tmp = simpleStatistics(vec, start, range);
    return tmp.relRMS();
  }
  
  /////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
protected:
  
  bool flagMeanTmp = true;//!< Flag if the mean has to be calculate
                    //!<
  
  T meanTmp;
  
};

#endif // SIMPLE_STATISTICS_HPP
