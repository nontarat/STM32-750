#include <gui/bathroomscreen_screen/BathroomScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <gui/common/Defines.hpp>

BathroomScreenView::BathroomScreenView() :
    fadeButtonCallback(this, &BathroomScreenView::fadebuttonHandler),
    clickListnerImageCallback(this, &BathroomScreenView::clickListnerImageHandler),
    fadeCounter(0)
{

}

void BathroomScreenView::setupScreen()
{
    BathroomScreenViewBase::setupScreen();

    buttonBathtub.setFadeAnimationEndedAction(fadeButtonCallback);
    background.setClickAction(clickListnerImageCallback);
}

void BathroomScreenView::tearDownScreen()
{
    BathroomScreenViewBase::tearDownScreen();
}

void BathroomScreenView::setBathtubWaterState(bool on)
{
    imageBathtubWater.setVisible(on);
}

void BathroomScreenView::setWasherState(bool on)
{
    imageWasherActive.setVisible(on);
    imageWasherUI.setVisible(on);
}

void BathroomScreenView::setBathtubUIState(bool on)
{
    imageBathtubUI.setVisible(on);
}

void BathroomScreenView::setHomeUIState(bool on)
{
    imageHomeUI.setVisible(on);
}

void BathroomScreenView::startGlowAnimaton()
{
    buttonWasher.startFadeAnimation(255, FADE_TICKS);
    buttonBathtub.startFadeAnimation(255, FADE_TICKS);
    buttonHomeControl.startFadeAnimation(255, FADE_TICKS);
}

void BathroomScreenView::fadebuttonHandler(const FadeAnimator<Button>& src)
{
    if (fadeCounter < FADE_COUNT)
    {
        if (buttonBathtub.getAlpha() == 255)
        {
            buttonBathtub.startFadeAnimation(0, FADE_TICKS);
            buttonWasher.startFadeAnimation(0, FADE_TICKS);
            buttonHomeControl.startFadeAnimation(0, FADE_TICKS);
        }
        else
        {
            buttonBathtub.startFadeAnimation(255, FADE_TICKS);
            buttonWasher.startFadeAnimation(255, FADE_TICKS);
            buttonHomeControl.startFadeAnimation(255, FADE_TICKS);
        }
        fadeCounter++;
    }
}

void BathroomScreenView::clickListnerImageHandler(const Image& img, const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::RELEASED)
    {
        // Starts the glow animation if it is not already running.
        if (!buttonBathtub.isFadeAnimationRunning())
        {
            startGlowAnimaton();
        }
        fadeCounter = 0;
    }
}
