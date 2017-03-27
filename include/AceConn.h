/*  File: AceConn.h
 *  Author: Ed Griffiths (edgrif@sanger.ac.uk)
 *  Copyright (c) 2002-2017: Genome Research Ltd.
 *-------------------------------------------------------------------
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 *-------------------------------------------------------------------
 * Description: Interface for communicating with the AceDB server.
 *              Currently the server is sockets based but this is not
 *              exposed in this interface.
 *              
 *              You should see AceConn.html for full details
 *              of the interface.
 *              
 * HISTORY:
 * Last edited: Oct  3 15:31 2007 (edgrif)
 * Created: Wed Mar  6 13:58:41 2002 (edgrif)
 * CVS info:   $Id: AceConn.h,v 1.2 2007-10-03 14:39:02 edgrif Exp $
 *-------------------------------------------------------------------
 */
#ifndef DEF_ACECONN_H
#define DEF_ACECONN_H

#ifdef __cplusplus
extern "C" {
#endif


#include <glib.h>

/* Library version stuff.                                                    */
#define     ACECONN_VERSION 1
#define     ACECONN_RELEASE 2
#define     ACECONN_UPDATE  0

#define ACECONN_CHECK_VERSION(version, release, update)    \
    (ACECONN_VERSION > (version) || \
     (ACECONN_VERSION == (version) && ACECONN_RELEASE > (release)) || \
     (ACECONN_VERSION == (version) && ACECONN_RELEASE == (release) && \
      ACECONN_UPDATE >= (update)))


/* Opaque handle to a connection to an Acedb socket server.                  */
typedef struct _AceConnRec *AceConnection ;

/* Return codes for the AceConn calls.                                       */
typedef enum {ACECONN_OK = 0,
	      ACECONN_QUIT,				    /* Command to server was "quit" so
							       connection is now closed. */
	      ACECONN_INVALIDCONN,			    /* Connection points to invalid memory. */
	      ACECONN_BADARGS,				    /* caller has supplied bad args. */
	      ACECONN_NOTOPEN,				    /* Connection not open. */
	      ACECONN_NOALLOC,				    /* could not allocate  */
	      ACECONN_NOSOCK,				    /* socket creation problem. */
	      ACECONN_UNKNOWNHOST,			    /* server host not known. */
	      ACECONN_NOCONNECT,			    /* Could not connect to host. */
	      ACECONN_NOSELECT,				    /* select on socket failed. */
	      ACECONN_HANDSHAKE,			    /* Handshake to server failed. */
	      ACECONN_READERROR,			    /* Error in reading from socket. */
	      ACECONN_WRITEERROR,			    /* Error in writing to socket. */
	      ACECONN_SIGSET,				    /* Problem with signal setting. */
	      ACECONN_NONBLOCK,				    /* Non-blocking for socket failed. */
	      ACECONN_TIMEDOUT,				    /* Connection timed out. */
	      ACECONN_NOCREATE,				    /* Could not create connection
							       control block. */
	      ACECONN_INTERNAL				    /* Dire, internal package error. */
} AceConnStatus ;


/* Default time (seconds) to wait for reply from server. */
enum {ACECONN_DEFAULT_TIMEOUT = 120} ;


/* Creates a connection struct. */
AceConnStatus AceConnCreate(AceConnection *connection, char *server_netid, int server_port,
			    char *userid, char *passwd, int timeout) ;


/* Open a connection to the database. */
AceConnStatus AceConnConnect(AceConnection connection) ;

/* Send a request to the database and get the reply. */
AceConnStatus AceConnRequest(AceConnection connection,
			     char *request,
			     void **reply, int *reply_len) ;

/* Close down the connection. */
AceConnStatus AceConnDisconnect(AceConnection connection) ;


/* Free the connection struct. */
void AceConnDestroy(AceConnection connection) ;



/* Utility functions.                                                        */
/*                                                                           */

void AceConnGetVersion(guint *version, guint *release, guint *update) ;

AceConnStatus AceConnSetTimeout(AceConnection connection, int timeout) ;

AceConnStatus AceConnConnectionOpen(AceConnection connection) ;


char *AceConnGetErrorMsg(AceConnection connection, AceConnStatus err_status) ;


/* Deprecated, use AceConnGetErrorMsg() instead. */
char *AceConnGetLastErrMsg(AceConnection connection) ;


#ifdef __cplusplus
}
#endif



#endif /* !defined DEF_ACECONN_H */
