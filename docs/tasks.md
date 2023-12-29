## In order to develop your flight management system, you should meet the following important requirements, along with other functionalities you may find relevant.

Read and parse the provided data. This includes loading the airports, airlines and connections into
an appropriate graph data structure. You may create one or more graphs that allow for the
implementation of the required management system features. Note that for this project it is
mandatory to use the data structure provided for the practical classes to represent and CRUD
graphs (i.e., the Graph class).

Develop a flight management system. The system must incorporate a comprehensive set of
functionalities that provide a detailed view of the global connectivity of the air travel network, and
also ensure that users can make informed decisions when searching this network. Therefore, the
system must include all the functionalities specified for this project and any others deemed relevant.
It must also have a user-friendly menu, displaying the features you have implemented and their
corresponding outputs in a clear, organized, and logical manner.

Calculate and list statistics of the network, including existing airports and connections. The following statistics 
are mandatory:

1. [x] Global number of airports and number of available flights; 
2. [x] Number of flights out of an airport; and from how many different airlines; 
3. [x] Number of flights per city/airline; 
4. [x] Number of different countries that a given airport/city flies to; 
5. [x] Number of destinations (airports, cities or countries) available for a given airport; 
6. [ ] Number of reachable destinations (airports, cities or countries) from a given airport in a maximum number of X stops (lay-overs);
7. [ ] Maximum trip and corresponding pair of source-destination airports (or pairs, if more than one), that is, the flight trip(s) with the greatest number of stops in between them;
8. [x] Identify the top-k airport with the greatest air traffic capacity, that is, with the greatest number of flights;
9. [ ] Identify the airports that are essential to the network’s circulation capability (airports are essential if, when removed, areas of the network start to be unreachable). 

Present the best flight option (or the set of options if they are equivalent) for a given source and
   destination locations. The best flight option is considered to be the one with the least amount of stops.
   Locations may be specified by the user (inputs) using different criteria:
1. [X] Airport code or name;
2. [X] City name, encapsulating all the airports departing from a given city; 
3. [X] Geographical coordinates, considering the closest airport to the given coordinates. If there is
   more than one, consider all the closest ones.

The user may also wish to use combinations of these, that is, the system must allow the user to
   consider different criteria, for example, requesting a flight option from an airport to a city, or from a
   city to a location, or other possible combinations. If you wish to use distances in your program, make
   use of the Haversine Distance Function (Haversine Formula / implementation example). 
5. [ ] Search for the best flight option with filters (that is, using only a subset of nodes/edges of the
   network) that respect user preferences. Some users may wish to travel using only one or a set of given
   airlines. Other users may want to minimize the number of different airlines in their travel. The system
   must present the best flight option (or the set of options if they are equivalent) taking into
   consideration the choices of the user. 
6. [ ] Include documentation for the most relevant functions that you implemented, generated using
   Doxygen. Indicate the time complexity of the most relevant functions or algorithms in your program.
   
## Expected Results
   Your implementation should allow for storing and managing several different entities and their relationships,
   making use of an appropriate graph definition (based on the given Graph class) and the data structures that
   you consider relevant. In this sense, you should pay close attention to the following mandatory items:
   - Create and maintain an appropriate graph class to achieve the desired operations; 
   - Allow constant-time lookup for airlines, airports and cities; 
   - Mind the complexity of your algorithms so that the program does not take too long to compute any
   of the required operations; 
   - Include documentation of the implemented code (generated using Doxygen) and indicate the time
   complexity of the most relevant functions or algorithms of your program.
   Your program should also make use of important graph algorithms such as:
   - Breadth and depth-first search; 
   - Connected components; 
   - Articulation points; 
   - ...