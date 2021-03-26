/*! \mainpage CSCI 3081 Delivery Simulation project
*
* 
*
* To generate documentation, first build the project with `make` in the `project` directory.
* Next, navigate to `project/docs` and run `doxygen Doxyfile`.


* \section intro_sec Introduction
This simulation is a prototype of an automated system that has a drone picking up a package, following an specific route and dropping the package to the customer that ordered it.
The rout is gathered from the graph object that is provided by the facade, and feed to the update function in delivery_simulation.cc
In order to start the simulation, the user must have docker pre installed.
Assuming a correct installation of the docker system, the steps are as follow.
./bin/build-env.sh
from the root of the repox500 github repository.
After this step the simulation is built.
The second step is to start a docker environment, this could be achieved by going to the project folder and running
./bin/run-env.sh
then the user should make the project by using the prewritten makefile with the command (make -j)
and finally to run the simulation inside the project folder∂:
./bin/run.sh
as soon as the simulation starts, the user should go to the preferable browser and type the address:
http://127.0.0.1:8081/
which will show the simulation.
By selecting the different entities different actions are possible.
Selecting the drone, starts the process.
If the simulation runs correctly, the drone will fly to the package, pick it up and fly to the customer.
In order to run the simulation again the user should ctrl+c on the terminal to kill the simulation, and run 
./bin/run.sh again, then refreshing the browser will restart the process.

* \section factories_sec A brief discussion on the idea of factories.
The first important concept to be understood is when the use of a factory is an advantage over the traditional way of creating objects..
If we are dealing with a very simple code, or if every element of the code is concentrated in only one place, using a factory may not be a good idea.
It might be easier just to implement the creation of objects by the traditional way with constructors and if statements.
However, if the code is a little more complex, or if we are implementing a code with various types of objects that are created in multiple places, a factory can really make the programmer's life easier and the code more flexible for future upgrades and fixes.
Now let us understand a little more about the different types of factories that may be used in such a case.

  *\subsection concrete_factory_sec Concrete Factory
When we are dealing with code where the number of elements rarely varies, and their types are mostly fixed, using a concrete factory is a great design pattern.
In this case, the concrete factory would simply generate objects from a certain number of classes depending on their types. The concrete factory is faster and easier to implement for a number of elements that do not vary by a lot than the abstract factory that would be necessary here. Also, the concrete factory deals quite well with types that do not vary a lot, since it gets its types from classes that are passed directly from classes to its createEnttity method.
The issue with concrete factories rises when we need to deal with varying number of elements or types. Since the concrete factory createEntity function gets its types directly from the classes inherited by the concrete class, it does not have a lot of variability, making it a bad choice for dynamic codes and future upgrades.

\image html ./FactoryDiagramConcrete.PNG "Concrete Factory UML" width=600cm

*\subsection abstract_factory_sec Abstract Factory
The abstract factory is a great option for ever varying codes where the number of elements is unknown and the types may change throughout the programming process.
Its advantage is mostly due to the fact that it does reduce drastically the number of if statements that the programmer needs to type, therefore making it less probable that mistakes will be made and syntax errors generated. Also, abstract classes make it very easy for future upgrades  of the program. When compared with concrete factories, for example, they allow for huge flexibility, and when compared with the no factories implementation they allow for simple changes that will affect the entire code. This last advantage comes from the fact that abstract factories have an automatic handling of object creation by taking advantage of the concept of polymorphism of the pattern.
The only issues with abstract factories rises from the ideas that they could be unnecessary in cases that we don't have changing types and number of elements, were the concrete factory is easier to be implemented. Also, since they deal with polymorphism if there is an error in one of the upper factories it may reflect in other classes. making the code more difficult to debug.

\image html ./FactoryDiagramAbstract.png "Abstract Factory UML" width=700cm

* \subsection composite_factory_sec Composite Factory
The idea of composite factory rises from the concept of combining composite pattern with factories.
Composite pattern is the design pattern in which various objects are combined into smaller groups of objects, hence the composite name.
Composite factories are factories that are combined into groups and handled by a main factory.
In the case of this simulation, for example, we had the main composite factory being responsible to first add the drones, packages and customer factories.
Later those sub-factories would be the ones responsible for the creation of the entities of the simulation.
This makes it very easy to add new entities by simply adding an extra simple class that has a single createEntity function and adding that to the composite factory.
The composite factory serves as a middle layer as the sub-factories and the main interface factory that is hidden in the facade.
The disadvantages of the composite factories are similar to the abstract factory. It is not necessary in simple codes, and because the elements are grouped together it may be harder to debug.

\image html ./FactoryDiagramComposite.png "Composite Factory UML" width=800cm

* \subsection no_factory_sec No Factory
Even though factories are a great addition to a design programming pattern, in some cases as we have seen above they are unnecessary. For example, when the code is very short, or we are creating a very small number of objects all concentrated in a single place, the best option would be to go with the general idea of having constructors and if statements since factories would not make a lot of sense.
The issue happens when we want  to expand the code. Having no factories makes it really difficult to expand the number of entities or types to be created in an efficient manner, and so that is why factories are recommended in systems where the possibility of a large number of entities or types exist.

*/
