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

template <class ProtoPtr, class ParserType>
ProtoPtr parse_layer_with_parser( ParserType parser, ParseContext& context ) {
#ifdef LOGGING
	LOG(INFO) << "Begin parsing at: " << context.get_current_index();
#endif
	size_t saved_spot = context.get_current_index();
	ProtoPtr to_return = parser(context);
	if( !to_return ) {

#ifdef LOGGING
		LOG(WARNING) << "Reseting parse context";
#endif
		// reset parse context
		context.set_to_index(saved_spot);
	}

	return to_return;
}

template <class ProtoPtr, class ParserType>
ProtoPtr parse_layer(std::map<int, ParserType> parsers, ParseContext& context, ParseHint hint) {
	ProtoPtr to_return;
	if( hint.get_suggested_protocol() != PType::UNKNOWN ) {
		to_return = parse_layer_with_parser<ProtoPtr,ParserType>(parsers[hint.get_suggested_protocol()],context);
	} else {
		typedef typename std::map<int, ParserType>::const_iterator ParserIterator;
		ParserIterator i = parsers.begin();
		for(; i != parsers.end(); ++i ) {
			// Attempt parse
			ParserType current = i->second;
			to_return = parse_layer_with_parser<ProtoPtr,ParserType>(i->second,context);
			if(to_return)
				break;
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


	ParseHint hint(true);
	size_t before_processing_size;

	resultsC* results = (resultsC*)user;
	results->incrementPacketCount();

	BytesContainer bytes_from_packet( packet, packet + pkthdr->caplen );

	ParseContext parse( bytes_from_packet );

 	before_processing_size = parse.get_remaining();

#ifdef LOGGING
	LOG(INFO) << "\n" << demaria_util::to_string(parse);
#endif

	LinkLayerProtocolMaybePtr link = parse_layer<LinkLayerProtocolMaybePtr,LinkParser>(link_parsers,parse,false);

#ifdef LOGGING
	LOG(INFO) << "Offset after parsing link: " << parse.get_current_index();
#endif

	if(link) {
		hint = results->process(*link, before_processing_size);
	} else {
		hint = results->process(LinkLayerProtocolPtr(new LinkLayerProtocol()),0);
#ifdef LOGGING
		LOG(WARNING) << "could not parse link layer";
#endif
	}

	if( !hint.get_should_parse() ) {return;}

 	before_processing_size = parse.get_remaining();

	NetworkLayerProtocolMaybePtr net = parse_layer<NetworkLayerProtocolMaybePtr,NetworkParser>(network_parsers,parse,hint);

#ifdef LOGGING
	LOG(INFO) << "Offset after parsing network: " << parse.get_current_index();
#endif

	if(net) {
		hint = results->process(*net, before_processing_size);
	} else {
		hint = results->process(NetworkLayerProtocolPtr(new NetworkLayerProtocol()),0);
#ifdef LOGGING
		LOG(WARNING) << "Could not parse network layer";
#endif
	}

	if( !hint.get_should_parse() ) {return;}

 	before_processing_size = parse.get_remaining();

	TransportLayerProtocolMaybePtr trans = parse_layer<TransportLayerProtocolMaybePtr,TransportParser>(transport_parsers,parse, hint);

#ifdef LOGGING
	LOG(INFO) << "Offset after parsing transport: " << parse.get_current_index();
#endif

	if(trans) {
		hint = results->process(*trans,before_processing_size);
	} else {
		hint = results->process(TransportLayerProtocolPtr(new TransportLayerProtocol()),0);
#ifdef LOGGING
		LOG(WARNING) << "Could not parse transport layer";
#endif
	}

	// ignore this so that it isnt necessary to have a transport layer protocol?
	if( !hint.get_should_parse() ) {return;}	
 	before_processing_size = parse.get_remaining();

	ApplicationLayerProtocolMaybePtr app = parse_layer<ApplicationLayerProtocolMaybePtr,ApplicationParser>(application_parsers,parse,hint);

	if(app) {
		hint = results->process(*app,before_processing_size);
	} else {
		hint = results->process(ApplicationLayerProtocolPtr(new ApplicationLayerProtocol()),0);
#ifdef LOGGING
		LOG(WARNING) << "Could not parse application layer";
#endif
	}

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

	init_log(0,PROJECT_NAME);


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


