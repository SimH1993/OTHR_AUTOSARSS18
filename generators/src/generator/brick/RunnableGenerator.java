package generator.brick;

import java.nio.file.Path;

import autosarMetaModel.Runnable;
import autosarMetaModel.SWC;
import generator.oil.FileGenerator;

public class RunnableGenerator {

	private final SWC swc;
	private final Runnable runnable;
	private final Path rootPath;

	public RunnableGenerator(SWC swc, Runnable runnable, Path rootPath) {
		this.swc = swc;
		this.runnable = runnable;
		this.rootPath = rootPath;
	}

	public void generate() {
		new FileGenerator("templates\\brick\\runnable.c", false)
				.addReplacement("<RUNNABLE_NAME>", runnable.getName().replace(' ', '_'))
				.execute(rootPath.resolve("Runnable_" + runnable.getName() + ".c"));
	}

}
