# ![R - TYPE](./Client/Assets/Sprites/MDtitle.png) ![an online shmup](./Client/Assets/Sprites/MDlogo.png)
## 1] Compilation Method
#
In the project directory, create a build directory:

* `mkdir build`<br/>
* `cd build`<br/>

Then build the project using:<br/> 
* `conan install .. --build=missing`<br/>
* `cmake .. -G "Unix Makefiles"`<br/>
* `make`<br/>
#
## 2] How to run the project
#
#### Binaries are located in **`CPP_rtype_2019/build/bin/`**
* First of all one __server__ need to be running to host the client's games.<br/>
-> to start the server launch **`r-type_server`** <br/>
* Then when a server is running launch a __client__. <br/>
-> to start a client launch **`r-type_client`** <br/>
You can put a **nickname** in parameter but it's optional. <br/>

#### `/!\` you don't need to launch a server for every client, only one is needed.

#
## 3] Code explanation
#
## ECS /> Entity.Component.System

The architectural pattern the project is based on, divided in 3 parts :

* ### Entity

<ul>

Entities are created with a factory and can contain various components. <br/>
To create an entity use the **`createEntity(`** **string** detailing the components values parsed **`)`** method. <br/>
To add a component to an entity use the **`addComponent(`** **int** id of the entity **`)`** method. <br/>

</ul>

* ### Component

<ul>

You can create components easily with a factory templated covering a lot of types. <br/>
Just precise the type your component is storing that way:

<ul>

**`ComponentTypeList<`** **type** **`>`**

<ul>  

\ If you want to **add** data in a Component use the **`addComponent(`** **int** id , **type** data **`)`** method. <br/>
\ If you want to **access** data at a specific **id** use the **`getComponent(`** **int** id **`)`** method. <br/>
\ If you want to get every **data** and **id** use the **`getComponentsMap()`** method. <br/>

</ul>
</ul>
</ul>

* ### System

<ul>

Every system contains a reference to **ComponentTypeList** given to them at their creation. <br/>
Only the **`update`** method is called for every system, parameters differ depending on what the system do. You can add a system just by calling his **`update`** method in the main loop<br/>

</ul>

#
For more details on **Components** or **Systems** see the UML [here](https://www.lucidchart.com/documents/view/5cf23102-bd80-4430-9778-7d86e3e00753/XIr7ItL8STTP?shared=true "UML ECS on Lucidchart").
#

## 4] How to continue the project

The following part will shortly explain how to continue developping the project.

* ### Creating a new Bydos monster


* ### Creating a totally different game

