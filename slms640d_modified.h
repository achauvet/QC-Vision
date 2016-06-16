
//#ifndef _LIBSLMS640D_H
#define _LIBSLMS640D_H


#ifdef __cplusplus
    extern "C" {
#endif


#include <fctypes_modified.h>

#include <stdio.h>

#define SLMS640D_VERSION_MAJOR (1)
#define SLMS640D_VERSION_MINOR (1)

#define SLM_GUID(g)   \
(fuint32) (g & 0xffffffff), (fuint32)((g>>32) & 0xffffffff)
		
		
/**This enum lists all possible success/error values.
If you get error SLM_Error_Communication, you can call SLM_GetFirewireError() to get
a more detailed error code.
*/
enum
{
   SLM_Ok=                          0,   ///< Everything ok :-)
   SLM_Error=                       1,   ///< It seems there was an error...
   SLM_Error_InvalidParameter=      2,   ///< The value of one of the input parameters was outside the valid range.
   SLM_Error_CommandNotTerminated=  3,   ///< The given command was not 0-terminated within SLM_MAX_TEXT_SIZE bytes.
   SLM_Error_TooManyParameters=     4,   ///< The command given to SLM_OperateTextCommand contained to many parameters.
   SLM_Error_Communication=         5,   ///< There was an error in the firewire communication with the modulator.
   SLM_Error_NoSuchDevice=          6,
   SLM_Error_NullPointer=           7,   ///< You gave a null pointer as a parameter to a function, which really requires a valid pointer.
   SLM_Error_UnknownCommand=     0x80,   ///<unknown command id
   SLM_Error_WrongVersion=       0x81,   ///<unsupported protocol version
   SLM_Error_CompatMode=         0x82,   ///<a new command was received but the device is in compat mode
   SLM_Error_InvalidDisplay=     0x83,   ///<an invalid display number was found (e.g. 2 if there are only displays a and b)
   SLM_Error_InvalidStripe=      0x84,   ///<an invalid stripe index was found
   SLM_Error_ValueOutOfRange=    0x85,   ///<a parameter value was out of range
   SLM_Error_SequenceActive=     0x86,   ///<a command was received which can't be executed if a sequence is active
   SLM_Error_ExpActive=          0x87,   ///<a command was received which can't be executed if the exposure time is still active
   SLM_Error_TestActive=         0x88,   ///<... while the device is in test mode
   SLM_Error_ModulatorStopped=   0x89,   ///<the modulator has been stopped due to critical hardware conditions
   SLM_Error_InvalidPattern=     0x8a,   ///<an invalid pattern index was found
   SLM_Error_PatternInSequence=  0x8b,   ///<the specified pattern is used in a sequence
   SLM_Error_Processing=         0x8c,   ///<something unexpected happened
   SLM_Error_SequenceTooLong=    0x8d,   ///<given sequence is too long
   SLM_Error_NoSequence=         0x8e,   ///<get seq but no sequence was defined
   SLM_Error_TooSmall=           0x8f,   ///<the given data array is not big enough to hold all data
   SLM_Error_InvalidCount=       0x90,  
   SLM_Error_TableEmpty=         0x91,
   SLM_Error_EnhancedMode=       0x92,
   SLM_Error_InvalidSensor=      0x93,   ///<invalid temperature sensor
   SLM_Error_InvalidMode=        0x94    ///<invalid exposure mode
};

///This is the return type for all functions of this library.
typedef int SLM_Result;

/** This enum is used to specify display A or B. This is used in almost all functions
which deal with the displays. 
\sa  SLM_DirectStripe(), SLM_Direct(), SLM_DirectPattern(), SLM_WritePattern(),
SLM_FillPattern(), SLM_FillAllPattern(), SLM_RotatePattern(), SLM_SetPatternStripe(),
SLM_GetPattern(), SLM_IsPatternValid(), SLM_AllPatternValid(),
SLM_SetHighVoltage(), SLM_IsHighVoltageSet(), SLM_GetLcdVoltage()
*/
typedef enum 
{
   SLM_DisplayA=0,     ///<Use display A
   SLM_DisplayB=1      ///<Use display B
} SLM_DisplayId;

/** This enum is used to specify which temperature sensor to query.
 \sa SLM_GetTemperature
 */
typedef enum
{
   SLM_TempSensorA=0,
   SLM_TempSensorB=1
} SLM_TempSensorId;

/** Specify the exposure mode of the patterns, especially useful in pattern sequences.
\sa SLM_SetExpParam(), SLM_GetExpParam(), SLM_SetExpMode(), SLM_GetExpMode()
*/
typedef enum
{
   SLM_ExposureTrigger=0,    ///<Proceed with the next pattern after a specified number of trigger events
   SLM_ExposureTime=1        ///<Proceed with the next pattern after a specified time
} SLM_ExposureModeId;

/** Initializes the library. You have to call SLM_Init() once
 before using any other function of this library.\n
 Internal data structures of the library are initialized and the multithreading
 required for the communication with the modulator is started.\n
 \returns
 SLM_Ok\n
 SLM_Error_Communication\n
 \sa SLM_Exit()
 */

struct SLM_VersionInfo
{
   unsigned int major;     ///< The major version number.
   unsigned int minor;     ///< The minor version number.
   unsigned int year;      ///< The year of the release date of the modulator.
   unsigned int month;     ///< The month of the release date of the modulator.
   unsigned int day;       ///< The release of day of the release date of the modulator.
   char text[128];         ///< The name and some human readable information.
};


int __stdcall SLM_Init(void);
void __stdcall SLM_Exit(void);   
int __stdcall SLM_FindDevices(unsigned int length, fuint32* devices, unsigned int *real_size);     
int __stdcall SLM_Connect(fuint32 guid_low, fuint32 guid_high);  
int __stdcall SLM_InitModulator(fuint32 guid_low, fuint32 guid_high);
int __stdcall SLM_GetVersion(fuint32 guid_low, fuint32 guid_high, struct SLM_VersionInfo* version); 
int __stdcall SLM_GetTemperature(fuint32 guid_low, fuint32 guid_high, SLM_TempSensorId sensor, float *temp);




int __stdcall SLM_GetFirewireError();

int __stdcall  SLM_Disconnect(fuint32 guid_low, fuint32 guid_high);


/** Before disconnecting from the modulator with SLM_Disconnect(), you have to*/

int __stdcall  SLM_ExitModulator(fuint32 guid_low, fuint32 guid_high);


int __stdcall  SLM_GetVersion(fuint32 guid_low, fuint32 guid_high, struct SLM_VersionInfo* version);

int __stdcall  SLM_GetTemperature(fuint32 guid_low, fuint32 guid_high, SLM_TempSensorId sensor, float *temp);

int __stdcall  SLM_StartTest(fuint32 guid_low, fuint32 guid_high);

int __stdcall  SLM_NextTest(fuint32 guid_low, fuint32 guid_high);

int __stdcall  SLM_StopTest(fuint32 guid_low, fuint32 guid_high);

/** This function affects the specified modulator immediately. It sets the count of a single stripe
on one display to the given value.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param stripe - the number of the stripe
 \param value - the new value (count) of the stripe
 \returns  */

int __stdcall  SLM_DirectStripe(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int stripe, unsigned int value);

/** This function immediately sets all stripes of one display to the given value.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param value - the new value (count) of the stripe
 \returns  */

int __stdcall  SLM_Direct(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int value);

/** This function immediately sets all stripes of one display to the
values given in a array \a pattern. It does \em not affect the pattern memory in the modulator.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param length - number of values contained in the array \a values, \em not the size in bytes
 \param values - array containing the values (counts), each value corresponds to one stripe
 \returns */
/*
 \b Example: \n
 int result=0;
 fuint64 guid=...;
 SLM_DisplayId display=SLM_DisplayA;
 unsigned int length=640;
 unsigned int pattern[640];
// ... fill the pattern with values...
 result=SLM_DirectPattern(SLM_GUID(guid), display, length, pattern);
 \endcode
 */
int __stdcall  SLM_DirectPattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int length, unsigned int *values);

/** This function writes one pattern to the internal pattern memory of the modulator.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param pattern - the pattern number
 \param length - the number of values contained in the array \a values, i.e. not the size in bytes
 \param values - array of integers holding the values (counts) for the pattern
 \returns */

int __stdcall  SLM_WritePattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int pattern, unsigned int length, unsigned int *values);

/** This function fills one pattern in the pattern memory of the modulator with one value.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param pattern - the pattern number
 \param value - the fill value (count)

 \returns   */

int __stdcall  SLM_FillPattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int pattern, unsigned int value);

/** This function sets all pattern assigned to one display to one value.
 */
int __stdcall  SLM_FillAllPattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int value);

/** Rotate (or shift) the contents of a pattern in the pattern memory of the modulator 
 */
int __stdcall  SLM_RotatePattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int pattern, int rotate);

/** Change a single stripe of the specified pattern in the pattern memory of the modulator.
 */
int __stdcall  SLM_SetPatternStripe(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int pattern, unsigned int stripe, unsigned int value);

/** Activate i.e. display a pattern pair from the pattern memory on the modulator. The patterns
have to be valid in order to be activated. This means the pattern has to be filled when you 
call SLM_ActivatePattern().
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param pattern - the pattern number
 \returns  */

int __stdcall  SLM_ActivatePattern(fuint32 guid_low, fuint32 guid_high, /*SLM_DisplayId display,*/ unsigned int pattern);

/** Obtain the contents of a pattern from the pattern memory.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param display - display A or B
 \param pattern - the pattern number
 \param size - the length of the array \a values, \em not the size in bytes
 \param values - an array of integers, it will be filled with the pattern contents
 \param real_size - pointer to an int, here you will find the number of stripes in the pattern, i.e. how big the array \a values should be.
 \returns */
 
int __stdcall  SLM_GetPattern(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, unsigned int pattern, unsigned int size, unsigned int *values, unsigned int *real_size);

/** Checks whether a pattern is valid, i.e. ready to be displayed using SLM_ActivatePattern().
A pattern becomes valid if you have filled it with contents, you can do this with SLM_WritePattern(),
SLM_FillPattern() or SLM_FillAllPattern(). */

/** Check whether all pattern for one display are valid, see also SLM_IsPatternValid() .
*/

int __stdcall  SLM_AllPatternValid(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, int* valid);

/** Adjust the parameter for an exposure mode.*/

int __stdcall  SLM_SetExpParam(fuint32 guid_low, fuint32 guid_high, SLM_ExposureModeId mode, fint16 value);

/** Query the parameter for an exposure mode. */

int __stdcall  SLM_GetExpParam(fuint32 guid_low, fuint32 guid_high, SLM_ExposureModeId mode, fint16* value);

/** Set the exposure mode, especially useful when working with sequences. Currently
yu can chose between timed and triggered exposure. The different exposure can be parameterized.
*/ 

int __stdcall  SLM_SetExpMode(fuint32 guid_low, fuint32 guid_high, SLM_ExposureModeId mode);

/** Obtain the currently active exposure mode. See also SLM_SetExpMode().
*/

int __stdcall  SLM_GetExpMode(fuint32 guid_low, fuint32 guid_high, SLM_ExposureModeId *mode);


/** Set the delay time after a pattern exposure has started.
*/
int __stdcall  SLM_SetDelay(fuint32 guid_low, fuint32 guid_high, fuint16 delay);

/** Obtain the current delay time. */

int __stdcall  SLM_GetDelay(fuint32 guid_low, fuint32 guid_high, fuint16 *delay);

/** Obtain the voltage measured by the built-in AD-converter. The digital 12-bit value
directly from the ADC is returned, i.e. the value can range from 0 up to to 4095, which
equals 2.5 Volt.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param value - here the AD conversion result will be entered
*/ 

int __stdcall  SLM_GetADC(fuint32 guid_low, fuint32 guid_high, unsigned int *value);

/** Define a sequence of patterns which can be "played" automatically on the
modulator. Depending on the current exposure mode the next pattern will
be activated  either after a fixed timeout or after a number of trigger events.
In order to start a sequence, the required patterns have to be filled
with valid patterns, both for display A \em and \em B if you have a double display modulator.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param length - the number of patterns in the array \a sequence, not the size in bytes
 \param sequence - the array containing the numbers of the desired patterns
 \returns
*/
int __stdcall  SLM_DefineSequence(fuint32 guid_low, fuint32 guid_high, unsigned int length, unsigned int *sequence);

/** Get the defined pattern sequence from the modulator. */

int __stdcall  SLM_GetSequence(fuint32 guid_low, fuint32 guid_high, unsigned int length, unsigned int *sequence, unsigned int *real_size);

/** Starts a defined sequence.*/

int __stdcall  SLM_StartSequence(fuint32 guid_low, fuint32 guid_high);

/** Stops a running sequence. */

int __stdcall  SLM_StopSequence(fuint32 guid_low, fuint32 guid_high);

/** Clears a defined sequence.  */

int __stdcall  SLM_ClearSequence(fuint32 guid_low, fuint32 guid_high);

/** Generates a trigger event in the modulator. You can use it if you
 want to simulate an external trigger with software, e.g. when running
 sequences. */

int __stdcall  SLM_Trigger(fuint32 guid_low, fuint32 guid_high);

/** Set the trigger out signal of the modulator via software.
 You can use this e.g. together with SLM_DirectPattern() to
 synchronize external hardware to the modulator.*/

int __stdcall  SLM_SetTriggerOut(fuint32 guid_low, fuint32 guid_high, unsigned int value);

/** Get the current state trigger out signal of the modulator.*/

int __stdcall  SLM_GetTriggerOut(fuint32 guid_low, fuint32 guid_high, unsigned int* value);

///Use this type to read and write the non-volatile user data of the modulator.
typedef char SLM_UserData[65520];

/** Read the user data from the modulator  */

int __stdcall  SLM_ReadUserData(fuint32 guid_low, fuint32 guid_high, SLM_UserData data);

/** The modulator offers an memory area of 65520 bytes for storing user-defined data.
This data is not volatile, i.e. it is not lost on power-off.\n
*/
int __stdcall  SLM_WriteUserData(fuint32 guid_low, fuint32 guid_high, const SLM_UserData data);

/**Used for the modulator specific transmission data.
\sa SLM_TableSet, SLM_ReadTableSet(), SLM_WriteTableSet()
*/
typedef unsigned int SLM_DisplayTable[4096] ;

/**Contains the four transmission tables which describe the 
transmission properties of the two displays.
\sa SLM_DisplayTable, SLM_ReadTableSet(), SLM_WriteTableSet()
*/
struct SLM_TableSet
{
   SLM_DisplayTable tableALow;            ///<display A, low voltage
   SLM_DisplayTable tableAHigh;           ///<display A, high voltage
   SLM_DisplayTable tableBLow;            ///<display B, low voltage
   SLM_DisplayTable tableBHigh;           ///<display B, high voltage
};

/** Read a set of transmission tables from the modulator. */

int __stdcall  SLM_ReadTableSet(fuint32 guid_low, fuint32 guid_high, struct SLM_TableSet* tables);

/** Write a set of transmission tables into the modulator. \n*/

int __stdcall  SLM_WriteTableSet(fuint32 guid_low, fuint32 guid_high, const struct SLM_TableSet* tables);

/** Set the voltage for a display to \em high or \em low . */

int __stdcall  SLM_SetHighVoltage(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, int high_voltage);

/** Check whether the voltage for a display is set to \em high . */

int __stdcall  SLM_IsHighVoltageSet(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, int* high_voltage);

/** Obtain the current voltage for a display .  */

int __stdcall  SLM_GetLcdVoltage(fuint32 guid_low, fuint32 guid_high, SLM_DisplayId display, float* voltage);

/** Return the time in hours this modulator has been running. */

int __stdcall  SLM_GetUptime(fuint32 guid_low, fuint32 guid_high, fuint32* uptime);

/** Used with SLM_GetConfig() to get some information about the device.
\sa SLM_GetConfig()
*/
struct SLM_ConfigData
{
   unsigned int number_of_displays;             ///<The number of displays in the modulator (should be 1 or 2)
   unsigned int number_of_stripes;              ///<The number of stripes per display (usually 640 or 320)
   unsigned int max_number_of_patterns;         ///<The maximum number of patterns you can store in the modulator for each display.
   unsigned int max_voltage;                    ///<The maximum value (count) you can set for a stripe. With 12 bit resolution this is 4095.
};

/** Get the hardware configuration information about the modulator.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param config - pointer to a SLM_ConfigData structure, this will be filled with the values
 \returns */

int __stdcall  SLM_GetConfig(fuint32 guid_low, fuint32 guid_high, struct SLM_ConfigData *config);

///Maximum size of a command or command response of a text command
#define SLM_MAX_TEXT_SIZE (4*1024)

/** Sends a text command to th modulator.\n
They have to follow the syntax as documented in your printed manual.
 \param guid_low , guid_high - the GUID of the modulator, split in two 32 bit integers
 \param command - the text command, it has to be '\\0'-terminated and may not exceed SLM_MAX_TEXT_SIZE bytes
 \param error - if this is not NULL, you get a return code here as in all other functions
 \returns either the response text or NULL if there was an error
*/
const char* __stdcall SLM_OperateTextCommand(fuint32 guid_low, fuint32 guid_high, const char* command, int *error);











#ifdef __cplusplus
}
#endif

