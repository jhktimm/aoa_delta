#include <vector>
#include <iostream>
#include <string>
#include <cassert>
#include <sstream>
#include <iomanip>
#include <fstream>
#include <algorithm>


std::ostream & operator << (std::ostream & out, std::vector<float> const& obj) {
    auto s = obj.size();
    out.write((char *)(&s), sizeof(s));
    for ( auto o : obj) out.write(reinterpret_cast<char *>(&o), sizeof(o));
    return out;
}

std::istream & operator >> (std::istream & in, std::vector<float> & obj) {
    auto s = obj.size();
    in.read((char*)&s, sizeof(s));
    obj.resize(s);
    for ( auto &o : obj) in.read((char*)&o, sizeof(o));
    return in;
}
    
    
class doocs_snapdaq_data_channel
{
public:
    std::string doocschannel;
    std::string section;
    std::string station;
    std::string type;    
    float delay;
    float filling;
    float flattop;
    float fs;
    float f0;   
    std::vector<float> forward_signal;
    std::vector<float> forward_phase;
    std::vector<float> reflected_signal;
    std::vector<float> reflected_phase;
    std::vector<float> probe_signal;
    std::vector<float> probe_phase;
    
    bool operator==(const doocs_snapdaq_data_channel & obj) const {
        return (doocschannel == obj.doocschannel) 
        && (section == obj.section) 
        && (station == obj.station) 
        && (type == obj.type) 
        && (delay == obj.delay)
        && (filling == obj.filling)
        && (flattop == obj.flattop)
        && (fs == obj.fs)
        && (f0 == obj.f0)
        && (forward_signal == obj.forward_signal) 
        && (forward_phase == obj.forward_phase) 
        && (reflected_signal == obj.reflected_signal) 
        && (reflected_phase == obj.reflected_phase) 
        && (probe_signal == obj.probe_signal) 
        && (probe_phase == obj.probe_phase) ;
    }
    
    friend std::ostream & operator << (std::ostream & out, const doocs_snapdaq_data_channel & obj) {
        
        auto s = obj.doocschannel.size();
        out.write((char *)(&s), sizeof(s));
        out << obj.doocschannel;
        s = obj.section.size();
        out.write((char *)(&s), sizeof(s));
        out << obj.section;
        s = obj.station.size();
        out.write((char *)(&s), sizeof(s));
        out << obj.station;
        s = obj.type.size();
        out.write((char *)(&s), sizeof(s));
        out << obj.type;
        out.write((char *)(&obj.delay), sizeof(float));
        out.write((char *)(&obj.filling), sizeof(float));
        out.write((char *)(&obj.flattop), sizeof(float));
        out.write((char *)(&obj.fs), sizeof(float));
        out.write((char *)(&obj.f0), sizeof(float));
        out << obj.forward_signal
            << obj.forward_phase
            << obj.reflected_signal
            << obj.reflected_phase
            << obj.probe_signal
            << obj.probe_phase;    
        return out;
    }    
    friend std::istream & operator >> (std::istream & in, doocs_snapdaq_data_channel & obj) {
        auto s = obj.doocschannel.size();
        in.read((char*)&s, sizeof(s));
        obj.doocschannel.resize(s);
        for ( auto &o : obj.doocschannel ) in >> o;
        s = obj.section.size();
        in.read((char*)&s, sizeof(s));
        obj.section.resize(s);
        for ( auto &o : obj.section ) in >> o;
        s = obj.station.size();
        in.read((char*)&s, sizeof(s));
        obj.station.resize(s);
        for ( auto &o : obj.station ) in >> o;
        s = obj.type.size();
        in.read((char*)&s, sizeof(s));
        obj.type.resize(s);
        for ( auto &o : obj.type ) in >> o;
        in.read((char*)&obj.delay, sizeof(obj.delay));
        in.read((char*)&obj.filling, sizeof(obj.filling));
        in.read((char*)&obj.flattop, sizeof(obj.flattop));
        in.read((char*)&obj.fs, sizeof(obj.fs));
        in.read((char*)&obj.f0, sizeof(obj.f0));
        in >> obj.forward_signal
           >> obj.forward_phase
           >> obj.reflected_signal
           >> obj.reflected_phase
           >> obj.probe_signal
           >> obj.probe_phase;    
        return in;
    }
    
        
    friend std::ostream & operator << (std::ostream & out, const std::vector<doocs_snapdaq_data_channel>& obj) {
        auto s = obj.size();
        out.write((char *)(&s), sizeof(s));
        for ( auto o : obj) out << o;
        return out;
    }    
    friend std::istream & operator >> (std::istream & in, std::vector<doocs_snapdaq_data_channel>& obj) {
        auto s = obj.size();
        in.read((char*)&s, sizeof(s));        
        obj.resize(s);
        for ( auto &o : obj) in >> o;
        return in;
    }

};

class macro_pulse
{
public:
    int pid;    
    double time;
    std::string str;
    std::vector<doocs_snapdaq_data_channel> channel;

    bool operator==(const macro_pulse & obj) {
        return (pid == obj.pid) 
        && (time == obj.time) 
        && (str == obj.str)
        && (channel == obj.channel) ;
    }
    
    
    friend std::ostream & operator << (std::ostream & out, const macro_pulse & obj) {    
        out.write((char *) (&obj.pid), sizeof(int));
        out.write((char *)(&obj.time), sizeof(double));
        auto s = obj.str.size();
        out.write((char *)(&s), sizeof(s));
        out << obj.str;
        s = obj.channel.size();
        out.write((char *)(&s), sizeof(s));
        for ( auto o : obj.channel )  out << o;
        return out;
    }    
    friend std::istream & operator >> (std::istream & in, macro_pulse & obj) {    
        in.read((char*)&obj.pid, sizeof(obj.pid));
        in.read((char*)&obj.time, sizeof(obj.time));
        auto s = obj.str.size();
        in.read((char*)&s, sizeof(s));
        obj.str.resize(s);
        for ( auto &o : obj.str ) in >> o;
        s = obj.channel.size();
        in.read((char*)&s, sizeof(s));
        obj.channel.resize(s);
        for ( auto &o : obj.channel ) in >> o;
        return in;
    }
    
    friend std::ostream & operator << (std::ostream & out, const std::vector<macro_pulse>& obj) {
        auto s = obj.size();
        out.write((char*) &s, sizeof(s));
        for ( auto o : obj) out << o;
        return out;
    }    
    friend std::istream & operator >> (std::istream & in, std::vector<macro_pulse> & obj) {
        auto s = obj.size();
        in.read((char*) &s, sizeof(s));
        obj.resize(s);
        for ( auto &o : obj ) in >> o;
        return in;
    }
    
    void print() {
        std::cout << "\n";
        std::cout << "**********************************************************************************\n";
//         std::cout << "sizeof_this(): " << this->sizeof_this() << "\n";
        std::cout << "pid: " << this->pid << " time: " << std::setprecision(16) << this->time  << " str: " << this->str <<"\n";
        std::cout << "size(): " << this->channel.size() << "\n"; 
        std::cout << std::setprecision(15) ;
        for ( auto ch : this->channel ) {
            std::cout << "--------------------------------------------------\n";
            std::cout << "doocschannel: " << ch.doocschannel << "\n"; 
            std::cout << "section: " << ch.section << " station: " << ch.station << " type: " << ch.type << "\n";
            std::cout << "probe_signal:\n";
            for ( auto x : ch.probe_signal ) std::cout << x << " ";
            std::cout << "\n";
            std::cout << "probe_phase:\n";
            for ( auto x : ch.probe_phase ) std::cout << x << " ";
            std::cout << "\n";
            std::cout << "forward_signal:\n";
            for ( auto x : ch.forward_signal ) std::cout << x << " ";
            std::cout << "\n";
            std::cout << "forward_phase:\n";
            for ( auto x : ch.forward_phase ) std::cout << x << " ";
            std::cout << "\n";
            std::cout << "reflected_signal:\n";
            for ( auto x : ch.reflected_signal ) std::cout << x << " ";
            std::cout << "\n";
            std::cout << "reflected_phase:\n";
            for ( auto x : ch.reflected_phase ) std::cout << x << " ";
            std::cout << "\n";
        }
        std::cout << "\n";
        std::cout << "\n";
        std::cout << "\n";
    }
};


class aoa_daq_datasclass
{
public:
	std::vector<macro_pulse> mps;
	
	aoa_daq_datasclass() {}
	aoa_daq_datasclass(std::string filename) {
			//~ this->appread(filename);
			this->read(filename);
		}
	~aoa_daq_datasclass() {}

    friend std::ostream & operator << (std::ostream & out, const aoa_daq_datasclass& obj) {
        auto s = obj.mps.size();
        out.write((char*) &s, sizeof(s));
        for ( auto o : obj.mps) out << o;
        return out;
    }    
    friend std::istream & operator >> (std::istream & in, aoa_daq_datasclass & obj) {
        auto s = obj.mps.size();
        in.read((char*) &s, sizeof(s));
        obj.mps.resize(s);
        for ( auto &o : obj.mps ) in >> o;
        return in;
    }
    
    void appread(std::string filename) {
		std::ifstream file_in(filename, std::ifstream::binary);
		while (!file_in.eof()) {
			aoa_daq_datasclass mp_tmp;
			file_in >> mp_tmp;
			//~ std::insert(this->mps.end(), mp_tmp.mps.cbegin(), mp_tmp.mps.cend());
			for (auto x : mp_tmp.mps) this->mps.push_back(x);
			//~ file_in >> *this;			
		}
		
		file_in.close();
	}
    
    void read(std::string filename) {
		std::ifstream file_in(filename, std::ifstream::binary);
		file_in >> *this;
		file_in.close();
	}
	
	void write(std::string filename) {
		std::ofstream file_out(filename, std::ofstream::binary);
		file_out << *this;
		file_out.close();
	}
	
	void appwrite(std::string filename) {
		std::ofstream file_out(filename, std::ofstream::app | std::ofstream::binary);
		file_out << *this;
		file_out.close();
	}
	
	void parser(std::string filename) {
		
	std::vector<macro_pulse>* macro_pulses = new std::vector<macro_pulse>;
    std::ifstream fs;
	fs.open(filename, std::ifstream::in);

        
    std::string zeile;// event, macro pulse, pid
    std::string channels;
    std::string headerstr;
    std::string eventtype;
    std::string wort;
    std::string value;

    char zdelim = '\n';//to separate macropulses every line
    char channel_delim = '{';// to separate event: eventheader { channel 0 data} { channel 1 data} {...}
//    char sdelim = '\t';//to separate event header: pid \t time \t date
    char et_delim = ':';//Event Type = et; to separate signal, phase je forwar, refected and probe
    char wdelim = ' ';// to separate samples, single vaules
    char trashdelim = ']';// to separate vaules trash
    
    int max_samples = 0;
    int max_channels = 0;
    int max_mevents = 0;
    double dvalue;
    
    int wortnummer = 0;
    int eventtypenumber = 0;
    int channelnummer = 0;
    int zeilennummer = 0;
    int trashnummer = 0;
    while (zeilennummer < 2) {
        getline(fs,zeile,zdelim);
//         std::cout << "zeile[" << zeilennummer << "]: " << zeile << "\n";
        std::stringstream szeile(zeile);
        channelnummer = 0;
        while (getline(szeile,channels,channel_delim)) {
            if (channelnummer == 0) {//Event Macro Pulse Header
                std::stringstream seventheader(channels);
            } else {//Event Macro Pulse Data
                std::stringstream seventtype(channels);
                while (getline(seventtype,eventtype,et_delim)) {
                    std::stringstream swort(eventtype);
                    wortnummer = 0;
                    while (getline(swort,wort,wdelim)) {
                        std::stringstream svalue(wort);
                        trashnummer = 0;
                        while (getline(svalue,value,trashdelim)) {
                            std::string::size_type sz;
                            try {
                                dvalue = std::stod (value,&sz);
                                trashnummer = 0;
                            } catch (const std::invalid_argument& ia) {
                                trashnummer++;
                            }
                            trashnummer++;
                        }
                        if ( wortnummer > max_samples) max_samples = wortnummer;
                        wortnummer++;
                    }
                }
            }
            if ( channelnummer > max_channels) max_channels = channelnummer;
            channelnummer++;
        }
        zeilennummer++;
    }
    std::cout << " max_samples: " << max_samples <<  " max_channels: " << max_channels << "\n";

    fs.seekg (0, fs.beg);
    
    int time_in_sec = 0;
    int time_in_nsec = 0;
    double time = 0.;
    wortnummer = 0;
    eventtypenumber = 0;
    channelnummer = 0;
    zeilennummer = 0;
    trashnummer = 0;
    int headernumber = 0;
    int pidheadernumber = 0;

    std::vector<doocs_snapdaq_data_channel> *header_channel_vec = new  std::vector<doocs_snapdaq_data_channel>;
    doocs_snapdaq_data_channel* header_channel = new doocs_snapdaq_data_channel();
    macro_pulse* mp_header = new macro_pulse();   
    
    while (getline(fs,zeile,zdelim)) {
//         std::cout << "zeile[" << zeilennummer << "]: " << zeile << "\n";
        std::stringstream szeile(zeile);
        channelnummer = 0;
        macro_pulse* mp = new macro_pulse();
        while (getline(szeile,channels,channel_delim)) {
//             std::cout << "zeile[" << zeilennummer <<"."<< channelnummer <<"."<< eventtypenumber <<"."<< wortnummer <<"."<< trashnummer <<"]\n";
            if ( channelnummer == 0 ){//Event Macro Pulse Header
                if ( (zeilennummer == 0) ){//DOOCs Channels
                    std::stringstream seventheader(channels);
//                     std::cout << "DOOCs Channels \n";
//                     std::cout << "channelnummer[" << channelnummer << "]: " << channels << "\n";   
                    headernumber = 0;
                    while (getline(seventheader,headerstr,'\t')) {
                        std::stringstream schannelstr(headerstr);
                        if (headernumber > 3) {
                            header_channel->doocschannel = headerstr;
                            std::string channelstr;
                            getline(schannelstr,channelstr,'/');
                            getline(schannelstr,channelstr,'/');
                            getline(schannelstr,channelstr,'/');
//                             std::cout << "headerstr[" << headernumber << "]: " << headerstr <<  "\n";      
//                             std::cout << "channelstr[" << headernumber << "]: " << channelstr <<  "\n";
                            std::stringstream splacestr(channelstr);
                            std::string placestr[4];
                            for (int i = 0; i< 4; i++) {
                                getline(splacestr, placestr[i],'.');
//                                 std::cout << i << ": "<< placestr[i] << "\n";
                            }
                            if (placestr[3] == "" ) {
//                                 std::cout << "1place: " << placestr[0] <<"  "<< placestr[1]<<"  "<< placestr[2] << "\n";
                                header_channel->section = placestr[2];
                                header_channel->station = placestr[1];
                                header_channel->type = placestr[0];
                            } else {
//                                 std::cout << "2place: " << placestr[0] <<"."<< placestr[1] <<"  "<< placestr[2]<<"  "<< placestr[3] << "\n";
				std::string tmp_str = placestr[0] + "." + placestr[1];
                                header_channel->section = placestr[3];
                                header_channel->station = placestr[2];
                                header_channel->type = placestr[0] + "." + placestr[1];
                            }
                        header_channel_vec->push_back(*header_channel);
                        }
                        headernumber++;
                    }
                }
                if (zeilennummer > 0) {
//                     std::cout << "Macro Event Header \n";
//                     std::cout << "channelnummer[" << channelnummer << "]: " << channels << "\n";
                    std::stringstream seventheader(channels);
                    pidheadernumber = 0;
                    while (getline(seventheader,headerstr,'\t')) {
//                         std::cout << "headerstr[" << pidheadernumber << "]: " << headerstr <<  "\n";
                        std::stringstream spid_str(headerstr);
                        if (pidheadernumber == 0) {
                            std::string pis_str_tmp;
                            getline(spid_str,pis_str_tmp,']');
//                             getline(spid_str,pis_str_tmp,']');
                            pis_str_tmp.erase(0,1);
//                             std::cout << "der komische string: " << pis_str_tmp <<  "\n";
                            mp_header->str = pis_str_tmp;
                            getline(spid_str,pis_str_tmp,']');
                            mp_header->pid = stoi(pis_str_tmp);
//                             std::cout << "PID: " << mp_header->pid <<  "\n";
                        }
                        if (pidheadernumber == 2) {
                            std::string pis_str_tmp;
                            getline(spid_str,pis_str_tmp,':');
//                             std::cout << "time[s]: " << pis_str_tmp <<  "\n";
                            std::string::size_type sz;
                            time_in_sec = std::stod (pis_str_tmp,&sz);
                            getline(spid_str,pis_str_tmp,':');
                            time_in_nsec = std::stod (pis_str_tmp,&sz);
                            time = (double) time_in_sec + (double) time_in_nsec/1000000;
//                             std::cout << "time[ns]: " << pis_str_tmp <<  "\n";
                            mp_header->time = time;
//                             std::cout << "time: " << std::setprecision(16) << mp_header->time <<  "\n";
                        }                        
//                         std::cout << "pis_str_tmp[" << pidheadernumber << "]: " << pis_str_tmp <<  "\n";
                        pidheadernumber++;
                    }
                }
            } else {//Event Macro Pulse Data
                doocs_snapdaq_data_channel* data_channel = new doocs_snapdaq_data_channel();
                std::stringstream seventtype(channels);
                eventtypenumber = 0;
                while (getline(seventtype,eventtype,et_delim)) {
                    std::stringstream swort(eventtype);
                    wortnummer = 0;
                    while (getline(swort,wort,wdelim)) {
                        std::stringstream svalue(wort);
                        trashnummer = 0;
                        while (getline(svalue,value,trashdelim)) {
                            std::string::size_type sz;
                            try {
                                dvalue = std::stod (value,&sz);
                                trashnummer = 0;
                            } catch (const std::invalid_argument& ia) {
                                dvalue = -666.666;
                                trashnummer++;
                            }
                            if (trashnummer==0) {
//                                     fdata[zeilennummer - 1][channelnummer - 1][eventtypenumber - 1][wortnummer]=dvalue;
//                                 ddd_e[1 - 1]->channel[1 - 1].trace[1 - 1][0] = dvalue;
//                                 ddd_e[zeilennummer - 1].channel[channelnummer - 1].trace[eventtypenumber - 1][wortnummer] = dvalue;
//                                 if (eventtypenumber==1) data_channel.forward_signal.push_back(dvalue);
                                if (eventtypenumber==1) data_channel->probe_signal.push_back(dvalue);
                                if (eventtypenumber==2) data_channel->probe_phase.push_back(dvalue);
                                if (eventtypenumber==3) data_channel->forward_signal.push_back(dvalue);
                                if (eventtypenumber==4) data_channel->forward_phase.push_back(dvalue);
                                if (eventtypenumber==5) data_channel->reflected_signal.push_back(dvalue);
                                if (eventtypenumber==6) data_channel->reflected_phase.push_back(dvalue);
//                             std::cout << "zeile[" << zeilennummer <<"."<< channelnummer <<"."<< eventtypenumber <<"."<< wortnummer <<"."<< trashnummer <<"]: "<< dvalue <<" :\t "<<value<< "\n";
                            }
                            trashnummer++;
                        }
                        wortnummer++;
                    }
                    eventtypenumber++;
                }
//                 std::cout << channelnummer << std::endl;
//                 std::cout << header_channel_vec->size() << std::endl;
                data_channel->doocschannel = header_channel_vec->at(channelnummer - 1).doocschannel;
                data_channel->section = header_channel_vec->at(channelnummer - 1).section;
                data_channel->station = header_channel_vec->at(channelnummer - 1).station;
                data_channel->type = header_channel_vec->at(channelnummer - 1).type;
//                 mp->channel.push_back(data_channel);
                mp->channel.push_back(*data_channel);
                delete data_channel;
            }
            channelnummer++;
        }
        mp->pid = mp_header->pid;
        mp->time = mp_header->time;
        mp->str = mp_header->str;
        if (zeilennummer != 0) macro_pulses->push_back(*mp);
        delete mp;
        if ( zeilennummer > max_mevents) max_mevents = zeilennummer;
        zeilennummer++;
    }
    std::cout <<  "max_mevents: " << max_mevents << "\n";

    fs.close();
    //~ doocs_snapdaq_llrf_dataclass* mpd_out = new doocs_snapdaq_llrf_dataclass;

    for (auto &in : *macro_pulses) this->mps.push_back(in);
    //~ for (auto &in : *macro_pulses) mpd_out->mps.push_back(in);
    //~ mpd_out->write("test2.bit");


	}
	
};

