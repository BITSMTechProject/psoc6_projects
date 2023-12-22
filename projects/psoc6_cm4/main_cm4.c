/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#include "cy_pdl.h"

#define GPIO_BASE                               0x40320000UL
#define GPIO                                    ((GPIO_Type*) GPIO_BASE) 
#define GPIO_PRT13                              ((GPIO_PRT_Type*) &GPIO->PRT[13]) 

/*****************************************************************************
* Function Name: main(void)
******************************************************************************
* Summary:
*  Entry to the application.
*
* Parameters:
*  void

* Return:
*  Does not return.
*****************************************************************************/
int main(void)
{

    cy_stc_gpio_pin_config_t pinCfg;
    
    memset((void *)&pinCfg, 0, sizeof(pinCfg));
    pinCfg.driveMode = CY_GPIO_DM_STRONG_IN_OFF;
    pinCfg.hsiom = 0;
    Cy_GPIO_Pin_Init(GPIO_PRT13, 7u, &pinCfg);

    
    while (1) {
        Cy_GPIO_Inv(GPIO_PRT13, 7u);
        Cy_SysLib_Delay(10);
    }

    /* Return statement will not be hit. */
    return 0;
}

/* [] END OF FILE */
