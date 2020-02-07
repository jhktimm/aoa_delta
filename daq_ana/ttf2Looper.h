#ifndef TTF2LOOPER_H
#define TTF2LOOPER_H

#include <daq_server_util_def.h>
#include <ttf2_daq_data.h>
#include <ttf2_daq_reader_2010.h>

#include <parse_chan_descr.h>
#include <ttf2_daq_slicer.h>

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

struct TTF2Looper {

 TTF2Looper();
 TTF2Looper(std::vector<char*> fileList);
 ~TTF2Looper();

 /// List of raw files to be opend, full path
 std::vector<char*> fileList;
 /// Sets fileList.
 void setFileList( std::vector<char*> _fileList) {fileList=_fileList;}

 /// Retruns the path of the first file in the list of files to be opend.
 /// Use TTF2Looper::setFileList() first, if fileList is empty, an exception
 /// is trhown.
 std::string path();

 /// Opens the raw data a first time, to get a list of channels.
 std::vector<daq_channel_entry*> getChannelList();

 bool readerOk(){return ((reader_2010.get_data(NULL, &res)) == TTF2_DAQ_READER_OK);}

 daq_server_request request;
 ttf2_daq_reader_2010 reader_2010;
 vector<ttf2_channel_entry_long*> res;

 ttf2_daq_getdata data;

};

#endif // TTF2LOOPER_H
