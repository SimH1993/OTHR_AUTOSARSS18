package generator.brick;

import java.nio.file.Path;
import java.util.Map;
import java.util.StringJoiner;

import autosarMetaModel.Brick;
import autosarMetaModel.SWC;
import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.TriggerPort;
import autosarMetaModel.TriggerPortType;
import generator.brick.ports.TriggerPortGenerator;
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
	private Brick brick;

	public MasterCGenerator(Path rootPath, MasterCModel model, OilFile oilFile,
			Map<SenderReceiverPort, Integer> localSenderReceiverIds, Brick brick) {
		this.rootPath = rootPath;
		this.model = model;
		this.oilFile = oilFile;
		this.localSenderReceiverIds = localSenderReceiverIds;
		this.brick = brick;
	}

	public void generate() {
		new FileGenerator("templates/brick/masterc.c").addReplacement("<REMOTE_TRIGGERS>", generateRemoteTriggers())
				.addReplacement("<INCLUDES>", model.getIncludes().toString())
				.addReplacement("<DECLARES>", generateDeclares())
				.addReplacement("<LOCAL_SENDER_RECEIVER_SIZE>", localSenderReceiverIds.size() / 2 + "")
				.addReplacement("<REMOTE_SENDER_RECEIVER_SIZE>", model.getRemoteConnectionIdMap().size() / 2 + "")
				.addReplacement("<FUNCTIONS>", model.getFunctions().toString()).execute(rootPath.resolve("master.c"));
	}

	private String generateRemoteTriggers() {
		StringJoiner result = new StringJoiner("\n");
		Map<SoftwarePort, Integer> remoteConnectionIdMap = model.getRemoteConnectionIdMap();
		for (SoftwarePort port : remoteConnectionIdMap.keySet()) {
			SWC swc = (SWC) port.eContainer();
			if (brick.getSwc().contains(swc)) {
				if (port instanceof TriggerPort) {
					TriggerPort triggerPort = (TriggerPort) port;
					if (triggerPort.getType() == TriggerPortType.INPUT) {
						String generated = new TriggerPortGenerator(triggerPort, remoteConnectionIdMap).generateRemote();
						result.add(generated);
					}
				}
			}
		}
		return result.toString();
	}

	private String generateDeclares() {
		StringBuilder builder = new StringBuilder();
		for (Alarm alarm : oilFile.getAlarms()) {
			builder.append("DeclareAlarm(" + alarm.getName() + ");\n");
		}
		for (Event event : oilFile.getEvents()) {
			builder.append("DeclareEvent(" + event.getName() + ");\n");
		}
		for (Task task : oilFile.getTasks()) {
			builder.append("DeclareTask(" + task.getName() + ");\n");
		}

		return builder.toString();
	}
}
