#include "mbed.h"
#include "display.h"
/*Declares all of my digigal inputs and outputs along with my interrupts */
DigitalOut red_light_1(D2);
DigitalOut amber_light_1(D3);
DigitalOut green_light_1(D4);
DigitalOut red_light_2(D5);
DigitalOut amber_light_2(D6);
DigitalOut green_light_2(D7);
InterruptIn  ped_button(D8);
InterruptIn safe_switch(USER_BUTTON);

int flagCheck, pedButton;   //Creates 2 global variables

void ped_switch(){          //Interrupt routine that sets the global variable to 1 to show that the button has been pressed
    pedButton=1;   
}

void flag_interrupt(){
   
    if(flagCheck==1){       //checks to see if the flag check has been set to 1 I.E the safe routine and changes if it has
        flagCheck=0;    
    }
    else if(flagCheck==0){  //checks to see if the flag check has been set to 0 I.E the unsafe routine and changes if it has
        flagCheck=1;
    }    
}
void ped_crossing(){
    pedButton=0;            //Clears the button flag variable
    red_light_1 = 1;        //Sets the 2 red lights on and all of the other lights off
    amber_light_1 = 0;
    green_light_1 = 0;
    red_light_2 = 1;
    amber_light_2 = 0;
    green_light_2 = 0;
    display_seven_segment();    //calls the 7 seven routine to count down from 9 to 0
    wait(0.2);
}

void safe_crossing(){
    red_light_1 = 1;        //sets the lights to red at the start of the sequence swap
    amber_light_1 = 0;
    green_light_1 = 0;
    red_light_2 = 1;
    amber_light_2 = 0;
    green_light_2 = 0;
    wait(2);
    
    red_light_2 = 0;        //1st sequence in the safe sequence order
    green_light_2 = 1;
    wait(5);
        
    amber_light_2 = 1;      //2nd sequence in the safe sequence order
    green_light_2 = 0;
    wait(5);
        
    red_light_2 = 1;        //3rd sequence in the safe sequence order
    amber_light_2 = 0;
    wait(5);
    
    if(pedButton==1){       //checks to see if pedestrian button has been pressed
        ped_crossing();     //If it has go to the function
        wait(0.1); 
    }     
        
    green_light_1 = 1;      //4th sequence in the safe sequence order
    red_light_1 = 0;
    wait(5);
        
    amber_light_1 = 1;      //5th sequence in the safe sequence order
    green_light_1 = 0;
    wait(5);
        
    red_light_1 = 1;        //6th sequence in the safe sequence order
    amber_light_1 = 0;
    wait(5);
        
    if(pedButton==1){       //checks to see if pedestrian button has been pressed
        ped_crossing();     //If it has go to the function
        wait(0.1); 
    }
}

void safe_fall(){           //Acts as a buffer for the switch being pressed
    wait(0.5);
}

void unsafe_crossing(){
    
        red_light_1 = 1;       //Initialises the 1st order of the unsafe sequence for all of the lights
        amber_light_1 = 0;
        green_light_1 = 0;
        red_light_2 = 0;
        amber_light_2 = 0;
        green_light_2 = 1;
        wait(5);
        
        amber_light_2 = 1;      //2nd sequence for the unsafe sequence
        green_light_2 = 0;
        wait(5);
        
        red_light_1 = 0;        //3rd sequence for the unsafe sequence
        green_light_1 = 1;
        red_light_2 = 1;
        amber_light_2 = 0;
        wait(5);
        
        amber_light_1 = 1;      //4th sequence for the unsafe sequence
        green_light_1 = 0;
        wait(5);
}    
int main(){
    
    safe_switch.rise(&flag_interrupt);  //Initialising all of the interrupts
    safe_switch.fall(&safe_fall);
    ped_button.rise(&ped_switch);
    
    flagCheck = 0;
    pedButton = 0;
    
    while(1){
        if(flagCheck==0){           //If the switch hasnt been pressed run the unsafe sequence
            unsafe_crossing();
        }
        else if(flagCheck==1){      //If the switch has been pressed run the safe sequence
            safe_crossing();        
        }  
    } 
}