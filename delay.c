/* Od Mateuszka Kami?skiego mkam@linux.pl */

#include <xc.h>
#include "delay.h"
#include <stdio.h>
#include <stdlib.h>

void delay_us(unsigned int us){
    us *= (SYS_FREQ / 1000000) / 2;
    _CP0_SET_COUNT(0);
    while (us > _CP0_GET_COUNT());
}
void delay_ms(unsigned int ms){
    delay_us(ms * 1000);
}
