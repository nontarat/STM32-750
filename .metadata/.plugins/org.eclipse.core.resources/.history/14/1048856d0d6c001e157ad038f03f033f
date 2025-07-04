#ifndef BATHROOMSCREEN_PRESENTER_HPP
#define BATHROOMSCREEN_PRESENTER_HPP

#include <gui/model/ModelListener.hpp>
#include <mvp/Presenter.hpp>

using namespace touchgfx;

class BathroomScreenView;

class BathroomScreenPresenter : public Presenter, public ModelListener
{
public:
    BathroomScreenPresenter(BathroomScreenView& v);

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

    virtual ~BathroomScreenPresenter() {};

    bool getBathtubOn()
    {
        return model->getBathtubOn();
    }

private:
    BathroomScreenPresenter();

    BathroomScreenView& view;
};


#endif // BATHROOMSCREEN_PRESENTER_HPP
