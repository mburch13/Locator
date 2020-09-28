#include "basicLocatorOverride.h"
#include "basicLocator.h"

#include <maya/MDagPath.h>
#include <maya/MDrawContext.h>
#include <maya/MFnDagNode.h>
#include <maya/MFrameContext.h>
#include <maya/MHWGeometryUtilities.h>
#include <maya/MPointArray.h>
#include <maya/MUintArray.h>
#include <maya/MUserData.h>
#include <maya/MViewport2Renderer.h>

MHWRender::MPxDrawOverride* basicLocatorOverride::creator(const MObject& obj){
  return new basicLocatorOverride(obj);
}

basicLocatorOverride::basicLocatorOverride(const MObject& obj) : MHWRender::MPxDrawOverride(obj, basicLocatorOverride::draw){}

MHWRender::DrawAPI basicLocatorOverride::supportedDrawAPIs() const {
  return (MHWRender::kOpenGL | MHWRender::kDirectX11 | MHWRender::kOpenGLCoreProfile);
}

MUserData* basicLocatorOverride::prepareForDraw(const MDagPath& objPath, const MDagPath& cameraPath, const MHWRender::MFrameContext& frameContext, MUserData* data){
   /* --------------------------------------------------------------------------------------------------
   Called before draw, this gives the override a chance to cache any data it needs from the DG and is the only  safe place to do so.

   Paramaters:
     objPath       -MDagPath of the object about to be drawn
     cameraPath    -MDagPath of the camera the object is going to be drawn with
     frameContext  -an MFrameContext containing information about the current frame and render targets etc.
     data          -the old user data or None if this is the first time the override is Called

   Returns:
     an instance of MUserData to be passed to the draw callback and addUIDrawables methodes
   -------------------------------------------------------------------------------------------------- */
   auto* boundsData = dynamic_cast<basicLocatorUserData*>(data);
   if(!boundsData){
     boundsData = new basicLocatorUserData();
   }

   boundsData -> fPath = objPath;

   MFnDagNode dagNodeFn(objPath);
   boundsData -> fBounds = dagNodeFn.boundingBox();

   return boundsData;
}

void basicLocatorOverride::addUIDrawables(const MDagPath& objPath, MHWRender::MUIDrawManager& drawManager, const MHWRender::MFrameContext& frameContext, const MUserData* data){
   /* --------------------------------------------------------------------------------------------------
   Add any UI drawables here

   Paramaters:
     objPath        -MDagPath of the object about to be drawn
     drawManager    -MDrawMnager instance that can be used to add UI drawables
     frameContext   -an MFrameContext containing information about the current frame and render targets etc.
     data           -the user data yhsy was returned by prepareForDraw()

   Returns:
     an instance of MUserData to be passed to the draw callback and addUIDrawables methodes
   -------------------------------------------------------------------------------------------------- */
   const auto* boundsData = dynamic_cast<const basicLocatorUserData*>(data);
   if(!boundsData){
     return;
   }

   MPointArray pnts;
   pnts.append(MPoint(-2.0, 1.0, 0.0));
   pnts.append(MPoint(-2.0, -1.0, 0.0));
   pnts.append(MPoint(2.0, 1.0, 0.0));
   pnts.append(MPoint(2.0, -1.0, 0.0));
   pnts.append(MPoint(2.0, -1.5, 0.0));
   pnts.append(MPoint(2.0, 1.5, 0.0));
   pnts.append(MPoint(3.0, 0.0, 0.0));

   MUintArray indices;
   indices.append(0);
   indices.append(1);
   indices.append(2);
   indices.append(1);
   indices.append(3);
   indices.append(2);
   indices.append(4);
   indices.append(5);
   indices.append(6);

   const MHWRender::DisplayStatus displayStatus = MHWRender::MGeometryUtilities::displayStatus(objPath);

   MColor color;
   if(displayStatus == MHWRender::DisplayStatus::kLead){
     color = MColor(0.0, 1.0f, 0.0, 0.3);
   }
   else{
     color = MColor(1.0, 0.0f, 0.0, 0.3);
   }

   drawManager.beginDrawable();
   {
     if(frameContext.getDisplayStyle() & (MHWRender::MFrameContext::kFlatShaded | MHWRender::MFrameContext::kGouraudShaded | MHWRender::MFrameContext::kTextured)){

       drawManager.setColor(color);
       drawManager.setDepthPriority(MHWRender::MRenderItem::sDormantFilledDepthPriority);

       drawManager.mesh(MHWRender::MUIDrawManager::kTriangles, pnts, NULL, NULL, &indices, NULL);
     }
   }

   //color and depth for wireFrame
   drawManager.endDrawable();
}

void basicLocatorOverride::draw(const MHWRender::MDrawContext& context, const MUserData* data){
}
