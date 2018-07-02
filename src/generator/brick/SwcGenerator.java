package generator.brick;

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
	private MasterCModel masterC;

	public SwcGenerator(Brick brick, SWC swc, OilFile oilFile, Path rootPath, MasterCModel masterC) {
		this.brick = brick;
		this.swc = swc;
		this.oilFile = oilFile;
		this.rootPath = rootPath;
		this.masterC = masterC;
		generatedFunctions = new StringBuilder(swc.getPort().size() * 150);
	}

	private void prepare() {
		masterC.getIncludes().append("#include \""+getFileName()+"\"\n");
		
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
		StringBuilder includes = new StringBuilder();
		for(autosarMetaModel.Runnable r : swc.getRunnable()) {
			includes.append("#include \"" + "SWC_" + swc.getName() + "_Runnable_" + r.getName() + ".c"+ "\"\n");
		}
		
		new FileGenerator("templates\\brick\\swcTemplate.c")
		.addReplacement("<INCLUDES>", includes.toString())
				.append(generatedFunctions.toString())
				.execute(rootPath.resolve(getFileName()));
	}
	
	private String getFileName() {
		return "SWC_" + swc.getName() + ".c";
	}

	public void generate() {
		prepare();
		process();
		persist();
	}

}
