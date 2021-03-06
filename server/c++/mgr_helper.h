/*
   collabREate mgr_helper.h
   Copyright (C) 2012 Chris Eagle <cseagle at gmail d0t com>
   Copyright (C) 2012 Tim Vidas <tvidas at gmail d0t com>

   This program is free software; you can redistribute it and/or modify it
   under the terms of the GNU General Public License as published by the Free
   Software Foundation; either version 2 of the License, or (at your option)
   any later version.

   This program is distributed in the hope that it will be useful, but WITHOUT
   ANY WARRANTY; without even the implied warranty of MERCHANTABILITY or
   FITNESS FOR A PARTICULAR PURPOSE. See the GNU General Public License for
   more details.

   You should have received a copy of the GNU General Public License along with
   this program; if not, write to the Free Software Foundation, Inc., 59 Temple
   Place, Suite 330, Boston, MA 02111-1307 USA
 */

#ifndef __MANAGER_HELPER_H
#define __MANAGER_HELPER_H

#include <map>
#include <string>

#include "utils.h"
#include "client.h"
#include "buffer.h"
#include "mgr_helper.h"

using namespace std;

class ConnectionManagerBase;

/**
 * ManagerHelper
 * This class is intented to facilitate getting current status information to
 * the ServerManager class.
 * @author Tim Vidas
 * @author Chris Eagle
 * @version 0.4.0, August 2012
 */

class ManagerHelper {
private:
   NetworkIO *nio;
   Tcp6Service *ss;
   map<string,string> *props;
   ConnectionManagerBase *cm;
   int pidForUpdates;

public:
   /**
    * very similary to the other constructor, execpt config paramters are attempted
    * to be read from a properties object p
    * @param connm the connectionManager associated with this ManagerHelper
    * @param p a propertied object (config file)
    */
   ManagerHelper(ConnectionManagerBase *connm, map<string,string> *p);

   /**
    * instantiates a new ManagerHelper with default parameters, the ManagerHelper
    * facilitates getting server state information to the ServerManager
    * @param connm the connectionManager associated with this ManagerHelper
    */
   ManagerHelper(ConnectionManagerBase *connm);

private:
   void initCommon();

   /**
    * send_data constructs the packet and sends it to the ServerManager
    * @param command the server command to send
    * @param data the data relevant to be sent with command
    */
   void send_data(int command, uint8_t *data, int dlen);

   /**
    * run kicks off a thread that perpetually waits for a single connection, if the connection is dropped
    * it waits again, once connected, the ManagerHelper processes commands similar to the server.
    */
   static void *run(void *arg);

   /**
    * closes the socket
    */
   void terminate();

   /**
    * logs a message to the configured log file (in the ConnectionManager)
    * @param msg the string to log
    * @param v apply a verbosity level to the msg
    */
   void log(const string &msg, int v = 0);

   /**
    * logs a message using log() (with newline)
    * @param msg the string to log
    * @param v apply a verbosity level to the msg
    */
   void logln(const string &msg, int v = 0);

public:
   void start();

};

#endif


