#include <gui/bathtubscreen_screen/BathtubScreenView.hpp>
#include <BitmapDatabase.hpp>
#include <touchgfx/Color.hpp>
#include <touchgfx/transforms/DisplayTransformation.hpp>
#include <math.h>
#include <gui/common/Defines.hpp>

BathtubScreenView::BathtubScreenView() :
    topbarButtonSelectedCallback(this, &BathtubScreenView::topbarButtonSelectedHandler),
    topbarButtonDeselectedCallback(this, &BathtubScreenView::topbarButtonDeselectedHandler),
    tempWheelItemSelectedCallback(this, &BathtubScreenView::tempWheelItemSelectedHandler),
    jetSpeedWheelItemSelectedCallback(this, &BathtubScreenView::jetSpeedWheelItemSelectedHandler),
    isDown(false)
{

}

void BathtubScreenView::setupScreen()
{
    BathtubScreenViewBase::setupScreen();

    radioButtonGroup.setDeselectionEnabled(true);
    radioButtonGroup.setRadioButtonSelectedHandler(topbarButtonSelectedCallback);
    radioButtonGroup.setRadioButtonDeselectedHandler(topbarButtonDeselectedCallback);

    scrollWheelTemperature.setItemSelectedCallback(tempWheelItemSelectedCallback);
    scrollWheelJetSpeed.setItemSelectedCallback(jetSpeedWheelItemSelectedCallback);

    setUpLightCircles();

    //If the the bathub os on the water and the topbar is moved into visible positions
    if (presenter->getBathtubOn())
    {
        imageWater.setY(WATER_ON);
        topBarButtonsContainer.setY(TOPBAR_ON);
    }

    // Sets if the toogle button is on C° or F° based on the saved state
    // And animates the stored temp value
    if (presenter->getTempCelcius())
    {
        toggleButtonTempUnit.forceState(true);
        scrollWheelTemperature.setNumberOfItems(TEMPERATURE_C_MAX - TEMPERATURE_C_MIN + 1);
        scrollWheelTemperature.stopAnimation();
        scrollWheelTemperature.animateToItem(presenter->getTempValue(), 0);
    }
    else
    {
        toggleButtonTempUnit.forceState(false);
        scrollWheelTemperature.setNumberOfItems(TEMPERATURE_F_MAX - TEMPERATURE_F_MIN + 1);
        scrollWheelTemperature.stopAnimation();
        scrollWheelTemperature.animateToItem(presenter->getTempValue(), 0);
    }

    if (presenter->getLightOn())
    {
        toggleButtonLight.forceState(true);
        if (presenter->getBathtubOn())
        {
            fadeLightCircles(CIRCLE_ALPHA, 0, EasingEquations::linearEaseNone, 0);
        }
    }

    // Calculates the center of the color picker.
    color_center_x = imageColorWheel.getX() + imageColorWheel.getWidth() / 2;
    color_center_y = imageColorWheel.getY() + imageColorWheel.getHeight() / 2 + 25; // + 25 is to compensate for part of the color picker bitmap that is not a color picker

    //Updates the picker position on the color picker base on the stored coordinates.
    uint32_t x, y;
    presenter->getColorCoordinates(x, y);
    selectColor(x, y);

    // Sets if the state of the toogle button based on the saved state
    // and animates the stored temp value
    if (presenter->getJetOn())
    {
        toggleButtonJetSpeed.forceState(true);
    }
    else
    {
        toggleButtonJetSpeed.forceState(false);
    }
    scrollWheelJetSpeed.stopAnimation();
    scrollWheelJetSpeed.animateToItem(presenter->getJetLevel(), 0);
}

void BathtubScreenView::tearDownScreen()
{
    BathtubScreenViewBase::tearDownScreen();
}

void BathtubScreenView::handleClickEvent(const ClickEvent& evt)
{
    if (containerLightColor.getRect().intersect(Rect(evt.getX(), evt.getY(), 1, 1)))
    {
        int offsetX = evt.getX() - containerLightColor.getX();
        int offsetY = evt.getY() - containerLightColor.getY();

        if (evt.getType() == ClickEvent::PRESSED)
        {
            const uint32_t dist = colorDistancesq(offsetX, offsetY);
            if (dist < MAX_DIST)
            {
                selectColor(offsetX, offsetY);
                isDown = true;
            }
        }
    }
    if (evt.getType() == ClickEvent::RELEASED)
    {
        isDown = false;
    }
    BathtubScreenViewBase::handleClickEvent(evt);
}

void BathtubScreenView::handleDragEvent(const DragEvent& evt)
{
    if (isDown)
    {
        int offsetX = evt.getNewX() - containerLightColor.getX();
        int offsetY = evt.getNewY() - containerLightColor.getY();

        const uint32_t dist = colorDistancesq(offsetX, offsetY);
        if (dist < MAX_DIST)
        {
            selectColor(offsetX, offsetY);
        }
        else
        {
            //calculate rim
            float angle = float(atan2(float(offsetY - color_center_y), float(offsetX - color_center_x)));
            selectColor(uint32_t(MAX_RADIUS * cosf(angle) + color_center_x), uint32_t(MAX_RADIUS * sinf(angle) + color_center_y));
        }
    }
    BathtubScreenViewBase::handleDragEvent(evt);
}

uint32_t BathtubScreenView::colorDistancesq(uint32_t x, uint32_t y)
{
    const int32_t dx = (x - color_center_x);
    const int32_t dy = (y - color_center_y);
    return dx * dx + dy * dy;
}

void BathtubScreenView::selectColor(uint32_t x, uint32_t y)
{
    presenter->setColorCoordinates(x, y);
    imagePicker.moveTo(x - imagePicker.getWidth() / 2, y - imagePicker.getHeight() / 2);

    const Bitmap bitmapColors = Bitmap(BITMAP_LIGHTCOLOR_BG_ID);
    const uint8_t* pixels = (const uint8_t*)bitmapColors.getData();
    int16_t _x = (int16_t)x;
    int16_t _y = (int16_t)y;

    _x -= imageColorWheel.getX();
    _y -= imageColorWheel.getY();

    pixels += (_x + _y * bitmapColors.getWidth()) * 4;

    b = *pixels++;
    g = *pixels++;
    r = *pixels++;

    circleLight1Painter.setColor(Color::getColorFromRGB(r, g, b));
    circleLight2Painter.setColor(Color::getColorFromRGB(r, g, b));
    circleLight3Painter.setColor(Color::getColorFromRGB(r, g, b));
    containerCircleLight.invalidate();
}

// When a radio button is selected, the corresponding wheel is moved into view.
// If another wheel is visible, that wheel moves out of view first.
void BathtubScreenView::topbarButtonSelectedHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &radioButtonTemperature)
    {
        if (containerLightColor.isMoveAnimationRunning() || containerJetControl.isMoveAnimationRunning())
        {
            containerTempWheel.setMoveAnimationDelay(WHEEL_DURATION + 10);
        }
        else
        {
            containerTempWheel.setMoveAnimationDelay(0);
        }
        containerTempWheel.startMoveAnimation(WHEEL_ON, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
    else if (&src == &radioButtonLight)
    {
        if (containerTempWheel.isMoveAnimationRunning() || containerJetControl.isMoveAnimationRunning())
        {
            containerLightColor.setMoveAnimationDelay(WHEEL_DURATION + 10);
        }
        else
        {
            containerLightColor.setMoveAnimationDelay(0);
        }
        containerLightColor.startMoveAnimation(WHEEL_ON, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
    else if (&src == &radioButtonJets)
    {
        if (containerTempWheel.isMoveAnimationRunning() || containerLightColor.isMoveAnimationRunning())
        {
            containerJetControl.setMoveAnimationDelay(WHEEL_DURATION + 10);
        }
        else
        {
            containerJetControl.setMoveAnimationDelay(0);
        }
        containerJetControl.startMoveAnimation(WHEEL_ON, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
}

// When a radio button is deselected, the corresponding wheel
void BathtubScreenView::topbarButtonDeselectedHandler(const touchgfx::AbstractButton& src)
{
    if (&src == &radioButtonTemperature)
    {
        containerTempWheel.setMoveAnimationDelay(0);
        containerTempWheel.startMoveAnimation(WHEEL_OFF, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
    else if (&src == &radioButtonLight)
    {
        containerLightColor.setMoveAnimationDelay(0);
        containerLightColor.startMoveAnimation(WHEEL_OFF, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
    else if (&src == &radioButtonJets)
    {
        containerJetControl.setMoveAnimationDelay(0);
        containerJetControl.startMoveAnimation(WHEEL_OFF, containerTempWheel.getY(), WHEEL_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
    }
}

void BathtubScreenView::tempUnitButtonClicked()
{
    if (toggleButtonTempUnit.getState())
    {
        presenter->setTempCelcius(true);
        int setTemp = presenter->getTempValue();
        setTemp = (setTemp > TEMPERATURE_C_MAX - TEMPERATURE_C_MIN + 1) ? TEMPERATURE_C_MAX - TEMPERATURE_C_MIN + 1 : setTemp;
        scrollWheelTemperature.setNumberOfItems(TEMPERATURE_C_MAX - TEMPERATURE_C_MIN + 1);
        scrollWheelTemperature.stopAnimation();
        scrollWheelTemperature.animateToItem(setTemp, 0);
    }
    else
    {
        presenter->setTempCelcius(false);
        scrollWheelTemperature.setNumberOfItems(TEMPERATURE_F_MAX - TEMPERATURE_F_MIN + 1);
        scrollWheelTemperature.stopAnimation();
        scrollWheelTemperature.animateToItem(presenter->getTempValue(), 0);
    }
}

void BathtubScreenView::lightButtonClicked()
{
    if (toggleButtonLight.getState())
    {
        //if the lights is turned on, the lightCircles are fadded in
        fadeLightCircles(CIRCLE_ALPHA, 30, EasingEquations::cubicEaseIn, 0);
        presenter->setLightOn(true);
    }
    else
    {
        //if the lights is turned off, the lightCircles are fadded out
        fadeLightCircles(0, 30, EasingEquations::cubicEaseIn, 0);
        presenter->setLightOn(false);
    }
}

void BathtubScreenView::jetSpeedOnOffButtonClicked()
{
    if (toggleButtonJetSpeed.getState())
    {
        presenter->setJetOn(true);
    }
    else
    {
        presenter->setJetOn(false);
    }
}

void BathtubScreenView::tempWheelItemSelectedHandler(int16_t item)
{
    presenter->setTempValue(item);
}

void BathtubScreenView::jetSpeedWheelItemSelectedHandler(int16_t item)
{
    presenter->setJetLevel(item);
}

void BathtubScreenView::powerButtonClicked()
{
    if (!presenter->getBathtubOn())
    {
        presenter->setBathtubOn(true);
        imageWater.setMoveAnimationDelay(0);
        imageWater.startMoveAnimation(imageWater.getX(), WATER_ON, WATER_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);
        topBarButtonsContainer.setMoveAnimationDelay(WATER_DURATION / 2);
        topBarButtonsContainer.startMoveAnimation(topBarButtonsContainer.getX(), TOPBAR_ON, TOPBAR_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseOut);

        if (presenter->getLightOn())
        {
            fadeLightCircles(CIRCLE_ALPHA, 30, EasingEquations::cubicEaseIn, 30);
        }
    }
    else
    {
        presenter->setBathtubOn(false);
        topBarButtonsContainer.setMoveAnimationDelay(0);
        topBarButtonsContainer.startMoveAnimation(topBarButtonsContainer.getX(), TOPBAR_OFF, TOPBAR_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseIn);
        imageWater.setMoveAnimationDelay(TOPBAR_DURATION / 2);
        imageWater.startMoveAnimation(imageWater.getX(), WATER_OFF, WATER_DURATION, EasingEquations::linearEaseNone, EasingEquations::cubicEaseIn);

        if (radioButtonTemperature.getSelected())
        {
            radioButtonTemperature.setSelected(false);
        }
        else if (radioButtonJets.getSelected())
        {
            radioButtonJets.setSelected(false);
        }
        else if (radioButtonLight.getSelected())
        {
            radioButtonLight.setSelected(false);
        }

        if (presenter->getLightOn())
        {
            fadeLightCircles(0, 30, EasingEquations::cubicEaseIn, 0);
        }
    }
}

void BathtubScreenView::scrollWheelTemperatureUpdateItem(BathtubWheelElement& item, int16_t itemIndex)
{
    item.setTemp(itemIndex, presenter->getTempCelcius());
}

void BathtubScreenView::scrollWheelTemperatureUpdateCenterItem(BathtubWheelElementCenter& item, int16_t itemIndex)
{
    item.setTemp(itemIndex, presenter->getTempCelcius());
}

void BathtubScreenView::scrollWheelJetSpeedUpdateItem(BathtubWheelElement& item, int16_t itemIndex)
{
    item.setJetspeed(itemIndex);
}

void BathtubScreenView::scrollWheelJetSpeedUpdateCenterItem(BathtubWheelElementCenter& item, int16_t itemIndex)
{
    item.setJetspeed(itemIndex);
}

void BathtubScreenView::setUpLightCircles()
{
    int i = 0;
    int x, y, r;

    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect1[i].setPosition(circleLight1.getX() + i, circleLight1.getY() + i, circleLight1.getWidth() - 2 * i, circleLight1.getHeight() - 2 * i);
        circleLight1.getCenter(x, y);
        ligthEffect1[i].setCenter(x - i, y - i);
        circleLight1.getRadius(r);
        ligthEffect1[i].setRadius(r - i);
        ligthEffect1[i].setLineWidth(0);
        ligthEffect1[i].setArc(0, 360);
        ligthEffect1[i].setPainter(circleLight1Painter);
        ligthEffect1[i].setAlpha(circleLight1.getAlpha());
        containerCircleLight.add(ligthEffect1[i]);
    }

    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect2[i].setPosition(circleLight2.getX() + i, circleLight2.getY() + i, circleLight2.getWidth() - 2 * i, circleLight2.getHeight() - 2 * i);
        circleLight2.getCenter(x, y);
        ligthEffect2[i].setCenter(x - i, y - i);
        circleLight2.getRadius(r);
        ligthEffect2[i].setRadius(r - i);
        ligthEffect2[i].setLineWidth(0);
        ligthEffect2[i].setArc(0, 360);
        ligthEffect2[i].setPainter(circleLight2Painter);
        ligthEffect2[i].setAlpha(circleLight2.getAlpha());
        containerCircleLight.add(ligthEffect2[i]);
    }

    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect3[i].setPosition(circleLight3.getX() + i, circleLight3.getY() + i, circleLight3.getWidth() - 2 * i, circleLight3.getHeight() - 2 * i);
        circleLight3.getCenter(x, y);
        ligthEffect3[i].setCenter(x - i, y - i);
        circleLight3.getRadius(r);
        ligthEffect3[i].setRadius(r - i);
        ligthEffect3[i].setLineWidth(0);
        ligthEffect3[i].setArc(0, 360);
        ligthEffect3[i].setPainter(circleLight3Painter);
        ligthEffect3[i].setAlpha(circleLight3.getAlpha());
        containerCircleLight.add(ligthEffect3[i]);
    }
}

void BathtubScreenView::fadeLightCircles(uint8_t endAlpha, uint16_t duration, EasingEquation equation, uint16_t delay)
{
    int i = 0;

    circleLight1.setFadeAnimationDelay(delay);
    circleLight1.startFadeAnimation(endAlpha, duration, equation);
    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect1[i].setFadeAnimationDelay(delay);
        ligthEffect1[i].startFadeAnimation(endAlpha, duration, equation);
    }
    circleLight2.setFadeAnimationDelay(delay);
    circleLight2.startFadeAnimation(endAlpha, duration, equation);
    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect2[i].setFadeAnimationDelay(delay);
        ligthEffect2[i].startFadeAnimation(endAlpha, duration, equation);
    }

    circleLight3.setFadeAnimationDelay(delay);
    circleLight3.startFadeAnimation(endAlpha, duration, equation);
    for (i = 0; i < NUMBER_OF_CIRCLES; i++)
    {
        ligthEffect3[i].setFadeAnimationDelay(delay);
        ligthEffect3[i].startFadeAnimation(endAlpha, duration, equation);
    }
}
