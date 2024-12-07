CC=C:\avr\bin\avr-g++
LD=C:\avr\bin\avr-ld
OBJCOPY="C:\avr\bin\avr-objcopy"
OBJDUMP="C:\avr\bin\avr-objdump"
AVRSIZE="C:\avr\bin\avr-size"
OBJISP="C:\avr\bin\avrdude"
MCU=atmega328p
<<<<<<< HEAD
CFLAGS=-Wall -Wextra -Wundef -pedantic \
		-Os -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=19200 -I.
=======
CFLAGS=-Wall -Wextra  -Wundef -pedantic \
		-Os  -DF_CPU=16000000UL -mmcu=${MCU} -DBAUD=19200
>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190
LDFLAGS=-mmcu=$(MCU)
PORT=\\\\.\\COM3
BIN=avrdemo
OUT=${BIN}.hex
<<<<<<< HEAD
SOURCES = main.cpp lcd.cpp uart.cpp customers.cpp customers_data.cpp utilities.cpp
=======
SOURCES = main.cpp lcd.cpp uart.cpp Costumer.cpp
>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190

DEBUG?=1

ifeq ($(DEBUG), 1)
	OUTPUTDIR=bin/debug
else
	OUTPUTDIR=bin/release
endif

OBJS =  $(addprefix $(OUTPUTDIR)/,$(SOURCES:.cpp=.o))

<<<<<<< HEAD
all: $(OUTPUTDIR) $(OUT)

$(OBJS): Makefile $(wildcard *.h)

$(OUTPUTDIR)/%.o: %.cpp
=======
all: $(OUTPUTDIR)  $(OUT) 

$(OBJS): Makefile

$(OUTPUTDIR)/%.o:%.cpp
>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190
	$(CC) $(CFLAGS) -MD -o $@ -c $<

%.lss: %.elf
	$(OBJDUMP) -h -S -s $< > $@

%.elf: $(OBJS)
	$(CC) -Wl,-Map=$(@:.elf=.map) $(LDFLAGS) -o $@ $^
	$(AVRSIZE) $@

<<<<<<< HEAD
=======

$(OBJS):$(SOURCES)

>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190
%.hex: %.elf
	$(OBJCOPY) -O ihex -R .fuse -R .lock -R .user_signatures -R .comment $< $@

isp: ${BIN}.hex
	$(OBJISP) -F -V -c arduino -p ${MCU} -P ${PORT} -U flash:w:$<

<<<<<<< HEAD
clean:
	@if exist "$(OUT)" del "$(OUT)"
	@if exist "*.map" del "*.map"
	@if exist "*.P" del "*.P"
	@if exist "*.d" del "*.d"
	@if exist "$(OUTPUTDIR)" rmdir /s /q "$(OUTPUTDIR)"

$(OUTPUTDIR): 
	@if not exist "$(OUTPUTDIR)" mkdir "$(OUTPUTDIR)"

-include $(OBJS:.o=.d)

=======

clean:
	del "$(OUT)"  *.map *.P *.d

$(OUTPUTDIR): 
	@mkdir "$(OUTPUTDIR)"
		   	
>>>>>>> fa46c9aece16cb6cbdcb2b7736ebb8142e74d190
.PHONY: clean dirs
