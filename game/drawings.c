#include "../devices/uart.h"

void drawHangman(uint8_t triesLeft)
{
  switch (triesLeft)
  {
    case 0:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |      \\|/\n");
      uart_writeString("  |       |\n");
      uart_writeString("  |      / \\\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 1:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |      \\|/\n");
      uart_writeString("  |       |\n");
      uart_writeString("  |      / \n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 2:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |      \\|/\n");
      uart_writeString("  |       |\n");
      uart_writeString("  | \n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 3:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |       |/\n");
      uart_writeString("  |       |\n");
      uart_writeString("  | \n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 4:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |       |\n");
      uart_writeString("  |       |\n");
      uart_writeString("  | \n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 5:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |      (_)\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 6:
      uart_writeString("   _______\n");
      uart_writeString("  |/      |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 7:
      uart_writeString("   _______\n");
      uart_writeString("  |/\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 8:
      uart_writeString("   _______\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 9:
      uart_writeString("   \n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString("  |\n");
      uart_writeString(" _|___\n");
      break;
    case 10:
      uart_writeString("   \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString(" _____\n");
      break;
    case 11:
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      uart_writeString("  \n");
      break;
    default:
      uart_writeString("TriesLeft not in valid interval\n");
  }
}
