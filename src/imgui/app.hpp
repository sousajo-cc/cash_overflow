#ifndef CASH_OVERFLOW_APP_HPP
#define CASH_OVERFLOW_APP_HPP

#include "db.hpp"

#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

enum class DrawActions {
  LOGIN,
  CREATE_USER,
  MAIN_SCREEN
};

struct App
{
  using Db = cash_overflow::db::Db;
  App(Db db) : db_{ std::move(db) } {}
  Db db_;
  DrawActions draw = DrawActions::LOGIN;
  bool loggedIn = false;
  bool createUser = false;
  std::array<char, 24> user{};
  std::array<char, 24> password{};

  void drawMainScreen()
  {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Options")) {
        ImGui::MenuItem("Save");
        ImGui::MenuItem("Save as");
        if (ImGui::MenuItem("Logout")) {
          draw = DrawActions::LOGIN;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
  }

  void drawLoginScreen()
  {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Options")) {
        if (ImGui::MenuItem("Create User")) {
          draw = DrawActions::CREATE_USER;
        }
        ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    cash_overflow::gui::Window login{ "Login" };
    ImGui::InputText("User Name", user.data(), user.size());
    ImGui::InputText("Password", password.data(), password.size(), ImGuiInputTextFlags_Password);
    if (ImGui::Button("Login")) {
      if (db_.read(user.data())) {
        draw = DrawActions::MAIN_SCREEN;
      }
    }
  }

  void drawCreateUserScreen()
  {
    if (ImGui::BeginMainMenuBar()) {
      if (ImGui::BeginMenu("Options")) {
          ImGui::EndMenu();
      }
      ImGui::EndMainMenuBar();
    }
    [[maybe_unused]] cash_overflow::gui::Window addCategory{ "Create User" };
    ImGui::InputText("User Name", user.data(), user.size());
    ImGui::InputText("Password", password.data(), password.size(), ImGuiInputTextFlags_Password);
    if (ImGui::Button("Create")) {
      if (db_.create(user.data(), password.data())) {
        std::fill(std::begin(password), std::end(password), 0);
        draw = DrawActions::LOGIN;
      }
    }
  }

  void start()
  {
    switch (draw) {
    case (DrawActions::LOGIN):
      drawLoginScreen();
      break;
    case (DrawActions::MAIN_SCREEN):
      drawMainScreen();
      break;
    case (DrawActions::CREATE_USER):
      drawCreateUserScreen();
      break;
    default:
      drawLoginScreen();
    }
  }
};

#endif//CASH_OVERFLOW_APP_HPP
