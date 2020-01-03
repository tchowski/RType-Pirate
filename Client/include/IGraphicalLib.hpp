/*
** EPITECH PROJECT, 2019
** IGraphicalLib.hpp
** File description:
** IGraphicalLib
*/

#ifndef IGraphicalLib_HPP_
#define IGraphicalLib_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <utility>
#include <unordered_map>
#include "Animation.hpp"

enum State {
    UNPRESSED = -1,
    UNCLICKED = 0,
    CLICKED = 1,
    PRESSED = 2,
    TRUE,
    FALSE
};

enum UserAction {
    UNKNOWN = -1,
    A = 0,
    B = 1,
    C = 2,
    D = 3,
    E = 4,
    F = 5,
    G = 6,
    H = 7,
    I = 8,
    J = 9,
    K = 10,
    L = 11,
    M = 12,
    N = 13,
    O = 14,
    P = 15,
    Q = 16,
    R = 17,
    S = 18,
    T = 19,
    U = 20,
    V = 21,
    W = 22,
    X = 23,
    Y = 24,
    Z = 25,
    SPACE = 57,
    ESCAPE = 36,
    RETURN = 58,
    LEFT_CTRL = 37,
    RIGHT_CTRL = 38,
    LEFT_SHIFT = 42,
    RIGHT_SHIFT = 66,
    UP = 73,
    DOWN = 74,
    LEFT = 71,
    RIGHT = 72,
    CLOSE = -84,
    KEYPRESS = -42
};

struct Drawable {
    int id;
    std::pair<std::string, std::string> current_sprite_rect;
    std::unordered_map<std::string, Animation> rectList;
    std::unordered_map<std::string, sf::Sprite> spriteList;
    std::pair<int, int> position;
};

class IGraphicalLib {
	public:
		virtual ~IGraphicalLib() = default;
        virtual bool loadSprite(const std::string &name) = 0;
        virtual bool unloadSprite(const std::string &name) = 0;
        virtual bool unloadAllSprites(void) = 0;
        virtual bool removeAllElements(void) = 0;
        virtual bool addElement(const uint &id, const std::pair<short int, short int> &position) = 0;
        virtual bool addElementSprite(const uint &id, const std::string &sprite_name) = 0;
        virtual bool addElementRect(const uint &id, const std::string &rect_name, const Animation &anim) = 0;
        virtual bool setElementSprite(const uint &id, const std::string &sprite_name, const std::string &rect_name, const int &nb) = 0;
        virtual bool updateElement(const uint &id, const std::pair<short int, short int> &position) = 0;
        virtual bool removeElement(const uint &id) = 0;
        virtual bool displayElements(void) = 0;
        virtual bool createWindow(void) = 0;
        virtual bool isWindowOpen(void) = 0;
        virtual bool destroyWindow(void) = 0;
        virtual const UserAction getEvent(void) = 0;
        virtual bool isAKeyPressed(void) = 0;
        virtual State isKeyPressed(const UserAction &key) = 0;
        virtual void drawSprite(const int &id) = 0;
        virtual void display(void) = 0;
        virtual void clear(void) = 0;
        virtual void setPWD(const std::string &) = 0;
        virtual void addText(const std::string &value, const std::pair<float, float> &pos, const std::string &) = 0;
        virtual void clearText(void) = 0;
        virtual void drawText(void) = 0;
        virtual void animate(void) = 0;

    protected:
    private:
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        std::map<uint, Drawable> _elementList;
        std::unordered_map<UserAction, State> _isKeyActive;
        std::unordered_map<std::string, sf::Sprite> _spriteList;
        std::unordered_map<std::string, sf::Texture> _textureList;
        std::unordered_map<std::string, std::string> _alias;
};

#endif /* !IGraphicalLib_HPP_ */
