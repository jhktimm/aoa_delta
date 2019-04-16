#ifndef DAQANALYSIS_H
#define DAQANALYSIS_H

#include "../include/OnlineAnalysis.h"

#include <ttf2_daq_reader_2010.h>
#include <daq_server_util_def.h>
#include <ttf2_daq_data.h>

struct DAQAnalysis : public OnlineAnalysis {
    DAQAnalysis(int samples, int div) : OnlineAnalysis(samples, div) {}

    void set_data(ttf2_daq_getdata* data)
    {
      ///to get pid and time
      u_int evid, tup, tlow;
      int status;
      int statusch;
      u_int len;
      int evtype, nsrvb;
      if(data->GetEventInfo(&evid, &evtype, &len, &tup, &tlow, &status, &nsrvb)) {
        printf("ttf2_user_loop(): failed to get event info\n");
      }

      ///-----  
      /// to get channel name
      char *channml;
      int llenl;
      if(data->GetChanInfo(&channml, NULL, &statusch, &llenl)) {
        printf("ttf2_user_loop(): failed to get Server Block info\n");
      }
      //~ std::cout << "Set data from .raw file for: " << channml << " " << std::endl;// channml
      //~ std::cout << "   evid: " << evid;// PID
      //~ std::cout << "    tup: " << tup << " " << std::endl;//time [s]
      //~ std::cout << "   tlow: " << tlow << " " << std::endl;//time [mus]
      
      std::string channelName(channml);
      std::stringstream ststChannelName(channelName);
      std::string strFacility, strDevice, strLocation, strProperty;
      getline(ststChannelName,strFacility,'/');
      getline(ststChannelName,strDevice,'/');
      getline(ststChannelName,strLocation,'/');
      //~ getline(ststChannelName,strProperty,'/');
      
      this->NAME = strLocation;
      
      std::stringstream strstream_name(this->NAME);//C1.M1.A20.L3
      std::string C_str, M_str, A_str, L_str;
      getline(strstream_name, C_str, '.');
      getline(strstream_name, M_str, '.');
      getline(strstream_name, A_str, '.');	
      getline(strstream_name, L_str, '.');	
      this->channel.section = M_str + '.' + L_str;
      this->channel.station = A_str;
      this->channel.type = C_str;
      
      //~ std::cout << strFacility << " " <<  strDevice << " " <<  strLocation << " " <<  C_str << " " <<  M_str << " " <<  A_str << " " <<  L_str ;
      
      ///-----
      ///main loop over numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
      int numberOfSubchannels;
      numberOfSubchannels = data->GetNmemb();
      /// numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
      if (numberOfSubchannels == 6) {
        for (uint i = 0; i < this->samples; i++) {
          this->Probe_Ampl->data[i]  = data->GetSpectVal(0, i);
          this->Probe_Phase->data[i] = data->GetSpectVal(1, i);
          this->Forw_Ampl->data[i]   = data->GetSpectVal(2, i);
          this->Forw_Phase->data[i]  = data->GetSpectVal(3, i);
          this->Refl_Ampl->data[i]   = data->GetSpectVal(4, i);
          this->Refl_Phase->data[i]  = data->GetSpectVal(5, i);
        }
      } else {
        std::cout << "error in set data from .raw files: not 6 subchannels found: " << numberOfSubchannels << " " << std::endl;
      }
      
      this->PID = evid;
      //~ this->TIME = tup;
      this->TIME = (double) tup + (double) tlow/1000000;
      this->DELAY       =  20;
      this->FILLING     =  750;
      this->FLATTOP     =  650;
      //~ this->FS          =  9.027999878;
      this->FS          =  1;
      this->F0          =  1300;
      //~ std::cout << "pid: " << this->PID << " time: " << std::setprecision(12)<< this->TIME << std::endl;
    }
};


struct DoocsAddressHelper {
  DoocsAddressHelper(std::string doocsadr){
      std::stringstream ststChannelName(doocsadr);
      getline(ststChannelName,strFacility,'/');
      getline(ststChannelName,strDevice,'/');
      getline(ststChannelName,strLocation,'/');
      getline(ststChannelName,strProperty,'/');
      
      std::stringstream strstream_name(strLocation);//C1.M1.A20.L3
      getline(strstream_name, C_str, '.');
      getline(strstream_name, M_str, '.');
      getline(strstream_name, A_str, '.');	
      getline(strstream_name, L_str, '.');	
  }
  
  void print() {
    std::cout << "strFacility: " << strFacility << " strDevice: " <<  strDevice << " strLocation: " <<  strLocation << " strProperty: " << strProperty << "\n";
    std::cout << "C_str: " << C_str << " M_str: " <<  M_str << " A_str: " <<  A_str << " L_str: " <<  L_str << "\n";
  }
  
  std::string strFacility;
  std::string strDevice;
  std::string strLocation;
  std::string strProperty;
  std::string C_str;
  std::string M_str;
  std::string A_str;
  std::string L_str;
};


struct FileSystemPath {
  FileSystemPath( std::string path) {
    std::stringstream ststPath(path);
    std::string tmp;
    size_t n = std::count(path.begin(), path.end(), '/');
    for (uint i = 0; i < n; i++){
      getline(ststPath,tmp,'/');
      dir += tmp + '/';           
    }
    getline(ststPath,tmp,'/');
    file = tmp;
    
    n = std::count(file.begin(), file.end(), '.');
    std::stringstream ststFile(file);
    for (uint i = 0; i < n; i++){
      getline(ststFile,tmp,'.');
    }
    getline(ststFile,tmp,'.');
    extension = tmp;
    
    //~ print();
  } 
  
  void print() {
    std::cout << "dir: " << dir << " file: " << file << " ext.: " << extension << std::endl; 
  }
  
  std::string dir;
  std::string file;
  std::string extension;
};

#endif 
