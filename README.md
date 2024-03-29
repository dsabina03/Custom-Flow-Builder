# Flow Builder Project

### Description

The Flow Builder is a tool designed to help users create linear flows comprising various predefined steps. These steps offer to different types of interactions and operations, allowing users to create dynamic sequences of actions and decisions.

#### Available Steps

* Title Step: Add a title and subtitle to introduce sections.
* Text Step: Add a title and copy for displaying text.
* Text Input Step: Add a description for expected text input.
* Number Input Step: Add a description of the expected numerical input.
* Calculus Step: Add two previous numerical inputs (steps) to combine them using mathematical operations.
  > Supported operations:  Addition (+), Subtraction (-), Multiplication (*), Division (/), Minimum (min), Maximum (max).

* Display Step: Add a file name to show content from previous steps.
  > Supported files: Text Input, CSV Input.
  
* Text File Input Step: Import a ".txt" file for processing.
* CSV File Input Step: Import a ".csv" file for processing.
* Output Step: Generate a text file with the provided information.
  > Requires a name, title, and description for the generated file
* End Step: Marks the end of the flow.

### User Stories

#### Flow Building and Analytics

- Users:
  *  can build new linear flows using the predefined steps, viewing their descriptions.
  *  can run already created flows, progressing through all added steps.
  *  can skip and unlimitedly add any steps to a flow.
  *  can delete flows from the system.

- Users can navigate steps by completing actions or skipping.

### Overview

#### OOP Principles

Classes and objects represent the steps, flows, and analytics. Encapsulation limits access to implementation details, and inheritance helps with code reuse, enabling the extension of base step classes to create specialized types. Polymorphism promotes flexibility, treating diverse step types within flows, and abstractization provides templates for implementations to facilitate the creation of generic structures. Exception handling ensures system stability by managing runtime errors during a flow execution. 

#### Requirements

* C++ IDE
* Git

### Contributors
Despoiu Sabina - Project Developer

Chis Daniel/POLITEHNICA Bucuresti National University for Science and Technology - Coordonator
