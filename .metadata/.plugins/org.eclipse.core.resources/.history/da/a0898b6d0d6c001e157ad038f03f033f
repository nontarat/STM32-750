#include <gui/washerscreen_screen/WasherScreenView.hpp>

WasherScreenView::WasherScreenView()
{

}

void WasherScreenView::setupScreen()
{
    WasherScreenViewBase::setupScreen();
}

void WasherScreenView::tearDownScreen()
{
    WasherScreenViewBase::tearDownScreen();
}

void WasherScreenView::handleClickEvent(const ClickEvent& event)
{
    View::handleClickEvent(event);

    if (washerContainer.isVisible())
    {
        washerContainer.clickEvent(event);
    }
}

void WasherScreenView::handleTickEvent()
{
    washerContainer.tickEvent();
}

uint16_t WasherScreenView::getSelectedProgram()
{
    return washerContainer.getWashingProgram();
}

uint16_t WasherScreenView::getWashingTime()
{
    return washerContainer.getWashingTime();
}

void WasherScreenView::setSelectedProgram(uint16_t program)
{
    washerContainer.setWashingProgram(program);
}
