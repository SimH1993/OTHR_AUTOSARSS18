package generator.oil.visitor;

import java.util.Objects;

import generator.oil.model.Event;
import generator.oil.model.OilFile;
import generator.oil.model.Task;
import generator.oil.model.alarm.Alarm;

public abstract class AbstractVisitor {
	protected final OilFile oilFile;

	public AbstractVisitor(OilFile file) {
		this.oilFile = Objects.requireNonNull(file);
	}

	protected void visitOilFile(OilFile oilFile) {
		for (Task task : oilFile.getTasks()) {
			visitTask(task);
		}

		for (Alarm alarm : oilFile.getAlarms()) {
			visitAlarm(alarm);
		}

		for (Event event : oilFile.getEvents()) {
			visitEvent(event);
		}
	}

	protected void visitEvent(Event event) {
	}

	protected void visitAlarm(Alarm alarm) {
	}

	protected void visitTask(Task task) {

	}

}
