#include <fstream>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include "../include/OnlineAnalysis.h"
#include <time.h>

int main(int argc, char *argv[])
{
  std::cout << "usage: " << argv[0] << " <json file with test data>\n";
	//~ double samples = 1821;
	double samples = 1820;
	//~ double div = 9;
	double div = 1;
	//~ double samples = 16384;
	//~ double div = 1;
	OnlineAnalysis * oa = new OnlineAnalysis(samples,div);
  
  oa->set_data(argv[1]);
  oa->FS = 1;
  oa->print_data();
  oa->getAutoParameters();
  oa->print_Parameters();
  
  oa->get_calCoeff();
  oa->print_calCoeff();
  
  oa->get_res();
  oa->print_res();
  
  delete (oa);
  return 0;	
}

