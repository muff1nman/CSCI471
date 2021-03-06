#ifndef __dns_config_h__
#define __dns_config_h__

#cmakedefine DAEMON_DEBUG 

#cmakedefine PROJECT_NAME "${CMAKE_PROJECT_NAME}"

#define LISTEN_PORT 16318

// LS stands for Long and Short
#define HELP_OPTION "help"
#define HELP_OPTION_LS "help,h"
#define NAME_OPTION "name"
#define NAME_OPTION_LS "name,n"
#define QUERY_OPTION "query"
#define QUERY_OPTION_LS "query,q"
#define TYPE_OPTION "type"
#define TYPE_OPTION_LS "type,t"
#define DAEMON_OPTION "daemon"
#define DAEMON_OPTION_LS "daemon,f"
#define PORT_OPTION "port"
#define PORT_OPTION_LS "port,p"
#define LOG_LEVEL_OPTION "log-level"
#define LOG_LEVEL_OPTION_LS "log-level,l"
#define DEBUG_OPTION "debug"
#define DEBUG_OPTION_LS "debug,d"

#define TIMEOUT_IN_USEC 100
#define TIMEOUT_IN_SEC 3

#define DNS_PORT 53

#define DNSMUNCHER_SEND_PORT 16318

#endif /* !__dns_config_h__ */
