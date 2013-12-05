/*
 * domain.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef ICMP_DOMAIN_DOMAIN_H
#define ICMP_DOMAIN_DOMAIN_H

#include "echo_builder.h"
#include "raw.h"
#include "ptr_types.h"

#include <boost/optional.hpp>
#include <boost/shared_ptr.hpp>

typedef   boost::optional<Echo>      EchoMaybe;
typedef   boost::shared_ptr<Echo>    EchoPtr;
typedef   boost::optional<EchoPtr>   EchoMaybePtr;

typedef   boost::optional<Raw>       RawMaybe;
typedef   boost::shared_ptr<Raw>     RawPtr;
typedef   boost::optional<RawPtr>    RawMaybePtr;

#endif /* !ICMP_DOMAIN_DOMAIN_H */

