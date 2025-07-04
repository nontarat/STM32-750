#include <gui/hallwayscreen_screen/HallwayScreenView.hpp>
#include <gui/common/Defines.hpp>
#include <touchgfx/Color.hpp>

HallwayScreenView::HallwayScreenView() :
    buttonMoveCallback(this, &HallwayScreenView::buttonMoveHandler),
    buttonFadeCallback(this, &HallwayScreenView::buttonFadeHandler),
    tickCounter(0), pixelsPrTick(0.5)
{
}

void HallwayScreenView::setupScreen()
{
    HallwayScreenViewBase::setupScreen();

    buttonKitchen.setMoveAnimationEndedAction(buttonMoveCallback);

    buttonKitchen.setFadeAnimationEndedAction(buttonFadeCallback);
    buttonBathroom.startFadeAnimation(255, HALLWAY_FADE_DURATION);
    buttonKitchen.startFadeAnimation(255, HALLWAY_FADE_DURATION);
}

void HallwayScreenView::tearDownScreen()
{
    HallwayScreenViewBase::tearDownScreen();
}

void HallwayScreenView::buttonMoveHandler(const MoveAnimator<Button>& src)
{
    if (buttonKitchen.getX() == BUTTON_KITCHEN_X_1)
    {
        buttonKitchen.startMoveAnimation(BUTTON_KITCHEN_X_2, buttonKitchen.getY(), calcDuration(BUTTON_KITCHEN_X_2, buttonKitchen.getX()));
        buttonBathroom.startMoveAnimation(BUTTON_BATHROOM_X_2, buttonBathroom.getY(), calcDuration(BUTTON_BATHROOM_X_2, buttonBathroom.getX()));
    }
    else if (buttonKitchen.getX() == BUTTON_KITCHEN_X_2)
    {
        buttonKitchen.startMoveAnimation(BUTTON_KITCHEN_X_3, buttonKitchen.getY(), calcDuration(BUTTON_KITCHEN_X_3, buttonKitchen.getX()));
        buttonBathroom.startMoveAnimation(BUTTON_BATHROOM_X_3, buttonBathroom.getY(), calcDuration(BUTTON_BATHROOM_X_3, buttonBathroom.getX()));
    }
}

void HallwayScreenView::buttonFadeHandler(const FadeAnimator< MoveAnimator<Button> >& src)
{
    buttonKitchen.startMoveAnimation(BUTTON_KITCHEN_X_1, buttonKitchen.getY(), calcDuration(BUTTON_KITCHEN_X_1, buttonKitchen.getX()));
    buttonBathroom.startMoveAnimation(BUTTON_BATHROOM_X_1, buttonBathroom.getY(), calcDuration(BUTTON_BATHROOM_X_1, buttonBathroom.getX()));
}

void HallwayScreenView::handleTickEvent()
{
    tickCounter++;

    if (tickCounter == 5)
    {
        moveTheClouds();
        tickCounter = 0;
    }
}

void HallwayScreenView::moveTheClouds()
{
    cloud_1.setXOffset((cloud_1.getXOffset() + 1) % cloud_1.getBitmap().getWidth());
    cloud_1.invalidate();
    cloud_2.setXOffset((cloud_2.getXOffset() + 1) % cloud_2.getBitmap().getWidth());
    cloud_2.invalidate();
}

int HallwayScreenView::calcDuration(int destinationX, int currentX)
{
    return abs(destinationX - currentX) / pixelsPrTick;
}
