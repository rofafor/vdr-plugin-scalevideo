/*
 * scalevideo.c: A plugin for the Video Disk Recorder
 *
 * See the README file for copyright information and how to reach the author.
 *
 * $Id$
 */

#include <vdr/plugin.h>
#include <vdr/device.h>
#include <vdr/osdbase.h>

static const char *VERSION        = "0.0.1";
static const char *DESCRIPTION    = "Scale Video Tester";
static const char *MAINMENUENTRY  = "Scalevideo";

class cScalevideoOsd : public cOsdObject {
private:
  bool fullscreen;
  void ScaleFullscreen(bool onOffP);

public:
  cScalevideoOsd();
  ~cScalevideoOsd();

  virtual eOSState ProcessKey(eKeys Key);
};

cScalevideoOsd::cScalevideoOsd()
: fullscreen(true)
{
  ScaleFullscreen(fullscreen);
}

cScalevideoOsd::~cScalevideoOsd()
{
  ScaleFullscreen(true);
}

void cScalevideoOsd::ScaleFullscreen(bool onOffP) {
    if (onOffP)
        cDevice::PrimaryDevice()->ScaleVideo(cRect::Null);
    else {
        int w = cOsd::OsdWidth() / 2;
        int h = cOsd::OsdHeight() / 2;
        int x = cOsd::OsdLeft() + w / 2;
        int y = cOsd::OsdTop() + h / 2;
        cRect videoWindow(x, y, w, h);
        if (cDevice::PrimaryDevice()->CanScaleVideo(videoWindow) != cRect::Null)
           cDevice::PrimaryDevice()->ScaleVideo(videoWindow);
    }
}

eOSState cScalevideoOsd::ProcessKey(eKeys Key)
{
  eOSState state = cOsdObject::ProcessKey(Key);
  if (state == osUnknown) {
     switch (int(Key)) {
       case kOk:
            fullscreen = !fullscreen;
            ScaleFullscreen(fullscreen);
            return osContinue;
       case kBack:
            return osEnd;
       default:
            break;
       }
     state = osContinue;
     }
  return state;
}

class cPluginScalevideo : public cPlugin {
private:
  // Add any member variables or functions you may need here.
public:
  cPluginScalevideo(void);
  virtual ~cPluginScalevideo();
  virtual const char *Version(void) { return VERSION; }
  virtual const char *Description(void) { return DESCRIPTION; }
  virtual const char *CommandLineHelp(void);
  virtual bool ProcessArgs(int argc, char *argv[]);
  virtual bool Initialize(void);
  virtual bool Start(void);
  virtual void Stop(void);
  virtual void Housekeeping(void);
  virtual void MainThreadHook(void);
  virtual cString Active(void);
  virtual time_t WakeupTime(void);
  virtual const char *MainMenuEntry(void) { return MAINMENUENTRY; }
  virtual cOsdObject *MainMenuAction(void);
  virtual cMenuSetupPage *SetupMenu(void);
  virtual bool SetupParse(const char *Name, const char *Value);
  virtual bool Service(const char *Id, void *Data = NULL);
  virtual const char **SVDRPHelpPages(void);
  virtual cString SVDRPCommand(const char *Command, const char *Option, int &ReplyCode);
  };

cPluginScalevideo::cPluginScalevideo(void)
{
  // Initialize any member variables here.
  // DON'T DO ANYTHING ELSE THAT MAY HAVE SIDE EFFECTS, REQUIRE GLOBAL
  // VDR OBJECTS TO EXIST OR PRODUCE ANY OUTPUT!
}

cPluginScalevideo::~cPluginScalevideo()
{
  // Clean up after yourself!
}

const char *cPluginScalevideo::CommandLineHelp(void)
{
  // Return a string that describes all known command line options.
  return NULL;
}

bool cPluginScalevideo::ProcessArgs(int argc, char *argv[])
{
  // Implement command line argument processing here if applicable.
  return true;
}

bool cPluginScalevideo::Initialize(void)
{
  // Initialize any background activities the plugin shall perform.
  return true;
}

bool cPluginScalevideo::Start(void)
{
  // Start any background activities the plugin shall perform.
  return true;
}

void cPluginScalevideo::Stop(void)
{
  // Stop any background activities the plugin is performing.
}

void cPluginScalevideo::Housekeeping(void)
{
  // Perform any cleanup or other regular tasks.
}

void cPluginScalevideo::MainThreadHook(void)
{
  // Perform actions in the context of the main program thread.
  // WARNING: Use with great care - see PLUGINS.html!
}

cString cPluginScalevideo::Active(void)
{
  // Return a message string if shutdown should be postponed
  return NULL;
}

time_t cPluginScalevideo::WakeupTime(void)
{
  // Return custom wakeup time for shutdown script
  return 0;
}

cOsdObject *cPluginScalevideo::MainMenuAction(void)
{
  // Perform the action when selected from the main VDR menu.
  return new cScalevideoOsd;
}

cMenuSetupPage *cPluginScalevideo::SetupMenu(void)
{
  // Return a setup menu in case the plugin supports one.
  return NULL;
}

bool cPluginScalevideo::SetupParse(const char *Name, const char *Value)
{
  // Parse your own setup parameters and store their values.
  return false;
}

bool cPluginScalevideo::Service(const char *Id, void *Data)
{
  // Handle custom service requests from other plugins
  return false;
}

const char **cPluginScalevideo::SVDRPHelpPages(void)
{
  // Return help text for SVDRP commands this plugin implements
  return NULL;
}

cString cPluginScalevideo::SVDRPCommand(const char *Command, const char *Option, int &ReplyCode)
{
  // Process SVDRP commands this plugin implements
  return NULL;
}

VDRPLUGINCREATOR(cPluginScalevideo); // Don't touch this!
