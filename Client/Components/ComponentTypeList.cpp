/*
** EPITECH PROJECT, 2019
** rtype
** File description:
** store a map of shared ptr on components, this class will be contained in the systems
*/

#include "ComponentTypeList.hpp"

template<typename T>
ComponentTypeList<T>::ComponentTypeList()
{
}

template<typename T>
ComponentTypeList<T>::~ComponentTypeList()
{
}

template<typename T>
void ComponentTypeList<T>::addComponent(const unsigned int id, const T& t)
{
    _allComponents.insert({id, t});
}

template<typename T>
T &ComponentTypeList<T>::getComponent(const unsigned int id)
{
    if (_allComponents.find(id) != _allComponents.end())
        return _allComponents[id];
    std::cerr << "ERROR: ";
    std::cerr << "The program will stop because you are trying to access to a component that doesn't exist.";
    std::cerr << std::endl << "Checkout ComponentTypeList.cpp -> getComponent" << std::endl;
    exit(84);
    return _allComponents[id];
}

template<typename T>
bool ComponentTypeList<T>::setComponent(const unsigned int id, const T& component)
{
    if (_allComponents.find(id) != _allComponents.end()) {
        _allComponents[id] = component;
        return false;
    }
    std::cerr << "WARNING: You tried to set a component that doesn't exist" << std::endl;
    std::cerr << "At ComponentTypeList.cpp -> setComponent" << std::endl;
    return true;
}

template<typename T>
bool ComponentTypeList<T>::deleteComponent(const unsigned int id)
{
    if (_allComponents.find(id) != _allComponents.end()) {
        _allComponents.erase(id);
        return false;
    }
    std::cerr << "WARNING: You tried to delete a component that doesn't exist" << std::endl;
    std::cerr << "At ComponentTypeList.cpp -> deleteComponent" << std::endl;
    return true;
}

template<typename T>
bool ComponentTypeList<T>::hasThisComponent(const unsigned int id)
{
    if (_allComponents.find(id) != _allComponents.end())
        return true;
    return false;
}

template class ComponentTypeList<std::string>;
template class ComponentTypeList<unsigned int>;
template class ComponentTypeList<short int>;
template class ComponentTypeList<std::pair<float, float>>;
template class ComponentTypeList<std::pair<unsigned int, unsigned int>>;
template class ComponentTypeList<std::pair<short, short>>;