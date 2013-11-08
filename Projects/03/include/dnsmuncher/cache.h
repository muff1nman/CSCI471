/*
 * cache.h
 * Copyright (C) 2013 Andrew DeMaria (muff1nman) <ademaria@mines.edu>
 *
 * All Rights Reserved.
 */

#ifndef __cache_h__
#define __cache_h__

#ifdef CACHING

#include <vector>
#include <string>
#include <map>

#include "util/logging.h"
#include "dns.h"
#include "domain/dns_builder.h"
#include "domain/dns.h"

// TODO clean up file: put impl into its own cpp file

typedef std::map< std::string, DNS::ResourceList> DnsCache;

// TODO move this somewhere else
boost::optional<DNS::QuestionPtr> filter_first_question( DnsPtr query ) {
	boost::optional<DNS::QuestionPtr> question;
	DNS::QuestionList qs = query->get_questions();
	if( !qs.empty() ) {
		question = qs.at(0);
	}

	return question;
}

DnsPtr build_with_resources( DNS::ResourceList list ) {
	DNSBuilder b;
	b.
		is_response().
		answer_count(list.size());
	for( size_t i = 0; i < list.size(); ++i ) {
		b.add_resource( list.at(i) );
	}

	return b.build_ptr();
}

DnsMaybePtr get_from_cache( DnsCache& cache, DnsPtr query ) {
	DnsMaybePtr cached_value;
	boost::optional<DNS::QuestionPtr> question = filter_first_question( query );
	if( question ) {
		std::string query_name = (*question)->get_name().to_string();
		// TODO return copy instead?
		DnsCache::iterator key = cache.find( query_name );
		if( key != cache.end() ) {
			DNS::ResourceList as = cache[query_name];
#ifdef LOGGING
			LOG(WARNING) << "Returning cached response for: " << query_name;
#endif
			cached_value = build_with_resources( as );
		}
	}
	return cached_value;
}

void add_to_cache( DnsCache& cache, DnsPtr query, DnsPtr answer ) {
	DNS::QuestionList qs = query->get_questions();
	if( !qs.empty() ) {
		DNS::QuestionPtr question = qs.at(0);
		// only cache A records (rdatas cannot be copied for other records yet)
		if( question->get_type() == Type::A ) {
			std::string query_name = question->get_name().to_string();
#ifdef LOGGING
			LOG(WARNING) << "Caching response for: " << query_name;
#endif
			DNS::ResourceList as = answer->get_answers();
			cache[query_name] = as;
		}
	}
}

#endif /* CACHING */

#endif /* !__cache_h__ */

