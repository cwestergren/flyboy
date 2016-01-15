#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

#include "uart.h"
#include "cli/cli.h"
#include "types.h"
#include "log.h"
#include "leds.h"

osThreadId defaultTaskHandle;

//extern uint32 stopModeEntrys;


void StartDefaultTask(void const *argument)
{
	leds_init();

	for(;;) {
		led_toggle();
		osDelay(100);
	}
}

void CAOS_OutputDebugString(const char *pzStr) {
	uart_puts(pzStr);
}

int main(void) {

	osThreadDef(defaultTask, StartDefaultTask, osPriorityNormal, 0, 256);
	defaultTaskHandle = osThreadCreate(osThread(defaultTask), NULL);

	osKernelStart();

  	// Should never reach this..
	for(;;);

	return 0;
}
