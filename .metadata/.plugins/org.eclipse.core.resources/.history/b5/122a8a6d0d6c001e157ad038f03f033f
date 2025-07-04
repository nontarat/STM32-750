#include <gui/extractorhoodscreen_screen/ExtractorHoodScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/hal/HAL.hpp>
#include <gui/common/Defines.hpp>

ExtractorHoodScreenView::ExtractorHoodScreenView() :
    fanKnobUpdateCallback(this, &ExtractorHoodScreenView::fanKnobUpdateHandler)
{

}

void ExtractorHoodScreenView::setupScreen()
{
    ExtractorHoodScreenViewBase::setupScreen();

    HAL::getInstance()->setFrameRateCompensation(false);

    //Sets up the texturemapper for the fan stop animation
    int borderWidth = 40;
    int borderHeight = 40;
    textureMapperFan.setBitmap(Bitmap(BITMAP_PROPEL_ID));
    int imageWidth = textureMapperFan.getBitmap().getWidth();
    int imageHeight = textureMapperFan.getBitmap().getHeight();
    textureMapperFan.setXY(143 - borderWidth, 7 - borderHeight);
    textureMapperFan.setWidth(imageWidth + borderWidth * 2);
    textureMapperFan.setHeight(imageHeight + borderHeight * 2);
    textureMapperFan.setBitmapPosition(borderWidth, borderHeight);
    textureMapperFan.setCameraDistance(300.0f);
    textureMapperFan.setOrigo(textureMapperFan.getBitmapPositionX() + 97, textureMapperFan.getBitmapPositionY() + 108, textureMapperFan.getCameraDistance());
    textureMapperFan.setCamera(textureMapperFan.getBitmapPositionX() + 97, textureMapperFan.getBitmapPositionY() + 108);
    textureMapperFan.setRenderingAlgorithm(TextureMapper::NEAREST_NEIGHBOR);

    // Adds the fan animation, to the screen.
    fanAnimation.setXY(FAN_ANIMATED_IMAGE_X, FAN_ANIMATED_IMAGE_Y);
    fanAnimation.setBitmaps(BITMAP_FRAMES_00000_ID, BITMAP_FRAMES_00009_ID);
    fanControlUpdate();
    add(fanAnimation);

    textureMapperFan.setVisible(false);
    gitter.setVisible(false);
    fanBg.setVisible(false);
    add(textureMapperFan);
    remove(gitter);
    add(gitter);

    fanKnob.setKnobUpdateAction(fanKnobUpdateCallback);
    fanKnob.setFanSpeed(presenter->getFanSpeed());

    // fanKnob is removed and added to ensure that it has the highest z-order.
    remove(fanKnob);
    add(fanKnob);
}

void ExtractorHoodScreenView::tearDownScreen()
{
    ExtractorHoodScreenViewBase::tearDownScreen();

    HAL::getInstance()->setFrameRateCompensation(false);
}

void ExtractorHoodScreenView::lightButtonClicked()
{
    if (flexButtonLight.getPressed())
    {
        imageLightBtn.startMoveAnimation(imageLightBtn.getX(), FAN_LIGHT_BUTTONS_ON_Y, FAN_LIGHT_BUTTONS_MOVE_DURATION, EasingEquations::circEaseOut, EasingEquations::circEaseOut);
        imageLightBtn.setBitmap(Bitmap(BITMAP_LIGHT_BUTTON_OFF_ID));
    }
    else
    {
        imageLightBtn.startMoveAnimation(imageLightBtn.getX(), FAN_LIGHT_BUTTONS_OFF_Y, FAN_LIGHT_BUTTONS_MOVE_DURATION, EasingEquations::circEaseOut, EasingEquations::circEaseOut);
        imageLightBtn.setBitmap(Bitmap(BITMAP_LIGHT_BUTTON_ON_ID));
    }

    presenter->setShowLight(flexButtonLight.getPressed());
}

void ExtractorHoodScreenView::fanButttonClicked()
{
    if (flexButtonFan.getPressed())
    {
        imageFanBtn.startMoveAnimation(imageFanBtn.getX(), FAN_LIGHT_BUTTONS_ON_Y, FAN_LIGHT_BUTTONS_MOVE_DURATION, EasingEquations::circEaseOut, EasingEquations::circEaseOut);
        imageFanBtn.setBitmap(Bitmap(BITMAP_FAN_BUTTON_OFF_ID));
    }
    else
    {
        imageFanBtn.startMoveAnimation(imageFanBtn.getX(), FAN_LIGHT_BUTTONS_OFF_Y, FAN_LIGHT_BUTTONS_MOVE_DURATION, EasingEquations::circEaseOut, EasingEquations::circEaseOut);
        imageFanBtn.setBitmap(Bitmap(BITMAP_FAN_BUTTON_ON_ID));
    }

    presenter->setFanState(flexButtonFan.getPressed());
    fanControlUpdate();
}

void ExtractorHoodScreenView::fanControlUpdate()
{
    if (presenter->getFanState())
    {
        switch (presenter->getFanSpeed())
        {
        case SPEED_1:
            fanAnimation.setUpdateTicksInterval(2);
            fanAnimation.setBitmapInterval(1);
            break;

        case SPEED_2:
            fanAnimation.setUpdateTicksInterval(2);
            fanAnimation.setBitmapInterval(2);
            break;

        case SPEED_3:
            fanAnimation.setUpdateTicksInterval(1);
            fanAnimation.setBitmapInterval(2);
            break;

        case SPEED_4:
            fanAnimation.setUpdateTicksInterval(1);
            fanAnimation.setBitmapInterval(3);
            break;

        case SPEED_5:
            fanAnimation.setUpdateTicksInterval(1);
            fanAnimation.setBitmapInterval(4);
            break;
        }

        if (!fanAnimation.isAnimatedImageRunning())
        {
            fanAnimation.startAnimation(false, true);

            fanBg.invalidate();
            fanAnimation.setVisible(true);

            textureMapperFan.setVisible(false);
            gitter.setVisible(false);
            fanBg.setVisible(false);
        }
    }
    else
    {
        if (fanAnimation.isAnimatedImageRunning())
        {
            fanAnimation.pauseAnimation();

            fanBg.invalidate();
            fanAnimation.setVisible(false);

            textureMapperFan.setVisible(true);
            gitter.setVisible(true);
            fanBg.setVisible(true);

            float cFan = (float)fanAnimation.getBitmap() - (float)Bitmap(BITMAP_FRAMES_00000_ID).getId();
            zAngle2D = cFan * 0.2F;
            textureMapperFan.updateAngles(0.0F, 0.0F, zAngle2D);

            beginningValue = 1;
            animationCounter = 0;
            targetValue = 200;

            switch (presenter->getFanSpeed())
            {
            case SPEED_1:
                scrollDuration = 10;
                targetValue = 25;
                break;

            case SPEED_2:
                scrollDuration = 25;
                targetValue = 50;
                break;

            case SPEED_3:
                scrollDuration = 40;
                targetValue = 75;
                break;

            case SPEED_4:
                scrollDuration = 60;
                targetValue = 100;
                break;

            case SPEED_5:
                scrollDuration = 75;
                targetValue = 150;
                break;
            }
            animate = true;
        }
    }
}

void ExtractorHoodScreenView::setFanButtonState(bool on)
{
    flexButtonFan.forceState(on);
    if (on)
    {
        imageFanBtn.setXY(imageFanBtn.getX(), FAN_LIGHT_BUTTONS_ON_Y);
        imageFanBtn.setBitmap(Bitmap(BITMAP_FAN_BUTTON_OFF_ID));
    }
    else
    {
        imageFanBtn.setXY(imageFanBtn.getX(), FAN_LIGHT_BUTTONS_OFF_Y);
        imageFanBtn.setBitmap(Bitmap(BITMAP_FAN_BUTTON_ON_ID));
    }
}

void ExtractorHoodScreenView::setLightButtonState(bool on)
{
    flexButtonLight.forceState(on);

    if (on)
    {
        imageLightBtn.setXY(imageLightBtn.getX(), FAN_LIGHT_BUTTONS_ON_Y);
        imageLightBtn.setBitmap(Bitmap(BITMAP_LIGHT_BUTTON_OFF_ID));
    }
    else
    {
        imageLightBtn.setXY(imageLightBtn.getX(), FAN_LIGHT_BUTTONS_OFF_Y);
        imageLightBtn.setBitmap(Bitmap(BITMAP_LIGHT_BUTTON_ON_ID));
    }
}

void ExtractorHoodScreenView::fanKnobUpdateHandler(uint16_t speed)
{
    presenter->setFanSpeed(speed);
    fanControlUpdate();
}

void ExtractorHoodScreenView::handleTickEvent()
{
    if (animate)
    {
        animationCounter++;
        if (animationCounter <= scrollDuration)
        {
            int16_t calculatedValue = EasingEquations::circEaseOut(animationCounter, beginningValue, targetValue, scrollDuration);
            zAngle2D += ((float)(targetValue - calculatedValue) / float(100));
            textureMapperFan.updateAngles(0.0F, 0.0F, zAngle2D);
        }
        else
        {
            animate = false;
        }
    }
}
