package generator.brick;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.util.HashMap;
import java.util.Map;
import java.util.StringJoiner;

import org.eclipse.emf.common.util.EList;

import autosarMetaModel.ActuatorSensor;
import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Brick;
import autosarMetaModel.Connection;
import autosarMetaModel.HardwareConnection;
import autosarMetaModel.Motor;
import autosarMetaModel.OperationMode;
import autosarMetaModel.SWC;
import autosarMetaModel.SenderReceiverPort;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.Taster;
import autosarMetaModel.Ultraschall;
import autosarMetaModel.helper.ModelHelper;
import generator.oil.FileGenerator;
import generator.oil.model.OilFile;
import generator.oil.visitor.OilFileVisitor;

public class BrickGenerator {

	private final Brick brick;
	private final Path rootPath;
	private final OilFile oilFile = new OilFile();
	private final AutosarSystem system;
	private final MasterCModel masterC = new MasterCModel();
	private Map<SenderReceiverPort, Integer> localSenderReceiverIds = new HashMap<>();
	private Map<SoftwarePort, Integer> remoteConnectionIdMap;

	public BrickGenerator(AutosarSystem system, Brick brick, Path rootpath, Map<SoftwarePort, Integer> map) {
		this.system = system;
		this.brick = brick;
		this.remoteConnectionIdMap = map;
		masterC.setRemoteConnectionIdMap(remoteConnectionIdMap);
		this.rootPath = rootpath.resolve("Brick_" + brick.getName().replace(" ", "_"));
	}

	private void prepare() {
		try {
			Files.createDirectories(rootPath);
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	private void process() {
		for (SWC swc : brick.getSwc()) {
			SwcGenerator swcGenerator = new SwcGenerator(brick, swc, oilFile, rootPath, masterC, localSenderReceiverIds, remoteConnectionIdMap);
			swcGenerator.generate();
		}

		configureDefines();
		new MasterCGenerator(rootPath, masterC, oilFile, localSenderReceiverIds, brick).generate();
	}

	private void configureDefines() {

		EList<Brick> bricks = system.getBrick();
		Brick otherBrick = null;
		for (int i = 0; i < bricks.size(); i++) {
			if (!bricks.get(i).equals(brick)) {
				otherBrick = bricks.get(i);
			}
		}

		String bluetoothMAC = otherBrick.getBluetoothMAC();
		String[] splits = bluetoothMAC.split(":");
		StringJoiner stringJoiner = new StringJoiner(", ", "{ ", " }");
		for (String s : splits) {
			stringJoiner.add(s);
		}

		FileGenerator fileGenerator = new FileGenerator("templates\\bsw\\defines.h")
				.addReplacement("<BT_SLAVE_ADDRESS>", stringJoiner.toString());
		if (brick.getBluetoothMode() == OperationMode.MASTER) {
			fileGenerator.append("#define COM_CONNECT_IS_MASTER\n");
		}
		String motorDefines = generateMotorDefines();
		fileGenerator.append(motorDefines);
		fileGenerator.append(generateSonarDefines());
		fileGenerator.append(generateTouchSensorDefines());

		fileGenerator.append("#endif");
		fileGenerator.execute(rootPath.resolve("defines.h"));
	}
	
	private String generateMotorDefines() {
		StringBuilder defines = new StringBuilder();
		for(HardwareConnection conn : brick.getHardwareconnection()) {
			ActuatorSensor actuatorSensor = (ActuatorSensor) conn;
			if(conn.getHardwareport() instanceof Motor) {
				Motor motor = (Motor) conn.getHardwareport();
				defines.append("#define MOTOR_" + motor.getKind().toString() + "	" + actuatorSensor.getPortNr().toString() + "\n");
			}
		}
		
		return defines.toString();
	}
	
	private String generateSonarDefines() {
		String result = "";
		for(HardwareConnection conn : brick.getHardwareconnection()) {
			ActuatorSensor actuatorSensor = (ActuatorSensor) conn;
			if(conn.getHardwareport() instanceof Ultraschall) {
				result = "#define SONAR_SENSOR_PORT\t" + actuatorSensor.getPortNr().toString()+ "\n";
			}
		}
		return result;
	}
	
	private String generateTouchSensorDefines() {
		String result = "";
		for(HardwareConnection conn : brick.getHardwareconnection()) {
			ActuatorSensor actuatorSensor = (ActuatorSensor) conn;
			if(conn.getHardwareport() instanceof Taster) {
				result = "#define TOUCH_SENSOR_PORT\t" + actuatorSensor.getPortNr().toString()+ "\n";
			}
		}
		return result;
	}

	public void generate() {
		generateLocalSenderReceiverIds();
		prepare();
		process();
		generateOil();
	}
	
	private void generateOil() {
		try {
			new OilFileVisitor(oilFile).generateOil(rootPath.resolve("master.oil"));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	private void generateLocalSenderReceiverIds() {
		int connectionIndex = 0;
		for(Connection c : system.getConnection()) {
			if(c.getInput() instanceof SenderReceiverPort && ModelHelper.isLocalConnection(c)) {
				Brick brickOfPort = ModelHelper.getBrickOfPort(system, c.getInput());
				if(brickOfPort.equals(brick)) {
					localSenderReceiverIds.put((SenderReceiverPort) c.getInput(), connectionIndex);
					localSenderReceiverIds.put((SenderReceiverPort) c.getOutput(), connectionIndex);
					connectionIndex++;
				}
			}
		}
	}
	
}
