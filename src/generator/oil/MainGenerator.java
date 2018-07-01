package generator.oil;

import java.nio.file.Path;
import java.nio.file.Paths;
import java.util.HashMap;
import java.util.Map;

import org.eclipse.emf.common.util.EList;

import autosarMetaModel.AutosarSystem;
import autosarMetaModel.Brick;
import autosarMetaModel.Connection;
import autosarMetaModel.helper.ModelHelper;
import generator.brick.BrickGenerator;

public class MainGenerator {

	public final static Path rootPath = Paths.get("C:\\Users\\loych\\Downloads\\generated");

	private final AutosarSystem system;

	private final Map<Connection, Integer> connectionIdMap = new HashMap<>();

	public MainGenerator(AutosarSystem system) {
		this.system = system;
	}

	public void prepare() {
		createBluetoothIds();
		for (Brick b : system.getBrick()) {
			BrickGenerator brickGenerator = new BrickGenerator(b, rootPath);
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
				connectionIdMap.put(conn, connectionIndx);
				connectionIndx++;
			}
		}

		System.out.println(connectionIdMap);
	}
}
