/*
** EPITECH PROJECT, 2019
** IGraphicalLib.hpp
** File description:
** IGraphicalLib
*/

#ifndef Animation_HPP_
#define Animation_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <utility>

class Animation {
    public:
        Animation();
        ~Animation();
        const sf::IntRect &getMaxSize(void);
        const sf::IntRect &getViewSize(void);
        const std::pair<int, int> &getMove(void);
        void setMaxSize(const uint &up_max, const uint &down_max,const uint &left_max,const uint &right_max);
        void setViewSize(const uint &up_view, const uint &down_view,const uint &left_view,const uint &right_view);
        void moveViewSize(void);
        void setMove(const int &hortizontal_move, const int &vertical_move);
    
    protected:
    private:
        sf::IntRect totalSize;
        sf::IntRect actualView;
        std::pair<int, int> move;
};

#endif