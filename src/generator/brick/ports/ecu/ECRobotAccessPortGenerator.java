package generator.brick.ports.ecu;

import autosarMetaModel.AccessMode;
import autosarMetaModel.ActuatorSensor;
import autosarMetaModel.Brick;
import autosarMetaModel.ECRobotAccess;
import autosarMetaModel.ECUPort;
import autosarMetaModel.HardwareConnection;
import autosarMetaModel.Motor;
import autosarMetaModel.Ultraschall;

public class ECRobotAccessPortGenerator extends EcuPortGenerator {
	private Brick brick;
	private ECUPort port;
	private ActuatorSensor connection;

	public ECRobotAccessPortGenerator(Brick brick, ECUPort port) {
		this.brick = brick;
		this.port = port;
		findConnectionConfiguration();
	}
	
	@Override
	public String generate() {
		StringBuilder result = new StringBuilder();
		if (connection instanceof ECRobotAccess) {
			ECRobotAccess ecrobot = (ECRobotAccess) connection;
			AccessMode accessMode = ecrobot.getAccessMode();
			if (port instanceof Motor) {
				if (accessMode == AccessMode.WRITE) {
					result.append(generateMotor());
				} else {
					throw new RuntimeException("AccessMode not available for this ECRobot device");
				}	
			} else if (port instanceof Ultraschall) {
				if (accessMode == AccessMode.READ) {
					result.append(generateUltraschall());
				} else {
					throw new RuntimeException("AccessMode not available for this ECRobot device");
				}
			}
		}
		return result.toString();
	}
	
	private String generateMotor() {
		String result = "#define RTE_ECR_MOTOR_WRITE_<PORT_NAME>(value)\tmotor_set_speed(<PORT>, value)\n";
		result = result.replace("<PORT_NAME>", port.getName())
				.replace("<PORT>", getPort());
		return result;
	}
	
	private String generateUltraschall() {
		String result = "#define RTE_ECR_ULTRASCHALL_READ_<PORT_NAME>()\tsonar_read_distance(<PORT>)\n";
		result = result.replace("<PORT_NAME>", port.getName())
				.replace("<PORT>", getPort());
		return result;
	}
	
	private String getPort() {
		return connection.getPortNr().toString();
	}
	
	
	private void findConnectionConfiguration() {
		for (HardwareConnection conn : brick.getHardwareconnection()) {
			if (conn.getHardwareport().equals(port)) {
				connection = (ActuatorSensor) conn;
			}
		}
		if (connection == null)
			throw new RuntimeException("Port is not configured");
	}
}
