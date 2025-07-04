#ifndef MODEL_HPP
#define MODEL_HPP

#include <touchgfx/Utils.hpp>
#include <stdint.h>


class ModelListener;

/**
 * The Model class defines the data model in the model-view-presenter paradigm.
 * The Model is a singular object used across all presenters. The currently active
 * presenter will have a pointer to the Model through deriving from ModelListener.
 *
 * The Model will typically contain UI state information that must be kept alive
 * through screen transitions. It also usually provides the interface to the rest
 * of the system (the backend). As such, the Model can receive events and data from
 * the backend and inform the current presenter of such events through the modelListener
 * pointer, which is automatically configured to point to the current presenter.
 * Conversely, the current presenter can trigger events in the backend through the Model.
 */

#define AUTO_DEMO_SCALER    10
#define AUTO_DEMO_TIMEOUT   1000

class Model
{
public:
    Model();

    /**
     * Sets the modelListener to point to the currently active presenter. Called automatically
     * when switching screen.
     */
    void bind(ModelListener* listener)
    {
        modelListener = listener;
    }


    // The enum keeps track of which view there is active
    enum Views
    {
        Hallway,
        Kitchen,
        Bathroom,
        ExtractorHood,
        Oven,
        HomeUI,
        RecipeSelector,
        Recipe,
        Washer,
        Bathtub,
        About
    } currentView;

    /**
     * This function will be called automatically every frame. Can be used to e.g. sample hardware
     * peripherals or read events from the surrounding system and inject events to the GUI through
     * the ModelListener interface.
     */
    void tick();

    /* Function to handle the states of the kitchen elements*/
    void setShowLight(bool show);
    bool getShowLight();
    void setShowPot(bool show);
    bool getShowPot();
    void setShowOven(bool show);
    bool getShowOven();
    void setFanState(bool state);
    bool getFanState();
    void setFanSpeed(uint16_t speed);
    uint16_t getFanSpeed();

    void setSelectedOvenMode(uint16_t mode);
    uint16_t getSelectedOvenMode();
    void setOvenTimerHour(int16_t hour);
    int16_t getOvenTimerHour();
    void setOvenTimerMinute(int16_t minute);
    int16_t getOvenTimerMinute();
    void setOvenTemperature(uint16_t temp);
    uint16_t getOvenTemperature();

    /*get/set bathroom*/
    void setBathtubOn(bool on);
    bool getBathtubOn();
    void setTempCelcius(bool celcius);
    bool getTempCelcius();
    void setJetOn(bool on);
    bool getJetOn();
    void setLightOn(bool on);
    bool getLightOn();

    void setTempValue(uint16_t temp);
    uint16_t getTempValue();
    void setJetLevel(uint16_t level);
    uint16_t getJetLevel();
    void setColorCoordinates(uint32_t x, uint32_t y);
    void getColorCoordinates(uint32_t& x, uint32_t& y);

    void setWashingProgram(uint16_t program);
    uint16_t getWashingProgram();
    void setWashingTime(uint16_t time);
    uint16_t getWashingTime();

    void setBathroomHomeUI(bool bathroom);
    bool getBathroomHomeUI();

    void setHoodEntered(bool entered);
    bool getHoodEntered();
    void setOvenEntered(bool entered);
    bool getOvenEntered();
    void setKitchenUIEntered(bool entered);
    bool getKitchenUIEntered();

    void setBathtubUIEntered(bool entered);
    bool getBathtubUIEntered();
    void setBathroomUIEntered(bool entered);
    bool getBathroomUIEntered();
    void setWasherUIEntered(bool entered);
    bool getWasherUIEntered();

    void setFromRecipeScreen(bool recipeScreen);
    bool getFromRecipeScreen();

    void setCurrentView(Views view);
protected:

    /**
     * Pointer to the currently active presenter.
     */
    ModelListener* modelListener;

    /* Varibles to handle the states of the kitchen elements*/
    bool showLight;
    bool showPot;
    bool showOven;
    bool hoodUIEntered;
    bool ovenUIEntered;
    bool kitchenUIEntered;

    bool fanState;
    uint16_t fanSpeed;

    uint16_t selectedOvenMode;
    int16_t ovenTimerHour;
    int16_t ovenTimerMinute;
    uint16_t ovenTemperature;

    /* Varibles to handle the states of the bathroom elements*/
    bool washerUIEntered;
    bool bathtubUIEntered;
    bool bathroomUIEntered;

    bool bathtubOn;
    bool tempCelcius;
    bool jetOn;
    bool lightOn;

    uint16_t tempValue;
    uint16_t jetLevel;
    uint32_t colorCoordinateX;
    uint32_t colorCoordinateY;

    uint16_t currentProgram;
    uint16_t washingTime;

    bool bathroomHomeUI;
    bool fromRecipeScreen;
};

#endif /* MODEL_HPP */
