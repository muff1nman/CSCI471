//
//  resultsC.h
//  Project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#ifndef analyzer_resultsC_h
#define analyzer_resultsC_h

#include "networkmuncher/domain/all.h"
#include "ethernet/domain/domain.h"
#include "icmp/domain/domain.h"
#include <boost/optional.hpp>

class resultsC {
  protected:
		size_t totalPacketCount;
		size_t ethernet_v2_count;
		size_t ethernet_8023;
		size_t other_network_count;
		size_t ip_count;
		boost::optional<size_t> ip_max_size;
		boost::optional<size_t> ip_min_size;
		void count_protocol(const Ethernetv2& ether);
		void count_protocol(const Ethernet8023& ether);
		void count_protocol(const Ip& ip);

  public:
   //resultsC() : 
		 //totalPacketCount(0),
		 //ethernet_v2_count(0),
		 //ethernet_8023(0) {}
   void incrementPacketCount() { totalPacketCount++; };
   void displayResults();
	 void count(const ProtocolPtr proto);
};

#endif
