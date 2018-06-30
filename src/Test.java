import java.io.File;

import org.eclipse.emf.common.util.URI;
import org.eclipse.emf.ecore.resource.Resource;
import org.eclipse.emf.ecore.resource.ResourceSet;
import org.eclipse.emf.ecore.resource.impl.ResourceSetImpl;
import org.eclipse.emf.ecore.xmi.impl.XMIResourceFactoryImpl;
import autosarMetaModel.*;


public class Test {
	
	public static void main(String[] args) {
		AutosarMetaModelPackage.eINSTANCE.eClass();
		ResourceSet resourceSet = new ResourceSetImpl();
		
		resourceSet.getResourceFactoryRegistry().getExtensionToFactoryMap().put
			(Resource.Factory.Registry.DEFAULT_EXTENSION, new XMIResourceFactoryImpl());
		
		File file = new File("C:\\Users\\gra44333\\runtime-EclipseApplication\\Test2\\My.autosarmetamodel");
		URI uri = file.isFile() ? URI.createFileURI(file.getAbsolutePath()) : URI.createURI("AutosarMetaModel");
		
		try {
			Resource resource = resourceSet.getResource(uri, true);
			System.out.println("Loaded: " + uri);
		} catch (RuntimeException e) {
            System.out.println("Problem loading " + uri);
            e.printStackTrace();
		}
	}
}
