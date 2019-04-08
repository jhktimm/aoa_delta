#include <iostream>
#include <string>
#include "../include/aoa_daq_datasclass.h"
//~ #include "doocs_snapdaq_llrf_datasclass.h"



int main(int argc, char *argv[])
{
    for (int a = 1; a < argc; a++) {
		aoa_daq_datasclass* data = new aoa_daq_datasclass;
        //~ std::cout << "argv["<<a<<"]: " << argv[a] << "\n";
        std::string filename = argv[a];
        std::cout << "convert file: " << filename << "\n";
        data->parser(filename);
        data->write(filename + ".bit");
    }
    if (argc == 1) {
		std::cout << "usage: ./txt2bit *.txt\noutput are *.bit files\n\n";
    }
    return 0;
}
