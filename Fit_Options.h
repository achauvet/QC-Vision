/**************************************************************************/
/* LabWindows/CVI User Interface Resource (UIR) Include File              */
/*                                                                        */
/* WARNING: Do not add to, delete from, or otherwise modify the contents  */
/*          of this include file.                                         */
/**************************************************************************/

#include <userint.h>

#ifdef __cplusplus
    extern "C" {
#endif

     /* Panels and Controls: */

#define  Fit_panel                        1
#define  Fit_panel_fit_function           2       /* control type: ring, callback function: (none) */
#define  Fit_panel_fit_live               3       /* control type: binary, callback function: (none) */
#define  Fit_panel_Fit_loaded_curve       4       /* control type: command, callback function: Fit_loaded_curve */
#define  Fit_panel_points_num             5       /* control type: numeric, callback function: (none) */
#define  Fit_panel_start_val              6       /* control type: numeric, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK Fit_loaded_curve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
