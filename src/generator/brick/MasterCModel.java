package generator.brick;

public class MasterCModel {
	private StringBuilder includes = new StringBuilder();
	private StringBuilder functions = new StringBuilder();
	
	
	public StringBuilder getFunctions() {
		return functions;
	}
	public void setFunctions(StringBuilder functions) {
		this.functions = functions;
	}
	public StringBuilder getIncludes() {
		return includes;
	}
	public void setIncludes(StringBuilder includes) {
		this.includes = includes;
	}
	
}
