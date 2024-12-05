#include "lcd.h"
#include <avr/io.h>
#include <util/delay.h>

HD44780::HD44780() {
  position_x = 0;
  position_y = 0;
  Initialize();
}

void HD44780::WriteCommand(unsigned char cmd) {
  OutNibble(cmd >> 4);
  OutNibble(cmd);
  _delay_us(50);
}

void HD44780::WriteData(unsigned char data) {
  LCD_RS_PORT |= LCD_RS;
  Write(data);
  LCD_RS_PORT &= ~LCD_RS;
}

void HD44780::WriteText(const char *text) {
    // Write text to display code
}

void HD44780::GoTo(unsigned char x, unsigned char y) {
  unsigned char addr = 0x80 + x + (0x40 * y);
  WriteCommand(addr);
}

void HD44780::Clear() {
    // Clear display code
}

void HD44780::Home(void) {
  WriteCommand(HD44780_HOME);
  _delay_ms(2);
}

void HD44780::Initialize() {
    // Initialization code
}

void HD44780::OutNibble(unsigned char nibble) {
  if (nibble & 1)
    LCD_DB4_PORT |= LCD_DB4;
  else
    LCD_DB4_PORT &= ~LCD_DB4;
  if (nibble & 2) 
    LCD_DB5_PORT |= LCD_DB5;
  else
    LCD_DB5_PORT &= ~LCD_DB5;
  if (nibble & 4)
    LCD_DB6_PORT |= LCD_DB6;
  else
    LCD_DB6_PORT &= ~LCD_DB6;
  if (nibble & 8)
    LCD_DB7_PORT |= LCD_DB7;
  else
    LCD_DB7_PORT &= ~LCD_DB7;

  LCD_E_PORT |= LCD_E;
  _delay_us(1);
  LCD_E_PORT &= ~LCD_E;
}

void HD44780::Write(unsigned char byte) {
  OutNibble(byte >> 4);
  OutNibble(byte);
}

#define LCD_SETCGRAMADDR 0x40
void HD44780::CreateChar(uint8_t location, uint8_t charArray[]) {
  location &= 0x7;
  WriteCommand(LCD_SETCGRAMADDR | (location << 3));
  for (uint8_t i = 0; i < 8; i++) {
    WriteData(charArray[i]);
  }
}