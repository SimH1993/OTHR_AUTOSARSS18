package generator.brick;

import java.util.Map;

import autosarMetaModel.SoftwarePort;

public class MasterCModel {
	private StringBuilder includes = new StringBuilder();
	private StringBuilder functions = new StringBuilder();
	private Map<SoftwarePort, Integer> remoteConnectionIdMap;
	
	
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
	
	public Map<SoftwarePort, Integer> getRemoteConnectionIdMap() {
		return remoteConnectionIdMap;
	}
	
	public void setRemoteConnectionIdMap(Map<SoftwarePort, Integer> remoteConnectionIdMap) {
		this.remoteConnectionIdMap = remoteConnectionIdMap;
	}
	
}
