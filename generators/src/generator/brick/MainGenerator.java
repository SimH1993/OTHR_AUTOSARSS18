package generator.brick;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.emf.common.util.EList;

import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Brick;
import autosarMetaModel.Connection;
import autosarMetaModel.SoftwarePort;
import autosarMetaModel.helper.ModelHelper;
import generator.brick.BrickGenerator;

public class MainGenerator {

	public final static Path rootPath = Paths.get("C:\\Users\\sct43297\\Downloads\\generated");

	private final AutosarSystem system;

	private final Map<SoftwarePort, Integer> connectionIdMap = new HashMap<>();

	public MainGenerator(AutosarSystem system) {
		this.system = system;
	}

	public void prepare() {
		createBluetoothIds();
		for (Brick b : system.getBrick()) {
			BrickGenerator brickGenerator = new BrickGenerator(system, b, rootPath, Collections.unmodifiableMap(connectionIdMap));
			brickGenerator.generate();
		}
	}

	public void generate() {
		prepare();
	}

	private void createBluetoothIds() {
		EList<Connection> connections = system.getConnection();

		int connectionIndx = 0;
		for (Connection conn : connections) {
			if (ModelHelper.isBluetoothConnection(conn)) {
				connectionIdMap.put(conn.getInput(), connectionIndx);
				connectionIdMap.put(conn.getOutput(), connectionIndx);
				connectionIndx++;
			}
		}

		System.out.println(connectionIdMap);
	}
}
