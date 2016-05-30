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

#define  BOARD                           1
#define  BOARD_SEND_2                    2
#define  BOARD_SEND_1                    3
#define  BOARD_COMMAND                   4
#define  BOARD_STATUS                    5
#define  BOARD_QUIT                      6
#define  BOARD_ERR                       7
#define  BOARD_OPENBOARDCOMMAND          8
#define  BOARD_INTERFACECLEARCOMMAND     9

#define  PNL                             2
#define  PNL_MESSAGE                     2
#define  PNL_READ_BYTES                  3
#define  PNL_GO                          4       /* callback function: Go */
#define  PNL_STATUS                      5
#define  PNL_QUIT                        6       /* callback function: Quit */
#define  PNL_ERR                         7
#define  PNL_GPIB_FUNC                   8
#define  PNL_DATA                        9
#define  PNL_STATUS_MSG                  10

#define  SETUP                           3
#define  SETUP_CONTINUE                  2
#define  SETUP_ADDRESS                   3
#define  SETUP_NOTEIFNODEVICEISCONNE     4


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */ 

int  CVICALLBACK Go(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK Quit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif
