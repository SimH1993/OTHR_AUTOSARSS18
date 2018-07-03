package generator.brick.ports;

import java.util.Map;

import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SenderReceiverPortType;
import generator.oil.FileGenerator;

public class SenderReceiverGenerator extends SoftwarePortGenerator {
	private final SenderReceiverPort port;
	private Map<SenderReceiverPort, Integer> localSenderReceiverIds;

	public SenderReceiverGenerator(SenderReceiverPort port, Map<SenderReceiverPort, Integer> localSenderReceiverIds) {
		this.port = port;
		this.localSenderReceiverIds = localSenderReceiverIds;
	}

	@Override
	public String generate() {
		if (port.getType() == SenderReceiverPortType.RECEIVER) {
			return generateReceiver();

		} else {
			return generateSender();
			/*return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
					.addReplacement("<PORT_NAME>", port.getName()).execute();*/
		}
	}

	private String generateReceiver() {
		if (localSenderReceiverIds.containsKey(port)) {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateReceiver.txt")
					.addReplacement("<FUNCTION_BODY>",
							"return localSenderReceiver[" + localSenderReceiverIds.get(port) + "];")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		} else {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateReceiver.txt")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		}

	}

	private String generateSender() {
		if(localSenderReceiverIds.containsKey(port)) {
		return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
				.addReplacement("<FUNCTION_BODY>",
						"localSenderReceiver[" + localSenderReceiverIds.get(port) + "] = value;")
				.addReplacement("<PORT_NAME>", port.getName()).execute();
		} else {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
					.addReplacement("<PORT_NAME>", port.getName()).execute(); 
		}
	}
}
