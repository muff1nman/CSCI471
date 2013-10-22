#ifndef __config_h__
#define __config_h__

#cmakedefine DEBUG
#cmakedefine LOGGING

#cmakedefine CACHING

#cmakedefine OLDBOOST

#define LISTEN_PORT 16318

#cmakedefine PROJECT_NAME "${CMAKE_PROJECT_NAME}"

#define HELP_OPTION "help"
#define NAME_OPTION "name"
#define QUERY_OPTION "query"
#define TYPE_OPTION "type"
#define DAEMON_OPTION "daemon"
#define PORT_OPTION "port"
#define LOG_LEVEL_OPTION "log-level"
#define DEBUG_OPTION "debug"

#define TEST_LOG_LEVEL 0

#define TIMEOUT_IN_USEC 100
#define TIMEOUT_IN_SEC 3

#define DNS_PORT 53

#define DNSMUNCHER_SEND_PORT 16318

#endif /* !__config_h__ */
