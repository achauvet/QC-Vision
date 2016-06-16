#include "Sequence.h" 
#include <ansi_c.h>
#include <cvinetv.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "global.h"  
#include "ERG.h" 


extern int	Sequence_pnl_handle;   




int CVICALLBACK mask_sequence (int panel, int control, int event,
							   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			if ((Sequence_pnl_handle = LoadPanel (0, "Sequence.uir", Seq_panel)) < 0)
			return -1;
			DisplayPanel (Sequence_pnl_handle);
			RunUserInterface ();
			DiscardPanel (Sequence_pnl_handle );
			break;
	}
	return 0;
}

int CVICALLBACK add_mask (int panel, int control, int event,
						  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if (m<10){
				strcpy (mask[m].name, mask_filename);
				for (i=0;i<Npixel;i++){
					mask[m].voltages[i]=drive_level[i];
				}
				InsertListItem (Sequence_pnl_handle, Seq_panel_mask_list, -1, mask_filename, m);
	//			printf("%d\n",m);
				m++;
			}
			
			else{
				printf("Structure is full!\n");			
			}
	//		printf("%f\n",mask[m-1].voltages[0]);
			break;
			
			
	}
	return 0;
}

int CVICALLBACK Clear_list (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			ClearListCtrl (Sequence_pnl_handle, Seq_panel_mask_list);
			if (m>=0){
				for (i=0;i<Npixel;i++){
					mask[m].voltages[i]=0;
				}
				m--;
			}
			m=0;
			break;
	}
	return 0;
}

int CVICALLBACK Deletefromlist (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			GetCtrlIndex (Sequence_pnl_handle, Seq_panel_mask_list, &l);
			DeleteListItem (Sequence_pnl_handle, Seq_panel_mask_list, (l), 1);
			for(k=l;k<m; k++) {
				for (i=0;i<Npixel;i++){
					mask[k].voltages[i]=mask[k+1].voltages[i];
				}
				strcpy (mask[k].name, mask[k+1].name);
			}
			m--;
			SetCtrlIndex (Sequence_pnl_handle, Seq_panel_mask_list, -1);			
			break;
	}
	return 0;
}

int CVICALLBACK start_sequence (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			experiment=1;				// indicates if the command came from the Sequence Panel		
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_Clear_list, ATTR_DIMMED, 1);
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_Deletefromlist, ATTR_DIMMED, 1);
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_start_sequence, ATTR_DIMMED, 1);
			acquire_scans();
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_Clear_list, ATTR_DIMMED, 0);
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_Deletefromlist, ATTR_DIMMED, 0);
			SetCtrlAttribute (Sequence_pnl_handle, Seq_panel_start_sequence, ATTR_DIMMED, 0);
			experiment=0;						
			break;
	}
	return 0;
}

