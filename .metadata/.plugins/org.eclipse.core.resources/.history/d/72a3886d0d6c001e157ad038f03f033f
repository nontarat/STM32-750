#ifndef WASHERSCREEN_VIEW_HPP
#define WASHERSCREEN_VIEW_HPP

#include <gui_generated/washerscreen_screen/WasherScreenViewBase.hpp>
#include <gui/washerscreen_screen/WasherScreenPresenter.hpp>

class WasherScreenView : public WasherScreenViewBase
{
public:
    WasherScreenView();
    virtual ~WasherScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& event);
    virtual void handleTickEvent();

    uint16_t getSelectedProgram();
    uint16_t getWashingTime();
    void setSelectedProgram(uint16_t program);
protected:
};

#endif // WASHERSCREEN_VIEW_HPP
