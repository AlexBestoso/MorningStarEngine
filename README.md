# MorningStarEngine

run <code>make</code> from the terminal to compile the application. This will automatically run the application and create a binary called <code>msge</code>
This application requires the openGL c libraries to build. The exact commands for debian-based OS' will be added upon identifying all of the dependancies.

The Morning Star Engine is a graphical application created in OpenGL for the Linux Operating System. 

<b>December 11th 2022 Update</b>

The following changes have been made to the software:
<ul>
<li>Refactored the location of all the code files.</li>
<li>Upgraded the code infrastructure to allow for the use of shared objects/shared libraries.</li>
<li>Fixed minor bugs in all of the views and components.</li>
</ul>

<b>What's Coming Next?</b>
<p>
	Most of what's planned can be found in the devnotes document within this repository. The current goal is to create a class to allow me to create popups.
	Once this is built out, I'll be creating the ability to change the default color of the simulation window and save it to the file via right click action.
	Upon creation of the popup and save features, I'll be building out the engine compiler. Which will be used to convert the project into an independant 
	application. Where the simulation will be able to interact with the generated application via shared object importation.
</p>
