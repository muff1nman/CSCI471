/*
 * ptr_types.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef DOMAIN_PTR_TYPES_H
#define DOMAIN_PTR_TYPES_H

#include "application_layer_protocol.h"
#include "link_layer_protocol.h"
#include "network_layer_protocol.h"
#include "transport_layer_protocol.h"

#include <boost/shared_ptr.hpp>
#include <boost/optional.hpp>

typedef boost::shared_ptr<Protocol> ProtocolPtr;
typedef boost::optional<ProtocolPtr> ProtocolMaybePtr;

typedef boost::shared_ptr<ApplicationLayerProtocol> ApplicationLayerProtocolPtr;
typedef boost::optional<ApplicationLayerProtocolPtr> ApplicationLayerProtocolMaybePtr;

typedef boost::shared_ptr<TransportLayerProtocol> TransportLayerProtocolPtr;
typedef boost::optional<TransportLayerProtocolPtr> TransportLayerProtocolMaybePtr;

typedef boost::shared_ptr<NetworkLayerProtocol> NetworkLayerProtocolPtr;
typedef boost::optional<NetworkLayerProtocolPtr> NetworkLayerProtocolMaybePtr;

typedef boost::shared_ptr<LinkLayerProtocol> LinkLayerProtocolPtr;
typedef boost::optional<LinkLayerProtocolPtr> LinkLayerProtocolMaybePtr;

#endif /* !DOMAIN_PTR_TYPES_H */

