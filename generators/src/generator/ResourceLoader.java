package generator;

import java.io.BufferedReader;
import java.io.IOException;
import java.io.InputStream;
import java.io.InputStreamReader;

public class ResourceLoader {

	public static String load(String path) throws IOException {
		InputStream stream = ResourceLoader.class.getResourceAsStream(path);
		return readInputStream(stream);
	}

	private static String readInputStream(InputStream stream) throws IOException {
		String newLine = System.getProperty("line.separator");
		BufferedReader reader = new BufferedReader(new InputStreamReader(stream));
		StringBuilder result = new StringBuilder();
		String line;
		boolean flag = false;
		while ((line = reader.readLine()) != null) {
			result.append(flag ? newLine : "").append(line);
			flag = true;
		}
		return result.toString();
	}
}
