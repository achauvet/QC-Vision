#include <ansi_c.h>
#include <cvinetv.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "global.h"  
#include "ERG.h" 
#include <NIDAQmx.h>
#include <DAQmxIOctrl.h>
TaskHandle taskHandle;
TaskHandle init_DAQ(void);  

/*********************************************/
// DAQmx Read Code
/*********************************************/

  
TaskHandle init_DAQ(void)
{
	char buffer[128];
	int value;
	DAQmxCreateTask("", &taskHandle);
	DAQmxCreateAIVoltageChan (taskHandle, "Dev1/ai0", "Tension", DAQmx_Val_Cfg_Default, -5, 5, DAQmx_Val_Volts, NULL);

	// External Trigger setting to restore for actual operation
	DAQmxCfgSampClkTiming (taskHandle, "PFI0", 1, DAQmx_Val_Rising, DAQmx_Val_HWTimedSinglePoint, 1);
	return taskHandle;
}


void readDAQ(void)
{
	int status=0;
	int32 numRead;
	Clear1D (channel_data, 1);

	DAQmxStartTask(taskHandle);
	DAQmxReadAnalogF64 (taskHandle, 1, 20.0, DAQmx_Val_GroupByChannel, channel_data, 1, &numRead, NULL);
	DAQmxStopTask(taskHandle);

	while (status != 0)
	{
		printf("DAQ error:%i numRead:%i\n", status, numRead);
		// try once more
		DAQmxStartTask(taskHandle);
		status = DAQmxReadAnalogF64(taskHandle, 1, 20.0,DAQmx_Val_GroupByChannel, channel_data, 1, &numRead,NULL);
		DAQmxStopTask(taskHandle);
	}
}
