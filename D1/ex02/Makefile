MCU=atmega328p
CC=avr-gcc
OBJCOPY=avr-objcopy
AVRDUDE=avrdude
CFLAGS= -DF_CPU=$(F_CPU)  -mcall-prologues -mmcu=$(MCU) -Os
TARGET=main


LDFLAGS=-Wl,-relax
F_CPU=16000000UL
BAUD=115200
PORT=/dev/ttyUSB0

all: hex flash

hex: $(TARGET).hex

$(TARGET).hex: $(TARGET).c
	$(CC) $(CFLAGS) $(LDFLAGS) -o $(TARGET).elf $<
	$(OBJCOPY) -O binary -R .eeprom $(TARGET).elf $(TARGET).bin 
	$(OBJCOPY) -I binary -O ihex $(TARGET).bin $(TARGET).hex

flash:  $(TARGET).hex
		$(AVRDUDE) -F -V -c arduino -p $(MCU) -P $(PORT) -b $(BAUD) -U flash:w:$<:i

fclean:
		rm -f $(TARGET).elf $(TARGET).bin $(TARGET).hex

.PHONY: all hex flash fclean
