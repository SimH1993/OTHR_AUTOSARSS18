package autosarMetaModel.helper;

import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Brick;
import autosarMetaModel.Connection;
import autosarMetaModel.SWC;
import autosarMetaModel.SoftwarePort;

import java.util.NoSuchElementException;

public class ModelHelper {
    private final AutosarSystem autosarSystem;

    public ModelHelper(AutosarSystem autosarSystem) {
        this.autosarSystem = autosarSystem;
    }

    public Brick getBrickOfPort(SoftwarePort port) {
        return getBrickOfPort(autosarSystem, port);
    }
    
    public static Brick getBrickOfPort(AutosarSystem system, SoftwarePort port) {
        SWC swc = (SWC) port.eContainer();
        for (Brick brick: system.getBrick()) {
            if (brick.getSwc().contains(swc)) {
                return brick;
            }
        }
        throw new NoSuchElementException("Port "+ port.getName() + " is not associated to a brick");
    }
    
    public static boolean isLocalConnection(Connection conn) {
    	AutosarSystem system = (AutosarSystem) conn.eContainer();
		SoftwarePort input = conn.getInput();
		SoftwarePort output = conn.getOutput();
		return getBrickOfPort(system, input).equals(getBrickOfPort(system, output));
    }
    
    public static boolean isBluetoothConnection(Connection conn) {
    	return !isLocalConnection(conn);
    }
}
