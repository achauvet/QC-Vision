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

#define  Seq_panel                        1
#define  Seq_panel_mask_list              2       /* control type: listBox, callback function: (none) */
#define  Seq_panel_add_mask_button        3       /* control type: command, callback function: add_mask */
#define  Seq_panel_Clear_list             4       /* control type: command, callback function: Clear_list */
#define  Seq_panel_Deletefromlist         5       /* control type: command, callback function: Deletefromlist */
#define  Seq_panel_start_sequence         6       /* control type: command, callback function: start_sequence */
#define  Seq_panel_seq_number             7       /* control type: numeric, callback function: (none) */
#define  Seq_panel_abort_seq              8       /* control type: command, callback function: abort_seq */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK abort_seq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK add_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Clear_list(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Deletefromlist(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK start_sequence(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
