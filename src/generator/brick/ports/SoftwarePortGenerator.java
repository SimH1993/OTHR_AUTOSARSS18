package generator.brick.ports;

import java.util.Map;

import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.TriggerPort;
import generator.oil.FileGenerator;

public abstract class SoftwarePortGenerator {
	public static SoftwarePortGenerator of(SoftwarePort port, Map<SenderReceiverPort, Integer> localSenderReceiverIds) {
		if (port instanceof SenderReceiverPort) {
			return new SenderReceiverGenerator((SenderReceiverPort) port, localSenderReceiverIds);
		} else if (port instanceof TriggerPort) {
			return new TriggerPortGenerator((TriggerPort) port);
		} else {
			throw new RuntimeException("WE NEED TO MAKE MORE PORT-GENS!");
		}
	}

	public abstract String generate();

	protected FileGenerator generateByTemplate(String name) {
		return new FileGenerator("templates\\brick\\ports\\" + name);
	}
}
