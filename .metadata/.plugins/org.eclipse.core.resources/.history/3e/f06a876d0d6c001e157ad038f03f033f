#ifndef HALLWAYSCREEN_VIEW_HPP
#define HALLWAYSCREEN_VIEW_HPP

#include <gui_generated/hallwayscreen_screen/HallwayScreenViewBase.hpp>
#include <gui/hallwayscreen_screen/HallwayScreenPresenter.hpp>

class HallwayScreenView : public HallwayScreenViewBase
{
public:
    HallwayScreenView();
    virtual ~HallwayScreenView() {}
    virtual void setupScreen();
    virtual void tearDownScreen();

    virtual void handleTickEvent();

protected:
    // The callback registers when a move animaiton for bathroom- and kitchenbutton is done.
    Callback<HallwayScreenView, const MoveAnimator<Button>&> buttonMoveCallback;
    void buttonMoveHandler(const MoveAnimator<Button>& src);

    // The callback registers when a fade animaiton for bathroom- and kitchenbutton is done.
    Callback<HallwayScreenView, const FadeAnimator< MoveAnimator<Button> >&> buttonFadeCallback;
    void buttonFadeHandler(const FadeAnimator< MoveAnimator<Button> >& src);

    void moveTheClouds();
    int calcDuration(int destinationX, int currentX);

    int tickCounter;
    float pixelsPrTick;
};

#endif // HALLWAYSCREEN_VIEW_HPP
