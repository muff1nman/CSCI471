#ifndef __config_h__
#define __config_h__

#cmakedefine DEBUG
#cmakedefine LOGGING

#define LOG_LEVEL @LOG_LEVEL@

#cmakedefine OLDBOOST

#define HOST_POSITION 1
#define SERVER_POSITION 2

#define LISTEN_PORT 16318

#cmakedefine PROJECT_NAME "${CMAKE_PROJECT_NAME}"

#endif /* !__config_h__ */
