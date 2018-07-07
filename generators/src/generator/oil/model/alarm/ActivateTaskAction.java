package generator.oil.model.alarm;

import generator.oil.model.Task;

public class ActivateTaskAction extends Action {
	public ActivateTaskAction(Task task) {
		super(task);
	}

	@Override
	public String toString() {
		return "ACTIVATETASK { TASK = " + getTask().getName() + "; }";
	}
}
