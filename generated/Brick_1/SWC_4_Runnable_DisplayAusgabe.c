


void swc_4_DisplayAusgabe(){
   
	display_goto_xy(0, 0);
	display_int(((S8)RTE_JOYSTICK_X_READ()),5);
	display_goto_xy(0, 1);
	display_int(((S8)RTE_JOYSTICK_Y_READ()),5);
	display_goto_xy(0, 2);
	display_int(((S8)RTE_JOYSTICK_BUTTON_READ()),5);
	display_update();
}

