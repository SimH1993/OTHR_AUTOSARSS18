package generator.brick;

import java.io.IOException;
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
		try {
			new FileGenerator("templates\\brick\\runnable.c").addReplacement("<SWC_NAME>", swc.getName())
					.addReplacement("<RUNNABLE_NAME>", runnable.getName().replace(' ', '_'))
					.execute(rootPath.resolve("SWC_" + swc.getName() + "_Runnable_" + runnable.getName() + ".c"));
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

}
