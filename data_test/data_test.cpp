#include "../include/OnlineAnalysis.h"

/**
 * This is a simple example and mostly a test to get the redsidual.
 * The data of one event of one cavity is taken from a .json file
 * in the directory, e.g. ./datatest data_set_2.json  
 * and the cal coeff is calculated as well as the residual of course.
 */
int main(int argc, char *argv[])
{
  std::cout << "usage: " << argv[0] << " <json file with test data>\n";
  //~ double samples = 1821;
  //~ double samples = 16384;
  double samples = 1820;// number of samples, your data have
  
  // you can reduce your data samples by deviding wiht div = 9
  // than only every 9th element of 16384 samples is taken
  //~ double div = 9;
  double div = 1;
  
  /// OnlineAnalysis constructor
  OnlineAnalysis * oa = new OnlineAnalysis(samples,div);
  
  /// setting up the data
  // depending on the source, you can set diffenret data types
  // in this test .json file is used
  oa->set_data(argv[1]);
  // if you have only 1820 samples and
  // you take your data only from .json file,
  // you have to set the sampling freq FS manually
  oa->FS = 1;
  oa->print_data();
    
  ///
  //~ oa->getAutoParameters();// here standard directtory is ../tau_k_x/
  oa->getAutoParameters("../../tau_k_x/");// set directory manually
  oa->print_Parameters();
  
  /// calculat calCoeff and print to screen
  // normally this is not always needed
  oa->get_calCoeff();
  oa->print_calCoeff();
  
  /// calculat residual and print to screen
  // if you loop over events from the same cavity,
  // you need to calculat calCoeff only one time at begin
  oa->get_res();
  oa->print_res();
  
  delete (oa);// to prevent a memory leak
  return 0;	
}

