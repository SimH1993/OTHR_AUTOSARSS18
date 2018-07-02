package generator.brick.ports;

import java.io.IOException;

import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SenderReceiverPortType;
import generator.oil.FileGenerator;

public class SenderReceiverGenerator extends SoftwarePortGenerator {
	private final SenderReceiverPort port;

	public SenderReceiverGenerator(SenderReceiverPort port) {
		this.port = port;
	}

	@Override
	public String generate() {
		if (port.getType() == SenderReceiverPortType.RECEIVER) {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateReceiver.txt")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		} else {
			return new FileGenerator("templates\\brick\\ports\\SenderReceiverTemplateSender.txt")
					.addReplacement("<PORT_NAME>", port.getName()).execute();
		}
	}
}
