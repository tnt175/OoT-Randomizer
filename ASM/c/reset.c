#include "reset.h"

typedef void(*TitleSetup_Init)();
#define TitleSetup_Init_Func ((TitleSetup_Init) 0x800A0748)
typedef void (*set_bgm)(unsigned int ID);
#define SET_BGM ((set_bgm) 0x800CAA70)
#define BGM_STOP 0x100000FF

static unsigned short s_reset_delay = 10;

void wait_for_reset_combo(){
	z64_controller_t pad_pressed = z64_game.common.input[0].raw;
	if ((pad_pressed.pad.cr) && (pad_pressed.pad.b) && (pad_pressed.pad.s)) {
		if (s_reset_delay != 0) {
			s_reset_delay--;
		}
		else {
			z64_game.common.state_continue = 0;
			z64_game.common.next_ctor = (void*)TitleSetup_Init_Func;
			z64_game.common.next_size = sizeof(z64_ctxt_t);
			SET_BGM(BGM_STOP);
		}
	}
	else {
		s_reset_delay = 10;
	}
}
