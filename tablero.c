#include <tablero.h>

/*********Timer 1 interruption*************/
#int_TIMER1       // Timer 1 interruption
void TIMER1_isr(void)  //Function
{
   timer_counter++;
   if((input(set_time) == 0) && (timer_counter == 4))  // If switch is off
   {
      if(seconds == 0)
      {
         if(minutes > 0)
         {
            minutes--;
            seconds = 60;
            dec_uni(&minutes, &dec_min, &uni_min);
         }
         else{
            seconds = 1;
         }
      }
      seconds--;
      dec_uni(&seconds, &dec_sec, &uni_sec);
   }
   if(timer_counter >= 4) timer_counter = 0;
   set_timer1(timer_feed);   // Feed TMR1
}
/********************************************/

void main()
{
   setup_oscillator(OSC_8MHZ|OSC_INTRC);
   setup_timer_1(T1_INTERNAL | T1_DIV_BY_8);    // Internal = timer; External = counter; Prescaler = 8
   set_timer1(timer_feed);                      // Reload of Timer 1
   enable_interrupts(int_TIMER1);               // Enables Timer 1
   enable_interrupts(global);                   // Enables general interruption
   
   port_b_pullups(TRUE);
   
   while(1)
   {
      set_time_func();
      displays();
   }
}

// Function to set time
void set_time_func()
{
   int i = 0, limit = 0;
   if(input(set_time))
      {
         // Debouncing functions for switches
         if (input(pin_secup))   
         {
            option = 1;
            increment = 1;
            //input_pin = pin_secup;
            //debouncing(pin_secup, &increment);
            //output_pin = pin_out;
         }
         if (input(pin_secdown))
         {
            option = 2;
            increment = 1;
            //input_pin = pin_secdown;
            //debouncing(pin_secdown, &increment);
            //output_pin = pin_out2;
         }
         if (input(pin_minup))
         {
            option = 3;
            increment = 1;
            //input_pin = pin_minup;
            //debouncing(pin_minup, &increment);
            //output_pin = pin_out3;
         }
         if (input(pin_mindown))
         {
            option = 4;
            increment = 1;
            //input_pin = pin_mindown;
            //debouncing(pin_mindown, &increment);
            //output_pin = pin_out4;
         }
         
         //debouncing(input_pin,output_pin,&increment);
         //debouncing(input_pin, &increment);
         
         if (increment == 1)
         {
            increment = 0;  // Reset variable
            incre_decre(&option, &minutes, &seconds);
            /*
            // Incrementing or decrementing variables
            if (option == 1) seconds = seconds + 1;
            else if (option == 2) seconds = seconds - 1;
            else if (option == 3) minutes = minutes + 1;
            else if (option == 4) minutes = minutes - 1;
            
            // Setting limits
            if (seconds < 0)   seconds = 59;
            if (seconds > 59)  seconds = 0;
            if (minutes < 0)   minutes = 99;
            if (minutes > 99)  minutes = 0;  
            */
            dec_uni(&minutes, &dec_min, &uni_min);
            //dec_min = minutes / 10;
            //uni_min = minutes % 10;
            dec_uni(&seconds, &dec_sec, &uni_sec);
            //dec_sec = seconds / 10;
            //uni_sec = seconds % 10;
            
            limit = 330 / (delay_time * 4);
            for(i=1;i<=limit;i++)
            {
               displays();
            }
            //delay_ms(250); // To avoid multiple switch readings
         }
      }
}

/*
// Debouncing function applied to switches
void debouncing(in_mask, out_mask, int* incre)
{
   delay_ms(10);
   if (input(in_mask))
   {
      *incre = 1;
      output_high(out_mask);
   }
   else
      output_low(out_mask);
   //return(incre,up_down);
}*/

/*
// Debouncing function applied to switches
void debouncing(in_mask, int* incre)
{
   delay_ms(10);
   if (input(in_mask))  *incre = 1;
}*/


void incre_decre(int* options, unsigned int* min, unsigned int* sec)
{
   // Incrementing or decrementing variables
   if (*options == 1) *sec = *sec + 1;
   else if (*options == 2) *sec = *sec - 1;
   else if (*options == 3) *min = *min + 1;
   else if (*options == 4) *min = *min - 1;
   
   // Setting limits
   if (*sec < 0)   *sec = 59;
   if (*sec > 59)  *sec = 0;
   if (*min < 0)   *min = 99;
   if (*min > 99)  *min = 0;   
}

// Storing tens and units in its corresponding variables
void dec_uni(int* value, int* dec, int* uni)
{
   *dec = *value / 10;
   *uni = *value % 10;
}

// Multiplexing of 7 segment displays with delay
void displays()
{
   output_c(segments[uni_sec]);
   output_a(0x01);
   delay_ms(delay_time);
   
   output_c(segments[dec_sec]);
   output_a(0x02);
   delay_ms(delay_time);
   
   output_c(segments[uni_min]);
   output_a(0x04);
   delay_ms(delay_time);
   
   output_c(segments[dec_min]);
   output_a(0x08);
   delay_ms(delay_time);
}
