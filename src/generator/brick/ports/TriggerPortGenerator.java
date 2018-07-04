package generator.brick.ports;

import java.util.Map;

import org.eclipse.emf.ecore.EObject;

import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Connection;
import autosarMetaModel.SWC;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.TriggerEvent;
import autosarMetaModel.TriggerPort;
import autosarMetaModel.TriggerPortTrigger;
import autosarMetaModel.TriggerPortType;
import autosarMetaModel.helper.ModelHelper;
import generator.brick.ports.SoftwarePortGenerator;

public class TriggerPortGenerator extends SoftwarePortGenerator {

	private final TriggerPort port;
	private Map<SoftwarePort, Integer> remoteConnectionIdMap;

	public TriggerPortGenerator(TriggerPort port, Map<SoftwarePort, Integer> remoteConnectionIdMap) {
		this.port = port;
		this.remoteConnectionIdMap = remoteConnectionIdMap;
	}

	@Override
	public String generate() {
		if (port.getType() == TriggerPortType.OUTPUT) {
			SWC swc = (SWC) port.eContainer();
			if (isLocal(port)) {
				String replace = "SetEvent(" + "SWC_" + swc.getName() + "_Main" + ", " + findTrigger(port).getName()
						+ ")";
				return generateByTemplate("TriggerTemplateOutput.txt").addReplacement("<PORT_NAME>", port.getName())
						.addReplacement("<MACRO_BODY>", replace).execute();
			} else {
				int id = remoteConnectionIdMap.get(port);
				return generateByTemplate("TriggerTemplateOutput.txt").addReplacement("<PORT_NAME>", port.getName())
						.addReplacement("<MACRO_BODY>", "com_send_packet(" + id + ", 0, 1)").execute();
			}

		} else {
			return "";
		}
	}

	public String generateRemote() {
		if (port.getType() == TriggerPortType.INPUT) {
			int portId = remoteConnectionIdMap.get(port);
			SWC swc = (SWC) port.eContainer();
			String eventName = findTriggerActivator(port).getName();
			String result = "if(portId == " + portId + ") SetEvent(" + "SWC_" + swc.getName() + "_Main, " + eventName
					+ ");";
			return result;
		} else {
			throw new RuntimeException("This only works for input ports");
		}
	}

	private boolean isLocal(TriggerPort port) {
		AutosarSystem system = (AutosarSystem) port.eContainer().eContainer();
		for (Connection conn : system.getConnection()) {
			if (conn.getInput().equals(port)) {
				return ModelHelper.isLocalConnection(conn);
			}
		}
		throw new RuntimeException("Port was not found in a connection");
	}

	private TriggerPortTrigger findTrigger(TriggerPort triggerPort) {
		AutosarSystem container = (AutosarSystem) triggerPort.eContainer().eContainer();
		for (Connection conn : container.getConnection()) {
			if (conn.getInput().equals(triggerPort)) {
				return findTriggerActivator((TriggerPort) conn.getOutput());
			}
		}
		throw new RuntimeException("No TriggertPortTrigger found");
	}

	private TriggerPortTrigger findTriggerActivator(TriggerPort port) {
		AutosarSystem system = (AutosarSystem) port.eContainer().eContainer();
		for (SWC swc : system.getSwc()) {
			for (autosarMetaModel.Runnable runnable : swc.getRunnable()) {
				TriggerEvent triggerEvent = runnable.getTriggerevent();
				if (triggerEvent instanceof TriggerPortTrigger) {
					TriggerPortTrigger triggerPortEvent = (TriggerPortTrigger) triggerEvent;
					if (triggerPortEvent.getTriggerport().equals(port)) {
						return triggerPortEvent;
					}
				}
			}
		}
		throw new RuntimeException("No TriggertPortTrigger found");
	}
}
