#ifndef RECIPESELECTEDSCREEN_PRESENTER_HPP
#define RECIPESELECTEDSCREEN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class RecipeSelectedScreenView;

class RecipeSelectedScreenPresenter : public Presenter, public ModelListener
{
public:
    RecipeSelectedScreenPresenter(RecipeSelectedScreenView& v);

    /**
     * The activate function is called automatically when this screen is "switched in"
     * (ie. made active). Initialization logic can be placed here.
     */
    virtual void activate();

    /**
     * The deactivate function is called automatically when this screen is "switched out"
     * (ie. made inactive). Teardown functionality can be placed here.
     */
    virtual void deactivate();

    virtual ~RecipeSelectedScreenPresenter() {};
private:
    RecipeSelectedScreenPresenter();

    RecipeSelectedScreenView& view;
};


#endif // RECIPESELECTEDSCREEN_PRESENTER_HPP
