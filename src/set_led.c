
#include "platform_hal.h"
#include "set_led.h"


int ParodusSetLed(int color, int state, int interval)
{
    LEDMGMT_PARAMS ledMgmt;
    memset(&ledMgmt, 0, sizeof(LEDMGMT_PARAMS));

	ledMgmt.LedColor = color;
	ledMgmt.State	 = state;
	ledMgmt.Interval = interval;
#if defined(_XB6_PRODUCT_REQ_)
	if(RETURN_ERR == platform_hal_setLed(&ledMgmt)) {
		ParodusError("platform_hal_setLed failed\n");
		return 1;
	}
#endif
    return 0;	
}
