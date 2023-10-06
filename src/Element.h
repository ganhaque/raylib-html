// Element.h
# pragma once
#include <raylib.h>
#include <string>
#include <limits.h>
#include <functional>
#include <vector>

class Element {
  public:
    std::string id;
    std::string className;

    int x = 0;
    int y = 0;
    int width = 0; // actual width
    int height = 0; // actual height
    int fixedWidth = 0;
    int fixedHeight = 0;
    int minWidth = 0;
    int minHeight = 0;
    int maxWidth = INT_MAX;

    Color bgColor = BLACK;
    Color onHoverBgColor;
    bool isOnHoverBgColorSet = false;
    Color fgColor = RAYWHITE;

    int fontSize = 20;
    std::string text;

    int margin[4] = {0}; // top, right, bottom, left
    int padding[4] = {0}; // top, right, bottom, left

    std::vector<Element*> children;
    // Element* parent;
    // Element* root;

    bool isFlex = true;
    int flexFactor = 0;
    int gap = 0;
    std::string flexDirection = "row";
    std::string alignItems = "center";

    // bool isSizeChanged = false;
    std::function<void()> onClick;

    bool isHover = false;

    Element(const std::string& text = "")
      : text(text) {

      }

    void draw() {
      isHover = CheckCollisionPointRec(
          GetMousePosition(),
          {
          static_cast<float>(x),
          static_cast<float>(y),
          static_cast<float>(width),
          static_cast<float>(height)
          });

      handleInput();

      if (isHover && isOnHoverBgColorSet) {
        DrawRectangle(x, y, width, height, onHoverBgColor);
      }
      else {
        DrawRectangle(x, y, width, height, bgColor);
      }

      int textX = x + padding[3] + (width - padding[1] - padding[3] - MeasureText(text.c_str(), fontSize)) / 2;
      int textY = y + padding[0] + (height - padding[0] - padding[2] - fontSize) / 2;


      if (!text.empty()) {
        DrawText(text.c_str(), textX, textY, fontSize, fgColor);
      }

      for (Element* child : children) {
        child->draw();
      }
    };

    void handleInput() {
      // Handle mouse click event
      if (isHover && IsMouseButtonPressed(MOUSE_LEFT_BUTTON) && onClick) {
        onClick();
      }
    }

    // void onSizeChange() {
    //   if (root) {
    //     root->calculateSize();
    //   }
    // }

    void setBackgroundColor(Color color) {
      bgColor = color;
    }
    void setForegroundColor(Color color) {
      fgColor = color;
    }
    void setOnHoverBgColor(Color color) {
      isOnHoverBgColorSet = true;
      onHoverBgColor = color;
    }

    void setPadding(int top, int right, int bottom, int left) {
      padding[0] = top;
      padding[1] = right;
      padding[2] = bottom;
      padding[3] = left;
    }

    void setMargin(int top, int right, int bottom, int left) {
      margin[0] = top;
      margin[1] = right;
      margin[2] = bottom;
      margin[3] = left;
    }

    void addChild(Element* child) {
      // child->parent = this;
      // child->root = this;
      children.push_back(child);
      calculateSize();
      alignItemsCenter();
    }

    void calculateSize() {
      int totalWidth = padding[1] + padding[3];
      int totalHeight = padding[0] + padding[2];

      if (text != "") {
        int textWidth = MeasureText(text.c_str(), fontSize);
        int textHeight = fontSize;
        totalWidth += textWidth;
        totalHeight += textHeight;
      }

      int maxChildWidth = 0;
      int maxChildHeight = 0;
      int currentX = padding[3];
      int currentY = padding[0];
      for (Element* child : children) {
        child->calculateSize();

        child->x = currentX + x;
        child->y = currentY + y;

        if (flexDirection == "row") {
          currentX += child->width + gap;
          maxChildWidth = std::max(maxChildWidth, child->width);
          totalHeight = std::max(totalHeight, currentY + child->height + padding[2]);
        }
        else if (flexDirection == "column") {
          currentY += child->height + gap;
          maxChildHeight = std::max(maxChildHeight, child->height);
          totalWidth = std::max(totalWidth, currentX + child->width + padding[3]);
        }
      }

      if (flexDirection == "row") {
        totalWidth = std::max(totalWidth, currentX - gap + padding[3]);
      }
      else if (flexDirection == "column") {
        totalHeight = std::max(totalHeight, currentY - gap + padding[2]);
      }


      if (!fixedWidth) {
        width = totalWidth;
      }
      if (!fixedHeight) {
        height = totalHeight;
      }
    }

    void alignItemsCenter() {
      if (flexDirection == "row") {
        int parentCenterY = y + height / 2;

        for (Element* child : children) {
          int childCenterY = child->y + child->height / 2;
          int yOffset = parentCenterY - childCenterY;
          child->y += yOffset;
        }
      }
      else if (flexDirection == "column") {
        int parentCenterX = x + width / 2;

        for (Element* child : children) {
          int childCenterX = child->x + child->width / 2;
          int xOffset = parentCenterX - childCenterX;
          child->x += xOffset;
        }
      }
    }
};
