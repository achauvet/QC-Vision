#include "Generate_Mask.h"
#include "Fit_Options.h"
#include <cvinetv.h>
#include <analysis.h>
#include "toolbox.h"
#include "ERG.h"
#include "Fit_options.h" 
#include "Sequence.h"  
#include "global.h"  


/*---------------------------------------------------------------------------*/
/* Modified on May 2016: changed to TDS 3032  (from TDS 220 )                */
/* Resolution max y:9 bits, x:10.000 pts                                     */
/*                                                                           */
/*---------------------------------------------------------------------------*/

/*---------------------------------------------------------------------------*/
/* Include files                                                             */
/*---------------------------------------------------------------------------*/
#include <cvirte.h>
#include <utility.h>
#include <ansi_c.h>
#include <gpib.h>
#include <formatio.h>
#include <userint.h>
#include "gpibrw.h"

/*---------------------------------------------------------------------------*/
/* Internal function prototypes                                              */
/*---------------------------------------------------------------------------*/


FILE* IO_output;
FILE* IO_intensity;

char pathname[FILENAME_MAX]; 


/*---------------------------------------------------------------------------*/
/* Module-globals                                                            */
/*---------------------------------------------------------------------------*/






/*---------------------------------------------------------------------------*/
/* This is the application's entry-point.                                    */
/*---------------------------------------------------------------------------*/
int main (int argc, char *argv[])
{
	init_variables();
	if (InitCVIRTE (0, argv, 0) == 0)
		return -1;
	DisableBreakOnLibraryErrors ();
	setup_oscillo();
	setup_SRS();
	start_shaper();
	generate_xarray ();


	if ((Main_pnl_handle = LoadPanel (0, "ERG.uir", ERG_panel)) < 0)
		return -1;
	mask_folder(Main_pnl_handle,99,EVENT_COMMIT,0,0,0);
	PopulateList();
	strcpy (mask_filename, "flat");
	display_masks();
	DisplayPanel (Main_pnl_handle);
	RunUserInterface ();
	DiscardPanel (Main_pnl_handle);
	stop_shaper();
	return 0;
}

void init_variables(void)
{
	pause_flag=0;
	Nscans=10;
	i=0;
	start=0;
	Npoints=10; 
	SRS_flag=0;
	data=0;
	Npixel=640;
	for (i=0;i<Npixel;i++){
		drive_level[i]=0;
	}
}

void setup_SRS(void)
{
	static char write_buffer[100];
	reset_connection_SRS();
	strcpy (write_buffer, "OM 4,3");
	ibwrt (device1, write_buffer, strlen(write_buffer));
	SRS_flag=0;
	SRS_onoff();
}

void reset_connection_SRS(void)
{
	address=2; //GPIB address of SRS DG 535
	device1 = ibdev (0, address, NO_SAD, T10s, 1, 00001000);
	ibsic(device1);
}

void setup_oscillo(void)
{
	static char write_buffer[100];
	// find hardware
	reset_connection_oscillo();
	// configure oscilloscope 
	strcpy (write_buffer, "DATA:ENCdg RIBinary");
	ibwrt (device, write_buffer, strlen(write_buffer));

	strcpy (write_buffer, "DATA:WIDTH 1");
	ibwrt (device, write_buffer, strlen(write_buffer));

	strcpy (write_buffer, "DATA:SOURCE CH1");
	ibwrt (device, write_buffer, strlen(write_buffer));
	SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel1, 1);
	SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel2, 0);
	return;

}

void reset_connection_oscillo(void)
{
	address=1; //GPIB address of oscilloscope
	device = ibdev (0, address, NO_SAD, T30s, 1, 0);
	ibsic(device);
	
}

void generate_xarray (void)
{
	j=0;
	while ( j < 10000 ) 
	{
		xarray[j] = j;
		j++;
	}
}

void acquire_scans (void)
{
	int color;
	int Nleft=0;
	char file [ FILENAME_MAX ];

	SetCtrlAttribute (Main_pnl_handle, ERG_panel_acquire, ATTR_DIMMED, 1);
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_abortscan, ATTR_DIMMED, 1);
	if (experiment==1){
		GetCtrlVal (Sequence_pnl_handle, Seq_panel_seq_number, &seq_num);
		Nscans=	seq_num*m;
	}
	else {
		GetCtrlVal (Main_pnl_handle, ERG_panel_nscans, &Nscans);
	}

	DirSelectPopup ("d:\\data\\test", "Select Directory", 1, 1, pathname);

	i=0;
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_DIMMED, 0);
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_abortscan, ATTR_DIMMED, 0);
	
// start trigger 
	SRS_flag=2;
	SRS_onoff();
	DeleteGraphPlot (Main_pnl_handle, ERG_panel_mask_display, -1, VAL_IMMEDIATE_DRAW);
	
	if (experiment==1){			 // mode sequence
		for (i=0;i<seq_num;i++) {
			for (h=0;h<m;h++){
				SetCtrlIndex (Sequence_pnl_handle, Seq_panel_mask_list, h);
				for (k=0;k<Npixel;k++){
					drive_level[k]=mask[h].voltages[k];
				}				
				display_masks();
				
				ProcessSystemEvents();
				GetLabelFromIndex (Sequence_pnl_handle, Seq_panel_mask_list, h, &mask_filename);
				strcpy(filename, pathname);
				
				//prepare file to write
				sprintf(file, "\\sequence%d_%s.txt", i, mask_filename);
				strcat(filename, file);
				data_file = OpenFile (filename, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
				
				//enable oscillo then wait for trigger and get ERG trace
				color=floor(256/Nscans)*(i*m+h);
				waveform(color, data_file);	
				get_intensity();
				
				//write header file
				headerfile();
				
				//write ERG trace 
				ArrayToFile (filename, data2fit, VAL_DOUBLE, 10000, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_ROWS, VAL_SEP_BY_TAB, 100, VAL_ASCII, VAL_APPEND);
				nmeasure[0]=i*m+h+1;
				displaychannel();
				
				Nleft=Nscans-(i*m+h);
				SetCtrlVal (Main_pnl_handle, ERG_panel_nremain, Nleft);
				ProcessSystemEvents();
				if (pause_flag)
				{
					while (pause_flag)
						ProcessSystemEvents();
				}
			}
		}
	}
	
	else{				  // mode normal
	//prepare file name for acquiring data
		while ( i < Nscans )
		{
			strcpy(filename, pathname);
			sprintf(file, "\\scope_data%d.txt", i);
			strcat(filename, file);
			data_file = OpenFile (filename, VAL_WRITE_ONLY, VAL_TRUNCATE, VAL_ASCII);
			color=floor(256/Nscans)*i;
			waveform(color, data_file);
			get_intensity();
			
			headerfile();
			ArrayToFile (filename, data2fit, VAL_DOUBLE, 10000, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_ROWS, VAL_SEP_BY_TAB, 100, VAL_ASCII, VAL_APPEND);
			
			i++;
			Nleft=Nscans-i+1;
			SetCtrlVal (Main_pnl_handle, ERG_panel_nremain, Nleft);
			ProcessSystemEvents();
			if (pause_flag)
			{
				while (pause_flag)
					ProcessSystemEvents();
			}
			CloseFile (data_file);
		}
	}
	
	SetCtrlVal (Main_pnl_handle, ERG_panel_nremain, 0);
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_DIMMED, 1);
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_abortscan, ATTR_DIMMED, 1);
	SetCtrlAttribute (Main_pnl_handle, ERG_panel_acquire, ATTR_DIMMED, 0);
	
// stop trigger 	
	SRS_flag=0;
	SRS_onoff();
	
	ibsic(device); 
	return;
}

int waveform (int color, int data_file)
{
	static char write_buffer[100];
	int numToRead=10000;
	char * read_buffer;
	read_buffer = malloc (numToRead);
	
	
	memset(read_buffer, 0, 10000);
	ibsic(device);

	strcpy (write_buffer, "DATA:STARt 1");
	ibwrt (device, write_buffer, strlen(write_buffer));
	sprintf (write_buffer, "DATA:STOP 10000");
	ibwrt (device, write_buffer, strlen(write_buffer));
	strcpy (write_buffer, "ACQUIRE:MODE SAMPLE");
	ibwrt (device, write_buffer, strlen(write_buffer));

	strcpy (write_buffer, "ACQUIRE:STOPAFTER SEQUENCE");
	ibwrt (device, write_buffer, strlen(write_buffer));
	
	strcpy (write_buffer, "ACQUIRE:STATE ON");
	ibwrt (device, write_buffer, strlen(write_buffer));

	strcpy (write_buffer, "*WAI");				// wait for trigger to continue
	ibwrt (device, write_buffer, strlen(write_buffer));

	strcpy (write_buffer, "CURVe?");
	ibwrt (device, write_buffer, strlen(write_buffer));
	Delay(0.3); 

	ibrd (device, read_buffer, numToRead);

	ConvertArrayType (read_buffer, VAL_CHAR, data2fit, VAL_DOUBLE, 10000);
	free (read_buffer)  ;
	
	
	
	
	plot_data(color);                   
	
	// check if live-fitting is enabled
	GetCtrlVal (Fit_pnl_handle, Fit_panel_fit_live, &fit_status);
	if (fit_status==1)
	{
		fit_data ();
	}
	
	return 1;
}

int headerfile (void)
{
	static char write_buffer[100],  read_buffer[2500];
	int numToRead=2500;
	
// Sequence number
	sprintf (msg,"Sequence= %d", i);
	WriteLine (data_file, msg, -1);
	
// mask number and name
	sprintf (msg, "Mask ID= %d\nMask name=%s", h, mask_filename);
	WriteLine (data_file, msg, -1);

// Pulse intensity	
	sprintf (msg,"Pulse intensity= %f", channel_data[0]);
	WriteLine (data_file, msg, -1);

// Fit type 
	if (fit_status==1){
		if (fit_type==0){
			sprintf (msg,"Fit type= linear (slope)");
		}
		if (fit_type==1){
			sprintf (msg,"Fit type= Gaussian (tau)");
		}
		if (fit_type==2){
			sprintf (msg,"Fit type= wave A-B (amplitude)");
		}
	}
	else {
		sprintf (msg,"Fit type= no fit");
	}
	WriteLine (data_file, msg, -1);

//Optimization value	
	sprintf (msg,"Optimization value=%f", value);	
	WriteLine (data_file, msg, -1);
	
//  wave x interval
	memset(read_buffer, 0, 2500);
	strcpy (write_buffer, "WFMPre:XINcr?");
	ibwrt (device, write_buffer, strlen(write_buffer));
	ibrd (device, read_buffer, numToRead);
	sprintf (msg, "X interval= %s", read_buffer);
	WriteLine (data_file, msg, -1);

//  Y scaling factor
	memset(read_buffer, 0, 2500);
	strcpy (write_buffer, "WFMPre:YMUlt?");
	ibwrt (device, write_buffer, strlen(write_buffer));
	ibrd (device, read_buffer, numToRead);
	sprintf (msg, "Y scaling factor= %s", read_buffer);
	WriteLine (data_file, msg, -1);
	
// First x data point
	memset(read_buffer, 0, 2500);
	strcpy (write_buffer, "WFMPre:XZEro?");
	ibwrt (device, write_buffer, strlen(write_buffer));
	ibrd (device, read_buffer, numToRead);
	sprintf (msg, "X0= %s", read_buffer);
	WriteLine (data_file, msg, -1);
	
	return 1;
}

void get_intensity(void)
{
	init_DAQ();
	readDAQ();
	
}

void displaychannel(void)
{
	PlotXY (Main_pnl_handle, ERG_panel_signal_display, nmeasure, channel_data, 1, VAL_INTEGER, VAL_DOUBLE, VAL_DOT, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_RED);
}

void SRS_onoff(void)
{
	static char write_buffer[100];
	ibsic(device1);

	if (SRS_flag==0)	 //SRS output set on 0.1V --> not triggering
	{
		SRS_flag=1;
		strcpy (write_buffer, "OM 4,3");
		ibwrt (device1, write_buffer, strlen(write_buffer));

		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_LABEL_TEXT, "Enable");
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
		SetCtrlVal(Main_pnl_handle, ERG_panel_LED_SRS, 0);
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_DIMMED, 0);
	}

	else if (SRS_flag==1)   //SRS output set on TTL --> triggering!
	{

		SRS_flag=0;
		strcpy (write_buffer, "OM 4,0");
		ibwrt (device1, write_buffer, strlen(write_buffer));

		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_LABEL_TEXT, "Disable");
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_CMD_BUTTON_COLOR, VAL_RED);
		SetCtrlVal(Main_pnl_handle, ERG_panel_LED_SRS, 1);
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_DIMMED, 0);
	}

	else  if (SRS_flag==2)   //Scanning mode SRS output set on TTL --> triggering!
	{

		SRS_flag=1;
		strcpy (write_buffer, "OM 4,0");
		ibwrt (device1, write_buffer, strlen(write_buffer));

		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_LABEL_TEXT, "Scanning");
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_DIMMED, 1);
		SetCtrlAttribute (Main_pnl_handle, ERG_panel_SRS, ATTR_CMD_BUTTON_COLOR, VAL_BLUE);
		SetCtrlVal(Main_pnl_handle, ERG_panel_LED_SRS, 1);
	}
	return;
}

double ModelFunct (double x, double a[], int ncoef)
{
	double yy;
	if ((x-a[0])<0)
	{
		yy=baseline-(baseline-minimumValue)*exp(-(x-a[0])*(x-a[0])/a[1]);
	}
	else
	{
		yy= minimumValue;
	}
	return (yy);
}  

void plot_data (int color)
{
	int pix_num,bckgrd_satus;
	double bckgrd_val;

	GetCtrlVal (Main_pnl_handle, ERG_panel_bckgrd_sub, &bckgrd_satus); 
	if (bckgrd_satus==1)
	{
		GetCtrlVal (Main_pnl_handle, ERG_panel_bckgrd, &pix_num);
		Mean (&data2fit[pix_num-50], 100, &bckgrd_val);
		j=0;
		while (j<10000)
		{
			buffer[j] = data2fit[j]-bckgrd_val;
			j++;
		}
	}
	else
	{
		  j=0;
		while (j<10000)
		{
			buffer[j] = data2fit[j];
			j++;
		}
	}
	
	PlotY (Main_pnl_handle, ERG_panel_scope, buffer, 10000,VAL_DOUBLE , VAL_THIN_LINE, VAL_EMPTY_SQUARE, VAL_SOLID, 1, MakeColor(color,color,color));
}

int display_masks(void)
{   
		
	DeleteGraphPlot (Main_pnl_handle, ERG_panel_mask_display, -1, VAL_IMMEDIATE_DRAW);
	send_masks(drive_level);
	PlotY (Main_pnl_handle, ERG_panel_mask_display, drive_level, Npixel, VAL_INTEGER, VAL_VERTICAL_BAR, VAL_NO_POINT, VAL_SOLID, 1, VAL_RED);
															 
					
	return 0;
}

void PopulateList()
{
	char label[MAX_PATHNAME_LEN];
	char fileName[MAX_PATHNAME_LEN];
	int numItems = 1; 
	
	ClearListCtrl (Main_pnl_handle, ERG_panel_loaded_mask_list);
	InsertListItem (Main_pnl_handle, ERG_panel_loaded_mask_list, -1, "flat", 0);
	
	SplitPath (mask_path, NULL, NULL, fileName);
	Fmt (label, "%s<%s%s%s", "Project Directory (", fileName, ")");
	GetFiles(mask_path, &numItems, numItems-1);
}

void GetFiles(char dir[], int* numItems, int parentItem)
{
	char fileName[MAX_PATHNAME_LEN], searchPath[MAX_PATHNAME_LEN];
	strcpy (searchPath, dir); 
	strcat (searchPath, "\\*");
	
	if (!GetFirstFile (searchPath, 1, 1, 0, 0, 0, 0, fileName)) // has at least one file
	{
		InsertListItem (Main_pnl_handle, ERG_panel_loaded_mask_list, -1, fileName, (*numItems)++);
		while (!GetNextFile (fileName))
		{
			InsertListItem (Main_pnl_handle, ERG_panel_loaded_mask_list, -1, fileName, (*numItems)++);
		}
	}
}


int CVICALLBACK acquire (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			acquire_scans();
		break;
	}
	return 0;
}

int CVICALLBACK abortscan (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			//set value of Nscans to zerro to properly quite the acqquire-scans-loop while writing the leftover buffer from oscillo.
			Nscans=0;
			seq_num=0;
			SetCtrlAttribute (Main_pnl_handle, ERG_panel_abortscan, ATTR_DIMMED, 0);
			break;
	}
	return 0;
}

int CVICALLBACK quitbutton (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			pause_flag=0;
			i=Nscans;
			SRS_flag=0;
			SRS_onoff();
			QuitUserInterface (0);
			break;
	}
	return 0;
}

int CVICALLBACK delete_plot (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			DeleteGraphPlot (Main_pnl_handle, ERG_panel_scope, -1, VAL_IMMEDIATE_DRAW);
			break;
	}
	return 0;
}

int CVICALLBACK chanel1 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	static char write_buffer[100];
	switch (event)
	{
		case EVENT_COMMIT:
			strcpy (write_buffer, "DATA:SOURCE CH1");
			ibwrt (device, write_buffer, strlen(write_buffer));
			SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel1, 1);
			SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel2, 0);
			break;
	}
	return 0;
}

int CVICALLBACK chanel2 (int panel, int control, int event,
						 void *callbackData, int eventData1, int eventData2)
{
	static char write_buffer[100];
	switch (event)
	{
		case EVENT_COMMIT:
			strcpy (write_buffer, "DATA:SOURCE CH2");
			ibwrt (device, write_buffer, strlen(write_buffer));
			SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel2, 1);
			SetCtrlVal(Main_pnl_handle, ERG_panel_LED_chanel1, 0);
			break;
	}
	return 0;
}

int CVICALLBACK pause (int panel, int control, int event,
					   void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			if (pause_flag)
			{
				pause_flag=0;
				SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_CMD_BUTTON_COLOR, VAL_RED);
				SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_LABEL_TEXT, "Pause");
				SRS_flag=2;
				SRS_onoff();
			}
			else
			{
				pause_flag=1;
				SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_CMD_BUTTON_COLOR, VAL_GREEN);
				SetCtrlAttribute (Main_pnl_handle, ERG_panel_pause, ATTR_LABEL_TEXT, "Resume");
				SRS_flag=0;
				SRS_onoff();
			}
			break;
	}
	return 0;
}

int CVICALLBACK SRS (int panel, int control, int event,
					 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			SRS_onoff();
			break;
	}
	return 0;
}

int CVICALLBACK pulsespertrigg (int panel, int control, int event,
								void *callbackData, int eventData1, int eventData2)
{
	static char write_buffer[100];
	int  Npulses;
	switch (event)
	{
		case EVENT_COMMIT:
			reset_connection_SRS();
			//get and set the opening time of the sutter in ms,
			//which corresponds to the number of pulses at 1kHz.
			GetCtrlVal(Main_pnl_handle, ERG_panel_npulses, &Npulses);
			sprintf(write_buffer,"DT 3,2,%d.03E-3", Npulses);
			ibwrt (device1, write_buffer, strlen(write_buffer));
			break;
	}
	return 0;
}

int CVICALLBACK secbwtrigg (int panel, int control, int event,
							void *callbackData, int eventData1, int eventData2)
{
	static char write_buffer[100];
	int  Nsec;
	switch (event)
	{
		case EVENT_COMMIT:
			reset_connection_SRS();
			//get and set the waiting time bewteen to trigger pulses sent to the sutter, in sec.
			GetCtrlVal(Main_pnl_handle, ERG_panel_nsec, &Nsec);
			sprintf(write_buffer,"DT 5,1,%d", Nsec);
			ibwrt (device1, write_buffer, strlen(write_buffer));
			break;
	}
	return 0;
}

int CVICALLBACK resetoscillo (int pfanel, int control, int event,
							  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			reset_connection_oscillo();
			break;
	}
	return 0;
}

int CVICALLBACK load_plot (int panel, int control, int event,
						   void *callbackData, int eventData1, int eventData2)
{
	int color;
	switch (event)
	{
		case EVENT_COMMIT:
			color=0;
			FileSelectPopupEx ("d:\\data\\test", "*.*", "txt", "Load data", VAL_LOAD_BUTTON, 0, 0, pathname);
			
			memset(data2fit, 0, sizeof(data2fit));
			FileToArray (pathname, data2fit, VAL_DOUBLE, 10000, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_ROWS, VAL_ASCII);
			plot_data (color); 
			break;
	}
	return 0;
}

int CVICALLBACK mask_folder (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:

			DirSelectPopup ("d:\\test", "Masks Folder", 1, 1, mask_path);
			SetCtrlVal (ERG_panel,ERG_panel_folder_path , mask_path);
			PopulateList();

			

			  
			  
			break;
	}
	return 0;
}

int  CVICALLBACK loaded_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2)
{	
	char dummy[500];
	switch (event)
			
	{
	case EVENT_COMMIT:
		GetCtrlVal (Main_pnl_handle, ERG_panel_loaded_mask_list, &mask_index);
		GetLabelFromIndex (Main_pnl_handle, ERG_panel_loaded_mask_list, mask_index, &mask_filename);
		if (mask_index==0){
			for (i=0;i<Npixel;i++){
					drive_level[i]=0;
				}
		
		}
		else{
			strcpy (dummy, mask_path);
			strcat (dummy, "\\");
			strcat(dummy, mask_filename);
		
			FileToArray (dummy, drive_level, VAL_INTEGER, Npixel, 1, VAL_GROUPS_TOGETHER, VAL_GROUPS_AS_COLUMNS, VAL_ASCII);
		}
		
		display_masks();



			  
			break;
	}
	return 0;
}
