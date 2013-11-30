/*
 * parser_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef PARSER_TYPES_H
#define PARSER_TYPES_H

#include <boost/function.hpp>
#include <boost/assign.hpp>
#include "networkmuncher/domain/all.h"
#include "networkmuncher/util/byte/parse_context.h"

typedef boost::function<ApplicationLayerProtocolMaybePtr(ParseContext&)> ApplicationParser;
typedef boost::function<TransportLayerProtocolMaybePtr(ParseContext&)> TransportParser;
typedef boost::function<NetworkLayerProtocolMaybePtr(ParseContext&)> NetworkParser;
typedef boost::function<LinkLayerProtocolMaybePtr(ParseContext&)> LinkParser;

typedef ApplicationLayerProtocolMaybePtr (&ApplicationParseFunction)(ParseContext&);
typedef TransportLayerProtocolMaybePtr (&TransportParseFunction)(ParseContext&);
typedef NetworkLayerProtocolMaybePtr (*NetworkParseFunction)(ParseContext&);
typedef LinkLayerProtocolMaybePtr (*LinkParseFunction)(ParseContext&);

#endif /* !PARSER_TYPES_H */

