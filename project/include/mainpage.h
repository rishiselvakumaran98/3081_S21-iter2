/*! \mainpage CSCI 3081 Delivery Simulation project
*
* 
*
* To generate documentation, first build the project with `make` in the `project` directory.
* Next, navigate to `project/docs` and run `doxygen Doxyfile`.


* \section Introduction
## Welcome to the CSCI 3081 Drone Simulation Project!

To build and run the project make sure to have the right environment.
*****************************
Some of the common environments to run the projects include Docker, Linux platforms, CSE Lab Machines or VOLE/VOLE 3D

First open up a Terminal and cd into the `repo-selva053` directory,
Then,

- Build the docker image

~~~~~~~~~~~~~~{.sh}   
    bin/build-env.sh
~~~~~~~~~~~~~~

- Run docker image

~~~~~~~~~~~~~~
    #Usage bin/run-env.sh <port - optional(default 8081)>
    bin/run-env.sh
~~~~~~~~~~~~~~
    
- Build project web server (inside docker image) NOTE: You won't be able to `cd` here yet because the project directory does not exist. If you were able to launch the above commands you should now be inside the docker image. You can exit it with CTRL+D now.

~~~~~~~~~~~~~~
    # Inside docker image
    cd /home/user/repo/project
    make
~~~~~~~~~~~~~~
    
- Run web server (inside docker image)

~~~~~~~~~~~~~~
    # MUST be within project/ directory inside docker image
    cd /home/user/repo/project
    ./bin/run.sh
~~~~~~~~~~~~~~
    
- Open up Firefox and browse to http://127.0.0.1:8081/


## Getting Started using SSH on CSE Lab machines

- Initial Setup of remote web server (full copy)

~~~~~~~~~~~~~~
    #Example: ./project/bin/setup-server.sh dtorban 05
    ./project/bin/setup-server.sh <username> <computer_number>
~~~~~~~~~~~~~~

- Run remote web server (only copies src directory)

~~~~~~~~~~~~~~
    #Example: ./project/bin/server.sh dtorban 05 8081
    ./project/bin/server.sh <username> <computer_number> <port>
~~~~~~~~~~~~~~

    
- Open up Firefox and browse to http://127.0.0.1:8081/

## Getting Started with VOLE-3D or VOLE

- Log on to [VOLE-3D or VOLE](https://vole.cse.umn.edu/) (VOLE is slower for graphics, but is great for tests, etc...)

- Build project

~~~~~~~~~~~~~~
    cd /path/to/cloned/repository
    cd project
    make
~~~~~~~~~~~~~~
    
 - Run project

~~~~~~~~~~~~~~
    # MUST be within project/ directory <scenes/<scene>.json - optional(default umn.json)>
    ./bin/run.sh
~~~~~~~~~~~~~~
    
 - Open up Firefox and browse to http://127.0.0.1:8081/ 



* \section routes_sec Designing and Implementing the different routes

  In the graphical simulation, we implemented different routes for the drone entity using the Strategy Pattern. 

  Classes:
    IStrategy: We defined a class named IStrategy that has two methods: a pure virtual method named GetPath and a void returning method named SetGraph. 
    Although the SetGraph() was previously defined elsewhere, we changed its location to within the IStrategy class because when we call on Smart Path, we already need to have a Graph object defined, so this change was necessary.

    Beeline: Initially, our challenge was that we were thinking of adding more points to the path to make the drone movement smoother. 
    However, this approach resulted in the observer for the simulation getting stuck due to large vector input values.
    We resolved this issue by designing a beeline path that includes only 4 subvectors: the drone's initial position, the drone's hovering position over the initial position, the drone's final destination, and the drone's hovering position over the final destination.
          
    Parabolic: Initially, the parabolic path was just an array of vectors that formed an arc over the initial and final destinations of the drone. 
    However, the issue we faced was that the drone was cutting through buildings in order to arrive at the package. 
    Since this drone behavior is incorrect, we fixed this issue by adding offset values in the drone's arrival position vector so that it would arrive in a smooth fashion.

  Methods: 
    GetPath() -> GetPath() is a pure virual method defined in the IStrategy abstract class is used by the strategy objects such as Parabolic, Beeline, and Smart Paths to implement in the GetPath() method 
    from the IStrategy class for generating 2D vectors of directions for the Drone to navigate around in the simulation.

    Beeline::GetPath() -> We overrode the GetPath method from IStrategy class. The y-coordinate of both the source and destination vectors are increased by 200 so that they float above the buildings. 
    Then, these two points are added to the path nested float vector. Once we are finished, we subtract 200 to the y-coordinate of the destination vector and add it to the path vector so that the drone lands to pick up the package or deliver to a customer. 

    Parabolic::GetPath() -> We overrode the GetPath() method from IStrategy class. We defined an array of vectors that formed an arc over the initial and final destinations of the drone, with offset values added to the drone's arrival position vector so that it would arrive in a smooth fashion.

  Resources: 
    Lecture 19 was a good resource for implementing the strategy pattern. Lecture 20 was also useful for the strategy pattern, and also provided some hints regarding the implementation of the parabolic path.
    Lab 14 was quite useful to implement the parabolic path as it gave intuitive equations as well as a clear indication of where and how to implement them in the parabolic path. 

* \subsection Strategy Pattern for the Drone Paths

  CONTEXT:
  In the strategy pattern, we create a context object which helps to represent strategies and whose behavior 
  varies as per its strategy objects that are being created. The strategy object uses the context object as a reference 
  while changing the executing algorithm. This phenomenon is possible as the drone acts as the context object in our project
  that would change the respective algorithms based on the context of the simultaion. In the project, defined an abstract class named IStrategy 
  that acts as the interface needed for Strategy objects to implement on. The IStrategy class consists of the pure abstract method 
  GetPath() that is used by the strategy objects such as Parabolic, Beeline, and Smart Paths to implement in the GetPath() method 
  from the IStrategy class for generating 2D vectors of directions for the Drone to navigate around in the simulation.
  In our implementation of IStrategy, we rely on composition instead of inheritance of objects for reusability and to have more flexibility to add paths in the future for the drone. 
  Instead of implementing a behavior, the Context delegates it to a Strategy. This delegation is necessary as the IStrategy class, in this case, would require changing behaviors 
  during runtime as the drone is initialized using the picojson object file which contains a "path" parameter specifying which 
  path the drone should take in the simulation. This way, the path is initialized in the drone dynamically during program execution.

  For designing the Drone path we had to implement on the Beeline and Parabolic path. The beeline path consists of 4 points, 

  ADVANTAGE:
  The strategy pattern consists of a family of algorithms that can be defined as a class hierarchy and can be used interchangeably to 
  alter application behavior without changing its architecture. By encapsulating the algorithm separately, new algorithms complying 
  with the same interface can be easily introduced. The application can switch strategies at run-time. Strategy enables the clients 
  to choose the required algorithm, without using a “switch” statement or a series of “if-else” statements. Data structures used for 
  implementing the algorithm are completely encapsulated in Strategy classes. Therefore, the implementation of an algorithm can be changed 
  without affecting the Context class.

  DISADVANTAGE:
  The application using the strategy pattern must be aware of all the strategies to select especially the right one for the right situation, 
  Which could lead to possible runtime bugs if the particular strategy is not defined for the right situation. To fix this issue, a default strategy 
  must be set which the entites could rely on when the particular strategies are not used. Context and the Strategy classes normally communicate 
  through the interface specified by the abstract Strategy base class, which doesnt provide flexibility for starategies 
  that might require different implementations. Strategy base class must expose interface for all the required behaviours, which some concrete 
  Strategy classes might not implement. In most cases, the application configures the Context with the required Strategy object. 
  Therefore, the application needs to create and maintain two objects in place of one.

    
 \subsection Observer Pattern for the Simulation
 
  The Observer Pattern is used to provide a one to many dependency between a specified subject 
  and any amount of observer objects. The aim of the observer pattern is for the subject to be able 
  to notify all observers about a change in state, so that the observers can then react to the state change 
  and execute their respective instructions.

 ADVANTAGE:
  The observer pattern is useful because it provides the ability for two objects to interact with each other 
  with the least amount of information about the other object that allows them to interact. Since the vast majority 
  of the information about the two communicating objects is withheld from each other, the developer is granted with the 
  power of changing object attributes in the middle of a simulation/program without the changes affecting the 
  communication between objects.

 DISADVANTAGE:
  A notable disadvantage of implementing the observer pattern is that it can cause memory leaks if not implemented carefully. 
  If one of the observers is deleted from memory without being unregistered from the subject, it becomes a dangling pointer. 
  Everytime the subject notifies the observers in the simulation, this unregistered observer will cause a segmentation fault.
  The observer pattern should, therefore, be used when a program contains multiple objects that are directly dependent on the 
  state of one object as it provides a neat and well tested design for the same.

  CONTEXT: 
  In our delivery simulation, we implemented the observer pattern for notifying the status of the Drone, Package and also the
  Robot Entities. We used the ISubject as the Interface to contain templates for the AddObserver, RemoveObserver and OnEvent
  methods that are used to notify the observer within the simulation on the status of the entities.
  
* \section team_sec Team Documentation
  New section created in mainpage.h containing teamwork documentation

  Hamza: Beeline path, Google Tests for Beeline Path and Parabolic Path, UML Diagram
    Implementing the beeline path was relatively straightforward, however, the google testing
    for the beeline and parabolic paths revealed some errors and fixing them, and making sure the
    testing provided accurate feedback and accounted for edge cases was the most time consuming aspect.
    I also modified the UML Diagram to match our individual variable name choices.
    Additionally, there were plenty of stylistic errors in the UML diagram, such as overlapping lines and
    incorrect directions for some arrows, as well as incorrect naming of various methods that I had to fix.

  Lucas: Parabolic path, Strategy Pattern, Observer Pattern
    Implementation of the Parabolic Path seemed fairly simple from the equations, however debugging the 
    equations and implementing them properly took about 1 hour. The hardest part about the parabolic path was defining the correct parameters, especially the doubles j and t.
    The offsets for the parabolic pattern was also an adjustment I had to make. 
    The Observer Pattern, on the other hand, led to a lot of segmentation faults in the simulation, primarily because of not unregistering observers
    before deleting them. 

  Rishi: Battery class, Delivery rescheduling, Drone movements related to battery, dropping package
  The Battery class was initially set to be 

  Shreyas: Multiple schedule relivery, Robot class, Robot movements related to battery
    Trying to locate the data structure and integrate the queue into the delivery simulation to 
    schedule packages to the empty drones and robots was a challenge, and took over 2 days. 
    The Robot class was a relatively straightforward implementation, but it was quite tedious and
    took a long time to finish up. I believe the Robot class took around 7 hours combined. 

  Team Member meetings:

  

*/


