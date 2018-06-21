package autosarMetaModel;

import autosarMetaModel.persistency.FileLoader;
import org.eclipse.emf.ecore.EObject;

import java.util.Iterator;

public class Util {

    private static <T> Iterable<T> iterate(Iterator<T> iterator) {
        return () -> iterator;
    }

    public static void main(String[] args) {
        AutosarSystem sys = FileLoader.load("C:\\Users\\loc34770\\runtime-EclipseApplication\\Playground\\My.autosarmetamodel");
        for (EObject o: iterate(sys.eAllContents())) {
            if (o instanceof Connection) {
                Connection conn = (Connection) o;
                System.out.println(conn);
                System.out.println("BluetoothConnection: " + conn.isBluetoothConnection());
            }
        }
    }
}
