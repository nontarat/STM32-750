#include <gui/recipescreen_screen/RecipeScreenView.hpp>
#include <gui/recipescreen_screen/RecipeScreenPresenter.hpp>

RecipeScreenPresenter::RecipeScreenPresenter(RecipeScreenView& v) :
    view(v)
{
}

void RecipeScreenPresenter::activate()
{
    model->setCurrentView(Model::RecipeSelector);
}

void RecipeScreenPresenter::deactivate()
{
    model->setFromRecipeScreen(true);
}
