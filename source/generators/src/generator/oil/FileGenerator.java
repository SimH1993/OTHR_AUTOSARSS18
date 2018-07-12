package generator.oil;

import java.io.IOException;
import java.nio.file.Files;
import java.nio.file.Path;
import java.nio.file.StandardOpenOption;
import java.util.Collections;
import java.util.HashMap;
import java.util.Map;

import generator.ResourceLoader;

public class FileGenerator {
	private final String inputPath;
	private final Map<String, String> replacements = new HashMap<>();
	private final StringBuilder appendments = new StringBuilder();
	private final boolean overwrite;

	public FileGenerator(String inputPath) {
		this(inputPath, true);
	}

	public FileGenerator(String inputPath, boolean overwrite) {
		this.inputPath = inputPath;
		this.overwrite = overwrite;
	}

	public FileGenerator addReplacement(String original, String replacement) {
		replacements.put(original, replacement);
		return this;
	}

	public FileGenerator append(String string) {
		appendments.append(string);
		return this;
	}

	public void execute(Path output) {
		try {
			if (Files.exists(output) && !overwrite) {
				return;
			}
			Files.write(output, Collections.singletonList(execute()), StandardOpenOption.TRUNCATE_EXISTING,
					StandardOpenOption.CREATE);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}

	public String execute() {
		String lines = readFile();
		for (Map.Entry<String, String> entry : replacements.entrySet()) {
			lines = lines.replace(entry.getKey(), entry.getValue());
		}
		lines += "\n" + appendments;
		return lines;
	}

	private String readFile() {
		try {
			return ResourceLoader.load(inputPath);
		} catch (IOException e) {
			throw new RuntimeException(e);
		}
	}
}
