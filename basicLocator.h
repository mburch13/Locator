//basicLocator.h

#ifndef basicLocator_H
#define basicLocator_H

#include <maya/MTypeId.h>  //Manage Maya Object type identifiers
#include <maya/MPxLocatorNode.h>  //Base class for user defined dependency nodes

class basicLocator : public MPxLocatorNode{
  public:
    static MStatus initialize();  //initialize node
    static void* creator();  //create node
    MStatus compute(const MPlug& plug, MDataBlock& data) override;  //implements core of the node

    void draw(M3dView&, const MDagPath&, M3dView::DisplayStyle, M3dView::DisplayStatus) override;
    bool isBounded() const override;

  public:
    //needed variables
    static MTypeId typeId;
    static MObject drawIt;
    static const MString kTypeName;
    static const MString kDrawDbClassification;

};

#endif
