#include <gui/kitchenscreen_screen/KitchenScreenView.hpp>
#include <gui/kitchenscreen_screen/KitchenScreenPresenter.hpp>

KitchenScreenPresenter::KitchenScreenPresenter(KitchenScreenView& v) :
    view(v)
{
}

void KitchenScreenPresenter::activate()
{
    model->setCurrentView(Model::Kitchen);
    model->setBathroomHomeUI(false);
    view.setLightState(model->getShowLight());
    view.setCookpotState(model->getShowPot());
    view.setOvenState(model->getShowOven());
    view.setOvenUIState(model->getOvenEntered());
    view.setHoodUIState(model->getHoodEntered());
    view.setHomeUIState(model->getKitchenUIEntered());
}

void KitchenScreenPresenter::deactivate()
{

}
