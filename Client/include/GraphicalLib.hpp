/*
** EPITECH PROJECT, 2019
** GraphicalLib.hpp
** File description:
** GraphicalLib
*/

#ifndef GraphicalLib_HPP_
#define GraphicalLib_HPP_

#include "IGraphicalLib.hpp"

class GraphicalLib {
	public:
        GraphicalLib();
		~GraphicalLib();
        bool loadSprite(const std::string &name);
        bool unloadSprite(const std::string &name);
        bool unloadAllSprites(void);
        bool removeAllElements(void);
        bool addElement(const uint &id, const std::pair<short int, short int> &position);
        bool addElementSprite(const uint &id, const std::string &sprite_name);
        bool addElementRect(const uint &id, const std::string &rect_name, const Animation &anim);
        bool setElementSprite(const uint &id, const std::string &sprite_name, const std::string &rect_name = "", const int &nb = 0);
        bool updateElement(const uint &id, const std::pair<short int, short int> &position);
        bool removeElement(const uint &id);
        bool displayElements(void);
        bool createWindow(void);
        bool isWindowOpen(void);
        bool destroyWindow(void);
        const UserAction getEvent(void);
        State isKeyPressed(const UserAction &key);
        bool isAKeyPressed(void);
        void drawSprite(const int &id);
        void display(void);
        void clear(void);
        void setPWD(const std::string &);
        void addText(const std::string &value, const std::pair<float, float> &pos, const std::string &);
        void clearText(void);
        void drawText(void);
        void animate(void);

    protected:
    private:
        std::string current_dir;
        sf::RenderWindow window;
        sf::Event event;
        sf::Clock clock;
        std::unordered_map<UserAction, State> _isKeyActive;
        std::map<uint, Drawable> _elementList;
        std::vector<sf::Text> _textList;
        std::unordered_map<std::string, sf::Sprite> _spriteList;
        std::unordered_map<std::string, sf::Texture> _textureList;
        std::unordered_map<std::string, std::string> _alias;
};

#endif /* !GraphicalLib_HPP_ */
