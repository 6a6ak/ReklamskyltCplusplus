/* uart: is not called directly for I/O
*	provides the link between the UNO and the standard C I/O
*	tested and confirmed with puts(), getchar() and printf() 
*	blocking I/O, does not use interrupts, slow 9600 baud
*/

#ifndef UART_H
#define UART_H

void uart_init(void);
void uart_puts(const char *s);
void uart_gets(char *s, int size);

#endif