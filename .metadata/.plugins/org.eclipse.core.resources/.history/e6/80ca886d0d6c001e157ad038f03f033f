#include <gui/bathroomscreen_screen/BathroomScreenView.hpp>
#include <gui/bathroomscreen_screen/BathroomScreenPresenter.hpp>

BathroomScreenPresenter::BathroomScreenPresenter(BathroomScreenView& v) :
    view(v)
{
}

void BathroomScreenPresenter::activate()
{
    model->setCurrentView(Model::Bathroom);
    model->setBathroomHomeUI(true);

    view.setBathtubWaterState(model->getBathtubOn());
    view.setBathtubUIState(model->getBathtubUIEntered());
    view.setWasherState(model->getWasherUIEntered());
    view.setHomeUIState(model->getBathroomUIEntered());
}

void BathroomScreenPresenter::deactivate()
{

}
