#include <gui/recipeselectedscreen_screen/RecipeSelectedScreenView.hpp>
#include <gui/recipeselectedscreen_screen/RecipeSelectedScreenPresenter.hpp>

RecipeSelectedScreenPresenter::RecipeSelectedScreenPresenter(RecipeSelectedScreenView& v)
    : view(v)
{
}

void RecipeSelectedScreenPresenter::activate()
{
    model->setCurrentView(Model::Recipe);
    model->setShowPot(true);
}

void RecipeSelectedScreenPresenter::deactivate()
{

}
