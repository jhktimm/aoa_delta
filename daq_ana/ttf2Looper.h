#ifndef TTF2LOOPER_H
#define TTF2LOOPER_H

#include <sstream>
#include <daq_server_util_def.h>
#include <ttf2_daq_data.h>
#include <ttf2_daq_reader_2010.h>

#include <parse_chan_descr.h>
#include <ttf2_daq_slicer.h>

///
/// \brief The AddressHelper struct
///
/// Little helper class, parsing names like:
/// XFEL.RF/LLRF.CONTROLLER.DAQ/C7.M3.A17.L3
/// in to pieces.
struct AddressHelper {
  AddressHelper(std::string doocsadr){
      fullName = doocsadr;
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

      shortName = A_str + '.' + L_str + '.' + M_str + '.' + C_str;
  }

  void print() {
    std::cout << "strFacility: " << strFacility << " strDevice: " <<  strDevice << " strLocation: " <<  strLocation << " strProperty: " << strProperty << "\n";
    std::cout << "C_str: " << C_str << " M_str: " <<  M_str << " A_str: " <<  A_str << " L_str: " <<  L_str << "\n";
  }

  std::string fullName;
  std::string shortName;
  std::string strFacility;
  std::string strDevice;
  std::string strLocation;
  std::string strProperty;
  std::string C_str;
  std::string M_str;
  std::string A_str;
  std::string L_str;
};

///
/// \brief The TTF2Looper struct
///
/// This is a helper class to loop over raw data.
/// Cunstruct with TTF2Looper looper(fileList);
/// Main lopp should be: while(looper.getData())
/// The subloop for (int i = 0; i < looper.numberOfChannels; i++) {
/// and auto channelName = looper.getChannel(i);
/// This also set set this channel i to the data, not only getting the name.
/// Than you have access to the data with looper.data .
struct TTF2Looper {

 TTF2Looper();
 TTF2Looper(std::vector<char*> fileList);
 ~TTF2Looper();

 /// Bool get Data for main loop
 /// Also set the numberOfChannels
 bool getData();

 /// Subloop of data.
 /// Returns name of the Channel and set this channel to the data.
 /// Loop over to max = numberOfChannels for all data.
 AddressHelper getChannel(int i);


 /// List of raw files to be opend, full path
 std::vector<char*> fileList;
 /// Sets fileList.
 void setFileList( std::vector<char*> _fileList) {fileList=_fileList;}

 /// Retruns the path of the first file in the list of files to be opend.
 /// Use TTF2Looper::setFileList() first, if fileList is empty, an exception
 /// is trhown.
 std::string path();


 /// Opens the raw data a first time, to get a list of channels.
 /// Normaly this is done with the xml files.
 std::vector<daq_channel_entry*> getChannelList();
 daq_server_request request;
 ttf2_daq_reader_2010 reader_2010;
 vector<ttf2_channel_entry_long*> res;
 /// This is the payload, data!
 ttf2_daq_getdata data;
 int numberOfChannels;

 unsigned long totalNumber{0};
};

#endif // TTF2LOOPER_H
