package generator.brick;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;

import autosarMetaModel.Brick;
import autosarMetaModel.SWC;
import generator.oil.model.OilFile;

public class BrickGenerator {

	private final Brick brick;
	private final Path rootPath;
	private final OilFile oilFile = new OilFile();

	public BrickGenerator(Brick brick, Path rootpath) {
		this.brick = brick;
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
			SwcGenerator swcGenerator = new SwcGenerator(brick, swc, oilFile, rootPath);
			swcGenerator.generate();
		}
	}

	public void generate() {
		prepare();
		process();
	}
}
