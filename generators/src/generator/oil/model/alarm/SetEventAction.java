package generator.oil.model.alarm;

import generator.oil.model.Event;
import generator.oil.model.Task;

public class SetEventAction extends Action {
	private Event event;

	public SetEventAction(Task task, Event event) {
		super(task);
		this.event = event;
	}

	public Event getEvent() {
		return event;
	}

	public void setEvent(Event event) {
		this.event = event;
	}

	@Override
	public String toString() {
		return "SETEVENT { TASK = " + getTask().getName() + "; EVENT = " + event.getName() + "; }";
	}
}
