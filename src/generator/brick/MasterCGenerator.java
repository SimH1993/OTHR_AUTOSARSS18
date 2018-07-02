package generator.brick;

import java.nio.file.Path;
import java.util.Map;

import autosarMetaModel.SenderReceiverPort;
import generator.oil.FileGenerator;
import generator.oil.model.Event;
import generator.oil.model.OilFile;
import generator.oil.model.Task;
import generator.oil.model.alarm.Alarm;

public class MasterCGenerator {
	private MasterCModel model;
	private Path rootPath;
	private OilFile oilFile;
	private Map<SenderReceiverPort, Integer> localSenderReceiverIds;

	public MasterCGenerator(Path rootPath, MasterCModel model, OilFile oilFile, Map<SenderReceiverPort, Integer> localSenderReceiverIds) {
		this.rootPath = rootPath;
		this.model = model;
		this.oilFile = oilFile;
		this.localSenderReceiverIds = localSenderReceiverIds;
	}

	public void generate() {
		new FileGenerator("templates/brick/masterc.c")
				.addReplacement("<INCLUDES>", model.getIncludes().toString())
				.addReplacement("<DECLARES>", generateDeclares())
				.addReplacement("<LOCAL_SENDER_RECEIVER_SIZE>", localSenderReceiverIds.size() / 2+"")
				.addReplacement("<FUNCTIONS>", model.getFunctions().toString())
				.execute(rootPath.resolve("master.c"));
	}
	
	private String generateDeclares() {
		StringBuilder builder = new StringBuilder();
		for(Alarm alarm: oilFile.getAlarms()) {
			builder.append("DeclareAlarm("+alarm.getName()+");\n");
		}
		for(Event event : oilFile.getEvents()) {
			builder.append("DeclareEvent("+event.getName()+");\n");
		}
		for(Task task : oilFile.getTasks()) {
			builder.append("DeclareTask("+task.getName()+");\n");
		}
		
		return builder.toString();
	}
}
