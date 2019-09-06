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
#include "config.h"
#include "heartBeat.h"
#include <stdlib.h>
#include <string.h>
#include <pthread.h>
#include <unistd.h>
//#include <sysevent/sysevent.h>
#include "time.h"
#include "close_retry.h"


/*
static pthread_t sysevent_tid;
static int sysevent_fd;
static token_t sysevent_token;


static void *parodus_sysevent_handler (void *data)
{
	ParodusInfo("parodus_sysevent_handler thread started\n");
	async_id_t conn_flush_id;
	async_id_t wan_status_id;
	sysevent_setnotification(sysevent_fd, sysevent_token, "firewall_flush_conntrack", &conn_flush_id);
	sysevent_setnotification(sysevent_fd, sysevent_token, "wan-status", &wan_status_id);
	time_t time_now = { 0 }, time_before = { 0 };

	pthread_detach(pthread_self());

	for (;;)
    {
        char name[25]={0};
		char val[42]={0};
        int namelen = sizeof(name);
        int vallen  = sizeof(val);
        int err;
        async_id_t getnotification_asyncid;
        err = sysevent_getnotification(sysevent_fd, sysevent_token, name, &namelen,  val, &vallen, &getnotification_asyncid);

        if (err)
        {
			*//* 
			   * Log should come for every 1hour 
			   * - time_now = getting current time 
			   * - difference between time now and previous time is greater than 
			   *	3600 seconds
			   * - time_before = getting current time as for next iteration 
			   *	checking		   
			   */ /*
			time(&time_now);
			
			if(LOGGING_INTERVAL_SECS <= ((unsigned int)difftime(time_now, time_before)))
			{
				ParodusError("%s-**********ERR: %d\n", __func__, err);
				time(&time_before);
			}

		   sleep(10);
        }
	else 
	{
		if (strcmp(name, "firewall_flush_conntrack")==0)
		{
			  int onFlush = atoi(val);
			  ParodusInfo("firewall_flush_conntrack value is %d \n",onFlush);
			  if(!onFlush) {
			  	                     
				if(strcmp(get_global_reconnect_reason(),"wan_down")==0){
				    ParodusInfo("Received firewall_flush_conntrack event,not closing the connection since interface is down\n");					
				}
				else{
				    ParodusInfo("Received firewall_flush_conntrack event,Close the connection and retry again\n");		
				    set_global_reconnect_reason("Firewall_Restart");
				    set_global_reconnect_status(true);
				    set_close_retry();
				}
				
			  } 		   
		} else if (strcmp(name, "wan-status")==0) {
			if (strcmp(val, "stopped")==0) {
				ParodusInfo("Received wan-stop event, Close the connection\n");
				set_global_reconnect_reason("wan_down");
				set_global_reconnect_status(true);
				*//* The wan-stop event should close the connection but shouldn't retry ,
				   inorder to avoid that interface_down_event flag is set 
                                *//*
			  	set_interface_down_event();
				ParodusInfo("Interface_down_event is set\n");				
				close_and_unref_connection (get_global_conn());
				set_global_conn(NULL);
                                pause_heartBeatTimer();

			} else if (strcmp(val, "started")==0) {
			  	ParodusInfo("Received wan-started event, Close the connection and retry again \n");
				reset_interface_down_event();
				ParodusInfo("Interface_down_event is reset\n");
				resume_heartBeatTimer();
				set_close_retry();
			}
		}
	}

    } *//* end for *//*
    return 0;
}

void EventHandler()
{
	sysevent_fd = sysevent_open("127.0.0.1", SE_SERVER_WELL_KNOWN_PORT, SE_VERSION, "parodus-connFlush", &sysevent_token);

	if (sysevent_fd >= 0)
	{
		pthread_create(&sysevent_tid, NULL, parodus_sysevent_handler, NULL);
	}
	return;
} */

void parodusOnPingStatusChangeHandler(char * status)
{	
	char cmd[128];
/*
	snprintf(cmd,40,"sysevent set ping_status %s", status);
	
	system(cmd);	
	ParodusInfo("sysevent set ping_status %s", status);
*/
	snprintf(cmd,14,"touch %s",status);
	ParodusInfo("touch %s",status);
}

void register_callback(parodusOnPingMissHandler ptr_reg_callback)
{                                                
	notifyCbFn =   ptr_reg_callback;
}                                       
