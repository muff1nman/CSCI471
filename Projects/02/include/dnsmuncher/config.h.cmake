#ifndef __config_h__
#define __config_h__

#cmakedefine DEBUG
#cmakedefine LOGGING

#cmakedefine OLDBOOST

#define LISTEN_PORT 16318

#cmakedefine PROJECT_NAME "${CMAKE_PROJECT_NAME}"

#define HELP_OPTION "help"
#define NAME_OPTION "name"
#define QUERY_OPTION "query"
#define TYPE_OPTION "type"
#define LOG_LEVEL_OPTION "log-level"

#define TEST_LOG_LEVEL 0

#define TIMEOUT_IN_USEC 100
#define TIMEOUT_IN_SEC 3


#endif /* !__config_h__ */
