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
int  Nscans, i, j, k,l,m;
int  start;
int  Npoints; 
int  SRS_flag;
int  function_type;
int  Npixel;
int  mask_index;
int  seq_num;

double phase[512];
double drive_level[512];
double xarray[10000];
double data2fit[10000];
double buffer[10000];
double baseline;   
double maximumValue, minimumValue;
double tobelog[3];    
double alpha, gamma, delta;

char mask_path[500];
char mask_name[500];
char mask_filename[500];
char file[500];

CNVData data;
CNVData fields;

struct mask_struct {
	char name[500];
	double voltages[512];
};
			
struct mask_struct mask[10];
/*---------------------------------------------------------------------------*/
/* Internal function prototypes                                              */
/*---------------------------------------------------------------------------*/
int send_board_commands (void);
int waveform(int color, int data_file);
int wavepreamble(void);
int wavexinterval(void);
int waveyscaling(void);
int wavex0(void);
int cleanbuffer (void);
int phase2voltage(double phi);

double display_masks(double drive_level[]);

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


double ModelFunct (double x, double a[], int ncoef);
void get_intensity(void);
static void CVICALLBACK dataCallback(void * handle,CNVData data, void * callbackData);

