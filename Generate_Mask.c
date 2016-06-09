#include "ERG.h"
#include <ansi_c.h>
#include <cvinetv.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "global.h" 
#include "Generate_Mask.h" 

FILE* IO_mask;

void set_levels(void)
{
	int i;
	
	GetActiveTabPage (Mask_pnl_handle, Mask_panel_TAB_function_type, &function_type);
	//Chirp Mask
	if (function_type==0)
	{   
		GetPanelHandleFromTabPage (Mask_pnl_handle, Mask_panel_TAB_function_type, 0, &function_type_handle);

		GetCtrlVal (function_type_handle,TAB_chirp_input_alpha,&alpha); //  The coefficient of Chirp   
		GetCtrlVal (function_type_handle,TAB_chirp_input_gamma,&gamma); //  To center the parabollic mask   
		GetCtrlVal (function_type_handle,TAB_chirp_input_delta,&delta); //  To avoid over-range values   

		for (i = 0; i < Npixel; i++)
		{
			phase[i]=alpha*(gamma-i)*(i-gamma)+delta+4*PI;   //   Parabollic function
			while (phase[i]<delta){				//   Do 4 Pi jumps
				phase[i]=phase[i]+4*PI; 		
				

			}
			//printf("%f\n",phase[i]);
			drive_level[i] = phase2voltage(phase[i]+2);
 
		}
		display_masks(drive_level);
		
	}

}

int phase2voltage(double phi)

{
	double voltage;
	double p[6];
	
	p[0] = -647.2 ;      
	p[1] =2957.6 ; //A1
	p[2] =2.49327  ; //x0
	p[3] =0.54902  ; //tau1
	p[4] =1519.3 ; //A2
	p[5] =24.874  ; //tau2
	
	
	voltage=p[0]+p[1]*exp(-(phi-p[2])/p[3])+p[4]*exp(-(phi-p[2])/p[5]);
	if (voltage>4096) 
	{
	voltage=4096;
	}
	if (voltage<0) 
	{
	voltage=0;
	}
	return voltage;
}

int CVICALLBACK generate_mask (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			if ((Mask_pnl_handle = LoadPanel (0, "generate_mask.uir", Mask_panel)) < 0)
			return -1;
	
			DisplayPanel (Mask_pnl_handle );  
			RunUserInterface ();
			DiscardPanel (Mask_pnl_handle );
			break;
	}
	return 0;
}

int CVICALLBACK visualize_mask (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			set_levels();
			break;
	}
	return 0;
}

int CVICALLBACK save_mask (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			
			GetCtrlVal (Mask_pnl_handle, Mask_panel_mask_name_field, mask_name);
			sprintf(file,"%s\\mask_%s.msk",mask_path,mask_name);
			IO_mask = fopen (file, "w");
			
			for (i=0; i<Npixel; i++)
                {
                    fprintf(IO_mask,"%f\t",drive_level[i]);
                }
				
			fclose(IO_mask);
			PopulateList();

			break;
	}
	return 0;
}
