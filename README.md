# Lem-in
Pathfinding algorithm, flow-chart management.

## Subject
[Lem-in subject](https://cdn.intra.42.fr/pdf/pdf/6161/lem-in.en.pdf)

## Goal

Find the shortest path to get **n** ants across a colony (comprised of rooms and tunnels). <br />
<br />

At the beginning of the game, all the ants are in the room **##start**. 
The goal is to bring them to the room **##end** with as few moves as possible. <br />

Each room can only contain one ant at a time (except at **##start** and **##end** which can contain as many ants as necessary). <br />

The shortest path isn't necessarily the simplest. <br />
Some maps will have many rooms and many links, but no path between **start** and **end**. <br />
Some maps will have rooms that link to themselves, sending your path-search spinning in circles. <br />
Some maps will have too many/too few ants, no start or end, duplicate rooms, links to unknown rooms, <br />
rooms with invalid coordinates, and a variety of other invalid or poorly-formatted input. <br />
Ants will also need to avoid traffic jams (walking all over their fellow ants). <br />

## The Project

Create the program ```lem-in```. <br />
```lem-in``` will read the map (describing the ants and the colony) from the ```sdtin```. 

Upon successfully finding the shortest path, ```lem-in``` will display the parsed input, and each ant's move from room to room. <br />

The program must handle errors carefully, or your program risks crashing violently. In no way can it quit <br />
in an unexpected manner (segmentation fault, bus error, double free, etc). It must not have any memory leaks. <br />

**Lem-in** must conform to the [42 Norm](https://cdn.intra.42.fr/pdf/pdf/960/norme.en.pdf). Using normal ```libc``` functions is strictly forbidden. <br /> 
Students are however, allowed to use: ```write```, ```read```, ```malloc```, ```free```, ```exit```. <br /> 
<br /> 

## Approach

The subject for ```lem-in``` is deliberately vague (like most projects at 42), so some error handling comes down to <br />
design choice.

The following macros can be modified in the ```lem_in.h``` header file:

- ```MAX_ANTS```: Ants are malloc'ed as structs, and having too many ants can slow the program down and cause <br />
poor performance.
- ```COMMENTS```: Input is broken by comments, which start with #. A comment that looks like: ```###comment##``` can be <br />
considered valid or invalid input, depending on the individual's interpretation of the subject. <br />
- ```LINK-SELF```: Rooms that link to back onto themselves may send your path-search spinning in circles, <br />
and can also be considered valid or invalid input. <br />
- ```NAME_SPACE```: A room is defined by ```name coord_x coord_y```, and will usually look like: ```Room 1 2``` <br />
(so a string, separated by 2 spaces). But what if a room name has a space inside it? Turning on this macro allows <br />
rooms to be formatted as ```Big Room 1 2```, ```Big Beautiful Room 1 2```, etc. <br />

<br />

Once you have overcome the initial challenge of parsing the input, how do you store all that information? And how do you <br />
find a path in a map that has 10,000 rooms?

I store all parsed data in structs. The ants, rooms, and links are each stored in linked lists. <br />

<br />

The rooms also contain connection and path next/prev structs, which are also stored in linked lists. <br />

<br />

I **implemented a hashtable** for more efficient room storage, which means I can almost instantaneously jump from ```Room 1``` to ```Room 9999```, if they are connected by a link (giving me the name of the room for the hashcode).  <br />

**The path-solving algorithm** I used Suurballe algorithm witch is a more strict requirement than Bhandari's algorithm that does allow two paths to use the same node. Completed with Belman-ford algorithm (shortest path finding algorithm) we could manage to have a really efficient path solving algorithm for a nodes and edges disjoint chart-flow problematic.

## Usage
Run ```make```.
```c
$>./lem-in < maps/test1.map
```

<br />
