################################################################################
# These are variables for the GBA toolchain build
# You can add others if you wish to
# ***** YOUR NAME HERE *****
################################################################################

# TA-TODO: Put your game name here.
# The name of your desired application
# This should be a just a name i.e MyFirstGBAGame
# No SPACES AFTER THE NAME.
PROGNAME = Game

# TA-TODO: Add the C files you want compiled here (replace extension with .o)
# Here you must put a list of all of the object files
# that will be compiled into your program. For example
# if you have main.c and myLib.c then in the following
# line you would put main.o and myLib.o
OFILES = gba.o font.o game.o images/garbage.o \
pacman.o ghost.o gameMap.o mazeUtil.o canvas.o\
images/background/image_gamestart.o \
images/background/image_gameover.o \
images/background/image_gamewin.o \
images/pacman/image_pacman_down_0.o \
images/pacman/image_pacman_down_1.o \
images/pacman/image_pacman_right_0.o \
images/pacman/image_pacman_right_1.o \
images/pacman/image_pacman_up_0.o \
images/pacman/image_pacman_up_1.o \
images/pacman/image_pacman_left_0.o \
images/pacman/image_pacman_left_1.o \
images/ghost/image_ghost_down_0.o \
images/ghost/image_ghost_down_1.o \
images/ghost/image_ghost_right_0.o \
images/ghost/image_ghost_right_1.o \
images/ghost/image_ghost_up_0.o \
images/ghost/image_ghost_up_1.o \
images/ghost/image_ghost_left_0.o \
images/ghost/image_ghost_left_1.o \
images/map/image_food.o \
images/map/image_horizontal_empty.o \
images/map/image_vertical_empty.o \
images/map/image_wall_0.o \
images/map/image_wall_1.o \
images/map/image_wall_2.o \
images/map/image_wall_3.o \
images/map/image_wall_4.o \
images/map/image_wall_5.o \
images/map/image_wall_6.o \
images/map/image_wall_7.o \
images/map/image_wall_8.o \
images/map/image_wall_9.o \
images/map/image_wall_a.o \
images/map/image_wall_b.o \
images/map/image_wall_c.o \
images/map/image_wall_d.o \
images/map/image_wall_e.o \
images/map/image_wall_f.o \
images/map/image_wall_g.o \
images/map/image_wall_h.o \
images/map/image_wall_i.o \
images/map/image_wall_j.o \
images/map/image_wall_k.o \
images/map/image_wall_l.o \
images/map/image_wall_m.o \
images/map/image_wall_n.o \
images/map/image_wall_o.o \
images/map/image_wall_p.o \
images/map/image_wall_q.o \
images/map/image_wall_r.o \
images/map/image_empty.o

################################################################################
# These are various settings used to make the GBA toolchain work
# DO NOT EDIT BELOW.
################################################################################

.PHONY: all
all : CFLAGS += $(CRELEASE) -I../shared
all : LDFLAGS += $(LDRELEASE)
all: $(PROGNAME).gba
	@echo "[FINISH] Created $(PROGNAME).gba"

include /opt/cs2110-tools/GBAVariables.mak

# Son, it's time to be an adult and use adult prototypes
CFLAGS += -Wstrict-prototypes -Wold-style-definition

debug : CFLAGS += $(CDEBUG) -I../shared
debug : LDFLAGS += $(LDDEBUG)
debug : $(PROGNAME).gba
	@echo "[FINISH] Created $(PROGNAME).gba"

$(PROGNAME).gba : $(PROGNAME).elf
	@echo "[LINK] Linking objects together to create $(PROGNAME).gba"
	@$(OBJCOPY) -O binary $(PROGNAME).elf $(PROGNAME).gba

$(PROGNAME).elf : crt0.o $(GCCLIB)/crtbegin.o $(GCCLIB)/crtend.o $(GCCLIB)/crti.o $(GCCLIB)/crtn.o $(OFILES) libc_sbrk.o
	$(CC) -o $(PROGNAME).elf $^ $(LDFLAGS)

.PHONY : emu
emu : med

.PHONY : vba
vba : CFLAGS += $(CRELEASE) -I../shared
vba : LDFLAGS += $(LDRELEASE)
vba : $(PROGNAME).gba
	@echo "[EXECUTE] Running Emulator VBA-M"
	@echo "          Please see emulator.log if this fails"
	@vbam $(VBAOPT) $(PROGNAME).gba >emulator.log 2>&1

.PHONY : med
med : CFLAGS += $(CRELEASE) -I../shared
med : LDFLAGS += $(LDRELEASE)
med : $(PROGNAME).gba
	@echo "[EXECUTE] Running emulator Mednafen"
	@echo "          Please see emulator.log if this fails"
# Default mednafen keybinds are "Gaaarbage", in the words of Farzam
	@mkdir -p ~/.mednafen/
	@cp mednafen-09x.cfg ~/.mednafen/
	@mednafen $(MEDOPT) $(PROGNAME).gba >emulator.log 2>&1

.PHONY : submit
submit: clean
	@rm -f submission.tar.gz
	@tar czvf submission.tar.gz *

.PHONY : clean
clean :
	@echo "[CLEAN] Removing all compiled files"
	rm -f *.o *.elf *.gba *.log */*.o
