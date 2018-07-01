import autosarMetaModel.AutosarSystem;
import autosarMetaModel.persistency.FileLoader;
import generator.oil.MainGenerator;


public class Test {
	
	public static void main(String[] args) {
		AutosarSystem system = FileLoader.load("C:\\Users\\loych\\Development\\OTHR_AUTOSARSS18\\generator\\DemoProject\\My.autosarmetamodel\\");
		new MainGenerator(system).generate();
	}
}
