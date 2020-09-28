//basicLocator.cpp
#  include <OpenGL/gl.h>  // definitions for GL graphics routines
#  include <OpenGL/glu.h> // definitions for GL input device handling
#  include <GLUT/glut.h>  // deginitions for the GLUT utility toolkit

#include "basicLocator.h"

#include <maya/MGlobal.h>  //static class provviding common API global functions
#include <maya/MFnNumericAttribute.h>  //numeric attribute function set
#include <maya/MPlug.h>
#include <maya/MViewport2Renderer.h>

#include <cmath>  //c++ math library


MTypeId basicLocator::typeId(0x8000A);  //define value for typeId

MObject basicLocator::drawIt;
const MString basicLocator::kTypeName("basicLocatorDO");

//node drawdb classification string
const MString basicLocator::kDrawDbClassification("drawdb/geometry/basicLocatorDO");

void* basicLocator::creator(){
  return new basicLocator();
}

MStatus basicLocator::initialize(){
  MFnNumericAttribute numFn;
  MStatus stat;

  drawIt = numFn.create("drawIt", "dwi", MFnNumericData::kBoolean, 0);
  numFn.setStorable(true);
  numFn.setWritable(true);
  addAttribute(drawIt);

  return MS::kSuccess;
}

bool basicLocator::isBounded() const{
  return false;
}

MStatus basicLocator::compute(const MPlug& plug, MDataBlock& dataBlock){
  //trigger only when needed
  return MS::kSuccess;
}

void basicLocator::draw(M3dView& view, const MDagPath& path, M3dView::DisplayStyle dispStyle, M3dView::DisplayStatus status){
  MPlug drawItP(thisMObject(), drawIt);
  bool drawItV;
  drawItP.getValue(drawItV);

  if(!drawItV)
    return;

  view.beginGL();
  glPushAttrib(GL_ALL_ATTRIB_BITS);
  glEnable(GL_BLEND);
  // glBlendFunc(GL_SCR_ALPHA, GL_ONE_MINUS_SCR_ALPHA); // error: use of undeclared identifier 'GL_SCR_ALPHA' 'GL_ONE_MINUS_SCR_ALPHA'

  glLineWidth(10);

//Initialize openGL and draw
  if(status == M3dView::kLead)
    glColor4f(0.0, 1.0, 0.0, 0.3f);
  else
    glColor4f(1.0, 1.0, 0.0, 0.3f);

  glBegin(GL_TRIANGLES);
  glVertex3d(-2,1,0);
  glVertex3d(-2,-1,0);
  glVertex3d(2,1,0);

  glVertex3d(-2,-1,0);
  glVertex3d(2,-1,0);
  glVertex3d(2,1,0);

  glVertex3d(2,-1.5,0);
  glVertex3d(2,1.5,0);
  glVertex3d(3,0,0);
  glEnd();

  glDisable(GL_BLEND);
  glPopAttrib();

}
