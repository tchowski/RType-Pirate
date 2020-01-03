/*
** EPITECH PROJECT, 2019
** rtype project
** File description:
** store all the components of te program. can also create component containers
*/

#include <unordered_map>
#include <iostream>
#include <memory>

#pragma once

template<typename T>
class ComponentTypeList {
	public:
		ComponentTypeList();
		~ComponentTypeList();

        void addComponent(const unsigned int id, const T& t);
        T &getComponent(const unsigned int id);
		bool setComponent(const unsigned int id, const T& component);
		bool deleteComponent(const unsigned int id);
        bool hasThisComponent(const unsigned int);
		std::unordered_map<unsigned int, T>& getComponentsMap() {return _allComponents;};

	private:
		std::unordered_map<unsigned int, T> _allComponents;
};