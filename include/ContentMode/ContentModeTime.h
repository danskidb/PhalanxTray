#include "ContentModeBase.h"

namespace PhalanxTray
{
    class ContentModeTime : public ContentModeBase
    {
    public:
        const std::string contentModeName = "Time";

        ContentModeTime(serial::Serial* serialConnPtr) : ContentModeBase(serialConnPtr) { }
        virtual void OnActivate();
        virtual void OnDeactivate();
        virtual void OnTick();
    };
}