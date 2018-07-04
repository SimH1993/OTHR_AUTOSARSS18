package generator.brick.ports.ecu;

import autosarMetaModel.ADC;
import autosarMetaModel.ActuatorSensor;
import autosarMetaModel.Brick;
import autosarMetaModel.ECUPort;
import autosarMetaModel.HardwareConnection;
import autosarMetaModel.I2CExpander;
import autosarMetaModel.IC2Mode;

public class RawAccessPortGenerator {
	private ECUPort port;
	private Brick brick;
	private ActuatorSensor connection;

	public RawAccessPortGenerator(Brick brick, ECUPort port) {
		this.brick = brick;
		this.port = port;
		findConnectionConfiguration();
	}

	public String generateRead() {
		String result = "#define RTE_<MODE>_READ_<PORT_NAME>()	<MODE>_Read_Value(<INTERN_EXTERN>, <PORT>, <I2C>, <PIN>)";
		result = result.replace("<MODE>", getMode()).replace("<PORT_NAME>", port.getName())
				.replace("<INTERN_EXTERN>", isExtern() ? "1" : "0").replace("<PORT>", getPort())
				.replace("<I2C>", getIC2Address()).replace("<PIN>", getPin() + "");
		return result;
	}

	public String generateWrite() {
		String result = "#define RTE_<MODE>_WRITE_<PORT_NAME>(value)	<MODE>_Read_Value(<INTERN_EXTERN>, <PORT>, <I2C>, <PIN>, value)";
		result = result.replace("<MODE>", getMode()).replace("<PORT_NAME>", port.getName())
				.replace("<INTERN_EXTERN>", isExtern() ? "1" : "0").replace("<PORT>", getPort())
				.replace("<I2C>", getIC2Address()).replace("<PIN>", getPin() + "");
		return result;
	}

	private ActuatorSensor findConnectionConfiguration() {
		for (HardwareConnection conn : brick.getHardwareconnection()) {
			if (conn.getHardwareport().equals(port)) {
				connection = (ActuatorSensor) conn;
			}
		}
		throw new RuntimeException("Port is not configured");
	}

	private String getMode() {
		if (connection instanceof ADC) {
			return "ADC";
		} else if (connection instanceof I2CExpander) {
			I2CExpander exp = (I2CExpander) connection;
			IC2Mode mode = exp.getMode();
			if (mode == IC2Mode.DIO) {
				return "DIO";
			} else {
				return "ADC";
			}
		}

		throw new RuntimeException();
	}

	private boolean isExtern() {
		return connection instanceof I2CExpander;
	}

	private String getPort() {
		return connection.getPortNr().toString();
	}

	private String getIC2Address() {
		if (connection instanceof I2CExpander) {
			return ((I2CExpander) connection).getAddress();
		} else {
			return "0";
		}
	}

	private int getPin() {
		if (connection instanceof I2CExpander) {
			return ((I2CExpander) connection).getPin();
		} else {
			return 0;
		}
	}
}
