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
#define  ERG_panel_signal_display         5       /* control type: graph, callback function: (none) */
#define  ERG_panel_mask_display           6       /* control type: graph, callback function: (none) */
#define  ERG_panel_scope                  7       /* control type: graph, callback function: (none) */
#define  ERG_panel_delete_plot            8       /* control type: command, callback function: delete_plot */
#define  ERG_panel_chanel1                9       /* control type: command, callback function: chanel1 */
#define  ERG_panel_chanel2                10      /* control type: command, callback function: chanel2 */
#define  ERG_panel_LED_chanel2            11      /* control type: LED, callback function: (none) */
#define  ERG_panel_LED_chanel1            12      /* control type: LED, callback function: (none) */
#define  ERG_panel_nremain                13      /* control type: numeric, callback function: (none) */
#define  ERG_panel_pause                  14      /* control type: command, callback function: pause */
#define  ERG_panel_SRS                    15      /* control type: command, callback function: SRS */
#define  ERG_panel_SPLITTER_4             16      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_2             17      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_3             18      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER               19      /* control type: splitter, callback function: (none) */
#define  ERG_panel_LED_SRS                20      /* control type: LED, callback function: (none) */
#define  ERG_panel_nsec                   21      /* control type: numeric, callback function: (none) */
#define  ERG_panel_secbwtrigg             22      /* control type: command, callback function: secbwtrigg */
#define  ERG_panel_npulses                23      /* control type: numeric, callback function: (none) */
#define  ERG_panel_TEXTMSG_3              24      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_TEXTMSG                25      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_pulsespertrigg         26      /* control type: command, callback function: pulsespertrigg */
#define  ERG_panel_resetoscillo           27      /* control type: command, callback function: resetoscillo */
#define  ERG_panel_abortscan              28      /* control type: command, callback function: abortscan */
#define  ERG_panel_SPLITTER_6             29      /* control type: splitter, callback function: (none) */
#define  ERG_panel_SPLITTER_5             30      /* control type: splitter, callback function: (none) */
#define  ERG_panel_bckgrd_sub             31      /* control type: binary, callback function: (none) */
#define  ERG_panel_TEXTMSG_2              32      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_TEXTMSG_5              33      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_load_plot              34      /* control type: command, callback function: load_plot */
#define  ERG_panel_bckgrd                 35      /* control type: numeric, callback function: (none) */
#define  ERG_panel_fit_options            36      /* control type: command, callback function: fit_options */
#define  ERG_panel_TEXTMSG_6              37      /* control type: textMsg, callback function: (none) */
#define  ERG_panel_generate_mask          38      /* control type: command, callback function: generate_mask */
#define  ERG_panel_mask_sequence          39      /* control type: command, callback function: mask_sequence */
#define  ERG_panel_mask_folder_button     40      /* control type: command, callback function: mask_folder */
#define  ERG_panel_folder_path            41      /* control type: string, callback function: (none) */
#define  ERG_panel_loaded_mask_list       42      /* control type: ring, callback function: loaded_mask */
#define  ERG_panel_TEXTMSG_4              43      /* control type: textMsg, callback function: (none) */


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
int  CVICALLBACK fit_options(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK generate_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK load_plot(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK loaded_mask(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mask_folder(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK mask_sequence(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pause(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK pulsespertrigg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK quitbutton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK resetoscillo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK secbwtrigg(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK SRS(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
