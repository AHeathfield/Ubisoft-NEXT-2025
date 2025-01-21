// ECS.h
#pragma once

/*
 *	This is an Entity Component System.
 *	This organizes objects or behaviours in a flexible and efficient way
 *	Entity = identity, Component = data, System = behaviour
 *	It separates these into distinct parts making it easier to manage systems like games
 *
 *	This is very similar to what I have setup in my demo, but has many advantages:
 *	Less coupling and more organized are key advantages.
 *	Does this by separating parts into 3 distinct classes and the use of templates
 */

#include <iostream>
#include <vector>
#include <memory>
#include <algorithm>
#include <bitset>
#include <array>

class Component;
class Entity;
class Manager;

// Each component needs an ID (an alias for unsigned integer used to represent sizes and indices usually,)
// Size of the largest possible object in memory
using ComponentID = std::size_t;
using Group = std::size_t;

// inline puts this function code where ever we use it, this just makes sure all components made have a different ID
inline ComponentID getNewComponentTypeID()
{
	static ComponentID lastID = 0u;
	return lastID++;
}

// This is what actually gets called and will return the new components ID
template <typename T> inline ComponentID getComponentTypeID() noexcept	// noexcept makes function never throw any exceptions
{
	static ComponentID typeID = getNewComponentTypeID();
	return typeID;
}

constexpr std::size_t maxComponents = 32;						// Max number of components an entity can have
constexpr std::size_t maxGroups = 32;							// Max number of groups used for layering

// This is how we tell if an entity has a selection of components attached by comparing bitset to array
using ComponentBitSet = std::bitset<maxComponents>;				// An optimize array of boolean values
using GroupBitSet = std::bitset<maxGroups>;
using ComponentArray = std::array<Component*, maxComponents>;	// Array of component pointers

/*
 *	Component (data)
 */
class Component
{
public:
	Entity* entity;

	virtual void init() {}
	virtual void update() {}
	virtual void draw() {}

	virtual ~Component() {}
};


/*
 *	Entity (identity)
 */
class Entity
{
private:
	Manager& manager;
	bool active = true;
	std::vector<std::unique_ptr<Component>> components;

	ComponentArray componentArray;
	ComponentBitSet componentBitSet;
	GroupBitSet groupBitSet;			// Can find out which groups the entity is in

public:
	Entity(Manager& manager_) : manager(manager_) {}


	void update()
	{
		for (auto& c : components) c->update();
	}
	void draw()
	{
		for (auto& c : components) c->draw();
	}
	bool isActive() const { return active; }
	void destroy() { active = false; }


	bool hasGroup(Group group_)
	{
		return groupBitSet[group_];
	}


	void addGroup(Group group_);
	void delGroup(Group group_)
	{
		groupBitSet[group_] = false;	// This is because we no longer are going to be associated with that group
	}

	// This just checks if the entity has a component
	template <typename T> bool hasComponent() const
	{
		return componentBitSet[getComponentTypeID<T>()];
	}


	// This adds components to the entity (T is the type of Component being added)
	// Syntax notes: T& is an Lvalue reference, T&& is an Rvalue reference, TArgs... means it can take a number of arguements of diff types
	//		Ex: int a = 10; Lvalue = a, Rvalue = 10
	// std::forward creats perfect forwarding which ensures that arguements passed are forwarded exactly as they were received
	// This is important because it preserves the Lvalue and Rvalue
	template <typename T, typename... TArgs>
	T& addComponent(TArgs&&... mArgs)
	{

		T* c(new T(std::forward<TArgs>(mArgs)...));			// Creates component ptr
		c->entity = this;									// The entity field of this component is this entity
		std::unique_ptr<Component> uPtr{ c };				// Wraps ptr into smart ptr to ensure proper memory management
		components.emplace_back(std::move(uPtr));			// emplace construct the object in the container, more efficient

		componentArray[getComponentTypeID<T>()] = c;		// Lets say we add a position component, it will always be added to the same position in the array
		componentBitSet[getComponentTypeID<T>()] = true;	// Basically us activating the component added

		c->init();											// Gets references to other components
		return *c;
	}


	// This lets us get a specific component and allows us to work with the actual component
	// ex use: gameobject.getComponent<PositionComponent>().setXpos(25);
	template<typename T> T& getComponent() const
	{
		auto ptr(componentArray[getComponentTypeID<T>()]);
		return *static_cast<T*>(ptr);
	}
};




/*
 *	This class holds all the entities.
 *	Notice how entity holds components, and this holds entities
 */
class Manager
{
private:
	std::vector<std::unique_ptr<Entity>> entities;
	std::array<std::vector<Entity*>, maxGroups> groupedEntities;	// These are the groups of entities

public:
	void update()
	{
		for (auto& e : entities) e->update();
	}

	void draw()
	{
		for (auto& e : entities) e->draw();
	}

	// This removes entities if there not active
	void refresh()
	{
		// Looping through the groups
		for (auto i(0u); i < maxGroups; i++)
		{
			// This takes care of removing entities from group
			auto& vect(groupedEntities[i]);	// getting the vector array of entities
			vect.erase(
				std::remove_if(std::begin(vect), std::end(vect), [i](Entity* entity_)
					{
						return !entity_->isActive() || !entity_->hasGroup(i);
					}),
				std::end(vect));
		}

		entities.erase(std::remove_if(std::begin(entities), std::end(entities), [](const std::unique_ptr<Entity>& mEntity)
			{
				return !mEntity->isActive();
			}),
			std::end(entities));
	}


	void AddToGroup(Entity* entity_, Group group_)
	{
		groupedEntities[group_].emplace_back(entity_);	// Add entity to the group
	}


	std::vector<Entity*>& getGroup(Group group_)
	{
		return groupedEntities[group_];
	}

	Entity& addEntity()
	{
		// These 2 lines here are pretty much the same as the std::make_shared<type> but we can use unique now
		Entity* e = new Entity(*this);
		std::unique_ptr<Entity> uPtr{ e };

		entities.emplace_back(std::move(uPtr));		// std::move transfers the ownership (since it's unique) to the container
		return *e;
	}
};