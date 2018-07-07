package generator.brick.ports;

import java.util.Map;

import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SenderReceiverPortType;
import autosarMetaModel.SoftwarePort;
import generator.oil.FileGenerator;

public class SenderReceiverGenerator extends SoftwarePortGenerator {
	private final SenderReceiverPort port;
	private Map<SenderReceiverPort, Integer> localSenderReceiverIds;
	private Map<SoftwarePort, Integer> remoteConnectionIdMap;

	public SenderReceiverGenerator(SenderReceiverPort port, Map<SenderReceiverPort, Integer> localSenderReceiverIds,
			Map<SoftwarePort, Integer> remoteConnectionIdMap) {
		this.port = port;
		this.localSenderReceiverIds = localSenderReceiverIds;
		this.remoteConnectionIdMap = remoteConnectionIdMap;
	}

	@Override
	public String generate() {
		if (port.getType() == SenderReceiverPortType.RECEIVER) {
			return generateReceiver();
		} else {
			return generateSender();
		}
	}

	private String generateReceiver() {
		if (localSenderReceiverIds.containsKey(port)) {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateReceiver.txt")
					.addReplacement("<MACRO_BODY>", "localSenderReceiver[" + localSenderReceiverIds.get(port) + "]")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		} else {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateReceiver.txt")
					.addReplacement("<MACRO_BODY>", "remotePorts[" + remoteConnectionIdMap.get(port) + "]")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		}

	}

	private String generateSender() {
		if (localSenderReceiverIds.containsKey(port)) {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
					.addReplacement("<MACRO_BODY>",
							"localSenderReceiver[" + localSenderReceiverIds.get(port) + "] = value")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		} else {
			int id = remoteConnectionIdMap.get(port);
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
					.addReplacement("<MACRO_BODY>", "com_send_packet(" + id + ", 0, value)")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		}
	}
}
