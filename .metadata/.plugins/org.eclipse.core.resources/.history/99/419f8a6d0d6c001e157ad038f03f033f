#include <gui/kitchenscreen_screen/KitchenScreenView.hpp>
#include <gui/common/Defines.hpp>
#include <touchgfx/Color.hpp>

KitchenScreenView::KitchenScreenView() :
    fadeButtonCallback(this, &KitchenScreenView::fadebuttonHandler),
    clickListnerImageCallback(this, &KitchenScreenView::clickListnerImageHandler),
    fadeCounter(0)
{

}

void KitchenScreenView::setupScreen()
{
    KitchenScreenViewBase::setupScreen();
    buttonExtractorHood.setFadeAnimationEndedAction(fadeButtonCallback);
    background.setClickAction(clickListnerImageCallback);
}

void KitchenScreenView::tearDownScreen()
{
    KitchenScreenViewBase::tearDownScreen();
}

void KitchenScreenView::setLightState(bool on)
{
    imageLight.setVisible(on);
}

void KitchenScreenView::setCookpotState(bool on)
{
    imageCookpot.setVisible(on);
}

void KitchenScreenView::setOvenState(bool on)
{
    imageOvenOn.setVisible(on);
}

void KitchenScreenView::setOvenUIState(bool on)
{
    imageOvenUI.setVisible(on);
}

void KitchenScreenView::setHoodUIState(bool on)
{
    imageHoodUI.setVisible(on);
}

void KitchenScreenView::setHomeUIState(bool on)
{
    imageHomeUI.setVisible(on);
}

void KitchenScreenView::startGlowAnimaton()
{
    buttonExtractorHood.startFadeAnimation(255, FADE_TICKS);
    buttonOven.startFadeAnimation(255, FADE_TICKS);
    buttonThermo.startFadeAnimation(255, FADE_TICKS);
}

void KitchenScreenView::fadebuttonHandler(const FadeAnimator<Button>& src)
{
    if (fadeCounter < FADE_COUNT)
    {
        if (buttonExtractorHood.getAlpha() == 255)
        {
            buttonExtractorHood.startFadeAnimation(0, FADE_TICKS);
            buttonOven.startFadeAnimation(0, FADE_TICKS);
            buttonThermo.startFadeAnimation(0, FADE_TICKS);
        }
        else
        {
            buttonExtractorHood.startFadeAnimation(255, FADE_TICKS);
            buttonOven.startFadeAnimation(255, FADE_TICKS);
            buttonThermo.startFadeAnimation(255, FADE_TICKS);
        }
        fadeCounter++;
    }
}

void KitchenScreenView::clickListnerImageHandler(const Image& img, const ClickEvent& evt)
{
    if (evt.getType() == ClickEvent::RELEASED)
    {
        // Starts the glow animation if it is not already running.
        if (!buttonExtractorHood.isFadeAnimationRunning())
        {
            startGlowAnimaton();
        }
        fadeCounter = 0;
    }
}
