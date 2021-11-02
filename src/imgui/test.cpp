#include "raii_imgui.hpp"
#include <imgui-SFML.h>

#include <SFML/Graphics/RenderWindow.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/Window/Event.hpp>
#include <SFML/Graphics/CircleShape.hpp>

int main()
{
  sf::RenderWindow window(sf::VideoMode(640, 480), "Cash Overflow");
  window.setFramerateLimit(60);
  ImGui::SFML::Init(window);

  sf::CircleShape shape{100.F};
  shape.setFillColor(sf::Color::Cyan);
  shape.setPosition(sf::Vector2f{500.0, 350.0});

  const ImVec4 Red{.7F, .0F, .0F, 1.0F};
  const ImVec4 Green{.0F, .8F, .0F, 1.0F};

  sf::Clock deltaClock;
  while (window.isOpen()) {
    sf::Event event;
    while (window.pollEvent(event)) {
      ImGui::SFML::ProcessEvent(event);

      if (event.type == sf::Event::Closed) {
        window.close();
      }
    }

  bool popup = false;
  ImGui::SFML::Update(window, deltaClock.restart());
  Main_Menu() {
    if (ImGui::BeginMenu("Options")) {
      if(ImGui::MenuItem("Load")) {
        popup = true;
      }
      ImGui::MenuItem("Save");
      ImGui::MenuItem("Save as");
      ImGui::EndMenu();
    }
  }

  if (popup) 
    ImGui::OpenPopup("Popup");

  if (ImGui::BeginPopup("Popup"))
  {
    ImGui::Text("Hello World");
    ImGui::EndPopup();
  }

    ImGui::Begin("Mockup");
    ImGui::BeginTabBar("TabBar");
    if (ImGui::BeginTabItem("Accounts & Categories")) {
      if (ImGui::BeginTable("Table", 4)) {
        ImGui::TableSetupColumn("Account/Category");
        ImGui::TableSetupColumn("Remaining Budget");
        ImGui::TableSetupColumn("Change");
        ImGui::TableSetupColumn("Total");
        ImGui::TableHeadersRow();
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Assets");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$-778.32");
        ImGui::TableNextColumn();
        ImGui::Text("$29,754.72");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Cash");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$-2.85");
        ImGui::TableNextColumn();
        ImGui::Text("$236.30");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Checking Account");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$-634.99");
        ImGui::TableNextColumn();
        ImGui::Text("$7,327.01");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Euro Account");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "-120.00 EUR");
        ImGui::TableNextColumn();
        ImGui::Text("5,403.00 EUR");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Investment Account");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::Text("0 CNY");
        ImGui::TableNextColumn();
        ImGui::Text("20,400.00 CNY");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Savings Account");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::Text("$0.00");
        ImGui::TableNextColumn();
        ImGui::Text("$12,800.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Liabilities");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Green, "$-200.00");
        ImGui::TableNextColumn();
        ImGui::Text("$11,400.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Car Loan");
        ImGui::TableNextColumn();
        ImGui::TableNextColumn();
        ImGui::TextColored(Green, "$-200.00");
        ImGui::TableNextColumn();
        ImGui::Text("$11,400.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Incomes");
        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::Text("$0.00");
        ImGui::TableNextColumn();
        ImGui::Text("$18,853.50");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Other");
        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::Text("$0.00");
        ImGui::TableNextColumn();
        ImGui::Text("$5,853.50");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Salary");
        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::Text("$0.00");
        ImGui::TableNextColumn();
        ImGui::Text("$13,000.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("Expenses");
        ImGui::TableNextColumn();
        ImGui::TextColored(Green, "$226.67 of $460.00");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$578.32");
        ImGui::TableNextColumn();
        ImGui::Text("$4,532.67");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Bills");
        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$30.00");
        ImGui::TableNextColumn();
        ImGui::Text("$3,092.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Clothing");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$-40.48 of $100.00");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$140.48");
        ImGui::TableNextColumn();
        ImGui::Text("$949.48");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Groceries");
        ImGui::TableNextColumn();
        ImGui::TextColored(Green, "$74.15 of $160.00");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$85.85");
        ImGui::TableNextColumn();
        ImGui::Text("$155.20");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Leisure");
        ImGui::TableNextColumn();
        ImGui::TextColored(Green, "$193.00 of $200.00");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$7.00");
        ImGui::TableNextColumn();
        ImGui::Text("$21.00");
        ImGui::TableNextRow();
        ImGui::TableSetColumnIndex(0);
        ImGui::Text("|- Other");
        ImGui::TableNextColumn();
        ImGui::Text("-");
        ImGui::TableNextColumn();
        ImGui::TextColored(Red, "$314.99");
        ImGui::TableNextColumn();
        ImGui::Text("$314.99");
        ImGui::EndTable();
      }
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Expenses")) {
      ImGui::Text("Manga");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Incomes")) {
      ImGui::Text("My income is €100k (daily)");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Transfers")) {
      ImGui::Text("I transfered everything to the manga store");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Securities")) {
      ImGui::Text("NullPointerException");
      ImGui::EndTabItem();
    }
    if (ImGui::BeginTabItem("Schedule")) {
      ImGui::Text("Minha criatividade já se acabou");
      ImGui::EndTabItem();
    }
    ImGui::EndTabBar();
    ImGui::End();

    window.clear();
    window.draw(shape);
    ImGui::SFML::Render(window);
    window.display();
  }

  ImGui::SFML::Shutdown();

  return 0;
}
