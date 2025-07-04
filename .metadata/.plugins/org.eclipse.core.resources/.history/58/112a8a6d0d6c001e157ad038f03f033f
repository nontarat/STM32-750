#include <gui/extractorhoodscreen_screen/ExtractorHoodScreenView.hpp>
#include <gui/extractorhoodscreen_screen/ExtractorHoodScreenPresenter.hpp>

ExtractorHoodScreenPresenter::ExtractorHoodScreenPresenter(ExtractorHoodScreenView& v) :
    view(v)
{
}

void ExtractorHoodScreenPresenter::activate()
{
    model->setCurrentView(Model::ExtractorHood);
    model->setHoodEntered(true);

    view.setFanButtonState(getFanState());
    view.setLightButtonState(getShowLight());
}

void ExtractorHoodScreenPresenter::deactivate()
{

}

void ExtractorHoodScreenPresenter::setShowLight(bool show)
{
    model->setShowLight(show);
}

bool ExtractorHoodScreenPresenter::getShowLight()
{
    return model->getShowLight();
}

void ExtractorHoodScreenPresenter::setFanState(bool state)
{
    model->setFanState(state);
}

bool ExtractorHoodScreenPresenter::getFanState()
{
    return model->getFanState();
}
void ExtractorHoodScreenPresenter::setFanSpeed(uint16_t speed)
{
    model->setFanSpeed(speed);
}

uint16_t ExtractorHoodScreenPresenter::getFanSpeed()
{
    return model->getFanSpeed();
}
