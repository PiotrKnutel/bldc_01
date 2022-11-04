#ifndef ADC_H
#define	ADC_H

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

void ADC_init(void);
void ADC_meas(unsigned int*, unsigned int*, unsigned int*, unsigned int*,
        unsigned int*, unsigned int*);

#endif	/* ADC_H */

