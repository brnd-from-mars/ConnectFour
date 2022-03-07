#include "AppDelegate.hpp"



int main()
{
    auto ad = AppDelegate::Get();

    ad->SetWindow(800, 600, "Four Wins!");

    while (ad->Update())
    {
    }

    ad->Delete();

    return 0;
}
