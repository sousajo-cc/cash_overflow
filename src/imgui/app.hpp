#ifndef CASH_OVERFLOW_APP_HPP
#define CASH_OVERFLOW_APP_HPP

#include "db.hpp"
#include "imguiWrapper/mainMenuBar.hpp"
#include "imguiWrapper/menu.hpp"

#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

enum class DrawActions {
  Login,
  CreateUser,
  MainScreen
};

struct App
{
  using Db = cash_overflow::db::Db;
  App(Db db) : db_{ std::move(db) } {}
  Db db_;
  DrawActions draw = DrawActions::Login;
  bool loggedIn = false;
  bool createUser = false;
  std::array<char, 24> user{};
  std::array<char, 24> password{};

  void drawMainScreen()
  {
    if (cash_overflow::gui::MainMenuBar menuBar{}) {
      if (ImGui::BeginMenu("Options")) {
        ImGui::MenuItem("Save");
        ImGui::MenuItem("Save as");
        if (ImGui::MenuItem("Logout")) {
          draw = DrawActions::Login;
        }
        ImGui::EndMenu();
      }
    }
  }

  void drawLoginScreen()
  {
    if (cash_overflow::gui::MainMenuBar menuBar{}) {
      if (cash_overflow::gui::Menu menu{ "Options" }) {
        if (ImGui::MenuItem("Create User")) {
          draw = DrawActions::CreateUser;
        }
      }
    }
    cash_overflow::gui::Window login{ "Login" };
    ImGui::InputText("User Name", user.data(), user.size());
    ImGui::InputText("Password", password.data(), password.size(), ImGuiInputTextFlags_Password);
    if (ImGui::Button("Login")) {
      if (db_.read(user.data())) {
        draw = DrawActions::MainScreen;
      }
    }
  }

  void drawCreateUserScreen()
  {
    if (cash_overflow::gui::MainMenuBar menuBar{}) {
      if (cash_overflow::gui::Menu menu{ "Options" }) {
      }
    }
    cash_overflow::gui::Window addCategory{ "Create User" };
    ImGui::InputText("User Name", user.data(), user.size());
    ImGui::InputText("Password", password.data(), password.size(), ImGuiInputTextFlags_Password);
    if (ImGui::Button("Create")) {
      if (db_.create(user.data(), password.data())) {
        std::fill(std::begin(password), std::end(password), 0);
        draw = DrawActions::Login;
      }
    }
  }

  void start()
  {
    switch (draw) {
    case (DrawActions::Login):
      drawLoginScreen();
      break;
    case (DrawActions::MainScreen):
      drawMainScreen();
      break;
    case (DrawActions::CreateUser):
      drawCreateUserScreen();
      break;
    default:
      drawLoginScreen();
    }
  }
};

#endif// CASH_OVERFLOW_APP_HPP
