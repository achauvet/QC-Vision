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

#define  Mask_panel                       1
#define  Mask_panel_TAB_function_type     2       /* control type: tab, callback function: (none) */
#define  Mask_panel_mask_name_field       3       /* control type: string, callback function: (none) */
#define  Mask_panel_save_mask_button      4       /* control type: command, callback function: save_mask */
#define  Mask_panel_visualize_mask_button 5       /* control type: command, callback function: visualize_mask */

     /* tab page panel controls */
#define  TAB_chirp_input_delta            2       /* control type: numeric, callback function: (none) */
#define  TAB_chirp_input_gamma            3       /* control type: numeric, callback function: (none) */
#define  TAB_chirp_input_alpha            4       /* control type: numeric, callback function: (none) */
#define  TAB_chirp_TEXTMSG                5       /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK save_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK visualize_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
