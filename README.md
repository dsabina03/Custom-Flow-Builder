OOP 2023 Project
Vision
Our vision is to create an app that allows users to create custom flows for processes they use in their work.
Background
As companies go through the digitalization process, they need to move their process to apps that can help them automate and optimize their work. 

It is important for stakeholders to create flows needed for their own processes and be able to create new ones easily. 

At the same time it is important to see analytics about their processes to see how they can adapt them.

Companies like UiPath, IBM, Oracle have invested in tools to create processes.
Goal
Create a process builder that can help users make their own flows.
Types of steps
1.	TITLE step: title (string), subtitle (string)
2.	TEXT step: title (string), copy (string)
3.	TEXT INPUT step: description (string), text input (string)
4.	NUMBER INPUT step: description (string), number input (float)
5.	CALCULUS step: steps (integer), operation (string)
6.	DISPLAY steps: step (integer)
7.	TEXT FILE input step: description, file_name 
8.	CSV FILE input step: description, file_name
9.	OUTPUT step: step (integer), name of file (string), title (text), description (text)
10.	END step
User stories
1.	As a user, I want to build flows using existing predefined steps.
2.	As a user, I want to see what steps are available for me and a description of those steps.
3.	As a user, I want to be able to create new flows.
4.	As a user, when I create a flow, it will be a linear one, following all the steps I added.
5.	As a user, I can skip any step in a flow (skipping a screen will send me to the next step of the flow).
6.	As a user, I want to be able to add as many steps as I want for a flow.
7.	As a user, I can add any type of step as many times as I want into the flow.
8.	As a user, when I want to add a TITLE step, I need to add a title and a subtitle.
9.	As a user, when I want to add a TEXT step, I need to add a title and a copy (text).
10.	As a user, when I want to add a TEXT INPUT step, I need to add a description of the expected input.
11.	As a user, when I want to add a NUMBER INPUT step, I need to add description to the expected input.
12.	As a user, when I want to add a CALCULUS step, I need to be able to add previous NUMBER INPUT steps and operation symbols (e.g. step 3 + step 5).
13.	As a user, I want to be able to see the result of the CALCULUS step.
14.	As a system, I can perform the following operations for a CALCULUS step:
a.	Addition (+)
b.	Subtraction (-)
c.	Multiplication (*)
d.	Division (/)
e.	Minimum (min)
f.	Maximum (max)
15.	As a user, when I want to add a DISPLAY step, I will need to provide as an input a previous step that has information:
a.	TEXT INPUT
b.	CSV INPUT
16.	As a user, when I add a DISPLAY step, it will show me the content of the file.
17.	As a user, I want to add a TEXT FILE input step, that will allow me to add .txt files.
18.	As a user, I want to add a CSV FILE input step, that will allow me to add .csv files.
19.	As a user, I want to add an OUTPUT step that will generate a text file as an output.
20.	As a user, when I add an OUTPUT step I need to provide a name for the file that will be generated.
21.	As a user, when I add an OUTPUT step I need to provide a title for the file that will be generated.
22.	As a user, when I add an OUTPUT step I need to provide a description for the file that will be generated.
23.	As a user, when I add an OUTPUT step I can add information from the previous steps to be added in the file.
24.	As a user, when I want to signal the end of a flow, I need to be able to add an END step.
25.	As a user, when I don’t enter the right information in one of the steps I need to see an error screen with an error message.
26.	As a user, when I see an error screen I need to be able to either retry the step or go to the next one.
27.	As a user, I want to be able to add a name for each flow that I create.
28.	As a user, I want to see when each flow has been created (timestamp).
29.	As a user, I want to be able to run a flow that has been created.
30.	As a user, when I run a flow, I will need to be able to navigate to a next step by:
a.	Completing the action of the step and selecting next
b.	By skipping the step
31.	As a user, when I run the flow, I need to go through each of the steps that were added to that flow.
32.	As a user, I want to see analytics for each flow:
a.	How many times the flow has been started
b.	How many times the flow has been completed
c.	How many times each screen has been skipped
d.	Number of error screens displayed for each step
e.	Average number of errors per flow completed
33.	As a user, I can also delete flows from the system.

Requirements
1.	The project needs to be finalized by January 12th 23:59. An entry needs to be added to Moodle with a link to the Github repository.
2.	Access needs to be given to danielcdi (chisdanielioan@gmail.com) in order to access the repository.
3.	The repository needs to contain the following:
a.	Codebase
b.	Demo (video) going through the creation flow, running a flow and seeing analytics about the flows where you also explain what you are doing. Demo video must be of maximum 90 seconds.
c.	A testing matrix where you have at least 20 tests written that must be verified by the owner and confirmed that it works.
4.	In solving the homework, the following OOP concepts must be covered:
a.	Classes and objects
b.	Constructors and destructors
c.	Encapsulation
d.	Inheritance
e.	Polymorphism
f.	Abstractization
g.	Templates
h.	Exceptions

