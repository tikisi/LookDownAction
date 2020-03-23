#include "Title.h"

void Title::update() {
    if (SimpleGUI::ButtonAt(U"Start", Scene::Center() + Point::Down(50))) {
        this->changeScene(U"TestScene");
    }
    if (SimpleGUI::ButtonAt(U"Config", Scene::Center() + Point::Down(100))) {
        this->changeScene(U"Config");
    }
}

void Title::draw() const {
    //Font(50)(U"Title").drawAt(Scene::Center());
}