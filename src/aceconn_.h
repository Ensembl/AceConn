/*  File: aceconn_.h
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
 * Description: Private header for C package for accessing the AceDB
 *              socket server.
 *              
 *              Functions that have external binding but are internal
 *              to this package all start "aceconn" to separate them
 *              from the interface functions that start "AceConn".
 * HISTORY:
 * Last edited: Sep  5 11:29 2003 (edgrif)
 * Created: Wed Mar  6 13:58:41 2002 (edgrif)
 * CVS info:   $Id: aceconn_.h,v 1.1 2007-10-03 13:28:00 edgrif Exp $
 *-------------------------------------------------------------------
 */
#ifndef DEF_ACECONN_P_H
#define DEF_ACECONN_P_H

#include <stdio.h>					    /* Needed for NULL surprisingly... */
#include <string.h>
#include <glib.h>					    /* Needed here for some basic types. */
#include <AceConnProto.h>
#include <AceConn.h>


/* Opaque handle to an message passed to server.                             */
typedef struct AceConnMsgRec *AceConnMsg ;


/* Connection can be in one of a number of states.                           */
typedef enum
{
  ACECONNSTATE_NONE,					    /* not connected at all to server. */
  ACECONNSTATE_OPEN,					    /* socket open. */
  ACECONNSTATE_READY					    /* connection ready for requests. */
} AceConnState ;


/* Holds all the data for a particular connection to the ace server.         */
typedef struct _AceConnRec
{
  char **valid ;					    /* Used for checking valid block. */

  AceConnState state ;

  /* Server details                                                          */
  char *host ;
  int  port ;
  int  socket ;
  int  timeout ;					    /* command timeout in secs. */

  /* User details                                                            */
  char *userid ;
  char *passwd ;
  char *passwd_hash ;
  char *nonce_hash ;

  /* Current request. */
  AceConnMsg msg ;

  /* Misc. */
  AceConnStatus last_err_status ;			    /* status describiing last error. */
  gchar *last_errmsg ;					    /* string describing last error. */


} AceConnRec ;


/* Basic creation/destruction of an AceConnRec.                              */
AceConnection aceconnCreate(char *server_netid, int server_port,
			    char *userid, char *passwd, int timeout) ;
void aceconnDestroy(AceConnection connection) ;


/* Server requests.                                                          */
AceConnStatus aceconnServerOpen(AceConnection connection) ;
AceConnStatus aceconnServerHandshake(AceConnection connection) ;
AceConnStatus aceconnServerRequest(AceConnection connection,
				   char *request, void **reply, int *reply_len) ;
AceConnStatus aceconnServerClose(AceConnection connection) ;


/* Utilities.                                                                */

gboolean aceconnIsValid(AceConnection connection) ;

/* Used to get simple string version of error status. */
char *aceconnGetSimpleErrMsg(AceConnStatus status) ;

/* Use to set an error message in the connection struct, application can     */
/* retrieve error message for display/logging etc.                           */
/* N.B. for simple strings do this:  aceconnSetErrMsg(conn, "%s", string) ;  */
void aceconnSetErrMsg(AceConnection connection, AceConnStatus status,
		      char *format, ...) ;
void aceconnFreeErrMsg(AceConnection connection) ;



#endif /* !defined DEF_ACECONN_P_H */
