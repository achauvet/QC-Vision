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

#define  ERG_panel                        1
#define  ERG_panel_nscans                 2       /* control type: numeric, callback function: (none) */
#define  ERG_panel_acquire                3       /* control type: command, callback function: acquire */
#define  ERG_panel_quitbutton             4       /* control type: command, callback function: quitbutton */
#define  ERG_panel_scope                  5       /* control type: graph, callback function: (none) */
#define  ERG_panel_delete_plot            6       /* control type: command, callback function: delete_plot */
#define  ERG_panel_chanel1                7       /* control type: command, callback function: chanel1 */
#define  ERG_panel_chanel2                8       /* control type: command, callback function: chanel2 */
#define  ERG_panel_LED_chanel2            9       /* control type: LED, callback function: (none) */
#define  ERG_panel_LED_chanel1            10      /* control type: LED, callback function: (none) */
#define  ERG_panel_nremain                11      /* control type: numeric, callback function: (none) */
#define  ERG_panel_pause                  12      /* control type: command, callback function: pause */
#define  ERG_panel_SRS                    13      /* control type: command, callback function: SRS */
#define  ERG_panel_SPLITTER_4             14      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_2             15      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_3             16      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER               17      /* control type: splitter, callback function: (none) */
#define  ERG_panel_PICTURE                18      /* control type: picture, callback function: (none) */
#define  ERG_panel_LED_SRS                19      /* control type: LED, callback function: (none) */
#define  ERG_panel_nsec                   20      /* control type: numeric, callback function: (none) */
#define  ERG_panel_secbwtrigg             21      /* control type: command, callback function: secbwtrigg */
#define  ERG_panel_npulses                22      /* control type: numeric, callback function: (none) */
#define  ERG_panel_TEXTMSG_3              23      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_TEXTMSG                24      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_pulsespertrigg         25      /* control type: command, callback function: pulsespertrigg */
#define  ERG_panel_resetoscillo           26      /* control type: command, callback function: resetoscillo */
#define  ERG_panel_abortscan              27      /* control type: command, callback function: abortscan */
#define  ERG_panel_SPLITTER_6             28      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_5             29      /* control type: splitter, callback function: (none) */
#define  ERG_panel_bckgrd_sub             30      /* control type: binary, callback function: (none) */
#define  ERG_panel_fit_live               31      /* control type: binary, callback function: (none) */
#define  ERG_panel_TEXTMSG_2              32      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_TEXTMSG_5              33      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_TEXTMSG_4              34      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_load_plot              35      /* control type: command, callback function: load_plot */
#define  ERG_panel_Fit_loaded_curve       36      /* control type: command, callback function: Fit_loaded_curve */
#define  ERG_panel_points_num             37      /* control type: numeric, callback function: (none) */
#define  ERG_panel_start_val              38      /* control type: numeric, callback function: (none) */
#define  ERG_panel_fit_function           39      /* control type: ring, callback function: (none) */
#define  ERG_panel_bckgrd                 40      /* control type: numeric, callback function: (none) */
#define  ERG_panel_TEXTMSG_6              41      /* control type: textMsg, callback function: (none) */


     /* Control Arrays: */

#define  CTRLARRAY                        1

     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK abortscan(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK acquire(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK chanel1(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK chanel2(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK delete_plot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Fit_loaded_curve(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load_plot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pause(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pulsespertrigg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitbutton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resetoscillo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK secbwtrigg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SRS(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
