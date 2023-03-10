/// KnobsLM - configurable pocket language model of 1M to 250B neurons.
/// Nikolay Valentinovich Repnitskiy - License: WTFPLv2+ (wtfpl.net)


/* Version 1.0.0   Uses 1 whole CPU core & up to 250GB RAM, 1MB by default. Runs
on droids & old laptops.  Turn the 3 knobs below and adjust Knobs to your needs.
 ______________________________________________________________________________
/                                                                              \
|                   Create text file Training_data and fill                    |
|                    it with any text of 9, 10, & 32 - 126.                    |
|                                                                              |
|              You may inject small amounts of new text anywhere               |
|               over time, or replace Training_data completely.                |
\______________________________________________________________________________/



* Generative character prediction model.  Output = standard 9, 10, and 32 - 126.
* Creates universal model by default.  This allows models of  unique training to
  merge with minimal  catastrophic forgetting (safe learn-sharing.)  For example
  if 5 of 9 models have some same value, that value is final in  "Merged_model".
* No GPU usage; use fast CPU+RAM. Intel NUC is the fastest CPU-RAM communicator.
* KnobsLM runs on just about any  low-spec  hardware because it's  CPU+RAM-only.
* Mitigate catastrophic forgetting:  rehearsal--as recommended in the box above.
* Training len : 1k characters.  Uses every contiguous 1k char in TD with reuse.
* Output len   : adjustable.  Currently: length_of_response_in_characters = 160.
* Max input len: 500 char from user (32-126.)
* Neuron count : 1M to 250B (smaller = faster, bigger = waste. Choose wisely.)
* Layer count  : 1k to 250M (divide model_size_to_train_and_chat_with by 1,000.)
* Neurons/layer: 1k
* Neuron values: 95
* Neuron's job : take hash of previous layer.
* Each neuron  : 1 of 95 different hash algorithms.
* Train method : training data  sub-components  are  withheld then expected. For
  example: trains on "Meow like a ca"  until that string is classified under "t"
  where "Meow like a cat"  is the full sentence of focus from the training data.
  Next string to train on is "Meow like a c"  until that's classified under "a".
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
	
	
	//                                                                                                                  |
	bool            start_with_same_model_as_others   = true; //DEFAULT = TRUE.             unique init if broken >     |
	//                                                                                                                  |
	long long       length_of_response_in_characters  = 160;  //DEFAULT = 160.
	//
	const long long model_size_to_train_and_chat_with = 1000000; //DEFAULT = 1M.
	//                                                     Set this to 1M - 250B
	//                                                     in multiples of 1M.
	
	
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
	
	cout << " \n\n"; //Because misalignment upon landscape mode on Android.
	
	cout << "\n(KnobsLM) - configurable pocket language model\n\n"
	
	     << "(1) Train\n"
	     << "(2) Chat\n"
	     << "(3) Clean training data\n"
	     << "(4) Merge multiple models\n\n"
	
	     << "Enter option: ";
	
	int user_option; cin >> user_option;
	ifstream in_stream;
	ofstream out_stream;
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Train_______________________________________________________/
	if(user_option == 1)
	{	//Checks if requested neuron count is out of bounds.
		if((model_size_to_train_and_chat_with <      1000000     )
		|| (model_size_to_train_and_chat_with > 250000000000     )
		|| (model_size_to_train_and_chat_with %      1000000 != 0))
		{	cout << "\nmodel_size_to_train_and_chat_with is out of bounds.";
			return 0;
		}
		
		//Creates file Model if not existent.
		bool existence_of_file_Model = true;
		in_stream.open("Model");
		if(in_stream.fail() == true) {existence_of_file_Model = false;}
		in_stream.close();
		
		if(existence_of_file_Model == false)
		{	out_stream.open("Model");
			
			if(start_with_same_model_as_others == true) {srand(     0 );} //Seed = predetermined.
			else                                        {srand(time(0));} //Seed = Unix time.
			
			for(int a = 0; a < model_size_to_train_and_chat_with; a++)
			{	int neuron = (rand() % 95);
				out_stream << char(neuron + 32);
			}
			out_stream.close();
		}
		
		//Checks if model size is between 1MB & 250BG, is a multiple of 1M, and is composed of 32 - 126.
		in_stream.open("Model");
		long long model_byte_counter = 0;
		char garbage_byte;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			
			if((garbage_byte < 32) || (garbage_byte > 126))
			{	cout << "\nModel corrupted. Remove it to get a"
				     << "\nnew one upon training, or replace it.";
				
				in_stream.close();
				return 0;
			}
			
			model_byte_counter++;
		}
		in_stream.close();
		
		if((model_byte_counter <      1000000     )
		|| (model_byte_counter > 250000000000     )
		|| (model_byte_counter %      1000000 != 0))
		{	cout << "\nModel is " << model_byte_counter << " Bytes,"
			     << "\nbut should be between 1M and 250B"
			     << "\ninclusive, and a multiple of 1M."
			     << "\nRemove it to get a new one upon"
			     << "\ntraining, or replace it.";
			
			return 0;
		}
		
		//Checks if requested model size is equal to detected size.
		if(model_size_to_train_and_chat_with != model_byte_counter)
		{	cout << "\nModel is " << (model_byte_counter / 1000000) << "MB, but model_size_to_train_and_chat_with"
			     << "\nis set to " << (model_size_to_train_and_chat_with / 1000000) << "MB. Set it to match your model size, or"
			     << "\nremove the model to get a new one upon training.";
			
			return 0;
		}
		
		//Checks if training data is missing.
		in_stream.open("Training_data");
		if(in_stream.fail() == true)
		{	cout << "\nMissing file \"Training_data\". Create it"
			     << "\nand fill it with any text that is the"
			     << "\n95 printable characters, tab, and \\n.";
			
			in_stream.close();
			return 0;
		}
		in_stream.close();
		
		//Checks if training data is at least 1,000 characters.
		in_stream.open("Training_data");
		long long training_data_byte_counter = 0;
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	in_stream.get(garbage_byte);
			training_data_byte_counter++;
		}
		in_stream.close();
		
		if(training_data_byte_counter < 1000) {cout << "\nTraining_data must be at least 1,000 characters."; return 0;}
		
		//Checks if Training_data is composed of 9, 10, 13, and 32 - 126.
		in_stream.open("Training_data");
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	if((garbage_byte <  32)
			|| (garbage_byte > 126))
			{	if((garbage_byte !=  9)
				&& (garbage_byte != 10)
				&& (garbage_byte != 13))
				{	cout << "\nTraining_data must be composed of 9, 10, and 32 - 126"
					     << "\n(that is tab, \\n, and the 95 printable characters.)"
					     << "\nUse option 3.";
					
					in_stream.close();
					return 0;
				}
			}
			
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		
		//Checks if Training_data contains \r. (Excluding \r because it can erase terminal output generated by Knobs.
		in_stream.open("Training_data");
		in_stream.get(garbage_byte);
		for(; in_stream.eof() == false;)
		{	if(garbage_byte == 13)
			{	cout << "\nTraining_data cannot contain \\r, the file is perfect otherwise."
				     << "\nUse option 3.";
				
				in_stream.close();
				return 0;
			}
			
			in_stream.get(garbage_byte);
		}
		in_stream.close();
		
		//Loads model.
		static unsigned char model[model_size_to_train_and_chat_with];
		in_stream.open("Model");
		for(long long a = 0; a < model_size_to_train_and_chat_with; a++)
		{	in_stream.get(garbage_byte);
			model[a] = (garbage_byte - 32);
		}
		in_stream.close();
		
		cout << "\nExit/continue at any time. Overwrites model periodically;\n"
		     << "it's safest to exit right after an update. Backup models.\n\n";
		
		
		
		
		
		//Loops until all training data is consumed. # of loops = (TD Bytes - 1,000) + 1.
		for(long long training_data_bytes_to_skip = 0;; training_data_bytes_to_skip++)
		{	//..........Loads segment_of_training_data[] with 1,000 training data items, skipping n Bytes.
			int segment_of_training_data[1000];
			in_stream.open("Training_data");
			for(long long a = 0; a < training_data_bytes_to_skip; a++) {in_stream.get(garbage_byte);}
			for(int a = 0; a < 1000; a++)
			{	in_stream.get(garbage_byte);
				segment_of_training_data[a] = (garbage_byte - 32);
			}
			in_stream.close();
			
			if(in_stream.eof() == true) {cout << "\n\nDone.\n\n\n"; return 0;}
			
			//..........Trains on 998 strings per 1,000-character TD segment.
			for(int a = 0; a < 998; a++)
			{	//..........major here
				
			}
		}
	}
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Chat________________________________________________________/
	else if(user_option == 2)
	{	//Easy, consider it done when option 1 is done.
	}
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Clean_______________________________________________________/
	else if(user_option == 3)
	{	//Easy, consider it done when option 1 is done.
	}
	
	
	
	
	
	//_____________________________________________________________________________________________________________________
	//________________________________________________________Merge_______________________________________________________/
	else if(user_option == 4)
	{	//Merging is essentially Knobs in deep sleep (inactivity-based loss,)
		//and a refresh with focus on what's important (activity-based gain.)
		//This is true because the 1st model is used as a reference priority.
		
		//n2s: cout: priority on 1st model if no majority found. 1st model is 1st in file sorted alpha# as usual, read from ls > a.txt.
	}
	
	else {cout << "\nInvalid option, program ended.\n"; return 0;}
}
