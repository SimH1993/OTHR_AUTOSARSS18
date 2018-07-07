package generator.oil.model.alarm;

import java.util.Objects;

import generator.oil.model.Task;

public abstract class Action {
	private Task task;

	public Action(Task task) {
		this.task = Objects.requireNonNull(task);
	}

	public Task getTask() {
		return task;
	}

	public void setTask(Task task) {
		this.task = task;
	}
}
