#include <NIDAQmx.h>
#include <DAQmxIOctrl.h>

/*---------------------------------------------------------------------------*/
/* Defines                                                                   */
/*---------------------------------------------------------------------------*/
#define WRITE 0
#define READ 1
#define TRUE 1
#define FALSE 0
#define PI 3.14159265358979

/*---------------------------------------------------------------------------*/
/* Module-globals                                                            */
/*---------------------------------------------------------------------------*/
int  Main_pnl_handle;
int	 Fit_pnl_handle, Sequence_pnl_handle, Mask_pnl_handle;
int  function_type_handle;
int  device, device1;
int  address;
int  pause_flag;
int  Nscans, f, h, i, j, k,l,m;
int  fit_type;
int  start;
int  Npoints; 
int  SRS_flag;
int  function_type;
int  Npixel;
int  mask_index;
int  seq_num;
int  experiment;
int  data_file; 
int  nmeasure[1];
int  fit_status;
int  drive_level[2000];


double phase[640];
double xarray[10000];
double data2fit[10000];
double buffer[10000];
double baseline;   
double maximumValue, minimumValue;
double tobelog[3];    
double alpha, gamma, delta;
double data;
double value;

float64  channel_data[1];


char mask_path[500];
char mask_name[500];
char mask_filename[500];
char file[500];
char filename[FILENAME_MAX];  
char msg[100];

struct mask_struct {
	char name[500];
	int voltages[640];
};
			
struct mask_struct mask[10];

/*---------------------------------------------------------------------------*/
/* Internal function prototypes                                              */
/*---------------------------------------------------------------------------*/
int send_board_commands (void);
int waveform(int color, int data_file);
int headerfile(void);
int phase2voltage(double phi);
int send_masks(unsigned int drive_level[]);

void writeintensity(void);
void displaychannel(void);
void init_variables(void);
void reset_connection_SRS(void);
void reset_connection_oscillo(void);
void setup_oscillo(void);
void setup_SRS(void);
void acquire_scans(void);
void SRS_onoff(void);
void generate_xarray (void);
void plot_data (int);
void fit_data (void);
void GetFiles(char[], int*, int);
void PopulateList(void);
void maskID(void);
void get_intensity(void);
void readDAQ(void); 
void start_shaper(void);
void stop_shaper();

int display_masks(void);
double ModelFunct (double x, double a[], int ncoef);

TaskHandle init_DAQ(void);	
TaskHandle thShutter;


