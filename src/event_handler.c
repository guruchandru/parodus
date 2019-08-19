/*
 * If not stated otherwise in this file or this component's Licenses.txt file the
 * following copyright and licenses apply:
 *
 * Copyright 2016 RDK Management
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 * http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
*/

/**********************************************************************
   Copyright [2014] [Cisco Systems, Inc.]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
**********************************************************************/

#include "parodus_log.h"
#include "event_handler.h"
#include "connection.h"
#include "heartBeat.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
//#include <sysevent/sysevent.h>
#include "time.h"
#include "close_retry.h"

static pthread_t sysevent_tid;
//static int sysevent_fd;
//static token_t sysevent_token;

static void *parodus_event_handler ()
{
	ParodusInfo("parodus_event_handler thread started\n");

	pthread_detach(pthread_self());

	for (;;)
    {   
        char var[6];
        FILE *file;
		
                
		file = fopen("/sys/class/net/wlan0/operstate","r");
	        while(fgets(var, sizeof(var), file)!=NULL)
	        //ParodusInfo("Wan-status =%s\n",var);
	        fclose(file);
                
                //if(!get_interface_down_event() && (strncmp("up",var,2)!=0))
		   //sleep(90);
	       
	        if(strncmp("up",var,2)==0)
		{
                   if(get_interface_down_event())
		   {
		       ParodusInfo("Received wan-started event, Close the connection and retry again \n");
		       reset_interface_down_event();
		       ParodusInfo("Interface_down_event is reset\n");
		       resume_heartBeatTimer();
		       set_close_retry();
		   }
		   
                }
	        else if(!get_interface_down_event() && (strncmp("down",var,4)==0))
                {
		   ParodusInfo("wan is down not retrying ping");
		   //ParodusInfo("Received wan-stop event, Close the connection\n");
		   set_global_reconnect_reason("wan_down");
		   set_global_reconnect_status(true);
		   /* The wan-stop event should close the connection but shouldn't retry ,
		      inorder to avoid that interface_down_event flag is set 
                   */
	  	   set_interface_down_event();
		   ParodusInfo("Interface_down_event is set\n");				
		   close_and_unref_connection (get_global_conn());
		   set_global_conn(NULL);
		   pause_heartBeatTimer();
                }	
	

    } /* end for */
    return 0;
}

void EventHandler()
{
	
	
		pthread_create(&sysevent_tid, NULL, parodus_event_handler, NULL);

	return;
}
