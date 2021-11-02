#pragma once

/*-------------------------------------- 1st APPROACH --------------------------------------*/
/* Easy to understand, however I don't like it very much... 
    Create a class for each ImGui object we may need.
    This needs a lot of improvement, it's mainly a POC. */
#include <imgui.h>

/* This is a base class creation, that should fit for all
    imgui objects.
    TODO: Some end functions require to check the selected var.
            This must be added later.
*/
#define TEMPLATED_CLASS(NAME, BEGIN, END, ...) class NAME { \
    public: \
    explicit NAME() : selected{ BEGIN(__VA_ARGS__) } {} \
    ~NAME() { END(); } \
    NAME(NAME const&) = delete; \
    NAME& operator=(NAME const&) = delete; \
    NAME(NAME&&) = delete; \
    NAME& operator=(NAME&&) = delete; \
    explicit operator bool() const { return selected; } \
    private: \
    bool selected; \
};

#define RAII_MAIN_MENU(...) TEMPLATED_CLASS(MainMenuBar, ImGui::BeginMainMenuBar, ImGui::EndMenuBar, __VA_ARGS__)

#define Main_Menu(...) RAII_MAIN_MENU(__VA_ARGS__); if(MainMenuBar M{}) // this can be done in the code also
/*-------------------------------------- END 1st APPROACH --------------------------------------*/

/*-------------------------------------- 2nd APPROACH --------------------------------------*/



