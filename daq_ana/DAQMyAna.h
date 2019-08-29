
#ifndef DAQMYANA_H
#define DAQMYANA_H

#include "../include/myana.h"

#include <ttf2_daq_reader_2010.h>
#include <daq_server_util_def.h>
#include <ttf2_daq_data.h>

struct DAQMyAna : public MyAna {

    using MyAna::MyAna;
    using MyAna::setData;

    void setData(ttf2_daq_getdata* data, uint samples){
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
        std::getline(ststChannelName,strFacility,'/');
        std::getline(ststChannelName,strDevice,'/');
        std::getline(ststChannelName,strLocation,'/');
        //~ getline(ststChannelName,strProperty,'/');

        this->name = strLocation;

        std::stringstream strstream_name(this->name);//C1.M1.A20.L3
        std::string C_str, M_str, A_str, L_str;
        std::getline(strstream_name, C_str, '.');
        std::getline(strstream_name, M_str, '.');
        std::getline(strstream_name, A_str, '.');
        std::getline(strstream_name, L_str, '.');
//        this->channel.section = M_str + '.' + L_str;
//        this->channel.station = A_str;
//        this->channel.type = C_str;

        //~ std::cout << strFacility << " " <<  strDevice << " " <<  strLocation << " " <<  C_str << " " <<  M_str << " " <<  A_str << " " <<  L_str ;

        ///-----
        ///main loop over numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
        int numberOfSubchannels;
        numberOfSubchannels = data->GetNmemb();
        /// numberOfSubchannels = # of subchennels: pp, ps, refl and forw ...
        pulse.clear();
        if (numberOfSubchannels == 6) {
          for (uint i = 0; i < samples; i++) {
//              for (uint i = 0; i < this->samples; i++) {
//            this->Probe_Ampl->data[i]  = data->GetSpectVal(0, i);
            pulse.push_back(data->GetSpectVal(0, i));
//            this->Probe_Phase->data[i] = data->GetSpectVal(1, i);
//            this->Forw_Ampl->data[i]   = data->GetSpectVal(2, i);
//            this->Forw_Phase->data[i]  = data->GetSpectVal(3, i);
//            this->Refl_Ampl->data[i]   = data->GetSpectVal(4, i);
//            this->Refl_Phase->data[i]  = data->GetSpectVal(5, i);
          }
        } else {
          std::cout << "error in set data from .raw files: not 6 subchannels found: " << numberOfSubchannels << " " << std::endl;
        }

        this->pid = evid;
        //~ this->TIME = tup;
        this->time = (double) tup + (double) tlow/1000000;
        this->delay       =  20;
        this->filling     =  750;
        this->flattop     =  650;
        //~ this->FS          =  9.027999878;
        this->fs          =  1;
//        this->f0          =  1300;
        //~ std::cout << "pid: " << this->PID << " time: " << std::setprecision(12)<< this->TIME << std::endl;
      }

    };

//}

#endif // DAQMYANA_H
