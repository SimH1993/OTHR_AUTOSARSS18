package generator.brick.ports;

import autosarMetaModel.TriggerPort;
import autosarMetaModel.TriggerPortType;
import generator.brick.ports.SoftwarePortGenerator;

public class TriggerPortGenerator extends SoftwarePortGenerator {

	private final TriggerPort port;

	public TriggerPortGenerator(TriggerPort port) {
		this.port = port;
	}

	@Override
	public String generate() {
		if (port.getType() == TriggerPortType.INPUT) {
			return generateByTemplate("TriggerTemplateInput.txt").addReplacement("<PORT_NAME>", port.getName())
					.execute();
		} else {
			return generateByTemplate("TriggerTemplateOutput.txt").addReplacement("<PORT_NAME>", port.getName())
					.execute();
		}
	}
}
