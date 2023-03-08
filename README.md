<!--
Configurable pocket language model of 1-500MB running on droids &amp; old laptops.
-->



<p align="center">
  <img src="https://github.com/compromise-evident/KnobsLM/blob/main/Other/KnobsLM_icon_426070d3386f90447e77788c4987be1e7120baf23b8945ecb7296da979f6c5b4.png" width="205">
</p>

<p align="center">
  <img src="https://raw.githubusercontent.com/compromise-evident/KnobsLM/main/Other/KnobsLM_terminal.png">
</p>



<br>
<br>

# Where's the cpp?

Give me time to make 2 more decisions and it's done.
* Self-attention cycles
* Self-attention positions

<br>
<br>

# What to prepare for

```text

/// KnobsLM - configurable pocket language model of 1-500MB running on droids & old laptops.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/*  Version 1.0.0  Uses 1 CPU & 500MB RAM.  Auto-detects model size; share/swap.
 ______________________________________________________________________________
/                                                                              \
|                   Create text file Training_data and fill                    |
|                    it with any text. Now train & retrain.                    |
|                                                                              |
|              You may inject small amounts of new text anywhere               |
|               over time, or replace Training_data completely.                |
\______________________________________________________________________________/



* Generative character prediction model.  Output = standard 9, 10, 13, & 32-126.
* Creates unique model by default.  You may set  start_with_same_model_as_others
  to true so that models of unique training can merge for learn-sharing. For ex:
  if 2 of 3 models have some same value, that value is final in  "Merged_model".
* No GPU usage; use fast CPU+RAM. Intel NUC is the fastest CPU-RAM communicator.
* KnobsLM runs on just about any  low-spec  hardware because it's  CPU+RAM-only.
* Mitigate catastrophic forgetting:  rehearsal--as recommended in the box above.
* Training len : 1k characters.  Uses every contiguous 1k char in TD with reuse.
* Output len   : adjustable.  Currently: length_of_response_in_characters = 160.
* Max input len: 1k char from user (32-126.)
* Neuron count : 1M to 500M (smaller = faster, bigger = waste. Choose wisely.)
* Layer count  : 1k to 500k
* Neurons/layer: 1k
* Neuron values: 95
* Neuron's job : take hash of previous layer.
* Each neuron  : 1 of 95 different hash algorithms.
* Train method : training data  sub-components  are  withheld then expected. For
  example: trains on "Meow like a ca"  until that string is classified under "t"
  where "Meow like a cat"  is the full sentence of focus from the training data.
  Next string to train on is "Meow like a c"  until that's classified under "a".
* Self-attention cycles: ******************
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to run the program  -  Software package repositories for GNU+Linux operating
systems have all the tools you can imagine. Open a terminal and use this command
as root to install Geany and g++ on your computer: apt install geany g++   Geany
is a fast & lightweight text editor and Integrated Development Environment where
you can write and run code. g++ is the GNU compiler for C++ which allows written
code to run. The compiler operates in the background and displays errors in your
code as you will see in the lower Geany box. Make a new folder somewhere on your
machine. Paste this code into Geany. For clarity in auditing, enable indentation
guides: go to View >> Show Indentation Guides. Save the document as anything.cpp
within the newly-created folder. Use these shortcuts to run the program: F9, F5.
You may paste over this code with other  .cpp files, or open a new tab & repeat.
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~
How to make an executable with g++  -  Save this program as anything.cpp, open a
terminal, and type g++ then space. Drag & drop this saved file into the terminal
and its directory will be  appended to your pending entry. Click on the terminal
and press enter.   a.out now resides in the user directory, you may rename it to
anything.  To run that executable, simply drag and drop it into a terminal, then
click on the terminal and press enter.  Reminder:  executable's effect-directory
is /home/user or where you put the executable. Opening  .cpp  files in Geany and
hitting F9 creates the same executable--movable, renameable, drag & droppable.*/

#include <fstream>
#include <iostream>
using namespace std;

int main()
{	//                               user knobs
	
	/*\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\//////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\  /////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\    ////////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\      ///////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\        //////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\            ////////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\              ///////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\\\                  /////////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\\\\\                      ///////////////////////////
	\\\\\\\\\\\\\\\\\\\\\\\                              ///////////////////////
	\\\\\\\\\\\\\\\\\\                                        ////////////////*/
	
	//                                                                                                                     |
	bool start_with_same_model_as_others = false;     //DEFAULT = FALSE.                    universal init if broken >     |
	//                                                                                                                     |
	long long length_of_response_in_characters = 160; //DEFAULT = 160.
	
	int create_model_of_neuron_count_in_millions = 1; //DEFAULT = 1. (1 - 500.)
	
	
	/*////////////////                                          \\\\\\\\\\\\\\\\
	///////////////////////                              \\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////                      \\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////                  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////              \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////            \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////        \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	///////////////////////////////////      \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	////////////////////////////////////    \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	/////////////////////////////////////  \\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\
	//////////////////////////////////////\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\\*/

```
