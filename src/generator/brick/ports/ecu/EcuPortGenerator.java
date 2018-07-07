package generator.brick.ports.ecu;

import autosarMetaModel.ActuatorSensor;
import autosarMetaModel.Brick;
import autosarMetaModel.ECRobotAccess;
import autosarMetaModel.ECUPort;
import autosarMetaModel.HardwareConnection;
import autosarMetaModel.RawAccess;

public abstract class EcuPortGenerator {
	public static EcuPortGenerator of(Brick brick, ECUPort port) {
		ActuatorSensor configuration = findConnectionConfiguration(brick, port);
		if(configuration instanceof RawAccess) {
			return new RawAccessPortGenerator(brick, port);
		} else if (configuration instanceof ECRobotAccess) {
			return new ECRobotAccessPortGenerator(brick, port);
		} else {
			throw new RuntimeException("NOT NEEDED");
		}
	}
	
	public abstract String generate();
	
	private static ActuatorSensor findConnectionConfiguration(Brick brick, ECUPort port) {
		for (HardwareConnection conn : brick.getHardwareconnection()) {
			if (conn.getHardwareport().equals(port)) {
				return (ActuatorSensor) conn;
			}
		}
		throw new RuntimeException("Port "+ port +"is not configured");
	}
}
