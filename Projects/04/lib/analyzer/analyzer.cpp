//
//  project4.cpp
//  project4
//
//  Created by Phillip Romig on 4/3/12.
//  Copyright 2012 Colorado School of Mines. All rights reserved.
//

#include "analyzer.h"
#include <strings.h>
#include <string.h>
#include <stdlib.h>

#include "networkmuncher/domain/all.h"
#include "networkmuncher/util/byte/byte.h"
#include "networkmuncher/util/byte/print.h"
#include "networkmuncher/util/byte/parse_context.h"
#include "networkmuncher/util/logging.h"
#include "networkmuncher/parse/parsers.h"
#include "networkmuncher/parse/parser_types.h"

template <class ProtocolPtr, class ParserType>
ProtocolPtr parse_layer(std::vector<ParserType> parsers, ParseContext& context) {
	ProtocolPtr to_return;
	for( size_t i = 0; i < parsers.size(); ++i ) {
		// save context's spot
		ParseContext::ConstIterator saved_spot = context.current;

		// Attempt parse
		ParserType current = parsers.at(i);
		to_return = current(context);

		// Check if successful
		if( to_return ) {
			return to_return;
		} else {
			// reset parse context
			context.current = saved_spot;
		}
	}

	// unsuccessful
	return to_return;
}

// ****************************************************************************
// * pk_processor()
// *  Most of the work done by the program will be done here (or at least it
// *  it will originate here). The function will be called once for every 
// *  packet in the savefile.
// ****************************************************************************
void pk_processor(u_char *user, const struct pcap_pkthdr *pkthdr, const u_char *packet) {

  resultsC* results = (resultsC*)user;
  results->incrementPacketCount();

	BytesContainer bytes_from_packet( packet, packet + pkthdr->caplen );

	ParseContext parse( bytes_from_packet );

	LinkLayerProtocolMaybePtr link = parse_layer<LinkLayerProtocolMaybePtr,LinkParser>(link_parsers,parse);

	if(link) {
		// TODO count link
#ifdef LOGGING
		LOG(INFO) << "Successfully parsed link layer";		
#endif
	} else {
#ifdef LOGGING
		LOG(INFO) << "could not parse link layer";
#endif
		return;
	}

#ifdef LOGGING
	LOG(WARNING) << demaria_util::to_string(parse);
#endif

  return;
}


// ****************************************************************************
// * main()
// *  You should not have to worry about anything if you don't want to. 
// *  My code will open the file, initalize the results container class,
// *  call pk_processor() once for each packet and the finally call
// *  the displayResutls() method.
// ****************************************************************************
int main (int argc, const char * argv[])
{

  
  // **********************************************************************
  // * The program is called with a single argument, the name of the
  // * pcap save file to read.
  // **********************************************************************
  if (argc != 2) {
     std::cerr << "useage: project4 <filename>" << std::endl;
     exit(EXIT_FAILURE);
  }


  // **********************************************************************
  // * Instantiate the results class.  
  // **********************************************************************
  resultsC* results = new resultsC();



  // **********************************************************************
  // * Attempt to open the file.
  // **********************************************************************
  char errbuf[PCAP_ERRBUF_SIZE];
  pcap_t *PT;

  bzero(errbuf,PCAP_ERRBUF_SIZE);
  if ((PT = pcap_open_offline(argv[1],errbuf)) == NULL ) {
    std::cerr << "Unable to open pcap file: " << argv[1] << "\n"
         << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }

  if (strlen(errbuf) > 0)
    std::cerr << "Warning: pcap_open_offiline: " << pcap_geterr(PT) << std::endl;



  // **********************************************************************
  // * The dispatcher will call the packet processor once for packet
  // * in the capture file.
  // **********************************************************************
  int pk_count;
  if ((pk_count = pcap_dispatch(PT, -1, pk_processor, (u_char *)results)) < 0) {
    std::cerr << "Error calling dispatcher: " << pcap_geterr(PT) << std::endl;
    exit(EXIT_FAILURE);
  }
  std::cout << "Dispatcher processed " << pk_count << " packets." << std::endl;


  // **********************************************************************
  // * File your report here.
  // **********************************************************************
  results->displayResults();
  exit(EXIT_SUCCESS);
}


