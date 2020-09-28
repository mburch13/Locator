//McKenzie Burch
//Rigging Dojo Maya API
//mainPlugin.cpp
//standard setup for event node

#include "basicLocator.h"  //change include header for each node

#include <maya/MDrawRegistry.h>
#include "basicLocatorOverride.h"
#include <maya/MGlobal.h>
#include <maya/MFnPlugin.h> //Maya class that redisters and deregisters plug-ins with Maya

const MString pluginRegistrantId("basicLocator");

MStatus initializePlugin(MObject obj){
  MStatus status;
  MFnPlugin fnplugin(obj, "McKenzie Burch", "1.0", "Any");

  status = fnplugin.registerNode("basicLocator", basicLocator::typeId, basicLocator::creator, basicLocator::initialize, MPxNode::kLocatorNode, &basicLocator::kDrawDbClassification);

  if(status != MS::kSuccess){
    status.perror("Could not regiser the basicLocator node");
    return status;
  }

  //register the box handle draw override
  status = MHWRender::MDrawRegistry::registerDrawOverrideCreator(basicLocator::kDrawDbClassification, pluginRegistrantId, basicLocatorOverride::creator);

  if(!status){
    MGlobal::displayError("Undable to register basicLocator draw override.");
    return status;
  }

  return status;
}

MStatus uninitializePlugin(MObject obj){
  MFnPlugin pluginFn;
  //deregister the given user defined node type Maya
  pluginFn.deregisterNode(basicLocator::typeId);

  MStatus status = MHWRender::MDrawRegistry::deregisterDrawOverrideCreator(basicLocator::kDrawDbClassification, pluginRegistrantId);

  if(!status){
    MGlobal::displayError("Unable to register basicLocator draw override");
    return status;
  }

  return MS::kSuccess;
}
