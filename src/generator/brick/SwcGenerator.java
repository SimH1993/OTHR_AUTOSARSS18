package generator.brick;

import java.io.IOException;
import java.nio.file.Path;

import autosarMetaModel.Brick;
import autosarMetaModel.Port;
import autosarMetaModel.SWC;
import autosarMetaModel.SoftwarePort;
import generator.brick.ports.SoftwarePortGenerator;
import generator.oil.FileGenerator;
import generator.oil.model.OilFile;

public class SwcGenerator {

	private final Brick brick;
	private final SWC swc;
	private final OilFile oilFile;
	private final Path rootPath;

	private final StringBuilder generatedFunctions;

	public SwcGenerator(Brick brick, SWC swc, OilFile oilFile, Path rootPath) {
		this.brick = brick;
		this.swc = swc;
		this.oilFile = oilFile;
		this.rootPath = rootPath;
		generatedFunctions = new StringBuilder(swc.getPort().size() * 150);
	}

	private void prepare() {
		for (autosarMetaModel.Runnable r : swc.getRunnable()) {
			new RunnableGenerator(swc, r, rootPath).generate();
		}
	}

	private void process() {
		for (Port p : swc.getPort()) {
			if (p instanceof SoftwarePort) {
				SoftwarePort swPort = (SoftwarePort) p;
				String generate = SoftwarePortGenerator.of(swPort).generate();
				generatedFunctions.append(generate);
			}
		}
	}

	private void persist() {
		try {
			new FileGenerator("templates\\brick\\swcTemplate.c").append(generatedFunctions.toString())
					.execute(rootPath.resolve("SWC_" + swc.getName() + ".c"));
		} catch (IOException e) {
			e.printStackTrace();
		}
	}

	public void generate() {
		prepare();
		process();
		persist();
	}

}
