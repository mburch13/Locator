
#include <maya/MBoundingBox.h>
#include <maya/MPxDrawOverride.h>

//this class can not be iterated from
class basicLocatorOverride final : public ::MPxDrawOverride{
private:
  class basicLocatorUserData final : public MUserData{
  public:
    basicLocatorUserData() : MUserData(false){}
    virtual ~basicLocatorUserData() = default;

    MBoundingBox fBounds;
    MDagPath fPath;
  };

public:
  static MHWRender::MPxDrawOverride* creator(const MObject& obj);

  virtual ~basicLocatorOverride() = default;

  virtual MHWRender::DrawAPI supportedDrawAPIs() const override;

  //extract all needed data for rendering
  MUserData* prepareForDraw(const MDagPath& objPath, const MDagPath& cameraPath, const MHWRender::MFrameContext& frameContext, MUserData* data) override;

  bool hasUIDrawables() const override {return true;}
  void addUIDrawables(const MDagPath& objPath, MHWRender::MUIDrawManager& drawManager, const MHWRender::MFrameContext& frameContext, const MUserData* data) override;

  static void draw(const MHWRender::MDrawContext& context, const MUserData* data);

private:
  //private constructor
  basicLocatorOverride(const MObject& obj);

};
