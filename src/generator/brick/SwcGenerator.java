package generator.brick;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.Map;
import java.util.StringJoiner;

import autosarMetaModel.BaseClass;
import autosarMetaModel.Brick;
import autosarMetaModel.ECUPort;
import autosarMetaModel.Port;
import autosarMetaModel.SWC;
import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.TimeTrigger;
import autosarMetaModel.TriggerEvent;
import generator.brick.ports.SoftwarePortGenerator;
import generator.brick.ports.ecu.EcuPortGenerator;
import generator.oil.FileGenerator;
import generator.oil.model.Autostart;
import generator.oil.model.Event;
import generator.oil.model.OilFile;
import generator.oil.model.Task;
import generator.oil.model.alarm.Alarm;
import generator.oil.model.alarm.AlarmAutostart;
import generator.oil.model.alarm.SetEventAction;

public class SwcGenerator {

	private final Brick brick;
	private final SWC swc;
	private final OilFile oilFile;
	private final Path rootPath;

	private final StringBuilder generatedFunctions;
	private final StringBuilder mainTaskBuilder = new StringBuilder();
	private MasterCModel masterC;
	private Map<SenderReceiverPort, Integer> localSenderReceiverIds;
	private Map<SoftwarePort, Integer> remoteConnectionIdMap;

	public SwcGenerator(Brick brick, SWC swc, OilFile oilFile, Path rootPath, MasterCModel masterC,
			Map<SenderReceiverPort, Integer> localSenderReceiverIds, Map<SoftwarePort, Integer> remoteConnectionIdMap) {
		this.brick = brick;
		this.swc = swc;
		this.oilFile = oilFile;
		this.rootPath = rootPath;
		this.masterC = masterC;
		this.localSenderReceiverIds = localSenderReceiverIds;
		this.remoteConnectionIdMap = remoteConnectionIdMap;
		generatedFunctions = new StringBuilder(swc.getPort().size() * 150);
	}

	private void prepare() {
		masterC.getIncludes().append("#include \"" + getFileName() + "\"\n");

		try {
			Files.createDirectories(rootPath.getParent().resolve("runnables"));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
		for (autosarMetaModel.Runnable r : swc.getRunnable()) {
			new RunnableGenerator(swc, r, rootPath.getParent().resolve("runnables")).generate();
		}
	}

	private void process() {
		for (Port p : swc.getPort()) {
			if (p instanceof SoftwarePort) {
				SoftwarePort swPort = (SoftwarePort) p;
				String generate = SoftwarePortGenerator.of(swPort, localSenderReceiverIds, remoteConnectionIdMap).generate();
				generatedFunctions.append(generate);
			} if(p instanceof ECUPort) {
				try {
					String generate = EcuPortGenerator.of(brick, (ECUPort) p).generate();
					generatedFunctions.append(generate);
				} catch(Exception e) {
					if(!e.getMessage().equals("NOT NEEDED")) {
						e.printStackTrace();
					}
				}
			}
		}

		Task mainTask = generateMainTask();
		generateAlarmsAndEvents(mainTask);
	}

	private void persist() {
		StringBuilder includes = new StringBuilder();
		for (autosarMetaModel.Runnable r : swc.getRunnable()) {
			includes.append("#include \"..\\runnables\\" + "Runnable_" + r.getName() + ".c" + "\"\n");
		}

		new FileGenerator("templates\\brick\\swcTemplate.c").addReplacement("<INCLUDES>", includes.toString())
				.addReplacement("<ACCESS_FUNCTIONS>",generatedFunctions.toString())
				.addReplacement("<TASK>",mainTaskBuilder.toString())
				.execute(rootPath.resolve(getFileName()));
	}

	private String getFileName() {
		return "SWC_" + swc.getName() + ".c";
	}

	private Task generateMainTask() {
		StringBuilder methodCalls = new StringBuilder();
		StringJoiner eventList = new StringJoiner(" | ");
		for (autosarMetaModel.Runnable r : swc.getRunnable()) {
			String eventName = ((BaseClass) r.getTriggerevent()).getName();
			String runnableStarter = new FileGenerator("templates/brick/RunnableRunner.txt")
					.addReplacement("<EVENT_NAME>", eventName)
					.addReplacement("<RUNNABLE_NAME>", "runnable_" + r.getName()).execute();

			methodCalls.append(runnableStarter.toString() + "\n");
			eventList.add(eventName);
		}

		Task task = new Task("SWC_" + swc.getName() + "_Main");
		task.setAutostart(Autostart.TRUE);
		task.setSchedule("FULL");

		oilFile.getTasks().add(task);

		String execute = new FileGenerator("templates/brick/swcMainTask.txt")
				.addReplacement("<FUNCTION_BODY>", methodCalls.toString())
				.addReplacement("<EVENT_LIST>", eventList.toString()).addReplacement("<SWC_NAME>", swc.getName())
				.execute();

		mainTaskBuilder.append(execute);

		return task;
	}

	private void generateAlarmsAndEvents(Task mainTask) {
		for (autosarMetaModel.Runnable r : swc.getRunnable()) {
			TriggerEvent triggerevent = r.getTriggerevent();
			String name = ((BaseClass) triggerevent).getName();
			Event event = new Event(name);
			oilFile.getEvents().add(event);
			mainTask.getEvents().add(event);
			if (triggerevent instanceof TimeTrigger) {
				TimeTrigger timeTrigger = (TimeTrigger) triggerevent;
				SetEventAction eventAction = new SetEventAction(mainTask, event);
				Alarm alarm = new Alarm("alarmSWC" + swc.getName() + "_" + r.getName(), eventAction);
				alarm.setAutostart(new AlarmAutostart(timeTrigger.getMilliseconds(), timeTrigger.getMilliseconds()));
				oilFile.getAlarms().add(alarm);
			}
		}
	}

	public void generate() {
		prepare();
		process();
		persist();
	}

}
