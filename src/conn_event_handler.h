/**
 * Copyright 2015 Comcast Cable Communications Management, LLC
 *
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
 *
 */
/**
 * @file conn_event_handler.h
 *
 * @description This header defines the event parameters for different connections.
 *
 */
#ifndef _CONN_EVENT_HANDLER_H_
#define _CONN_EVENT_HANDLER_H_

#include <stdlib.h>
#include <stdio.h>


/*----------------------------------------------------------------------------*/
/*                                   Macros                                   */
/*----------------------------------------------------------------------------*/


/*----------------------------------------------------------------------------*/
/*                             Function Prototypes                            */
/*----------------------------------------------------------------------------*/

#ifdef __cplusplus
extern "C" {
#endif

/*------------------------------------------------------------------------------*/
/*                              For Connection Types                            */
/*------------------------------------------------------------------------------*/

void onPingMiss();

void onConnectionOpen();

#ifdef __cplusplus
}
#endif

#endif
