package generator.brick.ports;

import org.eclipse.emf.ecore.EObject;

import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Connection;
import autosarMetaModel.SWC;
import autosarMetaModel.TriggerPort;
import autosarMetaModel.TriggerPortType;
import autosarMetaModel.helper.ModelHelper;
import generator.brick.ports.SoftwarePortGenerator;

public class TriggerPortGenerator extends SoftwarePortGenerator {

	private final TriggerPort port;

	public TriggerPortGenerator(TriggerPort port) {
		this.port = port;
	}

	@Override
	public String generate() {
		if (port.getType() == TriggerPortType.OUTPUT) {
			SWC swc = (SWC) port.eContainer();
			if(isLocal(port)) {
				//TODO - we need to reference TriggerPorts
				String replace = "SetEvent("+"SWC_" + swc.getName() + "_Main" + ", ");
			}
			return generateByTemplate("TriggerTemplateOutput.txt").addReplacement("<PORT_NAME>", port.getName())
					.execute();
		} else
			return "";
	}
	
	private boolean isLocal(TriggerPort port) {
		AutosarSystem system = (AutosarSystem) port.eContainer().eContainer();
		for(Connection conn : system.getConnection()) {
			if(conn.getInput().equals(port)) {
				return ModelHelper.isLocalConnection(conn);
			}
		}
		throw new RuntimeException("Port was not found in a connection");
	}
}
