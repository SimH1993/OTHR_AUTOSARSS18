package generator.oil.model;

import java.util.ArrayList;
import java.util.List;

import generator.oil.model.alarm.Alarm;

public class OilFile {
	private List<Task> tasks = new ArrayList<>();
	private List<Event> events = new ArrayList<>();
	private List<Alarm> alarms = new ArrayList<>();

	public List<Task> getTasks() {
		return tasks;
	}

	public void setTasks(List<Task> tasks) {
		this.tasks = tasks;
	}

	public List<Event> getEvents() {
		return events;
	}

	public void setEvents(List<Event> events) {
		this.events = events;
	}

	public List<Alarm> getAlarms() {
		return alarms;
	}

	public void setAlarms(List<Alarm> alarms) {
		this.alarms = alarms;
	}
}
