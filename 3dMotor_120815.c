#include <stdio.h>
#include "pico/stdlib.h"

#define BTN_XM 0                                                //defining the Buttons
#define BTN_XP 1
#define BTN_YM 2
#define BTN_YP 3
#define BTN_ZM 4
#define BTN_ZP 5
#define BTN_START 6
#define BTN_STOP 7

const uint X_PINS[4] = {19, 18, 17, 16};                        //Motor Pins X Y Z
const uint Y_PINS[4] = {20, 21, 22, 26};
const uint Z_PINS[4] = {12, 13, 14, 15};

volatile bool emergency_stop = false;                           //volatile bool --> changeable and in every scope available

void gpio_callback(uint gpio, uint32_t events){                 //Interrupt Function for Stop

    if (gpio == BTN_STOP && (events & GPIO_IRQ_EDGE_FALL)){
        emergency_stop = true;
        printf("\n!!! Emergency Stop activated !!!\n");
    }
}

static const uint8_t STEP_SEQ[8][4] = {                         //Stepper List
    {1,0,0,0},
    {1,1,0,0},
    {0,1,0,0},
    {0,1,1,0},
    {0,0,1,0},
    {0,0,1,1},
    {0,0,0,1},
    {1,0,0,1}
};

void stepper_step_x(int step_index_x){                          //activate Pins for the X Motor
    for (int i = 0; i < 4; i++)
    {
        gpio_put(X_PINS[i], STEP_SEQ[step_index_x][i]);
    }  
}

void stepper_step_y(int step_index_y){                          //activate Pins for the Y Motor
    for (int i = 0; i < 4; i++) 
    {
        gpio_put(Y_PINS[i], STEP_SEQ[step_index_y][i]);
    }   
}

void stepper_step_z(int step_index_z){                          //activate Pins for the Z Motor
    for (int i = 0; i < 4; i++)
    {
        gpio_put(Z_PINS[i], STEP_SEQ[step_index_z][i]);
    }
}

int main()
{
    stdio_init_all();

    for (int i = 0; i < 4; i++)                     // Init for the X Motor
    {
        gpio_init(X_PINS[i]);
        gpio_set_dir(X_PINS[i], GPIO_OUT);
    }
    
    for (int i = 0; i < 4; i++)                     // Init for the Y Motor
    {
        gpio_init(Y_PINS[i]);
        gpio_set_dir(Y_PINS[i], GPIO_OUT);
    }

    for (int i = 0; i < 4; i++)                     // Init for the Z Motor
    {
        gpio_init(Z_PINS[i]);
        gpio_set_dir(Z_PINS[i], GPIO_OUT);
    }
    
    const uint btns[] = {BTN_START, BTN_STOP, BTN_XM, BTN_XP, BTN_YM, BTN_YP, BTN_ZM, BTN_ZP};

    for (int i = 0; i < sizeof(btns)/sizeof(btns[0]); i++)                        // Button init. with the array on top
    {                                                                             // sizeof --> easy changeable
        gpio_init(btns[i]);
        gpio_set_dir(btns[i], GPIO_IN);
        gpio_pull_up(btns[i]);
    }
    
    gpio_set_irq_enabled_with_callback(BTN_STOP, GPIO_IRQ_EDGE_FALL, true, &gpio_callback);         //interrupt setup

    int step_index_x = 0;                                                          // Starting Point
    int step_index_y = 0;
    int step_index_z = 0;

    while (true) {
        
        if (!gpio_get(BTN_START))                       //Every Button recognition
        {
            emergency_stop = false;
        }

        if (emergency_stop)
        {
            printf("\nSystem stopped\n");
            break;
        }

        if (!gpio_get(BTN_XM))
        {
            step_index_x = (step_index_x + 7) % 8;
            stepper_step_x(step_index_x);
            sleep_ms(2);
        }
        else if (!gpio_get(BTN_XP))
        {
            step_index_x = (step_index_x + 1) % 8;
            stepper_step_x(step_index_x);
            sleep_ms(2);
        }
        else if (!gpio_get(BTN_YM))
        {
            step_index_y = (step_index_y + 7) % 8;
            stepper_step_y(step_index_y);
            sleep_ms(2);
        }
        else if (!gpio_get(BTN_YP))
        {
            step_index_y = (step_index_y + 1) % 8;
            stepper_step_y(step_index_y);
            sleep_ms(2);
        }
        else if (!gpio_get(BTN_ZM))
        {
            step_index_z = (step_index_z + 7) % 8;
            stepper_step_z(step_index_z);
            sleep_ms(2);
        }
        else if (!gpio_get(BTN_ZP))
        {
            step_index_z = (step_index_z + 1) % 8;
            stepper_step_z(step_index_z);
            sleep_ms(2);
        }
    }
}
