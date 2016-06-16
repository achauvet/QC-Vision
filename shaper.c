#include <ansi_c.h>
#include <utility.h>
#include <analysis.h>
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

// hardware libraries
#include <NIDAQmx.h>
#include <DAQmxIOctrl.h>
//#include <gpib.h>
#include"global.h"
#include "slms640d_modified.h"   

// DAQ common parameters
uInt32 numChannels; 
TaskHandle taskHandle;
TaskHandle TriggerHandle;


// GPIB common parameters
#define	SET_DELAY	2   /* I reduced this, originally 2*/   
//GPIB_HANDLE mask1,mask2;
double signals[4];

// jenoptik
fuint64 guid; // this will store the name of the shaper


//int average;


/*-----------------------------------------------------------------------*/
void start_shaper(void)
{
   struct SLM_VersionInfo version[148];	

   int res;
   char *response=NULL;
   unsigned int real_size=0;
   fuint64 list_of_guids[128];
   int i=0;
   float temp;
   
   res=SLM_Init();
   if (res!=SLM_Ok)
      printf("Init problem:%i\n",res);
   
   res=SLM_FindDevices(128*2, (fuint32*)list_of_guids, &real_size);   
   if ((res!=SLM_Ok))
   printf("Find devices problem:%i\n",res);
   
   guid=list_of_guids[0];              //simply take the first one

   res=SLM_Connect(SLM_GUID(guid));
   if (res!=SLM_Ok)
   printf("Connect device problem:%i\n",res);

   
   res=SLM_InitModulator(SLM_GUID(guid));
   if (res!=SLM_Ok)
   printf("Init device problem:%i\n",res);
   
   res=SLM_SetHighVoltage(SLM_GUID(guid),SLM_DisplayA,0);
   if (res!=SLM_Ok)
   printf("Voltage problem:%i\n",res);

   res = send_masks(drive_level);
   if (res)
	   printf("Problem writing init flat mask to LCD...\n");
   
 return;
}


void stop_shaper()

{
	
   int res; 
   res=SLM_ExitModulator(SLM_GUID(guid)); 
   if (res!=SLM_Ok)
   printf("Exit problem:%i\n",res);

   SLM_Disconnect(SLM_GUID(guid));
   if (res!=SLM_Ok)
   printf("Disconnect problem:%i\n",res);

   SLM_Exit();
   
return;
}



/*-----------------------------------------------------------------------*/
int send_masks(unsigned int drive_level[])
{
	int i;
 	int res;
	

	
   res=SLM_DirectPattern(SLM_GUID(guid), 0, Npixel, drive_level); // check on the manual how it works with PiX / length    
   if (res!=SLM_Ok)
   printf("Fill problem:%i\n",res);
   
	return 0;
}
