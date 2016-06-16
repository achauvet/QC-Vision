#include <ansi_c.h>
#include <cvinetv.h>
#include <utility.h>
#include <analysis.h>
#include <userint.h>
#include "global.h"  
#include "ERG.h" 
#include "Fit_Options.h" 


extern int Fit_pnl_handle;




void fit_data (void)
{
	GetCtrlVal (Fit_pnl_handle, Fit_panel_start_val, &start);
	GetCtrlVal (Fit_pnl_handle, Fit_panel_points_num, &Npoints);
	double slope, intercept, residue, coef[4];
	double fit[Npoints];
	int maximumIndex, minimumIndex;
	CNVData data=0;
	CNVWriter writer = 0;
	
	for (int k = 0; k < Npoints; k++)
    fit[k] = 0;
	///////////////////////////////////////////////////////////////
	//////////////to do : create specific function for background subtraction
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
	//////////////////////////////////////////////////////////////
	
	generate_xarray ();  
	PlotXY (Main_pnl_handle, ERG_panel_scope, &xarray[start], &buffer[start], Npoints, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_GREEN); 
 	
	GetCtrlVal (Fit_pnl_handle, Fit_panel_fit_function, &fit_type);
	if (fit_type==0)  // Linear fit, returns slope
	{
		MaxMin1D(&buffer[start], Npoints, &maximumValue, &maximumIndex, &minimumValue, &minimumIndex);
//		Npoints=  minimumIndex;
		LinearFitEx (&xarray[start], &buffer[start], NULL, Npoints, LEAST_SQUARE, 0.0001, fit, &value, &intercept, &residue);

		
	}
							  
	if (fit_type==1)	// Gaussian fit, returns tau 
	{
		Mean (&buffer[start-100], 100, &baseline);
		MaxMin1D(&buffer[start], Npoints, &maximumValue, &maximumIndex, &minimumValue, &minimumIndex);
//		Npoints=  minimumIndex;
		Mean (&buffer[start+minimumIndex-5], 10, &minimumValue);
		coef[0]= start+minimumIndex;
		coef[1]= minimumIndex/2;
		NonLinearFitWithMaxIters (&xarray[start], &buffer[start], fit, Npoints, 100, ModelFunct, coef, 2, &residue);
		value=coef[1];

		
	}
	
	if (fit_type==2)	 // (max-min) amplitude fit, returns amplitude 
	{
		MaxMin1D(&buffer[start], Npoints, &maximumValue, &maximumIndex, &minimumValue, &minimumIndex);
		value= maximumValue - minimumValue;
		printf("%f\t%f\t%f\n", value, maximumValue, minimumValue);
	/*	
		if (minimumIndex < maximumIndex)
		{
//			Npoints=maximumIndex-minimumIndex;
			Copy1D (&buffer[minimumIndex+start], Npoints, fit);
			start= minimumIndex+start;
			value= maximumValue - minimumValue;
		}
		else
		{
			value= 0;
		}
	*/	
}
	

	PlotXY (Main_pnl_handle, ERG_panel_scope, &xarray[start], fit, Npoints, VAL_DOUBLE, VAL_DOUBLE, VAL_THIN_LINE, VAL_SOLID_SQUARE, VAL_SOLID, 1, VAL_RED);
}

int CVICALLBACK fit_options (int panel, int control, int event,
							 void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
		
			if ((Fit_pnl_handle = LoadPanel (0, "Fit_Options.uir", Fit_panel)) < 0)
			return -1;
	
			DisplayPanel (Fit_pnl_handle );  
			RunUserInterface ();
			DiscardPanel (Fit_pnl_handle );
			break;
	}
	return 0;
}

int CVICALLBACK Fit_loaded_curve (int panel, int control, int event,
								  void *callbackData, int eventData1, int eventData2)
{
	switch (event)
	{
		case EVENT_COMMIT:
			fit_data();
			break;
	}
	return 0;
}


