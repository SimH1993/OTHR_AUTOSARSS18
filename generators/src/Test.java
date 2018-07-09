import autosarMetaModel.AutosarSystem;
import autosarMetaModel.persistency.FileLoader;
import generator.brick.MainGenerator;

public class Test {
	
	public static void main(String[] args) {
		AutosarSystem system = FileLoader.load("C:\\Users\\sct43297\\Downloads\\OTHR_AUTOSARSS18\\generator\\DemoProject\\My.autosarmetamodel");
		new MainGenerator(system).generate();
	}
}
