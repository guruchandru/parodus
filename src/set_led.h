#ifndef _SET_LED_H_
#define _SET_LED_H_

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"
#include <ctype.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/sysinfo.h>
#include <pthread.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <getopt.h>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>

#include <cJSON.h>
#include <nopoll.h>
#include <nanomsg/nn.h>
#include <nanomsg/pipeline.h>
#include <wrp-c.h>

#include "parodus_log.h"
#include "platform_hal.h"

/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/

/* For LED behavior */
#define WHITE 0
#define YELLOW 1
#define SOLID	0
#define BLINK	1
#define RED 3

/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*                              For LED_Blink                                   */
/*------------------------------------------------------------------------------*/
int ParodusSetLed(int color, int state, int interval);

#ifdef __cplusplus
}
#endif

#endif
