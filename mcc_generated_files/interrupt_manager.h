

#ifndef _INTERRUPT_MANAGER_H
#define _INTERRUPT_MANAGER_H

/**
  @Summary
    Initializes the interrupt priorities of the dsPIC33EV256GM106

  @Description
    This routine sets the interrupt priorities of the modules that have been configured
    for the dsPIC33EV256GM106

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        INTERRUPT_Initialize ();
    }
    </code>

*/
void INTERRUPT_Initialize(void);

/**
  @Summary
    Enables global interrupts of the dsPIC33EV256GM106

  @Description
    This routine enables the global interrupt bit for the dsPIC33EV256GM106

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        INTERRUPT_GlobalEnable ();
    }
    </code>

*/
inline static void INTERRUPT_GlobalEnable(void)
{
    __builtin_enable_interrupts();
}

/**
  @Summary
    Disables global interrupts of the dsPIC33EV256GM106

  @Description
    This routine disables the global interrupt bit for the dsPIC33EV256GM106

  @Preconditions
    None.

  @Returns
    None.

  @Param
    None.

  @Example
    <code>
    void SYSTEM_Initialize(void)
    {
        // Other initializers are called from this function
        INTERRUPT_GlobalDisable ();
    }
    </code>

*/
inline static void INTERRUPT_GlobalDisable(void)
{
    __builtin_disable_interrupts();
}


#endif