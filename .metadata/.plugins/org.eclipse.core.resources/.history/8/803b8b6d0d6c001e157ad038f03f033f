#include <gui/recipescreen_screen/RecipeScreenView.hpp>
#include "BitmapDatabase.hpp"
#include <touchgfx/Color.hpp>

#include <gui/common/Defines.hpp>

RecipeScreenView::RecipeScreenView() :
    recipeSelectedCallback(this, &RecipeScreenView::recipeSelectedHandler),
    AnimationEndedCallback(this, &RecipeScreenView::AnimationEndedHandler)
{

}

void RecipeScreenView::setupScreen()
{
    RecipeScreenViewBase::setupScreen();
    scrollListRecipeSelector.setItemSelectedCallback(recipeSelectedCallback);
    scrollListRecipeSelector.setAnimationEndedCallback(AnimationEndedCallback);
}

void RecipeScreenView::tearDownScreen()
{
    RecipeScreenViewBase::tearDownScreen();
}

void RecipeScreenView::scrollListRecipeSelectorUpdateItem(RecipeListElement& item, int16_t itemIndex)
{
    item.updateItem(itemIndex);
}

void RecipeScreenView::recipeSelectedHandler(int16_t item)
{
    if (item == 0)
    {
        application().gotoRecipeSelectedScreenScreenCoverTransitionNorth();
    }
    else
    {
        scrollListRecipeSelector.animateToItem(0, item * 10);
        fadeTopRecipe = true;
    }
}

void RecipeScreenView::AnimationEndedHandler()
{
    if (fadeTopRecipe)
    {
        fadeTopRecipe = false;

        //The for loop runs through the visible items, starts a fade animation it finds item 0.
        for (int i = 0; i < scrollListRecipeSelectorListItems.getNumberOfDrawables(); i++)
        {
            if (scrollListRecipeSelector.getItem(i) == 0)
            {
                scrollListRecipeSelectorListItems[i].startFadeAnimation(RECIPE_FADE_END_ALPHA, RECIPE_FADE_DURATION);
                return;
            }
        }
    }
}

void RecipeScreenView::handleClickEvent(const ClickEvent& evt)
{
    //The for loop runs through the visible items, starts a fade animation it finds item 0.
    for (int i = 0; i < scrollListRecipeSelectorListItems.getNumberOfDrawables(); i++)
    {
        if (scrollListRecipeSelector.getItem(i) == 0)
        {
            if (scrollListRecipeSelectorListItems[i].isFadeAnimationRunning())
            {
                scrollListRecipeSelectorListItems[i].stopFadeAnimation();
            }
            break;
        }
    }
    RecipeScreenViewBase::handleClickEvent(evt);
}
