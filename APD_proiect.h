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

#define  FREQ_PANEL                       1       /* callback function: OnFreqPanel */
#define  FREQ_PANEL_GRAPH_FREQ_FILTER     2       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_FREQ_SIGNAL     3       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_FREQ_WINDOW     4       /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_EXIT_FREQ             5       /* control type: command, callback function: OnExitFreq */
#define  FREQ_PANEL_BINARYSWITCH          6       /* control type: binary, callback function: OnBinarySwitch */
#define  FREQ_PANEL_NUMERIC               7       /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_FILTER_TYPE           8       /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_WINDOW_TYPE           9       /* control type: ring, callback function: (none) */
#define  FREQ_PANEL_FSTOP                 10      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_FCUT                  11      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_FPASS                 12      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_GRAPH_SPECTRU_2       13      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_GRAPH_SPECTRU         14      /* control type: graph, callback function: (none) */
#define  FREQ_PANEL_IDC_FREQ_PEAK_2       15      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_IDC_FREQ_PEAK         16      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_IDC_POWER_PEAK_2      17      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_IDC_POWER_PEAK        18      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_IDC_TIMER_BUTTON      19      /* control type: command, callback function: OnTimerGo */
#define  FREQ_PANEL_COEFICIENTI           20      /* control type: numeric, callback function: (none) */
#define  FREQ_PANEL_TIMER                 21      /* control type: timer, callback function: OnTimer */

#define  MAIN_PANEL                       2       /* callback function: OnMainPanel */
#define  MAIN_PANEL_IDC_GRAPH             2       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_IDC_GRAPH_RAW_DATA    3       /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_BUTTON_DERIVATA       4       /* control type: command, callback function: OnDerivata */
#define  MAIN_PANEL_EXIT_BUTTON           5       /* control type: command, callback function: OnExit */
#define  MAIN_PANEL_LOAD_BUTTON           6       /* control type: command, callback function: OnLoadButton */
#define  MAIN_PANEL_APLICA_BUTTON         7       /* control type: command, callback function: OnAplicaButton */
#define  MAIN_PANEL_NEXT_BUTTON           8       /* control type: command, callback function: OnNextButton */
#define  MAIN_PANEL_PREV_BUTTON           9       /* control type: command, callback function: OnPrevButton */
#define  MAIN_PANEL_IDC_STOP              10      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_START             11      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_MEDIERE           12      /* control type: ring, callback function: (none) */
#define  MAIN_PANEL_IDC_FILTRU            13      /* control type: ring, callback function: (none) */
#define  MAIN_PANEL_IDC_DISPERSIE         14      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_VMAX_INDEX        15      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_KURTOSIS          16      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_ZEROS             17      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_SKEWNESS          18      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_MEDIE             19      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_VMAX              20      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_MEDIANA           21      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_VMIN              22      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_VMIN_INDEX        23      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_IDC_HISTOGRAM         24      /* control type: graph, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG               25      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_DECORATION            26      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_TEXTMSG_2             27      /* control type: textMsg, callback function: (none) */
#define  MAIN_PANEL_IDC_ALPHA             28      /* control type: numeric, callback function: (none) */
#define  MAIN_PANEL_BINARYSWITCH          29      /* control type: binary, callback function: OnBinarySwitch */
#define  MAIN_PANEL_DECORATION_3          30      /* control type: deco, callback function: (none) */
#define  MAIN_PANEL_DECORATION_2          31      /* control type: deco, callback function: (none) */


     /* Control Arrays: */

          /* (no control arrays in the resource file) */


     /* Menu Bars, Menus, and Menu Items: */

          /* (no menu bars in the resource file) */


     /* Callback Prototypes: */

int  CVICALLBACK OnAplicaButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnBinarySwitch(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnDerivata(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnExit(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnExitFreq(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnFreqPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnLoadButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnMainPanel(int panel, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnNextButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnPrevButton(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnTimer(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);
int  CVICALLBACK OnTimerGo(int panel, int control, int event, void *callbackData, int eventData1, int eventData2);


#ifdef __cplusplus
    }
#endif