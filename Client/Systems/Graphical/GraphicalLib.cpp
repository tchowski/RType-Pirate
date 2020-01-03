/*
** EPITECH PROJECT, 2019
** GraphicalLib.cpp
** File description:
** GraphicalLib
*/

#include "GraphicalLib.hpp"
#include <iostream>

Animation::Animation()
{
}

Animation::~Animation()
{
}

const sf::IntRect &Animation::getMaxSize(void)
{
    return totalSize;
}

const sf::IntRect &Animation::getViewSize(void)
{
    return actualView;
}

const std::pair<int, int> &Animation::getMove(void)
{
    return move;
}

void Animation::setMaxSize(const uint &up_max, const uint &down_max,const uint &left_max,const uint &right_max)
{
    totalSize = sf::IntRect (up_max, down_max, left_max, right_max);
}

void Animation::setViewSize(const uint &up_view, const uint &down_view,const uint &left_view,const uint &right_view)
{
    actualView = sf::IntRect (up_view, down_view, left_view, right_view);
}

void Animation::moveViewSize(void)
{
    actualView.left += move.first;
    actualView.top += move.second;
    if (actualView.left + actualView.width >
    totalSize.left + totalSize.width)
        actualView.left = totalSize.left;
    if (actualView.top + actualView.height >
    totalSize.top + totalSize.height)
        actualView.top = totalSize.top;
}

void Animation::setMove(const int &hortizontal_move, const int &vertical_move)
{
    move = std::pair<int, int>(hortizontal_move, vertical_move);
}

GraphicalLib::GraphicalLib()
{
    std::unordered_map<std::string, std::string> alias =
    {
    {"Empty", "Sprites/empty.png"},
    {"Placeholder", "Sprites/placeholder.png"},
    {"GameOver", "Sprites/GameOver.png"},
    {"LevelPassed1", "Sprites/LevelPassed.png"},
    {"LevelPassed2", "Sprites/LevelPassed2.png"},
    {"Credits", "Sprites/Credits.png"},
    {"BackgroundMenu", "Sprites/Menu/menuBck.png"},
    {"MonsterLeft", "Sprites/Menu/monsterMenuLeft.png"},
    {"MonsterRight", "Sprites/Menu/monsterMenuRight.png"},
    {"Underline", "Sprites/Menu/underline.png"},
    {"Title3", "Sprites/Menu/menuTitle3.png"},
    {"CatchPhrase", "Sprites/Menu/catchPhrase.png"},
    {"Play", "Sprites/Menu/play.png"},
    {"Bck_scroll", "Sprites/space_scroll.png"},
    {"P1", "Sprites/Login/p1.png"},
    {"P1P2", "Sprites/Login/p1p2.png"},
    {"P1P2P3", "Sprites/Login/p1p2p3.png"},
    {"P1P2P3P4", "Sprites/Login/p1p2p3p4.png"},
    {"P1P3P4", "Sprites/Login/p1p3p4.png"},
    {"P1P3", "Sprites/Login/p1p3.png"},
    {"P1P4", "Sprites/Login/p1p4.png"},
    {"P1P2P4", "Sprites/Login/p1p2p4.png"},
    {"Campaign", "Sprites/Login/campaign.png"},
    {"Survival", "Sprites/Login/survival.png"},    
    {"DestructibleWall", "Sprites/wall.png"},
    {"Wall", "Sprites/asteroid.png"},
    {"Player1_static", "Sprites/r-typesheet42.gif"},
    {"Player2_static", "Sprites/r-typesheet42.gif"},
    {"Player3_static", "Sprites/r-typesheet42.gif"},
    {"Player4_static", "Sprites/r-typesheet42.gif"},
    {"Player1_up", "Sprites/r-typesheet42.gif"},
    {"Player2_up", "Sprites/r-typesheet42.gif"},
    {"Player3_up", "Sprites/r-typesheet42.gif"},
    {"Player4_up", "Sprites/r-typesheet42.gif"},
    {"Player1_down", "Sprites/r-typesheet42.gif"},
    {"Player2_down", "Sprites/r-typesheet42.gif"},
    {"Player3_down", "Sprites/r-typesheet42.gif"},
    {"Player4_down", "Sprites/r-typesheet42.gif"},
    {"PlayerShot", "Sprites/r-typesheet1.gif"},
    {"Charge_attack", "Sprites/r-typesheet1.gif"},
    {"Missile", "Sprites/r-typesheet1.gif"},
    {"EnemyShot", "Sprites/r-typesheet2.gif"},
    {"EnemyBall", "Sprites/r-typesheet3.gif"},
    {"Enemy1", "Sprites/r-typesheet5.gif"},
    {"Enemy2", "Sprites/r-typesheet7.gif"},
    {"Enemy3", "Sprites/r-typesheet9.gif"},
    {"Enemy4", "Sprites/r-typesheet11.gif"},
    {"Enemy5", "Sprites/r-typesheet16.gif"},
    {"Enemy6", "Sprites/r-typesheet18.gif"},
    {"Enemy7", "Sprites/r-typesheet21.gif"},
    {"Boss1", "Sprites/r-typesheet28.gif"},
    {"Boss2", "Sprites/r-typesheet30.gif"},
    {"Boss3", "Sprites/r-typesheet37.gif"},
    {"Boss4", "Sprites/r-typesheet38.gif"},
    {"Boss5", "Sprites/r-typesheet44.gif"}
    };

    _alias = alias;
    _isKeyActive = {};
    _elementList = {};
    _textList = {};
    _spriteList = {};
    _textureList = {};
    current_dir = ".";
    createWindow();
}

GraphicalLib::~GraphicalLib()
{
}

void GraphicalLib::setPWD(const std::string &pwd)
{
    current_dir = pwd;
}

bool GraphicalLib::loadSprite(const std::string &name)
{
    sf::Texture texture;
    std::vector<std::string> path_dependencies = {"/../../Client/Assets/", "/../Client/Assets/", "/Client/Assets/"};
    bool load_success = false;

    if (_alias.find(name) == _alias.end())
        return false;
    if (_textureList.find(name) != _textureList.end())
        return false;
    if (_spriteList.find(name) != _spriteList.end())
        return false;
    for (auto dep : path_dependencies)
        if (texture.loadFromFile(current_dir + dep + _alias[name])) {
            load_success = true;
            break;
        }
    if (!load_success)
        if (name != "Placeholder") {
            loadSprite("Placeholder");
        }
    if (load_success) {
        if (!_textureList.insert({name, texture}).second)
            return false;
        sf::Sprite sprite(_textureList[name]);
        if (!_spriteList.insert({name, sprite}).second)
            return false;
    }
    
    return true;
}

bool GraphicalLib::unloadSprite(const std::string &name)
{
    if (!_spriteList.erase(name))
        return false;
    return true;
}

bool GraphicalLib::unloadAllSprites(void)
{
    _spriteList.clear();
    return true;
}

bool GraphicalLib::removeAllElements(void)
{
    _elementList.clear();
    return true;
}

bool GraphicalLib::addElementSprite(const uint &id, const std::string &sprite_name)
{
    Animation animation;
    std::unordered_map<std::string, std::vector<std::vector<int>>> rects = 
    {
    //                       {taille max}, {rect view}, {move}
    {"Bck_scroll",      {{0, 0,  3840, 1080},   {0, 0,  1920, 1080}, {1, 0}}},
    {"ChargeAttack",    {{0, 51,  166, 83},     {0, 51,  33, 83},    {33, 0}}},
    {"Player4_down",    {{0, 19,  33, 34},      {0, 19,  33, 15},    {0, 0}}},
    {"Player3_down",    {{0, 36,  33, 51},      {0, 36,  33, 15},    {0, 0}}},
    {"Player2_down",    {{0, 53,  33, 68},      {0, 53,  33, 15},    {0, 0}}},
    {"Player1_down",    {{0, 70,  33, 85},      {0, 70,  33, 15},    {0, 0}}},
    {"Player4_up",      {{132, 19,  165, 34},   {132, 19,  33, 15},  {0, 0}}},
    {"Player3_up",      {{132, 36,  165, 51},   {132, 36,  33, 15},  {0, 0}}},
    {"Player2_up",      {{132, 53,  165, 68},   {132, 53,  33, 15},  {0, 0}}},
    {"Player1_up",      {{132, 70,  165, 85},   {132, 70,  33, 15},  {0, 0}}},
    {"Player4_static",  {{66, 19,  99, 34},     {66, 19,  33, 15},   {0, 0}}},
    {"Player3_static",  {{66, 36,  99, 51},     {66, 36,  33, 15},   {0, 0}}},
    {"Player2_static",  {{66, 53,  99, 68},     {66, 53,  33, 15},   {0, 0}}},
    {"Player1_static",  {{66, 70,  99, 85},     {66, 70,  33, 15},   {0, 0}}},
    {"Charge_attack",  {{0, 51,  264, 32},     {0, 51,  33, 32},   {33, 0}}},
    {"Missile",  {{337, 255,  12, 4},     {337, 225,  12, 4},   {0, 0}}}
    };

    if (_elementList.find(id) == _elementList.end())
        return false;
    if (_spriteList.find(sprite_name) == _spriteList.end())
        return false;
    if (_elementList[id].spriteList.find(sprite_name) != _elementList[id].spriteList.end())
        return true;
    _elementList[id].spriteList.insert({sprite_name, _spriteList[sprite_name]});
    if (rects.find(sprite_name) == rects.end())
        return true;
    animation.setMaxSize(rects[sprite_name][0][0], rects[sprite_name][0][1], rects[sprite_name][0][2], rects[sprite_name][0][3]);
    animation.setViewSize(rects[sprite_name][1][0], rects[sprite_name][1][1], rects[sprite_name][1][2], rects[sprite_name][1][3]);
    animation.setMove(rects[sprite_name][2][0], rects[sprite_name][2][1]);
    addElementRect(id, sprite_name, animation);
    _elementList[id].spriteList[sprite_name].setTextureRect(_elementList[id].rectList[sprite_name].getViewSize());
    return true;
}

bool GraphicalLib::addElementRect(const uint &id, const std::string &rect_name, const Animation &animation)
{
    if (_elementList.find(id) == _elementList.end())
        return false;
    _elementList[id].rectList.insert({rect_name, animation});
    return true;
}

bool GraphicalLib::setElementSprite(const uint &id, const std::string &sprite_name, const std::string &rect_name, const int &nb)
{
    if (_elementList.find(id) == _elementList.end())
        return false;
    if (rect_name != "")
        _elementList[id].current_sprite_rect = std::pair<std::string, std::string>(sprite_name, rect_name);
    else {
        int index = 0;
        for (auto rect : _elementList[id].rectList) {
            if (index == nb) {
                _elementList[id].current_sprite_rect = std::pair<std::string, std::string>(sprite_name, rect.first);
            }
            index++;
        }
    }
    return true;
}

bool GraphicalLib::addElement(const uint &id, const std::pair<short int, short int> &position)
{
    Drawable element;

    element.position = position;
    element.id = id;
    if (_elementList.find(id) != _elementList.end())
        return false;
    if (!_elementList.insert({id, element}).second)
        return false;
    return true;
}

bool GraphicalLib::updateElement(const uint &id, const std::pair<short int, short int> &position)
{
    if (_elementList.find(id) == _elementList.end())
        return false;
    _elementList[id].position = position;
    return true;
}

bool GraphicalLib::removeElement(const uint &id)
{
    if (_elementList.find(id) == _elementList.end())
        return false;
    _elementList.erase(id);
    return true;
}

bool GraphicalLib::displayElements(void)
{
    sf::Time elapsed = clock.getElapsedTime();

    if (elapsed.asMilliseconds() > 10) {
        clock.restart();
        for (auto element : _elementList) {
            if (element.second.rectList.find(element.second.current_sprite_rect.second) != element.second.rectList.end()) {
                Animation rect = element.second.rectList.at(element.second.current_sprite_rect.second);
                rect.moveViewSize();
                _elementList.at(element.second.id).rectList.at(element.second.current_sprite_rect.second) = rect;
                if (element.second.spriteList.find(element.second.current_sprite_rect.first) != element.second.spriteList.end()) {
                    sf::Sprite sprite = element.second.spriteList.at(element.second.current_sprite_rect.first);
                    sprite.setTextureRect(rect.getViewSize());
                    _elementList.at(element.second.id).spriteList.at(element.second.current_sprite_rect.first) = sprite;
                }
            }
        }
    }
    if (!window.isOpen())
        return false;
    window.clear();
    for (auto element : _elementList) {        
        for (auto sprite : element.second.spriteList) {
            if (sprite.first == element.second.current_sprite_rect.first) {
                sprite.second.setPosition(element.second.position.first, element.second.position.second);
                window.draw(sprite.second);
            }
        }
    }
    window.display();
    return true;
}


bool GraphicalLib::createWindow(void)
{
    window.create(sf::VideoMode(1920, 1080, 60), "R-type_Client");
    return true;
}

bool GraphicalLib::isWindowOpen(void)
{
    return window.isOpen();
}


bool GraphicalLib::destroyWindow(void)
{
    window.close();
    return true;
}

State GraphicalLib::isKeyPressed(const UserAction &key)
{
    if (_isKeyActive.find(key) == _isKeyActive.end())
        return UNPRESSED;
    if (_isKeyActive[key] == UNCLICKED) {
        _isKeyActive[key] = UNPRESSED;
        return UNCLICKED;
    }
    if (_isKeyActive[key] == CLICKED) {
        _isKeyActive[key] = PRESSED;
        return CLICKED;
    }
    if (_isKeyActive[key] == PRESSED)
        return PRESSED;
    return UNPRESSED;
}

const UserAction GraphicalLib::getEvent(void)
{
    if (window.pollEvent(event)) {
        if (event.type == sf::Event::Closed)
            return UserAction::CLOSE;
    }
    if (event.type == sf::Event::KeyPressed)
        if (_isKeyActive.find((UserAction)event.key.code) == _isKeyActive.end())
            _isKeyActive.insert({(UserAction)event.key.code, CLICKED});
        else if (_isKeyActive[(UserAction)event.key.code] <= 0)
            _isKeyActive[(UserAction)event.key.code] = CLICKED;
    if (event.type == sf::Event::KeyReleased)
        if (_isKeyActive.find((UserAction)event.key.code) == _isKeyActive.end())
            _isKeyActive.insert({(UserAction)event.key.code, UNCLICKED});
        else if (_isKeyActive[(UserAction)event.key.code] >= 0)
            _isKeyActive[(UserAction)event.key.code] = UNCLICKED;
    if (event.type == sf::Event::Closed)
            return UserAction::CLOSE;
    return UserAction::UNKNOWN;
}

bool GraphicalLib::isAKeyPressed(void)
{
    if (event.type == sf::Event::KeyPressed)
        return true;
     if (window.pollEvent(event))
        if (event.type == sf::Event::KeyPressed)
            return true;
    return false;
}

void GraphicalLib::animate(void)
{
     sf::Time elapsed = clock.getElapsedTime();

    if (elapsed.asMilliseconds() > 10) {
        clock.restart();
        for (auto element : _elementList) {
            if (element.second.rectList.find(element.second.current_sprite_rect.second) != element.second.rectList.end()) {
                Animation rect = element.second.rectList[element.second.current_sprite_rect.second];
                rect.moveViewSize();
                _elementList[element.second.id].rectList[element.second.current_sprite_rect.second] = rect;
                if (element.second.spriteList.find(element.second.current_sprite_rect.first) != element.second.spriteList.end()) {
                    sf::Sprite sprite = element.second.spriteList[element.second.current_sprite_rect.first];
                    sprite.setTextureRect(rect.getViewSize());
                    _elementList[element.second.id].spriteList[element.second.current_sprite_rect.first] = sprite;
                }
            }
        }
    }
}

void GraphicalLib::drawSprite(const int &name)
{
    if (_elementList.find(name) == _elementList.end())
        return;
    auto element = _elementList[name];
    element.spriteList[element.current_sprite_rect.first].setPosition(element.position.first, element.position.second);
    window.draw(element.spriteList[element.current_sprite_rect.first]);
}

void GraphicalLib::display(void)
{
    window.display();
}

void GraphicalLib::clear(void)
{
    window.clear(sf::Color::Black);
}

void GraphicalLib::clearText()
{
    _textList.clear();
}

void GraphicalLib::drawText(void)
{
    for (auto text : _textList) {
        window.draw(text);
    }
}

void GraphicalLib::addText(const std::string &value, const std::pair<float, float> &pos, const std::string &font_name)
{
    std::vector<std::string> path_dependencies = {"/../../Client/Assets/", "/../Client/Assets/", "/Client/Assets/"};
    sf::Text text;
    sf::Font font;
    bool success_load = false;
    static std::unordered_map<std::string, sf::Font> fonts = {};

    if (fonts.find(font_name) == fonts.end()) {
        for (auto dep : path_dependencies) {
            if (font.loadFromFile(current_dir + dep + "Fonts/" + font_name + ".ttf")) {
                success_load = true;
                break;
            }
        }
        if (success_load)
            fonts.insert({font_name, font});
        else
            return;
    }
    text.setFont(fonts[font_name]);
    text.setPosition(sf::Vector2f(pos.first, pos.second));
    text.setFillColor(sf::Color::White);
    text.setCharacterSize(20);
    text.setString(value);
    _textList.push_back(text);
}
