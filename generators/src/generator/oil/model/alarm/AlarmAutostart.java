package generator.oil.model.alarm;

import generator.oil.model.Autostart;

public class AlarmAutostart extends Autostart {
	private int alarmTime;
	private int cycleTime;

	public final static AlarmAutostart FALSE = new AlarmAutostart(0, 0) {
		@Override
		public String toString() {
			return "FALSE";
		}
	};

	public AlarmAutostart(int alarmTime, int cycleTime) {
		this.alarmTime = alarmTime;
		this.cycleTime = cycleTime;
	}

	public int getCycleTime() {
		return cycleTime;
	}

	public void setCycleTime(int cycleTime) {
		this.cycleTime = cycleTime;
	}

	public int getAlarmTime() {

		return alarmTime;
	}

	public void setAlarmTime(int alarmTime) {
		this.alarmTime = alarmTime;
	}

	@Override
	public String toString() {
		return "TRUE { ALARMTIME = " + getAlarmTime() + "; CYCLETIME = " + getCycleTime() + "; APPMODE = "
				+ getAppMode() + "; }";
	}
}
