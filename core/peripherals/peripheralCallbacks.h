void updateKeyboardSpecial(bool keyDown, int key, int mouseX, int mouseY){
	gui_engine_global.mouse.mouseX = mouseX;
	gui_engine_global.mouse.mouseY = mouseY;
	switch(key){
		case 0x65:
			gui_engine_global.keyboard.key_up = keyDown;
			break;
		case 0x67:
        		gui_engine_global.keyboard.key_down = keyDown;
			break;
		case 0x64:
        		gui_engine_global.keyboard.key_left = keyDown;
			break;
		case 0x66:
        		gui_engine_global.keyboard.key_right = keyDown;
			break;
		case 0x70:
        		gui_engine_global.keyboard.key_leftshift = keyDown;
			break;
		case 0x71:
        		gui_engine_global.keyboard.key_rightshift = keyDown;
			break;
		case 0x72:
        		gui_engine_global.keyboard.key_leftctrl = keyDown;
			break;
		case 0x73:
        		gui_engine_global.keyboard.key_rightctrl = keyDown;
			break;
		case 0x74:
        		gui_engine_global.keyboard.key_leftalt = keyDown;
			break;
		case 0x6a:
        		gui_engine_global.keyboard.key_home = keyDown;
			break;
		case 0x6b:
        		gui_engine_global.keyboard.key_end = keyDown;
			break;
		case 0x68:
        		gui_engine_global.keyboard.key_pageup = keyDown;
			break;
		case 0x69:
        		gui_engine_global.keyboard.key_pagedown = keyDown;
			break;
		case 0x6c:
        		gui_engine_global.keyboard.key_insert = keyDown;
			break;
	}
}
void updateKeyboard(bool keyDown, unsigned char key, int mouseX, int mouseY){
	gui_engine_global.mouse.mouseX = mouseX;
	gui_engine_global.mouse.mouseY = mouseY;
	switch(key){
		case 0x61:
			gui_engine_global.keyboard.key_a = keyDown;
			break;
		case 0x62:
			gui_engine_global.keyboard.key_b = keyDown;
			break;
		case 0x63:
			gui_engine_global.keyboard.key_c = keyDown;
			break;
		case 0x64:
			gui_engine_global.keyboard.key_d = keyDown;
			break;
		case 0x65:
			gui_engine_global.keyboard.key_e = keyDown;
			break;
		case 0x66:
			gui_engine_global.keyboard.key_f = keyDown;
			break;
		case 0x67:
			gui_engine_global.keyboard.key_g = keyDown;
			break;
		case 0x68:
			gui_engine_global.keyboard.key_h = keyDown;
			break;
		case 0x69:
			gui_engine_global.keyboard.key_i = keyDown;
			break;
		case 0x6a:
			gui_engine_global.keyboard.key_j = keyDown;
			break;
		case 0x6b:
			gui_engine_global.keyboard.key_k = keyDown;
			break;
		case 0x6c:
			gui_engine_global.keyboard.key_l = keyDown;
			break;
		case 0x6d:
			gui_engine_global.keyboard.key_m = keyDown;
			break;
		case 0x6e:
			gui_engine_global.keyboard.key_n = keyDown;
			break;
		case 0x6f:
			gui_engine_global.keyboard.key_o = keyDown;
			break;
		case 0x70:
			gui_engine_global.keyboard.key_p = keyDown;
			break;
		case 0x71:
			gui_engine_global.keyboard.key_q = keyDown;
			break;
		case 0x72:
			gui_engine_global.keyboard.key_r = keyDown;
			break;
		case 0x73:
			gui_engine_global.keyboard.key_s = keyDown;
			break;
		case 0x74:
			gui_engine_global.keyboard.key_t = keyDown;
			break;
		case 0x75:
			gui_engine_global.keyboard.key_u = keyDown;
			break;
		case 0x76:
			gui_engine_global.keyboard.key_v = keyDown;
			break;
		case 0x77:
			gui_engine_global.keyboard.key_w = keyDown;
			break;
		case 0x78:
			gui_engine_global.keyboard.key_x = keyDown;
			break;
		case 0x79:
			gui_engine_global.keyboard.key_y = keyDown;
			break;
		case 0x7a:
			gui_engine_global.keyboard.key_z = keyDown;
			break;
		// Capitals
		case 0x41:
			gui_engine_global.keyboard.key_A = keyDown;
			break;
		case 0x42:
			gui_engine_global.keyboard.key_B = keyDown;
			break;
		case 0x43:
			gui_engine_global.keyboard.key_C = keyDown;
			break;
		case 0x44:
			gui_engine_global.keyboard.key_D = keyDown;
			break;
		case 0x45:
			gui_engine_global.keyboard.key_E = keyDown;
			break;
		case 0x46:
			gui_engine_global.keyboard.key_F = keyDown;
			break;
		case 0x47:
			gui_engine_global.keyboard.key_G = keyDown;
			break;
		case 0x48:
			gui_engine_global.keyboard.key_H = keyDown;
			break;
		case 0x49:
			gui_engine_global.keyboard.key_I = keyDown;
			break;
		case 0x4a:
			gui_engine_global.keyboard.key_J = keyDown;
			break;
		case 0x4b:
			gui_engine_global.keyboard.key_K = keyDown;
			break;
		case 0x4c:
			gui_engine_global.keyboard.key_L = keyDown;
			break;
		case 0x4d:
			gui_engine_global.keyboard.key_M = keyDown;
			break;
		case 0x4e:
			gui_engine_global.keyboard.key_N = keyDown;
			break;
		case 0x4f:
			gui_engine_global.keyboard.key_O = keyDown;
			break;
		case 0x50:
			gui_engine_global.keyboard.key_P = keyDown;
			break;
		case 0x51:
			gui_engine_global.keyboard.key_Q = keyDown;
			break;
		case 0x52:
			gui_engine_global.keyboard.key_R = keyDown;
			break;
		case 0x53:
			gui_engine_global.keyboard.key_S = keyDown;
			break;
		case 0x54:
			gui_engine_global.keyboard.key_T = keyDown;
			break;
		case 0x55:
			gui_engine_global.keyboard.key_U = keyDown;
			break;
		case 0x56:
			gui_engine_global.keyboard.key_V = keyDown;
			break;
		case 0x57:
			gui_engine_global.keyboard.key_W = keyDown;
			break;
		case 0x58:
			gui_engine_global.keyboard.key_X = keyDown;
			break;
		case 0x59:
			gui_engine_global.keyboard.key_Y = keyDown;
			break;
		case 0x5a:
			gui_engine_global.keyboard.key_Z = keyDown;
			break;

		// Numbers and symbols
		case 0x30:
                        gui_engine_global.keyboard.key_0 = keyDown;
                        break;
		case 0x31:
                        gui_engine_global.keyboard.key_1 = keyDown;
                        break;
		case 0x32:
                        gui_engine_global.keyboard.key_2 = keyDown;
                        break;
		case 0x33:
                        gui_engine_global.keyboard.key_3 = keyDown;
                        break;
		case 0x34:
                        gui_engine_global.keyboard.key_4 = keyDown;
                        break;
		case 0x35:
                        gui_engine_global.keyboard.key_5 = keyDown;
                        break;
		case 0x36:
                        gui_engine_global.keyboard.key_6 = keyDown;
                        break;
		case 0x37:
                        gui_engine_global.keyboard.key_7 = keyDown;
                        break;
		case 0x38:
                        gui_engine_global.keyboard.key_8 = keyDown;
                        break;
		case 0x39:
                        gui_engine_global.keyboard.key_9 = keyDown;
                        break;
		case 0x21:
                        gui_engine_global.keyboard.key_exclame = keyDown;
                        break;
		case 0x40:
                        gui_engine_global.keyboard.key_at = keyDown;
                        break;
		case 0x23:
                        gui_engine_global.keyboard.key_pound = keyDown;
                        break;
		case 0x24:
                        gui_engine_global.keyboard.key_money = keyDown;
                        break;
		case 0x25:
                        gui_engine_global.keyboard.key_percent = keyDown;
                        break;
		case 0x5e:
                        gui_engine_global.keyboard.key_carrot = keyDown;
                        break;
		case 0x26:
                        gui_engine_global.keyboard.key_amp = keyDown;
                        break;
		case 0x2a:
                        gui_engine_global.keyboard.key_star = keyDown;
                        break;
		case 0x28:
                        gui_engine_global.keyboard.key_popen = keyDown;
                        break;
		case 0x29:
                        gui_engine_global.keyboard.key_pclose = keyDown;
                        break;
		case 0x2d:
			gui_engine_global.keyboard.key_minus = keyDown;
			break;
		case 0x5f:
        		gui_engine_global.keyboard.key_underscore = keyDown;
			break;
		case 0x3d:
        		gui_engine_global.keyboard.key_equals = keyDown;
			break;
		case 0x2b:
        		gui_engine_global.keyboard.key_plus = keyDown;
			break;
		case 0x8:
        		gui_engine_global.keyboard.key_back = keyDown;
			break;
		case 0x7e:
        		gui_engine_global.keyboard.key_tilde = keyDown;
			break;
		case 0x60:
        		gui_engine_global.keyboard.key_backtick = keyDown;
			break;
		case 0xd:
			gui_engine_global.keyboard.key_enter = keyDown;
			break;
		case 0x9:
        		gui_engine_global.keyboard.key_tab = keyDown;
			break;
		case 0x1b:
        		gui_engine_global.keyboard.key_esc = keyDown;
			break;
	}
}

void updateMouse(int button, int state, int x, int y){
	gui_engine_global.mouse.mouseX = x;
	gui_engine_global.mouse.mouseY = y;
	switch(button){
		case 0:
			gui_engine_global.mouse.click_left = (state == 0) ? true : false;
			break;
		case 2:
        		gui_engine_global.mouse.click_right = (state == 0) ? true : false;
			break;
		case 1:
        		gui_engine_global.mouse.click_middle = (state == 0) ? true : false;
			break;
		case 3:
        		gui_engine_global.mouse.scroll_up = (state == 0) ? true : false;
			break;
		case 4:
        		gui_engine_global.mouse.scroll_down = (state == 0) ? true : false;
			break;
	}

}
