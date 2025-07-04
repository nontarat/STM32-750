#ifndef BATHTUBSCREEN_VIEW_HPP
#define BATHTUBSCREEN_VIEW_HPP

#include <gui_generated/bathtubscreen_screen/BathtubScreenViewBase.hpp>
#include <gui/bathtubscreen_screen/BathtubScreenPresenter.hpp>

static const int NUMBER_OF_CIRCLES = 4;
static const int CIRCLE_ALPHA = 40;

class BathtubScreenView : public BathtubScreenViewBase
{
public:
    BathtubScreenView();
    virtual ~BathtubScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleClickEvent(const ClickEvent& evt);
    virtual void handleDragEvent(const DragEvent& evt);

    //Called from the scroll wheels each time a item is updated.
    virtual void scrollWheelTemperatureUpdateItem(BathtubWheelElement& item, int16_t itemIndex);
    virtual void scrollWheelTemperatureUpdateCenterItem(BathtubWheelElementCenter& item, int16_t itemIndex);
    virtual void scrollWheelJetSpeedUpdateItem(BathtubWheelElement& item, int16_t itemIndex);
    virtual void scrollWheelJetSpeedUpdateCenterItem(BathtubWheelElementCenter& item, int16_t itemIndex);

    // Virtual functions created with the designer.
    virtual void powerButtonClicked();
    virtual void lightButtonClicked();
    virtual void tempUnitButtonClicked();
    virtual void jetSpeedOnOffButtonClicked();

    // Creates light effects by adding multiple circles wiht low alpha on top of eachother in different sizes
    void setUpLightCircles();
    void fadeLightCircles(uint8_t endAlpha, uint16_t duration, EasingEquation equation, uint16_t delay);

protected:

    // The Callback registers when a radiobutton in the topbare is selected.
    void topbarButtonSelectedHandler(const AbstractButton& src);
    Callback<BathtubScreenView, const AbstractButton&> topbarButtonSelectedCallback;

    // The Callback registers when a radiobutton in the topbare is deselected.
    void topbarButtonDeselectedHandler(const AbstractButton& src);
    Callback<BathtubScreenView, const AbstractButton&> topbarButtonDeselectedCallback;

    // The Callback registers when a value is selected in the temperature wheel.
    void tempWheelItemSelectedHandler(int16_t item);
    Callback<BathtubScreenView, int16_t> tempWheelItemSelectedCallback;

    // The Callback registers when a value is selected in the jet speed wheel.
    void jetSpeedWheelItemSelectedHandler(int16_t item);
    Callback<BathtubScreenView, int16_t> jetSpeedWheelItemSelectedCallback;

    // Calcualtes the distance from the pressed position on the color to the center.
    uint32_t colorDistancesq(uint32_t x, uint32_t y);

    // Retrives the rgb from the color picker and updates the light circles with the rgb value.
    void selectColor(uint32_t x, uint32_t y);

    // Distances used for calculating the color selected in the color wheel.
    enum
    {
        MAX_RADIUS = 60,
        MAX_DIST = MAX_RADIUS * MAX_RADIUS
    };

    int32_t color_center_x, color_center_y; // Center of the color picker

    uint8_t r, g, b; // Holds the rgb values retrived from the color picker bitmap.

    bool isDown; // Used for informing handleDragEvent

    // Circles used for the light graffic
    FadeAnimator<Circle> ligthEffect1[NUMBER_OF_CIRCLES];
    FadeAnimator<Circle> ligthEffect2[NUMBER_OF_CIRCLES];
    FadeAnimator<Circle> ligthEffect3[NUMBER_OF_CIRCLES];
};

#endif // BATHTUBSCREEN_VIEW_HPP
