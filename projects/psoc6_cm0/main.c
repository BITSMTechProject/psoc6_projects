/******************************************************************************
* File Name:   main.c
*
* Description: This is the source code for CM0+ in the the Dual CPU Empty 
*              Application for ModusToolbox.
*
* Related Document: See README.md
*
*
*******************************************************************************
* Copyright 2020-2021, Cypress Semiconductor Corporation (an Infineon company) or
* an affiliate of Cypress Semiconductor Corporation.  All rights reserved.
*
* This software, including source code, documentation and related
* materials ("Software") is owned by Cypress Semiconductor Corporation
* or one of its affiliates ("Cypress") and is protected by and subject to
* worldwide patent protection (United States and foreign),
* United States copyright laws and international treaty provisions.
* Therefore, you may use this Software only as provided in the license
* agreement accompanying the software package from which you
* obtained this Software ("EULA").
* If no EULA applies, Cypress hereby grants you a personal, non-exclusive,
* non-transferable license to copy, modify, and compile the Software
* source code solely for use in connection with Cypress's
* integrated circuit products.  Any reproduction, modification, translation,
* compilation, or representation of this Software except as specified
* above is prohibited without the express written permission of Cypress.
*
* Disclaimer: THIS SOFTWARE IS PROVIDED AS-IS, WITH NO WARRANTY OF ANY KIND,
* EXPRESS OR IMPLIED, INCLUDING, BUT NOT LIMITED TO, NONINFRINGEMENT, IMPLIED
* WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE. Cypress
* reserves the right to make changes to the Software without notice. Cypress
* does not assume any liability arising out of the application or use of the
* Software or any product or circuit described in the Software. Cypress does
* not authorize its products for use in any products where a malfunction or
* failure of the Cypress product may reasonably be expected to result in
* significant property damage, injury or death ("High Risk Product"). By
* including Cypress's product in a High Risk Product, the manufacturer
* of such system or application assumes all risk of such use and in doing
* so agrees to indemnify Cypress against all liability.
*******************************************************************************/


#include "cy_pdl.h"
#include "system_psoc6.h"
#include "cy_device.h"
#include <gpio_psoc6_02_124_bga.h>

cy_stc_gpio_pin_config_t pinConfig = {
        /*.outVal =*/       1UL,                    /* Output = High */
        /*.driveMode =*/    CY_GPIO_DM_PULLUP,      /* Resistive pull-up, input buffer on */
        /*.hsiom =*/        P13_7_GPIO,              /* Software controlled pin */
        /*.intEdge =*/      CY_GPIO_INTR_RISING,    /* Rising edge interrupt */
        /*.intMask =*/      1UL,                    /* Enable port interrupt for this pin */
        /*.vtrip =*/        1,     /* CMOS voltage trip */
        /*.slewRate =*/     0,      /* Fast slew rate */
        /*.driveSel =*/     0,     /* Full drive strength */
        /*.vregEn =*/       0UL,                    /* SIO-specific setting - ignored */
        /*.ibufMode =*/     0UL,                    /* SIO-specific setting - ignored */
        /*.vtripSel =*/     0UL,                    /* SIO-specific setting - ignored */
        /*.vrefSel =*/      0UL,                    /* SIO-specific setting - ignored */
        /*.vohSel =*/       0UL                     /* SIO-specific setting - ignored */
    };
    

int main(void)
{
    /* Enable global interrupts */
    __enable_irq();

    Cy_GPIO_Pin_Init(P13_7_PORT, P13_7_PIN, &pinConfig);

    
    while (1) {
        Cy_GPIO_Inv(P13_7_PORT, P13_7_PIN);
        Cy_SysLib_Delay(1000);
    }

    // /* Enable CM4. CY_CORTEX_M4_APPL_ADDR must be updated if CM4 memory layout is changed. */
    // Cy_SysEnableCM4(CY_CORTEX_M4_APPL_ADDR);

    // for (;;)
    // {
    //     Cy_SysPm_DeepSleep(CY_SYSPM_WAIT_FOR_INTERRUPT);
    // }
    while(1);
}

/* [] END OF FILE */
