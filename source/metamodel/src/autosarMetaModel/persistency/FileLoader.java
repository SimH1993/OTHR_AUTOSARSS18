package autosarMetaModel.persistency;

import autosarMetaModel.AutosarMetaModelPackage;
import autosarMetaModel.AutosarSystem;
import org.eclipse.emf.common.util.Diagnostic;
import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.util.Diagnostician;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;

import java.util.Map;

public class FileLoader {
    public static AutosarSystem load(String filePath) {
        return load(filePath, true);
    }

    public static AutosarSystem load(String filePath, boolean validateModel) {
        AutosarMetaModelPackage.eINSTANCE.eClass();
        Resource.Factory.Registry registry = Resource.Factory.Registry.INSTANCE;
        Map<String, Object> map = registry.getExtensionToFactoryMap();
        map.put(Resource.Factory.Registry.DEFAULT_EXTENSION, new XMIResourceFactoryImpl());

        ResourceSet set = new ResourceSetImpl();

        set.getPackageRegistry().put(AutosarMetaModelPackage.eNS_URI, AutosarMetaModelPackage.eINSTANCE);


        Resource resource = set.getResource(URI.createFileURI(filePath), true);

        AutosarSystem result = (AutosarSystem) resource.getContents().get(0);
        if (validateModel) {
            Diagnostic diagnostic = Diagnostician.INSTANCE.validate(result);
            if (diagnostic.getSeverity() != Diagnostic.OK) {
                throw new RuntimeException("Bad file!");
            }
        }

        return result;
    }
}
