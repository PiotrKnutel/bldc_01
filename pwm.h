/* PWM dla przetwornicy buck step-down CSD95377Q4M.
 * Realizowany poprzez blok Motor Control PWM (MCPWM). Nota "Section 44". */

#ifndef PWM_H
#define	PWM_H

#include <xc.h>
#include <stdio.h>
#include <stdlib.h>

void pwm_config();

#endif	/* PWM_H */
