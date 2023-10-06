#include "Element.h"
#include "raylib.h"
#include <ctime>
#include <iostream>
#include <ostream>
#include <vector>

int main() {
  SetConfigFlags(FLAG_WINDOW_RESIZABLE | FLAG_VSYNC_HINT);
  const int screenWidth = 800;
  const int screenHeight = 600;
  InitWindow(screenWidth, screenHeight, "HTML-like Elements");
  // SetWindowMinSize(320, 200);
  SetTargetFPS(60);

  // Create a root element
  Element rootElement;
  // rootElement.fixedWidth = screenWidth;
  // rootElement.fixedHeight = screenHeight;
  rootElement.setBackgroundColor(BLACK);
  rootElement.setPadding(10, 10, 10, 10);
  rootElement.setMargin(10, 10, 10, 10);
  rootElement.flexDirection = "column";

  // Create child elements
  // Element header("Header");
  Element header;
  header.setBackgroundColor(SKYBLUE);
  // header.setPadding(10, 10, 10, 10);
  header.flexDirection = "row";

  Element headerChild("Header child");
  headerChild.setBackgroundColor(RED);
  headerChild.setPadding(10, 10, 10, 10);
  headerChild.setMargin(10, 10, 10, 10);
  header.addChild(&headerChild);
  Element headerChild2("Header child 2, which have smaller text size");
  headerChild2.fontSize = 10;
  headerChild2.setBackgroundColor(BLUE);
  headerChild2.setPadding(10, 10, 10, 10);
  header.addChild(&headerChild2);

  rootElement.addChild(&header);

  Element paragraph("This is a paragraph.");
  paragraph.setBackgroundColor(LIGHTGRAY);
  paragraph.setPadding(10, 10, 10, 10);
  paragraph.fgColor = BLACK;
  rootElement.addChild(&paragraph);
  //
  Element button("Click me!");
  button.setBackgroundColor(GRAY);
  button.setPadding(5, 10, 5, 10);
  button.setOnHoverBgColor(RED);
  button.onClick = []() {
    // Handle button click event
    std::cout << "clicked!" << std::endl;
  };
  rootElement.addChild(&button);


  while (!WindowShouldClose()) {
    BeginDrawing();
    ClearBackground(DARKGRAY);

    rootElement.draw();

    EndDrawing();
  }

  CloseWindow();
  return 0;
}

