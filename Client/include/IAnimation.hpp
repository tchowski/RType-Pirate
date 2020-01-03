/*
** EPITECH PROJECT, 2019
** IGraphicalLib.hpp
** File description:
** IGraphicalLib
*/

#ifndef IAnimation_HPP_
#define IAnimation_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <utility>

class IAnimation {
    public:
        virtual ~IAnimation() = default;

        virtual const sf::IntRect &getMaxSize(void) = 0;
        virtual const sf::IntRect &getViewSize(void) = 0;
        virtual const std::pair<int, int> &getMove(void) = 0;
        virtual void setMaxSize(const uint &up_max, const uint &down_max,const uint &left_max,const uint &right_max) = 0;
        virtual void setViewSize(const uint &up_view, const uint &down_view,const uint &left_view,const uint &right_view) = 0;
        virtual void moveViewSize(void);
        virtual void setMove(const int &vertical_move, const int &hortizontal_move) = 0;
    private:
    sf::IntRect totalSize;
    sf::IntRect actualView;
    std::pair<int, int> move;
};

#endif