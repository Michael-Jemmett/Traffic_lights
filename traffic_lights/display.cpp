#include "display.h"
#include "mbed.h"
/* Declares my pins D9 to D15 as digital outputs */
extern DigitalOut A(D9);
extern DigitalOut B(D10);
extern DigitalOut C(D11);
extern DigitalOut D(D12);
extern DigitalOut E(D13);
extern DigitalOut F(D14);
extern DigitalOut G(D15);


void display_seven_segment(){
    A=0; B=0; C=0;D=1;E=1;F=0;G=0; //9
    wait(1);
    A=0; B=0; C=0;D=0;E=0;F=0;G=0; //8
    wait(1);
    A=0; B=0; C=0;D=1;E=1;F=1;G=1; //7
    wait(1);
    A=1; B=1; C=0;D=0;E=0;F=0;G=0; //6
    wait(1);
   A=0; B=1; C=0;D=0;E=1;F=0;G=0; //5
    wait(1);
    A=1; B=0; C=0;D=1;E=1;F=0;G=0; //4
    wait(1);
    A=0; B=0; C=0;D=0;E=1;F=1;G=0; //3
    wait(1);
    A=0; B=0; C=1;D=0;E=0;F=1;G=0; //2
    wait(1);
    A=1; B=0; C=0;D=1;E=1;F=1;G=1; //1
    wait(1);
    A=0; B=0; C=0;D=0;E=0;F=0;G=1; //0
    wait(1);
}


   
    

    

   
