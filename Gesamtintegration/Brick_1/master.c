#include "kernel.h"
#include "kernel_id.h"
#include "ecrobot_interface.h" 

int localSenderReceiver[3];
int remotePorts[3];

void rte_set_data(int portId, int data){
	remotePorts[portId] = data;
	
	
}

DeclareAlarm(alarmSWC1_JoystickAuslesen);
DeclareAlarm(alarmSWC1_UltraschallAuslesen);
DeclareAlarm(alarmSWC1_FlankenErkennung);
DeclareAlarm(alarmSWC2_WerteBerechnen);
DeclareAlarm(alarmSWC4_DisplayAusgabe);
DeclareAlarm(alarmSWC4_SoundAusgabe);
DeclareEvent(TriggerJoystickAuslesen);
DeclareEvent(TriggerUltraschallAuslesen);
DeclareEvent(TriggerFlankenErkennung);
DeclareEvent(TriggerWerteBerechnen);
DeclareEvent(TriggerDisplayAusgabe);
DeclareEvent(TriggerSoundAusgabe);
DeclareTask(SWC_1_Main);
DeclareTask(SWC_2_Main);
DeclareTask(SWC_4_Main);


#include "SWC_1.c"
#include "SWC_2.c"
#include "SWC_4.c"




