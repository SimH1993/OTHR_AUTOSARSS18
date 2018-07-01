package generator.oil.visitor;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.Arrays;
import java.util.Collections;
import java.util.StringJoiner;

import generator.oil.FileGenerator;
import generator.oil.model.Autostart;
import generator.oil.model.Constants;
import generator.oil.model.Event;
import generator.oil.model.OilFile;
import generator.oil.model.Task;
import generator.oil.model.alarm.Alarm;
import generator.oil.model.alarm.AlarmAutostart;
import generator.oil.model.alarm.SetEventAction;

public class OilFileVisitor extends AbstractVisitor {
	private final StringBuilder taskStringBuilder = new StringBuilder();
	private final StringBuilder eventStringBuilder = new StringBuilder();
	private final StringBuilder alarmStringBuilder = new StringBuilder();
	private String result = null;

	public OilFileVisitor(OilFile file) {
		super(file);
	}

	public String generateOil() {
		visitOilFile(oilFile);
		return result;
	}

	public void generateOil(Path output) throws IOException {
		String content = generateOil();
		Files.write(output, Collections.singletonList(content), StandardOpenOption.CREATE,
				StandardOpenOption.TRUNCATE_EXISTING);
	}

	@Override
	protected void visitOilFile(OilFile oilFile) {
		super.visitOilFile(oilFile);
		String execute = null;
		try {
			execute = new FileGenerator("templates/Masteroil.oil")
					.addReplacement("___ALARM_REPLACE___", alarmStringBuilder.toString())
					.addReplacement("___EVENT_REPLACE___", eventStringBuilder.toString())
					.addReplacement("___TASKS___", taskStringBuilder.toString()).execute();
			result = execute;
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void visitTask(Task task) {
		super.visitTask(task);
		StringJoiner stringJoiner = new StringJoiner("\n    ");
		stringJoiner.setEmptyValue("");
		for (Event event : task.getEvents()) {
			stringJoiner.add("EVENT = " + event.getName() + ";");
		}

		try {
			String execute = new FileGenerator("templates\\task_template.txt")
					.addReplacement("<TASK_NAME>", task.getName())
					.addReplacement("<AUTOSTART>", task.getAutostart().toString())
					.addReplacement("<PRIORITY>", task.getPriority() + "")
					.addReplacement("<SCHEDULE>", task.getSchedule())
					.addReplacement("<STACKSIZE_VALUE>", task.getStackSize() + "") // TODO - do we change stacksize
					.addReplacement("<EVENT>", stringJoiner.toString()).execute();
			taskStringBuilder.append(execute).append("\n");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void visitEvent(Event event) {
		super.visitEvent(event);
		try {
			String execute = new FileGenerator("templates\\event_template.txt")
					.addReplacement("<EVENT_NAME>", event.getName()).addReplacement("<MASK>", event.getMask())
					.execute();
			eventStringBuilder.append(execute).append("\n");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	@Override
	protected void visitAlarm(Alarm alarm) {
		super.visitAlarm(alarm);
		try {
			String execute = new FileGenerator("templates\\alarm_template.txt")
					.addReplacement("<ALARM_NAME>", alarm.getName()).addReplacement("<COUNTER>", Constants.counterName)
					.addReplacement("<ACTION>", alarm.getAction().toString())
					.addReplacement("<AUTOSTART>", alarm.getAutostart().toString()).execute();
			alarmStringBuilder.append(execute).append("\n");
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public static void main(String[] args) {
		OilFile oilFile = new OilFile();
		Event event = new Event("helloWorld");
		Task task = new Task("Task");
		task.setAutostart(Autostart.TRUE);
		task.setEvents(Arrays.asList(event, new Event("Horst")));
		Alarm alarm = new Alarm("Demo", new SetEventAction(task, event));
		alarm.setAutostart(new AlarmAutostart(10, 5));

		oilFile.setEvents(Arrays.asList(event));
		oilFile.setAlarms(Arrays.asList(alarm));
		oilFile.setTasks(Arrays.asList(task));
		new OilFileVisitor(oilFile).visitOilFile(oilFile);
	}
}
