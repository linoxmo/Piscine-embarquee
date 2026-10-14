#ifndef FT_ISR_H 
#define FT_ISR_H
#define sei() __asm__ __volatile__ ("sei" ::: "memory")
/*Enables interrupts by setting the global interrupt mask.
 - "sei" Set GLobal Interrupt Flag => Give the microcontroller the right to process interruptions
 - "__asm__ : sending assembler code"
 - "__volatile" : disable the compilator abilty to optimize that ligne
 - ":::"memory"":  clobber that indicates to thecompi;ator that this instruction  depends of variable stocked in RAM memory  
*/
#define cli() __asm__ __volatile__ ("cli" ::: "memory")
/*Enables interrupts by setting the global interrupt mask.
 - "cli" Clear Interrupt Flag => Desactivate sei
 - "__asm__ : sending assembler code"
 - "__volatile" : disable the compilator abilty to optimize that ligne
 - ":::"memory"":  clobber that indicates to thecompi;ator that this instruction  depends of variable stocked in RAM memory  
*/



#ifndef FT_ISR
#   define FT_ISR(vector) \
     void vector (void)__attribute__((__signal__, __used__, __externally_visible__));\
     void vector (void)
#endif

// declaration of function
// definition of function
/*
-__signal__ : Tells the compilator that this functionis an interruption
-__used__ :Tells the compilator that this functionn is activly used even  if its not  writen in the code c
-__externally_visible_: Tells the computer that this funciont should be visible
*/

#endif