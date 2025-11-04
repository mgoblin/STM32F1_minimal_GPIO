#include "stm32f1xx.h"

#define LED1 (13)
#define BUTTON (14)
#define ENABLE_PORTC_CLOCK (RCC->APB2ENR |= RCC_APB2ENR_IOPCEN)

void ms_delay(int ms)
{
   while (ms-- > 0) {
      volatile int x=500;
      while (x-- > 0)
         __asm("nop");
   }
}
int main(void)
{
    ENABLE_PORTC_CLOCK;

    GPIOC->CRH &= ~(
          GPIO_CRH_MODE13 | GPIO_CRH_CNF13 | GPIO_CRH_MODE14 | GPIO_CRH_CNF14
    );

    GPIOC->CRH |= (GPIO_CRH_MODE13_0);
    GPIOC->CRH |= (0x02 << GPIO_CRH_CNF14_Pos);
    GPIOC->ODR |= (1 << BUTTON); 

    while (1)
    {
        uint32_t idr_val = ~GPIOC->IDR;
        if (idr_val  & (1 << BUTTON))
        {
            GPIOC->ODR ^= (1 << LED1);
            ms_delay(500);
        } 
        else 
        {
            GPIOC->ODR |= (1 << LED1);
        }
    }
    return 0;
}