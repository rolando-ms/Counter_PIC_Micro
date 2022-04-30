//#include <18F4520.h>
#include <16F887.h>
//#device ADC=16

#FUSES   XT,NOWDT,NOBROWNOUT,PUT,NOWRT

#use delay(internal=2000000)

// Switches
#define  pin_secup   PIN_B0
#define  pin_secdown PIN_B1
#define  pin_minup   PIN_B2
#define  pin_mindown PIN_B3

// Test switches (LED outputs)
//#define  pin_out  PIN_B4
//#define  pin_out2 PIN_B5
//#define  pin_out3 PIN_B6
//#define  pin_out4 PIN_B7

// Enable display pins
#define  disp_min_dec   PIN_A3
#define  disp_min_uni   PIN_A2
#define  disp_sec_dec   PIN_A1
#define  disp_sec_uni   PIN_A0

// Pin to set time
#define  set_time PIN_B4

// Delay
#define  delay_time   30

//#use standard_io(d)

/* Function prototypes */
//void debouncing(pin_mask, out_pin,int* incre);
void debouncing(pin_mask, int* incre);
void incre_decre(int* options, unsigned int* min, unsigned int* sec);
void dec_uni(int* value, int* dec, int* uni);
void set_time_func();
void displays();

// Global variables
int increment = 0, min_up = 0, min_down = 0, sec_up = 0, sec_down = 0,
option = 0, dec_min = 0, uni_min = 0, dec_sec = 0, uni_sec = 0;
unsigned int minutes = 0, seconds = 0;
unsigned char input_pin, output_pin;
// Common cathode (a,b,...,g - pin0, pin1,...,pin6)
//int segments[10] = {0x3F, 0x06, 0x5B, 0x4F, 0x66, 0x6D, 0x7D, 0x07, 0x7F
//0x6F};
//Common Anode (a,b,...,g - pin0, pin1,...,pin6)
int segments[10] = {0x40, 0x79, 0x24, 0x30, 0x19, 0x12, 0x02, 0x78, 0x00
0x10};
