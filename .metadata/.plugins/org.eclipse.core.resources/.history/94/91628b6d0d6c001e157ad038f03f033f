#include <gui/washerscreen_screen/WasherScreenView.hpp>
#include <gui/washerscreen_screen/WasherScreenPresenter.hpp>

WasherScreenPresenter::WasherScreenPresenter(WasherScreenView& v) :
    view(v)
{
}

void WasherScreenPresenter::activate()
{
    model->setCurrentView(Model::Washer);
    model->setWasherUIEntered(true);
    view.setSelectedProgram(model->getWashingProgram());
}

void WasherScreenPresenter::deactivate()
{
    model->setWashingProgram(view.getSelectedProgram());
    model->setWashingTime(view.getWashingTime());
}
