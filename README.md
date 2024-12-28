# Ant-Farm-Stimulation-using-design-patterns
The Ant-Farm simulation in C++ uses design patterns to model the behavior of ants in a virtual environment. It applies patterns like the Strategy pattern to define ant movement algorithms, the Observer pattern for communication between ants, and the Factory pattern to create different types of ants, ensuring flexibility and scalability.
# Ant-Farm Simulation: C++ Design Patterns

This repository contains the code for a simulation of an ant farm, utilizing various design patterns to model the behavior of ants and their colonies. The design patterns used in this project include Singleton, Factory, Builder, and Decorator patterns to demonstrate the power of object-oriented principles.

## Features

- **Singleton Pattern**: Used in the `Habitat` class to ensure only one instance of the habitat exists and manage ant colonies and their resources.
- **Factory Pattern**: Insect types (Worker, Soldier, Monarch) are created using the `InsectFactory` class, which allows easy expansion by adding new insect types.
- **Builder Pattern**: Used to create customizable `AntNest` objects with different room counts and capacities.
- **Decorator Pattern**: The `InsectTraits` class allows dynamic addition of traits like agility and strength to insects, which can be applied on top of the basic insect traits.
- **Strategy Pattern**: Ant actions (like collecting resources, defending, and laying eggs) are determined by the type of insect.
- **Command-Line Interface**: Users can interact with the simulation by entering commands to create colonies, allocate resources, view colonies, and simulate insect actions in cycles.

## How It Works

1. **Habitat Class (Singleton)**: 
   - Manages a collection of ant colonies and their respective resources.
   - Ensures only one instance of the habitat exists, accessed via `getHabitatInstance()`.
   - Supports colony creation and resource allocation.

2. **AntNest Class (Builder)**: 
   - Allows the creation of an ant nest with customizable features, such as room count and resting capacity.
   
3. **Insect Class and Subclasses (Strategy)**: 
   - Defines base actions for different insect types (Worker, Soldier, Monarch).
   - The `InsectFactory` creates instances of these insect types based on user input.

4. **InsectTraits (Decorator)**: 
   - Adds dynamic traits (e.g., agility, strength) to insects using the decorator pattern, enhancing their abilities.

5. **SimulationCoordinator**:
   - Coordinates the execution of insect actions in randomized cycles, simulating realistic ant behaviors.
